////////////////////서버★★


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <Windows.h>
#include <process.h>
#include <math.h>
#include <time.h>
#pragma warning(disable:4996)
#pragma comment(lib,"ws2_32.lib")  // 이걸써야 소켓 관련 함수를 참조할 수 있다.
#define BUF_SIZE 100
#define NAME_SIZE 20
#define MAX_CLNT 256

unsigned WINAPI HandleClient(void* arg);//쓰레드 함수
unsigned WINAPI HandleClient2(void* arg);//쓰레드 함수
void SendMsg(char* msg, int len);//메시지 보내는 함수
void SendMsg1(char* msg, int len);
void SendMsg2(char* msg, int len);
void ErrorHandling(char* msg);//에러 출력 함수

int clientCount = 0;
SOCKET clientSocks[MAX_CLNT];//클라이언트 소켓 보관용 배열
HANDLE hMutex;//뮤텍스

char player1[100]; // 플레이어의 닉네임을 넣을 변수
char player2[100];
int order = 1; //플레이어간 차례로 번갈아가면서 할 수 있게해주는 변수
int playerNum = 1; // 플레이어 수 저장하는 변수

int main() {
	WSADATA wsaData;  //윈도우 소켓 정보를 담을 구조체
	SOCKET serverSock, clientSock;
	SOCKADDR_IN serverAddr, clientAddr;
	int clientAddrSize;
	HANDLE hThread,hThread2;

	char port[100];

	printf("Input port number : ");
	gets_s(port,100);

	//MAKEWORD(2,2) 가 뜻하는 것은 WinSock 2.2Ver 요청하는 것이다.
	if (WSAStartup(MAKEWORD(2, 2), &wsaData) != 0) //윈도우 소켓을 사용하겠다는 사실을 운영체제에 전달
		ErrorHandling("WSAStartup() error!"); // 윈도우 소켓 초기화 안됐을 때 에러내용 출력

	hMutex = CreateMutex(NULL, FALSE, NULL);//하나의 뮤텍스를 생성한다.  (보안속성(보통NULL), 신호상태(TRUE면 바로 사용권한), 뮤텍스이름)
	serverSock = socket(PF_INET, SOCK_STREAM, 0); //하나의 소켓을 생성한다.

	memset(&serverAddr, 0, sizeof(serverAddr));  //배열이나 구조체 등의 메모리의 모든 내용을 0으로 할 때 사용하는 함수
	serverAddr.sin_family = AF_INET;
	serverAddr.sin_addr.s_addr = htonl(INADDR_ANY);
	serverAddr.sin_port = htons(atoi(port));

	//bind함수가 소켓에 주소를 부여하는 기능 수행한다.(서버소켓, 소켓에 부여할 주소정보를 포함한 구조체, 데이터길이)->IP주소와 PORT번호 할당 받음
	if (bind(serverSock, (SOCKADDR*)&serverAddr, sizeof(serverAddr)) == SOCKET_ERROR) //생성한 소켓을 배치한다. 반환 성공시 0, 실패시 SOCKET_ERROR반환
		ErrorHandling("bind() error");

	//listen함수, (서버 소켓, 대기큐의 개수(대개5)) ->연결요청대기중
	if (listen(serverSock, 5) == SOCKET_ERROR)//소켓을 준비상태에 둔다. 반환 성공시 0, 실패시 SOCKET_ERROR반환
		ErrorHandling("listen() error");

	printf("listening...\n");

	while (1) {
		clientAddrSize = sizeof(clientAddr);

		if (clientCount <= 2)  //서버에 접속할 수 있는 플레이어 2명으로 제한
		{
			//accept함수, ->클라이언트의 연결 수락 (반환 성공시 0, 실패시 SOCKET_ERROR반환)
			clientSock = accept(serverSock, (SOCKADDR*)&clientAddr, &clientAddrSize);//서버에게 전달된 클라이언트 소켓을 clientSock에 전달
			WaitForSingleObject(hMutex, INFINITE);//뮤텍스 실행
			clientSocks[clientCount++] = clientSock;//클라이언트 소켓배열에 방금 가져온 소켓 주소를 전달
			ReleaseMutex(hMutex);//뮤텍스 중지
			if (clientCount == 1)
			{
				hThread = (HANDLE)_beginthreadex(NULL, 0, HandleClient, (void*)&clientSock, 0, NULL);//HandleClient 쓰레드 실행, clientSock을 매개변수로 전달
			}
			else if (clientCount == 2)
			{
				hThread2 = (HANDLE)_beginthreadex(NULL, 0, HandleClient2, (void*)&clientSock, 0, NULL);//HandleClient 쓰레드 실행, clientSock을 매개변수로 전달
				clientCount++; //클라이언트 2명이 접속한 상태에서 추가의 클라이언트 접속을 막기위해 1을 추가시킨다
			}
			printf("Connected Client IP : %s\n", inet_ntoa(clientAddr.sin_addr));
		}
		else if (clientCount > 2) // 서버에 클라이언트가 2명이상 접속하려고 하면 이후의 접속자를 강제로 퇴장시킨다
		{
			clientSock = accept(serverSock, (SOCKADDR*)&clientAddr, &clientAddrSize);//서버에게 전달된 클라이언트 소켓을 clientSock에 전달
			WaitForSingleObject(hMutex, INFINITE);//뮤텍스 실행
			clientSocks[clientCount] = clientSock;//클라이언트 소켓배열에 방금 가져온 소켓 주소를 전달
			send(clientSocks[clientCount], "q", 2, 0);//클라이언트들에게 메시지를 전달한다.
			ReleaseMutex(hMutex);//뮤텍스 중지
		}
	}
	closesocket(serverSock);//생성한 소켓을 끈다.
	WSACleanup();//윈도우 소켓을 종료하겠다는 사실을 운영체제에 전달
	system("pause");
	return 0;
}

unsigned WINAPI HandleClient(void* arg) {    //void *arg는 char, int, double 모두를 받을 수 있는 사기적?인 포인터
	SOCKET clientSock = *((SOCKET*)arg); //매개변수로받은 클라이언트 소켓을 전달
	int strLen = 0, i;
	char msg[BUF_SIZE];
	char msg2[5];
	char *result=(char *)malloc(sizeof(char)*(BUF_SIZE+NAME_SIZE));
	char *result2 = (char *)malloc(sizeof(char)*(BUF_SIZE + NAME_SIZE));
	int num;
	int strLen2;

	send(clientSocks[0], "1", 2, 0);//클라이언트1에게 메시지를 전달한다.

	while ((strLen = recv(clientSock, msg, sizeof(msg), 0)) != 0) { //클라이언트로부터 메시지를 받을때까지 기다린다. 받은 바이트수를 반환한다.
		if (strLen > 3)
		{
			strcpy(result, msg);   //result=msg; 라고 해버리면 result가 msg의 주소값을 받아 변경시 msg의 내용까지 변해버리기 때문인다.
			result2 = strtok(result, " ");
			strLen2 = strlen(result2);     //[r] run\n  3  = 8-3-2
			result2 = strtok(NULL, "\n");
			printf("%s\n", result2);
			result2[strLen-strLen2 - 2] = '\0';  // result는 탈출(q판단)용이기 때문에 굳이 문자열의 맨 끝에 \0을 넣지 않아도된다. 만일 \0안넣으면 문자열 끝을 인식못해 오류
		}

		/*if (strLen == 1 && strcmp(msg, 'q'))
		{
			break;
		}*/
		srand((unsigned)time(NULL));   //rand함수 사용시 일정하지 않은 난수생성, seed값으로 현재시간 넣어줌

		if (strcmp(result2, "run")==0 && strLen!=1) {
			num = rand() % 6;    //0~5 사이의 난수 생성 후 num에 대입

			if (num == 0) //백도
			{
				SendMsg("backDo", 7);
			}
			else if (num == 1) //도
			{
				SendMsg("do", 3);
			}
			else if (num == 2) //개
			{
				SendMsg("gae", 4);
			}
			else if (num == 3) //걸
			{
				SendMsg("girl", 5);
			}
			else if (num == 4) //윷
			{
				SendMsg("yut", 4);
			}
			else if (num == 5) //모
			{
				SendMsg("mo", 3);
			}

			//말 번호 받음
			recv(clientSock, msg2, sizeof(msg2), 0);
			msg2[1] = '\0';
			if (strcmp(msg2, "1") == 0)
			{
				SendMsg(msg2, 2);
			}
			else if (strcmp(msg2, "2") == 0)
			{
				SendMsg(msg2, 2);
			}
			else if (strcmp(msg2, "3") == 0)
			{
				SendMsg(msg2, 2);
			}
			else if (strcmp(msg2, "4") == 0)
			{
				SendMsg(msg2, 2);
			}

			if (order % 2 == 0)
			{
				SendMsg1("1q2b6hpoe5d4z1", 15);
			}
			else if (order % 2 == 1)
			{
				SendMsg2("1q2b6hpoe5d4z1", 15);
			}
			order++;
		}
		else if (strcmp(result2, "surrender") == 0)
		{
			break;
		}
		else
		{
			SendMsg(msg, strLen);//SendMsg에 받은 메시지를 전달한다.
		}
	}

	SendMsg(msg, strLen);//SendMsg에 받은 메시지를 전달한다.
	printf("client left the chat\n");
	//이 줄을 실행한다는 것은 해당 클라이언트가 나갔다는 사실임 따라서 해당 클라이언트를 배열에서 제거해줘야함
	WaitForSingleObject(hMutex, INFINITE);//뮤텍스 실행
	for (i = 0; i<clientCount; i++) {//배열의 갯수만큼
		if (clientSock == clientSocks[i]) {//만약 현재 clientSock값이 배열의 값과 같다면
			while (i++<clientCount - 1)//클라이언트 개수 만큼
				clientSocks[i] = clientSocks[i + 1];//앞으로 땡긴다.
			break;
		}
	}
	clientCount--;//클라이언트 개수 하나 감소
	ReleaseMutex(hMutex);//뮤텍스 중지
	closesocket(clientSock);//소켓을 종료한다.
	return 0;
}

unsigned WINAPI HandleClient2(void* arg) {    //void *arg는 char, int, double 모두를 받을 수 있는 사기적?인 포인터
	SOCKET clientSock = *((SOCKET*)arg); //매개변수로받은 클라이언트 소켓을 전달
	int strLen = 0, i;
	char msg[BUF_SIZE];
	char msg2[2];
	char *result = (char *)malloc(sizeof(char)*(BUF_SIZE + NAME_SIZE));
	char *result2 = (char *)malloc(sizeof(char)*(BUF_SIZE + NAME_SIZE));
	int num;
	int strLen2;

    send(clientSocks[1], "2", 2, 0);//클라이언트2에게 메시지를 전달한다.
	//플레이어가 둘다 들어오면 게임 시작
	send(clientSocks[0], "1", 2, 0);

	while ((strLen = recv(clientSock, msg, sizeof(msg), 0)) != 0) { //클라이언트로부터 메시지를 받을때까지 기다린다. 받은 바이트수를 반환한다.
		if (strLen > 3)
		{
			strcpy(result, msg);   //result=msg; 라고 해버리면 result가 msg의 주소값을 받아 변경시 msg의 내용까지 변해버리기 때문인다.
			result2 = strtok(result, " ");
			strLen2 = strlen(result2);     //[r] run\n  3  = 8-3-2
			result2 = strtok(NULL, "\n");
			printf("%s\n", result2);
			result2[strLen - strLen2 - 2] = '\0';  // result는 탈출(q판단)용이기 때문에 굳이 문자열의 맨 끝에 \0을 넣지 않아도된다. 만일 \0안넣으면 문자열 끝을 인식못해 오류
		}

		/*if (strLen == 1 && strcmp(msg, 'q'))
		{
		break;
		}*/

		if (strcmp(result2, "run") == 0 && strLen != 1) {
			num = rand() % 6;    //0~5 사이의 난수 생성 후 num에 대입

			if (num == 0) //백도
			{
				SendMsg("backDo", 7);
			}
			else if (num == 1) //도
			{
				SendMsg("do", 3);
			}
			else if (num == 2) //개
			{
				SendMsg("gae", 4);
			}
			else if (num == 3) //걸
			{
				SendMsg("girl", 5);
			}
			else if (num == 4) //윷
			{
				SendMsg("yut", 4);
			}
			else if (num == 5) //모
			{
				SendMsg("mo", 3);
			}

			//말 번호 받음
			recv(clientSock, msg2, sizeof(msg2), 0);
			msg2[1] = '\0';
			if (strcmp(msg2, "1") == 0)
			{
				SendMsg(msg2, 2);
			}
			else if (strcmp(msg2, "2") == 0)
			{
				SendMsg(msg2, 2);
			}
			else if (strcmp(msg2, "3") == 0)
			{
				SendMsg(msg2, 2);
			}
			else if (strcmp(msg2, "4") == 0)
			{
				SendMsg(msg2, 2);
			}

			if (order % 2 == 0) //상대에게 차례를 넘겨줌
			{
				SendMsg1("1q2b6hpoe5d4z1", 15);
			}
			else if (order % 2 == 1)
			{
				SendMsg2("1q2b6hpoe5d4z1", 15);
			}
			order++;
		}
		else if (strcmp(result2, "surrender") == 0)
		{
			break;
		}
		else
		{
			SendMsg(msg, strLen);//SendMsg에 받은 메시지를 전달한다.
		}
	}

	SendMsg(msg, strLen);//SendMsg에 받은 메시지를 전달한다.
	printf("client left the chat\n");
	//이 줄을 실행한다는 것은 해당 클라이언트가 나갔다는 사실임 따라서 해당 클라이언트를 배열에서 제거해줘야함
	WaitForSingleObject(hMutex, INFINITE);//뮤텍스 실행
	for (i = 0; i<clientCount; i++) {//배열의 갯수만큼
		if (clientSock == clientSocks[i]) {//만약 현재 clientSock값이 배열의 값과 같다면
			while (i++<clientCount - 1)//클라이언트 개수 만큼
				clientSocks[i] = clientSocks[i + 1];//앞으로 땡긴다.
			break;
		}
	}
	clientCount--;//클라이언트 개수 하나 감소
	ReleaseMutex(hMutex);//뮤텍스 중지
	closesocket(clientSock);//소켓을 종료한다.
	return 0;
}

void ErrorHandling(char* msg) {
	fputs(msg, stderr);
	fputc('\n', stderr);
	exit(1);
}


//기존 센드메시지함수
void SendMsg(char* msg, int len) { //메시지를 모든 클라이언트에게 보낸다.
	int i;
	WaitForSingleObject(hMutex, INFINITE);//뮤텍스 실행
	for (i = 0; i < clientCount; i++)//클라이언트 개수만큼
	{
		send(clientSocks[i], msg, len, 0);//클라이언트들에게 메시지를 전달한다.
	}
	ReleaseMutex(hMutex);//뮤텍스 중지
}

void SendMsg1(char* msg, int len) { //메시지를 모든 클라이언트에게 보낸다.
	WaitForSingleObject(hMutex, INFINITE);//뮤텍스 실행
	send(clientSocks[0], msg, len, 0);//클라이언트들에게 메시지를 전달한다.
	ReleaseMutex(hMutex);//뮤텍스 중지
}

void SendMsg2(char* msg, int len) { //메시지를 모든 클라이언트에게 보낸다.
	WaitForSingleObject(hMutex, INFINITE);//뮤텍스 실행
	send(clientSocks[1], msg, len, 0);//클라이언트들에게 메시지를 전달한다.
	ReleaseMutex(hMutex);//뮤텍스 중지
}

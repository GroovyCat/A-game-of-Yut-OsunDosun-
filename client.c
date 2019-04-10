//클라이언트 ★★★

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <Windows.h>
#include <process.h>
#include "interface.h"
#include "linkedList.h"
#pragma warning(disable:4996)
#pragma comment(lib,"ws2_32.lib")  // 이걸써야 소켓 관련 함수를 참조할 수 있다.

#define BUF_SIZE 100
#define NAME_SIZE 20

unsigned WINAPI SendMsg(void* arg);//쓰레드 전송함수
unsigned WINAPI RecvMsg(void* arg);//쓰레드 수신함수
void ErrorHandling(char* msg);

char name[NAME_SIZE] = "[DEFAULT]";
char msg[BUF_SIZE];

int playerNum = 0; // 자신의 턴이면 1, 상대턴이면 0인 변수
int startNum = 0; // 1이 되어야 게임 시작

int clientPower = 0;//1되면 send스레드 종료되며 서버와의 연결을 끊는다

HANDLE hMutex;//뮤텍스

COORD chat1 = { 13, 31 }; //상대 채팅란
COORD chat2 = { 13, 33 }; //나의 채팅란
COORD input = { 13, 35 }; 
COORD input2 = { 28, 35 };

COORD info = { 0, 38 }; // 안내표시
COORD info2 = { 9, 38 };
COORD info3 = { 0,39 };

char *HorseNum; //지정한 자신의 말 번호 저장

int main() {
	WSADATA wsaData;
	SOCKET sock;
	SOCKADDR_IN serverAddr;
	HANDLE sendThread, recvThread;

	char myIp[100];
	char port[100];
	char inputName[100];
	int select;

	hMutex = CreateMutex(NULL, FALSE, NULL);//하나의 뮤텍스를 생성한다.  (보안속성(보통NULL), 신호상태(TRUE면 바로 사용권한), 뮤텍스이름)

	do // 2선택시 게임 시작
	{
		select = startMenu();
		system("cls");

		if (select == 6) // 게임 설명
		{
			explain();
		}
		else if (select == 10) // 게임 종료
		{
			return 0;
		}
	} while (select != 2);

	printf("Input server IP : ");
	gets(myIp);

	printf("Input server port : ");
	gets(port);

	printf("Input your name : ");
	gets(inputName);

	if (WSAStartup(MAKEWORD(2, 2), &wsaData) != 0)// 윈도우 소켓을 사용한다고 운영체제에 알림
		ErrorHandling("WSAStartup() error!");

	sprintf(name, "[%s]", inputName);    //name에 [inputName]을 저장시킨다.
	sock = socket(PF_INET, SOCK_STREAM, 0);//소켓을 하나 생성한다.

	memset(&serverAddr, 0, sizeof(serverAddr));
	serverAddr.sin_family = AF_INET;               //서버의 주소 체계
	serverAddr.sin_addr.s_addr = inet_addr(myIp);  //서버의 IP주소
	serverAddr.sin_port = htons(atoi(port));       //서버의 포트번호

												   //serverAddr의 서버 IP주소, 포트번호에 해당하는 서버에 접속한다.
	if (connect(sock, (SOCKADDR*)&serverAddr, sizeof(serverAddr)) == SOCKET_ERROR)
		ErrorHandling("connect() error");

	//접속에 성공하면 이 줄 아래가 실행된다.

	sendThread = (HANDLE)_beginthreadex(NULL, 0, SendMsg, (void*)&sock, 0, NULL);//메시지 전송용 쓰레드가 실행된다.
	recvThread = (HANDLE)_beginthreadex(NULL, 0, RecvMsg, (void*)&sock, 0, NULL);//메시지 수신용 쓰레드가 실행된다.

	WaitForSingleObject(sendThread, INFINITE);//전송용 쓰레드가 중지될때까지 기다린다./
	WaitForSingleObject(recvThread, INFINITE);//수신용 쓰레드가 중지될때까지 기다린다.

											  //클라이언트가 종료를 시도한다면 이줄 아래가 실행된다.
	closesocket(sock);//소켓을 종료한다.
	WSACleanup();//윈도우 소켓 사용중지를 운영체제에 알린다.
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), info3);
	printf("                                                                                       ");
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), info3);
	printf("프로그램을 종료합니다.\n");
	system("pause");
	return 0;
}

unsigned WINAPI SendMsg(void* arg) {//전송용 쓰레드함수
	SOCKET sock = *((SOCKET*)arg);//서버용 소켓을 전달한다.
	char nameMsg[NAME_SIZE + BUF_SIZE];
	int order = 0;
	char horseNum[5];
	char horseNumM[5];

	while (1) {//반복
		WaitForSingleObject(hMutex, INFINITE);//뮤텍스 실행

		if (playerNum == 0 && startNum == 1) //상대방 차례일 때 입력란 공백으로 처리
		{
			SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), input);
			printf("                                                                                                   ");
		}

		if (playerNum == 1 && startNum == 1) // playerNum이 1이 되어야만 입력 가능
		{
			SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), input);
			printf("                                                                                                   ");
			SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), input);
			printf(">>your turn : ");
			SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), input2);
			fgets(msg, BUF_SIZE, stdin);//입력을 받는다.
			SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), info2);
			printf("                                                                                    ");
			if (!strcmp(msg, "q\n")) {//q를 입력하면 종료한다.
				send(sock, "q", 1, 0);//nameMsg를 서버에게 전송한다.
				break;
			}
			else if (!strcmp(msg, "run\n")) //윷 던지기
			{
				sprintf(nameMsg, "%s %s", name, msg);//nameMsg에 메시지를 전달한다.
				send(sock, nameMsg, strlen(nameMsg), 0);//nameMsg를 서버에게 전송한다.

				ReleaseMutex(hMutex);//뮤텍스 중지
				WaitForSingleObject(hMutex, INFINITE);//뮤텍스 실행
				int confirm = 0;
				do
				{
					if (confirm > 0)
					{
						SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), info2);
						printf("잘못 입력했습니다. 다시입력해주세요.\n");
					}
					SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), input);
					printf("                                                                                                   ");
					SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), input);
					printf("말 번호를 선택해주세요. :");
					scanf("%s", horseNum);
					HorseNum = horseNum;
					confirm++;
				} while (strcmp(horseNum, "1") != 0 && strcmp(horseNum, "2") != 0 && strcmp(horseNum, "3") != 0 && strcmp(horseNum, "4") != 0);
				SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), info2);
				printf("                                                                                    ");

				send(sock, horseNum, strlen(horseNum), 0);//nameMsg를 서버에게 전송한다.


				ReleaseMutex(hMutex);//뮤텍스 중지
				WaitForSingleObject(hMutex, INFINITE);//뮤텍스 실행
				playerNum = 0;

				SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), input);
				printf("                                                                                                   ");


			}
			else //채팅
			{
				sprintf(nameMsg, "%s %s", name, msg);//nameMsg에 메시지를 전달한다.
				send(sock, nameMsg, strlen(nameMsg), 0);//nameMsg를 서버에게 전송한다.
			}
		}
		if (clientPower == 1) // 상대 항복시 이 클라이언트도 서버와의 연결을 끊기 위함
		{
			break;
		}
		ReleaseMutex(hMutex);//뮤텍스 중지
	}
	return 0;
}

unsigned WINAPI RecvMsg(void* arg) {
	SOCKET sock = *((SOCKET*)arg);//서버용 소켓을 전달한다.
	char nameMsg[NAME_SIZE + BUF_SIZE];
	char yutNum[2];
	char startMsg[2];
	int strLen;
	int strlen;
	int order = 0;
	char *result = (char *)malloc(sizeof(char)*(NAME_SIZE + BUF_SIZE));
	char *result2 = (char *)malloc(sizeof(char)*(NAME_SIZE + BUF_SIZE));

	recv(sock, nameMsg, NAME_SIZE + BUF_SIZE - 1, 0);

	if (!strcmp(nameMsg, "1")) {
		playerNum = 1;
		printf("상대를 기다립니다.\n");

		recv(sock, nameMsg, NAME_SIZE + BUF_SIZE - 1, 0);

		if (!strcmp(nameMsg, "1")) {
			WaitForSingleObject(hMutex, INFINITE);//뮤텍스 실행
			startNum = 1;
			yutBoard(); //윷놀이 판 호출
			Initiation(); //윷놀이 판 이중연결리스트
			yutPan();// 각 노드를 가리키는 말포인터가 있으면 그림표시

			SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), info);
			printf("<<안내>>");
			SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), info2);
			printf("게임을 시작합니다!!!\n");
			SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), info3);
			printf("도착한 내 말의 개수: %d     //      도착한 상대의 말 개수: %d", myCount, yourCount);
			ReleaseMutex(hMutex);//뮤텍스 중지
		}
	}
	else if (!strcmp(nameMsg, "2")) // 플레이어로 두번째 입장시
	{
		WaitForSingleObject(hMutex, INFINITE);//뮤텍스 실행
		printf("기다리는 상대가 있습니다!\n");
		startNum = 1;
		yutBoard(); //윷놀이 판 호출
		Initiation(); // 윷놀이 판 이중연결리스트
		yutPan();// 각 노드를 가리키는 말포인터가 있으면 그림표시
		SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), info);
		printf("<<안내>>");
		SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), info2);
		printf("게임을 시작합니다!!!\n");
		SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), info3);
		printf("도착한 내 말의 개수: %d     //      도착한 상대의 말 개수: %d", myCount, yourCount);
		ReleaseMutex(hMutex);//뮤텍스 중지
	}

	while (1) {//반복
		WaitForSingleObject(hMutex, INFINITE);//뮤텍스 실행
		strLen = recv(sock, nameMsg, NAME_SIZE + BUF_SIZE - 1, 0);//서버로부터 메시지를 수신한다.
		if (strLen == -1)
			return -1;
		nameMsg[strLen] = 0;//문자열의 끝을 알리기 위해 설정

		if (!strcmp(nameMsg, "1q2b6hpoe5d4z1")) {   //자신의 게임 차례임을 알려준다
			playerNum = 1;
		}
		else if (!strcmp(nameMsg, "q") && playerNum == 1) {
			SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), info2);
			printf("                                                                                                   ");
			SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), info2);
			printf("left the game\n");
			break;
		}
		else if (!strcmp(nameMsg, "q") && playerNum == 0) {
			SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), info2);
			printf("                                                                                                   ");
			SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), info2);
			printf("상대가 항복했습니다.\n");
			clientPower = 1;
			break;
		}
		else
		{
			if (playerNum == 0) // 상대가 보낸 메시지
			{
				if (!strcmp(nameMsg, "backDo") || !strcmp(nameMsg, "do") || !strcmp(nameMsg, "gae") || !strcmp(nameMsg, "girl") || !strcmp(nameMsg, "yut") || !strcmp(nameMsg, "mo"))
				{
					SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), info2);
					printf("                                                                                                   ");
					SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), info2);
					printf("나온 윷: ");
					fputs(nameMsg, stdout);//자신의 콘솔에 받은 메시지를 출력한다.
					ReleaseMutex(hMutex);//뮤텍스 중지
					WaitForSingleObject(hMutex, INFINITE);//뮤텍스 실행
					recv(sock, yutNum, 5, 0);
					if (!strcmp(yutNum, "1"))
					{
						p2_1 = moveHorse(p2_1, nameMsg);
					}
					else if (!strcmp(yutNum, "2"))
					{
						p2_2 = moveHorse(p2_2, nameMsg);
					}
					else if (!strcmp(yutNum, "3"))
					{
						p2_3 = moveHorse(p2_3, nameMsg);
					}
					else if (!strcmp(yutNum, "4"))
					{
						p2_4 = moveHorse(p2_4, nameMsg);
					}
					catchHorse(0);
					yutPan();
					yutShape(nameMsg);
					SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), info3);
					printf("도착한 내 말의 개수: %d     //      도착한 상대의 말 개수: %d", myCount, yourCount);

					if (yourCount == 4) //패배조건
					{
						SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), info2);
						printf("                                                                                            ");
						SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), info2);
						printf("※..게임에서 패배하셨습니다..※");
						clientPower = 1;
						system("pause");
						return 0;
					}

					ReleaseMutex(hMutex);//뮤텍스 중지
					WaitForSingleObject(hMutex, INFINITE);//뮤텍스 실행
					
				}

				SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), chat1);
				printf("                                                                                                   ");
				SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), chat1);
				fputs(nameMsg, stdout);//자신의 콘솔에 받은 메시지를 출력한다.
			}
			else // 내가 보낸 메시지
			{
				if (!strcmp(nameMsg, "backDo") || !strcmp(nameMsg, "do") || !strcmp(nameMsg, "gae") || !strcmp(nameMsg, "girl") || !strcmp(nameMsg, "yut") || !strcmp(nameMsg, "mo"))
				{
					SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), info2);
					printf("                                                                                                   ");
					SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), info2);
					printf("나온 윷: ");
					fputs(nameMsg, stdout);//자신의 콘솔에 받은 메시지를 출력한다.
					ReleaseMutex(hMutex);//뮤텍스 중지
					WaitForSingleObject(hMutex, INFINITE);//뮤텍스 실행
					recv(sock, yutNum, 5, 0);
					if (!strcmp(HorseNum, "1"))
					{
						p1_1 = moveHorse(p1_1, nameMsg);
					}
					else if (!strcmp(HorseNum, "2"))
					{
						p1_2 = moveHorse(p1_2, nameMsg);
					}
					else if (!strcmp(HorseNum, "3"))
					{
						p1_3 = moveHorse(p1_3, nameMsg);
					}
					else if (!strcmp(HorseNum, "4"))
					{
						p1_4 = moveHorse(p1_4, nameMsg);
					}
					catchHorse(1);
					yutPan();
					yutShape(nameMsg);
					SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), info3);
					printf("도착한 내 말의 개수: %d     //      도착한 상대의 말 개수: %d", myCount, yourCount);

					if (myCount == 4) //승리조건
					{
						SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), info2);
						printf("                                                                                             ");
						SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), info2);
						printf("※!!게임에서 승리하셨습니다!!※");
						clientPower = 1;
						system("pause");
						return 0;
					}

					ReleaseMutex(hMutex);//뮤텍스 중지
					WaitForSingleObject(hMutex, INFINITE);//뮤텍스 실행
					
				}

				SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), chat2);
				printf("                                                                                                   ");
				SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), chat2);
				fputs(nameMsg, stdout);//자신의 콘솔에 받은 메시지를 출력한다.
			}
		}

		ReleaseMutex(hMutex);//뮤텍스 중지
	}
	return 0;
}

void ErrorHandling(char* msg) {
	fputs(msg, stderr);
	fputc('\n', stderr);
	exit(1);
}
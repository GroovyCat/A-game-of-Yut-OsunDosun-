////////////////////�����ڡ�


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <Windows.h>
#include <process.h>
#include <math.h>
#include <time.h>
#pragma warning(disable:4996)
#pragma comment(lib,"ws2_32.lib")  // �̰ɽ�� ���� ���� �Լ��� ������ �� �ִ�.
#define BUF_SIZE 100
#define NAME_SIZE 20
#define MAX_CLNT 256

unsigned WINAPI HandleClient(void* arg);//������ �Լ�
unsigned WINAPI HandleClient2(void* arg);//������ �Լ�
void SendMsg(char* msg, int len);//�޽��� ������ �Լ�
void SendMsg1(char* msg, int len);
void SendMsg2(char* msg, int len);
void ErrorHandling(char* msg);//���� ��� �Լ�

int clientCount = 0;
SOCKET clientSocks[MAX_CLNT];//Ŭ���̾�Ʈ ���� ������ �迭
HANDLE hMutex;//���ؽ�

char player1[100]; // �÷��̾��� �г����� ���� ����
char player2[100];
int order = 1; //�÷��̾ ���ʷ� �����ư��鼭 �� �� �ְ����ִ� ����
int playerNum = 1; // �÷��̾� �� �����ϴ� ����

int main() {
	WSADATA wsaData;  //������ ���� ������ ���� ����ü
	SOCKET serverSock, clientSock;
	SOCKADDR_IN serverAddr, clientAddr;
	int clientAddrSize;
	HANDLE hThread,hThread2;

	char port[100];

	printf("Input port number : ");
	gets_s(port,100);

	//MAKEWORD(2,2) �� ���ϴ� ���� WinSock 2.2Ver ��û�ϴ� ���̴�.
	if (WSAStartup(MAKEWORD(2, 2), &wsaData) != 0) //������ ������ ����ϰڴٴ� ����� �ü���� ����
		ErrorHandling("WSAStartup() error!"); // ������ ���� �ʱ�ȭ �ȵ��� �� �������� ���

	hMutex = CreateMutex(NULL, FALSE, NULL);//�ϳ��� ���ؽ��� �����Ѵ�.  (���ȼӼ�(����NULL), ��ȣ����(TRUE�� �ٷ� ������), ���ؽ��̸�)
	serverSock = socket(PF_INET, SOCK_STREAM, 0); //�ϳ��� ������ �����Ѵ�.

	memset(&serverAddr, 0, sizeof(serverAddr));  //�迭�̳� ����ü ���� �޸��� ��� ������ 0���� �� �� ����ϴ� �Լ�
	serverAddr.sin_family = AF_INET;
	serverAddr.sin_addr.s_addr = htonl(INADDR_ANY);
	serverAddr.sin_port = htons(atoi(port));

	//bind�Լ��� ���Ͽ� �ּҸ� �ο��ϴ� ��� �����Ѵ�.(��������, ���Ͽ� �ο��� �ּ������� ������ ����ü, �����ͱ���)->IP�ּҿ� PORT��ȣ �Ҵ� ����
	if (bind(serverSock, (SOCKADDR*)&serverAddr, sizeof(serverAddr)) == SOCKET_ERROR) //������ ������ ��ġ�Ѵ�. ��ȯ ������ 0, ���н� SOCKET_ERROR��ȯ
		ErrorHandling("bind() error");

	//listen�Լ�, (���� ����, ���ť�� ����(�밳5)) ->�����û�����
	if (listen(serverSock, 5) == SOCKET_ERROR)//������ �غ���¿� �д�. ��ȯ ������ 0, ���н� SOCKET_ERROR��ȯ
		ErrorHandling("listen() error");

	printf("listening...\n");

	while (1) {
		clientAddrSize = sizeof(clientAddr);

		if (clientCount <= 2)  //������ ������ �� �ִ� �÷��̾� 2������ ����
		{
			//accept�Լ�, ->Ŭ���̾�Ʈ�� ���� ���� (��ȯ ������ 0, ���н� SOCKET_ERROR��ȯ)
			clientSock = accept(serverSock, (SOCKADDR*)&clientAddr, &clientAddrSize);//�������� ���޵� Ŭ���̾�Ʈ ������ clientSock�� ����
			WaitForSingleObject(hMutex, INFINITE);//���ؽ� ����
			clientSocks[clientCount++] = clientSock;//Ŭ���̾�Ʈ ���Ϲ迭�� ��� ������ ���� �ּҸ� ����
			ReleaseMutex(hMutex);//���ؽ� ����
			if (clientCount == 1)
			{
				hThread = (HANDLE)_beginthreadex(NULL, 0, HandleClient, (void*)&clientSock, 0, NULL);//HandleClient ������ ����, clientSock�� �Ű������� ����
			}
			else if (clientCount == 2)
			{
				hThread2 = (HANDLE)_beginthreadex(NULL, 0, HandleClient2, (void*)&clientSock, 0, NULL);//HandleClient ������ ����, clientSock�� �Ű������� ����
				clientCount++; //Ŭ���̾�Ʈ 2���� ������ ���¿��� �߰��� Ŭ���̾�Ʈ ������ �������� 1�� �߰���Ų��
			}
			printf("Connected Client IP : %s\n", inet_ntoa(clientAddr.sin_addr));
		}
		else if (clientCount > 2) // ������ Ŭ���̾�Ʈ�� 2���̻� �����Ϸ��� �ϸ� ������ �����ڸ� ������ �����Ų��
		{
			clientSock = accept(serverSock, (SOCKADDR*)&clientAddr, &clientAddrSize);//�������� ���޵� Ŭ���̾�Ʈ ������ clientSock�� ����
			WaitForSingleObject(hMutex, INFINITE);//���ؽ� ����
			clientSocks[clientCount] = clientSock;//Ŭ���̾�Ʈ ���Ϲ迭�� ��� ������ ���� �ּҸ� ����
			send(clientSocks[clientCount], "q", 2, 0);//Ŭ���̾�Ʈ�鿡�� �޽����� �����Ѵ�.
			ReleaseMutex(hMutex);//���ؽ� ����
		}
	}
	closesocket(serverSock);//������ ������ ����.
	WSACleanup();//������ ������ �����ϰڴٴ� ����� �ü���� ����
	system("pause");
	return 0;
}

unsigned WINAPI HandleClient(void* arg) {    //void *arg�� char, int, double ��θ� ���� �� �ִ� �����?�� ������
	SOCKET clientSock = *((SOCKET*)arg); //�Ű������ι��� Ŭ���̾�Ʈ ������ ����
	int strLen = 0, i;
	char msg[BUF_SIZE];
	char msg2[5];
	char *result=(char *)malloc(sizeof(char)*(BUF_SIZE+NAME_SIZE));
	char *result2 = (char *)malloc(sizeof(char)*(BUF_SIZE + NAME_SIZE));
	int num;
	int strLen2;

	send(clientSocks[0], "1", 2, 0);//Ŭ���̾�Ʈ1���� �޽����� �����Ѵ�.

	while ((strLen = recv(clientSock, msg, sizeof(msg), 0)) != 0) { //Ŭ���̾�Ʈ�κ��� �޽����� ���������� ��ٸ���. ���� ����Ʈ���� ��ȯ�Ѵ�.
		if (strLen > 3)
		{
			strcpy(result, msg);   //result=msg; ��� �ع����� result�� msg�� �ּҰ��� �޾� ����� msg�� ������� ���ع����� �����δ�.
			result2 = strtok(result, " ");
			strLen2 = strlen(result2);     //[r] run\n  3  = 8-3-2
			result2 = strtok(NULL, "\n");
			printf("%s\n", result2);
			result2[strLen-strLen2 - 2] = '\0';  // result�� Ż��(q�Ǵ�)���̱� ������ ���� ���ڿ��� �� ���� \0�� ���� �ʾƵ��ȴ�. ���� \0�ȳ����� ���ڿ� ���� �νĸ��� ����
		}

		/*if (strLen == 1 && strcmp(msg, 'q'))
		{
			break;
		}*/
		srand((unsigned)time(NULL));   //rand�Լ� ���� �������� ���� ��������, seed������ ����ð� �־���

		if (strcmp(result2, "run")==0 && strLen!=1) {
			num = rand() % 6;    //0~5 ������ ���� ���� �� num�� ����

			if (num == 0) //�鵵
			{
				SendMsg("backDo", 7);
			}
			else if (num == 1) //��
			{
				SendMsg("do", 3);
			}
			else if (num == 2) //��
			{
				SendMsg("gae", 4);
			}
			else if (num == 3) //��
			{
				SendMsg("girl", 5);
			}
			else if (num == 4) //��
			{
				SendMsg("yut", 4);
			}
			else if (num == 5) //��
			{
				SendMsg("mo", 3);
			}

			//�� ��ȣ ����
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
			SendMsg(msg, strLen);//SendMsg�� ���� �޽����� �����Ѵ�.
		}
	}

	SendMsg(msg, strLen);//SendMsg�� ���� �޽����� �����Ѵ�.
	printf("client left the chat\n");
	//�� ���� �����Ѵٴ� ���� �ش� Ŭ���̾�Ʈ�� �����ٴ� ����� ���� �ش� Ŭ���̾�Ʈ�� �迭���� �����������
	WaitForSingleObject(hMutex, INFINITE);//���ؽ� ����
	for (i = 0; i<clientCount; i++) {//�迭�� ������ŭ
		if (clientSock == clientSocks[i]) {//���� ���� clientSock���� �迭�� ���� ���ٸ�
			while (i++<clientCount - 1)//Ŭ���̾�Ʈ ���� ��ŭ
				clientSocks[i] = clientSocks[i + 1];//������ �����.
			break;
		}
	}
	clientCount--;//Ŭ���̾�Ʈ ���� �ϳ� ����
	ReleaseMutex(hMutex);//���ؽ� ����
	closesocket(clientSock);//������ �����Ѵ�.
	return 0;
}

unsigned WINAPI HandleClient2(void* arg) {    //void *arg�� char, int, double ��θ� ���� �� �ִ� �����?�� ������
	SOCKET clientSock = *((SOCKET*)arg); //�Ű������ι��� Ŭ���̾�Ʈ ������ ����
	int strLen = 0, i;
	char msg[BUF_SIZE];
	char msg2[2];
	char *result = (char *)malloc(sizeof(char)*(BUF_SIZE + NAME_SIZE));
	char *result2 = (char *)malloc(sizeof(char)*(BUF_SIZE + NAME_SIZE));
	int num;
	int strLen2;

    send(clientSocks[1], "2", 2, 0);//Ŭ���̾�Ʈ2���� �޽����� �����Ѵ�.
	//�÷��̾ �Ѵ� ������ ���� ����
	send(clientSocks[0], "1", 2, 0);

	while ((strLen = recv(clientSock, msg, sizeof(msg), 0)) != 0) { //Ŭ���̾�Ʈ�κ��� �޽����� ���������� ��ٸ���. ���� ����Ʈ���� ��ȯ�Ѵ�.
		if (strLen > 3)
		{
			strcpy(result, msg);   //result=msg; ��� �ع����� result�� msg�� �ּҰ��� �޾� ����� msg�� ������� ���ع����� �����δ�.
			result2 = strtok(result, " ");
			strLen2 = strlen(result2);     //[r] run\n  3  = 8-3-2
			result2 = strtok(NULL, "\n");
			printf("%s\n", result2);
			result2[strLen - strLen2 - 2] = '\0';  // result�� Ż��(q�Ǵ�)���̱� ������ ���� ���ڿ��� �� ���� \0�� ���� �ʾƵ��ȴ�. ���� \0�ȳ����� ���ڿ� ���� �νĸ��� ����
		}

		/*if (strLen == 1 && strcmp(msg, 'q'))
		{
		break;
		}*/

		if (strcmp(result2, "run") == 0 && strLen != 1) {
			num = rand() % 6;    //0~5 ������ ���� ���� �� num�� ����

			if (num == 0) //�鵵
			{
				SendMsg("backDo", 7);
			}
			else if (num == 1) //��
			{
				SendMsg("do", 3);
			}
			else if (num == 2) //��
			{
				SendMsg("gae", 4);
			}
			else if (num == 3) //��
			{
				SendMsg("girl", 5);
			}
			else if (num == 4) //��
			{
				SendMsg("yut", 4);
			}
			else if (num == 5) //��
			{
				SendMsg("mo", 3);
			}

			//�� ��ȣ ����
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

			if (order % 2 == 0) //��뿡�� ���ʸ� �Ѱ���
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
			SendMsg(msg, strLen);//SendMsg�� ���� �޽����� �����Ѵ�.
		}
	}

	SendMsg(msg, strLen);//SendMsg�� ���� �޽����� �����Ѵ�.
	printf("client left the chat\n");
	//�� ���� �����Ѵٴ� ���� �ش� Ŭ���̾�Ʈ�� �����ٴ� ����� ���� �ش� Ŭ���̾�Ʈ�� �迭���� �����������
	WaitForSingleObject(hMutex, INFINITE);//���ؽ� ����
	for (i = 0; i<clientCount; i++) {//�迭�� ������ŭ
		if (clientSock == clientSocks[i]) {//���� ���� clientSock���� �迭�� ���� ���ٸ�
			while (i++<clientCount - 1)//Ŭ���̾�Ʈ ���� ��ŭ
				clientSocks[i] = clientSocks[i + 1];//������ �����.
			break;
		}
	}
	clientCount--;//Ŭ���̾�Ʈ ���� �ϳ� ����
	ReleaseMutex(hMutex);//���ؽ� ����
	closesocket(clientSock);//������ �����Ѵ�.
	return 0;
}

void ErrorHandling(char* msg) {
	fputs(msg, stderr);
	fputc('\n', stderr);
	exit(1);
}


//���� ����޽����Լ�
void SendMsg(char* msg, int len) { //�޽����� ��� Ŭ���̾�Ʈ���� ������.
	int i;
	WaitForSingleObject(hMutex, INFINITE);//���ؽ� ����
	for (i = 0; i < clientCount; i++)//Ŭ���̾�Ʈ ������ŭ
	{
		send(clientSocks[i], msg, len, 0);//Ŭ���̾�Ʈ�鿡�� �޽����� �����Ѵ�.
	}
	ReleaseMutex(hMutex);//���ؽ� ����
}

void SendMsg1(char* msg, int len) { //�޽����� ��� Ŭ���̾�Ʈ���� ������.
	WaitForSingleObject(hMutex, INFINITE);//���ؽ� ����
	send(clientSocks[0], msg, len, 0);//Ŭ���̾�Ʈ�鿡�� �޽����� �����Ѵ�.
	ReleaseMutex(hMutex);//���ؽ� ����
}

void SendMsg2(char* msg, int len) { //�޽����� ��� Ŭ���̾�Ʈ���� ������.
	WaitForSingleObject(hMutex, INFINITE);//���ؽ� ����
	send(clientSocks[1], msg, len, 0);//Ŭ���̾�Ʈ�鿡�� �޽����� �����Ѵ�.
	ReleaseMutex(hMutex);//���ؽ� ����
}

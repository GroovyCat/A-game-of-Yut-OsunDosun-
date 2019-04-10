//Ŭ���̾�Ʈ �ڡڡ�

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <Windows.h>
#include <process.h>
#include "interface.h"
#include "linkedList.h"
#pragma warning(disable:4996)
#pragma comment(lib,"ws2_32.lib")  // �̰ɽ�� ���� ���� �Լ��� ������ �� �ִ�.

#define BUF_SIZE 100
#define NAME_SIZE 20

unsigned WINAPI SendMsg(void* arg);//������ �����Լ�
unsigned WINAPI RecvMsg(void* arg);//������ �����Լ�
void ErrorHandling(char* msg);

char name[NAME_SIZE] = "[DEFAULT]";
char msg[BUF_SIZE];

int playerNum = 0; // �ڽ��� ���̸� 1, ������̸� 0�� ����
int startNum = 0; // 1�� �Ǿ�� ���� ����

int clientPower = 0;//1�Ǹ� send������ ����Ǹ� �������� ������ ���´�

HANDLE hMutex;//���ؽ�

COORD chat1 = { 13, 31 }; //��� ä�ö�
COORD chat2 = { 13, 33 }; //���� ä�ö�
COORD input = { 13, 35 }; 
COORD input2 = { 28, 35 };

COORD info = { 0, 38 }; // �ȳ�ǥ��
COORD info2 = { 9, 38 };
COORD info3 = { 0,39 };

char *HorseNum; //������ �ڽ��� �� ��ȣ ����

int main() {
	WSADATA wsaData;
	SOCKET sock;
	SOCKADDR_IN serverAddr;
	HANDLE sendThread, recvThread;

	char myIp[100];
	char port[100];
	char inputName[100];
	int select;

	hMutex = CreateMutex(NULL, FALSE, NULL);//�ϳ��� ���ؽ��� �����Ѵ�.  (���ȼӼ�(����NULL), ��ȣ����(TRUE�� �ٷ� ������), ���ؽ��̸�)

	do // 2���ý� ���� ����
	{
		select = startMenu();
		system("cls");

		if (select == 6) // ���� ����
		{
			explain();
		}
		else if (select == 10) // ���� ����
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

	if (WSAStartup(MAKEWORD(2, 2), &wsaData) != 0)// ������ ������ ����Ѵٰ� �ü���� �˸�
		ErrorHandling("WSAStartup() error!");

	sprintf(name, "[%s]", inputName);    //name�� [inputName]�� �����Ų��.
	sock = socket(PF_INET, SOCK_STREAM, 0);//������ �ϳ� �����Ѵ�.

	memset(&serverAddr, 0, sizeof(serverAddr));
	serverAddr.sin_family = AF_INET;               //������ �ּ� ü��
	serverAddr.sin_addr.s_addr = inet_addr(myIp);  //������ IP�ּ�
	serverAddr.sin_port = htons(atoi(port));       //������ ��Ʈ��ȣ

												   //serverAddr�� ���� IP�ּ�, ��Ʈ��ȣ�� �ش��ϴ� ������ �����Ѵ�.
	if (connect(sock, (SOCKADDR*)&serverAddr, sizeof(serverAddr)) == SOCKET_ERROR)
		ErrorHandling("connect() error");

	//���ӿ� �����ϸ� �� �� �Ʒ��� ����ȴ�.

	sendThread = (HANDLE)_beginthreadex(NULL, 0, SendMsg, (void*)&sock, 0, NULL);//�޽��� ���ۿ� �����尡 ����ȴ�.
	recvThread = (HANDLE)_beginthreadex(NULL, 0, RecvMsg, (void*)&sock, 0, NULL);//�޽��� ���ſ� �����尡 ����ȴ�.

	WaitForSingleObject(sendThread, INFINITE);//���ۿ� �����尡 �����ɶ����� ��ٸ���./
	WaitForSingleObject(recvThread, INFINITE);//���ſ� �����尡 �����ɶ����� ��ٸ���.

											  //Ŭ���̾�Ʈ�� ���Ḧ �õ��Ѵٸ� ���� �Ʒ��� ����ȴ�.
	closesocket(sock);//������ �����Ѵ�.
	WSACleanup();//������ ���� ��������� �ü���� �˸���.
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), info3);
	printf("                                                                                       ");
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), info3);
	printf("���α׷��� �����մϴ�.\n");
	system("pause");
	return 0;
}

unsigned WINAPI SendMsg(void* arg) {//���ۿ� �������Լ�
	SOCKET sock = *((SOCKET*)arg);//������ ������ �����Ѵ�.
	char nameMsg[NAME_SIZE + BUF_SIZE];
	int order = 0;
	char horseNum[5];
	char horseNumM[5];

	while (1) {//�ݺ�
		WaitForSingleObject(hMutex, INFINITE);//���ؽ� ����

		if (playerNum == 0 && startNum == 1) //���� ������ �� �Է¶� �������� ó��
		{
			SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), input);
			printf("                                                                                                   ");
		}

		if (playerNum == 1 && startNum == 1) // playerNum�� 1�� �Ǿ�߸� �Է� ����
		{
			SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), input);
			printf("                                                                                                   ");
			SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), input);
			printf(">>your turn : ");
			SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), input2);
			fgets(msg, BUF_SIZE, stdin);//�Է��� �޴´�.
			SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), info2);
			printf("                                                                                    ");
			if (!strcmp(msg, "q\n")) {//q�� �Է��ϸ� �����Ѵ�.
				send(sock, "q", 1, 0);//nameMsg�� �������� �����Ѵ�.
				break;
			}
			else if (!strcmp(msg, "run\n")) //�� ������
			{
				sprintf(nameMsg, "%s %s", name, msg);//nameMsg�� �޽����� �����Ѵ�.
				send(sock, nameMsg, strlen(nameMsg), 0);//nameMsg�� �������� �����Ѵ�.

				ReleaseMutex(hMutex);//���ؽ� ����
				WaitForSingleObject(hMutex, INFINITE);//���ؽ� ����
				int confirm = 0;
				do
				{
					if (confirm > 0)
					{
						SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), info2);
						printf("�߸� �Է��߽��ϴ�. �ٽ��Է����ּ���.\n");
					}
					SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), input);
					printf("                                                                                                   ");
					SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), input);
					printf("�� ��ȣ�� �������ּ���. :");
					scanf("%s", horseNum);
					HorseNum = horseNum;
					confirm++;
				} while (strcmp(horseNum, "1") != 0 && strcmp(horseNum, "2") != 0 && strcmp(horseNum, "3") != 0 && strcmp(horseNum, "4") != 0);
				SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), info2);
				printf("                                                                                    ");

				send(sock, horseNum, strlen(horseNum), 0);//nameMsg�� �������� �����Ѵ�.


				ReleaseMutex(hMutex);//���ؽ� ����
				WaitForSingleObject(hMutex, INFINITE);//���ؽ� ����
				playerNum = 0;

				SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), input);
				printf("                                                                                                   ");


			}
			else //ä��
			{
				sprintf(nameMsg, "%s %s", name, msg);//nameMsg�� �޽����� �����Ѵ�.
				send(sock, nameMsg, strlen(nameMsg), 0);//nameMsg�� �������� �����Ѵ�.
			}
		}
		if (clientPower == 1) // ��� �׺��� �� Ŭ���̾�Ʈ�� �������� ������ ���� ����
		{
			break;
		}
		ReleaseMutex(hMutex);//���ؽ� ����
	}
	return 0;
}

unsigned WINAPI RecvMsg(void* arg) {
	SOCKET sock = *((SOCKET*)arg);//������ ������ �����Ѵ�.
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
		printf("��븦 ��ٸ��ϴ�.\n");

		recv(sock, nameMsg, NAME_SIZE + BUF_SIZE - 1, 0);

		if (!strcmp(nameMsg, "1")) {
			WaitForSingleObject(hMutex, INFINITE);//���ؽ� ����
			startNum = 1;
			yutBoard(); //������ �� ȣ��
			Initiation(); //������ �� ���߿��Ḯ��Ʈ
			yutPan();// �� ��带 ����Ű�� �������Ͱ� ������ �׸�ǥ��

			SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), info);
			printf("<<�ȳ�>>");
			SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), info2);
			printf("������ �����մϴ�!!!\n");
			SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), info3);
			printf("������ �� ���� ����: %d     //      ������ ����� �� ����: %d", myCount, yourCount);
			ReleaseMutex(hMutex);//���ؽ� ����
		}
	}
	else if (!strcmp(nameMsg, "2")) // �÷��̾�� �ι�° �����
	{
		WaitForSingleObject(hMutex, INFINITE);//���ؽ� ����
		printf("��ٸ��� ��밡 �ֽ��ϴ�!\n");
		startNum = 1;
		yutBoard(); //������ �� ȣ��
		Initiation(); // ������ �� ���߿��Ḯ��Ʈ
		yutPan();// �� ��带 ����Ű�� �������Ͱ� ������ �׸�ǥ��
		SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), info);
		printf("<<�ȳ�>>");
		SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), info2);
		printf("������ �����մϴ�!!!\n");
		SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), info3);
		printf("������ �� ���� ����: %d     //      ������ ����� �� ����: %d", myCount, yourCount);
		ReleaseMutex(hMutex);//���ؽ� ����
	}

	while (1) {//�ݺ�
		WaitForSingleObject(hMutex, INFINITE);//���ؽ� ����
		strLen = recv(sock, nameMsg, NAME_SIZE + BUF_SIZE - 1, 0);//�����κ��� �޽����� �����Ѵ�.
		if (strLen == -1)
			return -1;
		nameMsg[strLen] = 0;//���ڿ��� ���� �˸��� ���� ����

		if (!strcmp(nameMsg, "1q2b6hpoe5d4z1")) {   //�ڽ��� ���� �������� �˷��ش�
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
			printf("��밡 �׺��߽��ϴ�.\n");
			clientPower = 1;
			break;
		}
		else
		{
			if (playerNum == 0) // ��밡 ���� �޽���
			{
				if (!strcmp(nameMsg, "backDo") || !strcmp(nameMsg, "do") || !strcmp(nameMsg, "gae") || !strcmp(nameMsg, "girl") || !strcmp(nameMsg, "yut") || !strcmp(nameMsg, "mo"))
				{
					SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), info2);
					printf("                                                                                                   ");
					SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), info2);
					printf("���� ��: ");
					fputs(nameMsg, stdout);//�ڽ��� �ֿܼ� ���� �޽����� ����Ѵ�.
					ReleaseMutex(hMutex);//���ؽ� ����
					WaitForSingleObject(hMutex, INFINITE);//���ؽ� ����
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
					printf("������ �� ���� ����: %d     //      ������ ����� �� ����: %d", myCount, yourCount);

					if (yourCount == 4) //�й�����
					{
						SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), info2);
						printf("                                                                                            ");
						SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), info2);
						printf("��..���ӿ��� �й��ϼ̽��ϴ�..��");
						clientPower = 1;
						system("pause");
						return 0;
					}

					ReleaseMutex(hMutex);//���ؽ� ����
					WaitForSingleObject(hMutex, INFINITE);//���ؽ� ����
					
				}

				SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), chat1);
				printf("                                                                                                   ");
				SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), chat1);
				fputs(nameMsg, stdout);//�ڽ��� �ֿܼ� ���� �޽����� ����Ѵ�.
			}
			else // ���� ���� �޽���
			{
				if (!strcmp(nameMsg, "backDo") || !strcmp(nameMsg, "do") || !strcmp(nameMsg, "gae") || !strcmp(nameMsg, "girl") || !strcmp(nameMsg, "yut") || !strcmp(nameMsg, "mo"))
				{
					SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), info2);
					printf("                                                                                                   ");
					SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), info2);
					printf("���� ��: ");
					fputs(nameMsg, stdout);//�ڽ��� �ֿܼ� ���� �޽����� ����Ѵ�.
					ReleaseMutex(hMutex);//���ؽ� ����
					WaitForSingleObject(hMutex, INFINITE);//���ؽ� ����
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
					printf("������ �� ���� ����: %d     //      ������ ����� �� ����: %d", myCount, yourCount);

					if (myCount == 4) //�¸�����
					{
						SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), info2);
						printf("                                                                                             ");
						SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), info2);
						printf("��!!���ӿ��� �¸��ϼ̽��ϴ�!!��");
						clientPower = 1;
						system("pause");
						return 0;
					}

					ReleaseMutex(hMutex);//���ؽ� ����
					WaitForSingleObject(hMutex, INFINITE);//���ؽ� ����
					
				}

				SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), chat2);
				printf("                                                                                                   ");
				SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), chat2);
				fputs(nameMsg, stdout);//�ڽ��� �ֿܼ� ���� �޽����� ����Ѵ�.
			}
		}

		ReleaseMutex(hMutex);//���ؽ� ����
	}
	return 0;
}

void ErrorHandling(char* msg) {
	fputs(msg, stderr);
	fputc('\n', stderr);
	exit(1);
}
#pragma once
#pragma warning(disable:4996)
#include <stdio.h>
#include <string.h>
#include <stdlib.h> // Rand 함수를 위한 해더파일
#include <windows.h> // 화면 Clear를 위한 해더파일
#include <time.h> // Srand를 사용하기 위한 해더파일
#include <conio.h> // getch를 사용하기 위한 해더파일

typedef struct ListNode {
	char data[100];
	struct ListNode *pre;
	struct ListNode *next;
	struct ListNode *another;
}ListNode; // 윷놀이 판 구조체

typedef struct {
	ListNode *head;
	int check; // 윷놀이 가장자리에서 시작시 판단하여 중앙쪽으로 이동하게끔 해주는 변수
	int stopNum;
}LinkedList_h; // 말 구조체

			   //R은 판 오른쪽, H는 판 위, L은 판 왼쪽, B는 판 아래, 
ListNode *Start1, *Start2, *R1, *R2, *R3, *R4, *E1, *H1, *H2, *H3, *H4, *E2, *L1, *L2, *L3, *L4, *E3, *B1, *B2, *B3, *B4, *LH1, *LH2, *RH1, *RH2, *LB1, *LB2, *RB1, *RB2, *CENTER, *LAST, *Destination;
LinkedList_h *p1_1, *p1_2, *p1_3, *p1_4, *p2_1, *p2_2, *p2_3, *p2_4;

//도착점에 도착한 말의 개수 카운트
int myCount = 0, myCount1 = 0, myCount2 = 0, myCount3 = 0, myCount4 = 0;
int yourCount = 0, yourCount1 = 0, yourCount2 = 0, yourCount3 = 0, yourCount4 = 0;


LinkedList_h* createLinkedList_h() {
	p1_1 = (LinkedList_h*)malloc(sizeof(LinkedList_h));
	p1_1->head = NULL;
	p1_1->check = 0;
	p1_1->stopNum = 0;

	p1_2 = (LinkedList_h*)malloc(sizeof(LinkedList_h));
	p1_2->head = NULL;
	p1_2->check = 0;
	p1_2->stopNum = 0;

	p1_3 = (LinkedList_h*)malloc(sizeof(LinkedList_h));
	p1_3->head = NULL;
	p1_3->check = 0;
	p1_3->stopNum = 0;

	p1_4 = (LinkedList_h*)malloc(sizeof(LinkedList_h));
	p1_4->head = NULL;
	p1_4->check = 0;
	p1_4->stopNum = 0;

	p2_1 = (LinkedList_h*)malloc(sizeof(LinkedList_h));
	p2_1->head = NULL;
	p2_1->check = 0;
	p2_1->stopNum = 0;

	p2_2 = (LinkedList_h*)malloc(sizeof(LinkedList_h));
	p2_2->head = NULL;
	p2_2->check = 0;
	p2_2->stopNum = 0;

	p2_3 = (LinkedList_h*)malloc(sizeof(LinkedList_h));
	p2_3->head = NULL;
	p2_3->check = 0;
	p2_3->stopNum = 0;

	p2_4 = (LinkedList_h*)malloc(sizeof(LinkedList_h));
	p2_4->head = NULL;
	p2_4->check = 0;
	p2_4->stopNum = 0;
}

void Initiation()
{
	createLinkedList_h(); // 말 구조체 선언

						  //중앙
	CENTER = (ListNode*)malloc(sizeof(ListNode));
	Start1 = (ListNode*)malloc(sizeof(ListNode));
	Start2 = (ListNode*)malloc(sizeof(ListNode));

	//오른쪽
	R1 = (ListNode*)malloc(sizeof(ListNode));
	R2 = (ListNode*)malloc(sizeof(ListNode));
	R3 = (ListNode*)malloc(sizeof(ListNode));
	R4 = (ListNode*)malloc(sizeof(ListNode));
	E1 = (ListNode*)malloc(sizeof(ListNode));

	//중앙지점으로 가는길 북동
	RH1 = (ListNode*)malloc(sizeof(ListNode));
	RH2 = (ListNode*)malloc(sizeof(ListNode));

	//위
	H1 = (ListNode*)malloc(sizeof(ListNode));
	H2 = (ListNode*)malloc(sizeof(ListNode));
	H3 = (ListNode*)malloc(sizeof(ListNode));
	H4 = (ListNode*)malloc(sizeof(ListNode));
	E2 = (ListNode*)malloc(sizeof(ListNode));

	//중앙지점으로 가는길 북서
	LH1 = (ListNode*)malloc(sizeof(ListNode));
	LH2 = (ListNode*)malloc(sizeof(ListNode));

	//왼쪽
	L1 = (ListNode*)malloc(sizeof(ListNode));
	L2 = (ListNode*)malloc(sizeof(ListNode));
	L3 = (ListNode*)malloc(sizeof(ListNode));
	L4 = (ListNode*)malloc(sizeof(ListNode));
	E3 = (ListNode*)malloc(sizeof(ListNode));

	//아래
	B1 = (ListNode*)malloc(sizeof(ListNode));
	B2 = (ListNode*)malloc(sizeof(ListNode));
	B3 = (ListNode*)malloc(sizeof(ListNode));
	B4 = (ListNode*)malloc(sizeof(ListNode));
	LAST = (ListNode*)malloc(sizeof(ListNode));

	//중앙에서 나오는지점 남서
	LB1 = (ListNode*)malloc(sizeof(ListNode));
	LB2 = (ListNode*)malloc(sizeof(ListNode));

	//중앙에서 나오는지점 남동
	RB1 = (ListNode*)malloc(sizeof(ListNode));
	RB2 = (ListNode*)malloc(sizeof(ListNode));

	//도착지
	Destination = (ListNode *)malloc(sizeof(ListNode));

	Start1->pre = Start1;
	Start1->next = R1;
	Start1->another = Start1;

	Start2->pre = Start2;
	Start2->next = R1;
	Start2->another = Start2;

	//오른쪽
	R1->pre = RB2;
	R1->next = R2;
	R1->another = NULL;

	R2->pre = R1;
	R2->next = R3;
	R2->another = NULL;

	R3->pre = R2;
	R3->next = R4;
	R3->another = NULL;

	R4->pre = R3;
	R4->next = E1;
	R4->another = NULL;

	E1->pre = R4;
	E1->next = H1;
	E1->another = RH1;

	//중앙지점으로 가는길 북동
	RH1->pre = E1;
	RH1->next = RH2;
	RH1->another = NULL;

	RH2->pre = RH1;
	RH2->next = CENTER;
	RH2->another = NULL;

	CENTER->pre = LH2;
	CENTER->next = RB1;
	CENTER->another = LB1;


	//위
	H1->pre = E1;
	H1->next = H2;
	H1->another = NULL;

	H2->pre = H1;
	H2->next = H3;
	H2->another = NULL;

	H3->pre = H2;
	H3->next = H4;
	H3->another = NULL;

	H4->pre = H3;
	H4->next = E2;
	H4->another = NULL;

	E2->pre = H4;
	E2->next = L1;
	E2->another = LH1;

	//중앙지점으로 가는길 북서
	LH1->pre = E2;
	LH1->next = LH2;
	LH1->another = NULL;

	LH2->pre = LH1;
	LH2->next = CENTER;
	LH2->another = NULL;


	//왼쪽
	L1->pre = E2;
	L1->next = L2;
	L1->another = NULL;

	L2->pre = L1;
	L2->next = L3;
	L2->another = NULL;

	L3->pre = L2;
	L3->next = L4;
	L3->another = NULL;

	L4->pre = L3;
	L4->next = E3;
	L4->another = NULL;

	E3->pre = L4;
	E3->next = B1;
	E3->another = NULL;

	//아래
	B1->pre = E3;
	B1->next = B2;
	B1->another = NULL;

	B2->pre = B1;
	B2->next = B3;
	B2->another = NULL;

	B3->pre = B2;
	B3->next = B4;
	B3->another = NULL;

	B4->pre = B3;
	B4->next = LAST;
	B4->another = NULL;

	LAST->pre = LB2;
	LAST->next = Destination;
	LAST->another = Destination;

	//중앙에서 나오는지점 남서
	LB1->pre = CENTER;
	LB1->next = LB2;
	LB1->another = NULL;

	LB2->pre = LB1;
	LB2->next = E3;
	LB2->another = NULL;

	//중앙에서 나오는지점 남동
	RB1->pre = CENTER;
	RB1->next = RB2;
	RB1->another = NULL;

	RB2->pre = RB1;
	RB2->next = LAST;
	RB2->another = NULL;

	//도착지
	Destination->pre = Destination;
	Destination->next = Destination; //튕김 방지 , 자기가 자신을 가리키므로써 도착지에 도착하고도 남은 next들을 수용할수있음
	Destination->another = Destination;



	//말 포인터 시작점으로 설정
	p1_1->head = Start1;
	p1_2->head = Start1;
	p1_3->head = Start1;
	p1_4->head = Start1;


	p2_1->head = Start2;
	p2_2->head = Start2;
	p2_3->head = Start2;
	p2_4->head = Start2;
}

void yutPan()
{
	//내 말
	//말 기본 자리
	if (p1_1->head == Start1)
	{
		COORD R1_ = { 93, 25 };
		SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), R1_);
		printf("★");
	}
	if (p1_2->head == Start1)
	{
		COORD R1_ = { 95, 25 };
		SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), R1_);
		printf("★");
	}
	if (p1_3->head == Start1)
	{
		COORD R1_ = { 93, 26 };
		SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), R1_);
		printf("★");
	}
	if (p1_4->head == Start1)
	{
		COORD R1_ = { 95, 26 };
		SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), R1_);
		printf("★");
	}

	//말이 초기 장소에 있지 않을 때
	if (p1_1->head != Start1)
	{
		COORD R1_ = { 93, 25 };
		SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), R1_);
		printf("  ");
	}
	if (p1_2->head != Start1)
	{
		COORD R1_ = { 95, 25 };
		SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), R1_);
		printf("  ");
	}
	if (p1_3->head != Start1)
	{
		COORD R1_ = { 93, 26 };
		SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), R1_);
		printf("  ");
	}
	if (p1_4->head != Start1)
	{
		COORD R1_ = { 95, 26 };
		SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), R1_);
		printf("  ");
	}

	//오른쪽
	if (p1_1->head == R1 || p1_2->head == R1 || p1_3->head == R1 || p1_4->head == R1)
	{
		COORD R1_ = { 74, 22 };
		SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), R1_);
		if (p1_1->head == R1)printf("1"); if (p1_2->head == R1)printf("2"); if (p1_3->head == R1)printf("3"); if (p1_4->head == R1)printf("4");
		printf("★");
	}
	if (p1_1->head == R2 || p1_2->head == R2 || p1_3->head == R2 || p1_4->head == R2)
	{
		COORD R1_ = { 74, 17 };
		SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), R1_);
		if (p1_1->head == R2)printf("1"); if (p1_2->head == R2)printf("2"); if (p1_3->head == R2)printf("3"); if (p1_4->head == R2)printf("4");
		printf("★");
	}
	if (p1_1->head == R3 || p1_2->head == R3 || p1_3->head == R3 || p1_4->head == R3)
	{
		COORD R1_ = { 74, 12 };
		SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), R1_);
		if (p1_1->head == R3)printf("1"); if (p1_2->head == R3)printf("2"); if (p1_3->head == R3)printf("3"); if (p1_4->head == R3)printf("4");
		printf("★");
	}
	if (p1_1->head == R4 || p1_2->head == R4 || p1_3->head == R4 || p1_4->head == R4)
	{
		COORD R1_ = { 74, 7 };
		SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), R1_);
		if (p1_1->head == R4)printf("1"); if (p1_2->head == R4)printf("2"); if (p1_3->head == R4)printf("3"); if (p1_4->head == R4)printf("4");
		printf("★");
	}
	if (p1_1->head == E1 || p1_2->head == E1 || p1_3->head == E1 || p1_4->head == E1)
	{
		COORD R1_ = { 74, 2 };
		SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), R1_);
		if (p1_1->head == E1)printf("1"); if (p1_2->head == E1)printf("2"); if (p1_3->head == E1)printf("3"); if (p1_4->head == E1)printf("4");
		printf("★");
	}

	//위
	if (p1_1->head == H1 || p1_2->head == H1 || p1_3->head == H1 || p1_4->head == H1)
	{
		COORD R1_ = { 60, 2 };
		SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), R1_);
		if (p1_1->head == H1)printf("1"); if (p1_2->head == H1)printf("2"); if (p1_3->head == H1)printf("3"); if (p1_4->head == H1)printf("4");
		printf("★");
	}
	if (p1_1->head == H2 || p1_2->head == H2 || p1_3->head == H2 || p1_4->head == H2)
	{
		COORD R1_ = { 46, 2 };
		SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), R1_);
		if (p1_1->head == H2)printf("1"); if (p1_2->head == H2)printf("2"); if (p1_3->head == H2)printf("3"); if (p1_4->head == H2)printf("4");
		printf("★");
	}
	if (p1_1->head == H3 || p1_2->head == H3 || p1_3->head == H3 || p1_4->head == H3)
	{
		COORD R1_ = { 32, 2 };
		SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), R1_);
		if (p1_1->head == H3)printf("1"); if (p1_2->head == H3)printf("2"); if (p1_3->head == H3)printf("3"); if (p1_4->head == H3)printf("4");
		printf("★");
	}
	if (p1_1->head == H4 || p1_2->head == H4 || p1_3->head == H4 || p1_4->head == H4)
	{
		COORD R1_ = { 18, 2 };
		SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), R1_);
		if (p1_1->head == H4)printf("1"); if (p1_2->head == H4)printf("2"); if (p1_3->head == H4)printf("3"); if (p1_4->head == H4)printf("4");
		printf("★");
	}
	if (p1_1->head == E2 || p1_2->head == E2 || p1_3->head == E2 || p1_4->head == E2)
	{
		COORD R1_ = { 4, 2 };
		SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), R1_);
		if (p1_1->head == E2)printf("1"); if (p1_2->head == E2)printf("2"); if (p1_3->head == E2)printf("3"); if (p1_4->head == E2)printf("4");
		printf("★");
	}

	//왼쪽
	if (p1_1->head == L1 || p1_2->head == L1 || p1_3->head == L1 || p1_4->head == L1)
	{
		COORD R1_ = { 4,7 };
		SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), R1_);
		if (p1_1->head == L1)printf("1"); if (p1_2->head == L1)printf("2"); if (p1_3->head == L1)printf("3"); if (p1_4->head == L1)printf("4");
		printf("★");
	}
	if (p1_1->head == L2 || p1_2->head == L2 || p1_3->head == L2 || p1_4->head == L2)
	{
		COORD R1_ = { 4, 12 };
		SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), R1_);
		if (p1_1->head == L2)printf("1"); if (p1_2->head == L2)printf("2"); if (p1_3->head == L2)printf("3"); if (p1_4->head == L2)printf("4");
		printf("★");
	}
	if (p1_1->head == L3 || p1_2->head == L3 || p1_3->head == L3 || p1_4->head == L3)
	{
		COORD R1_ = { 4, 17 };
		SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), R1_);
		if (p1_1->head == L3)printf("1"); if (p1_2->head == L3)printf("2"); if (p1_3->head == L3)printf("3"); if (p1_4->head == L3)printf("4");
		printf("★");
	}
	if (p1_1->head == L4 || p1_2->head == L4 || p1_3->head == L4 || p1_4->head == L4)
	{
		COORD R1_ = { 4, 22 };
		SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), R1_);
		if (p1_1->head == L4)printf("1"); if (p1_2->head == L4)printf("2"); if (p1_3->head == L4)printf("3"); if (p1_4->head == L4)printf("4");
		printf("★");
	}
	if (p1_1->head == E3 || p1_2->head == E3 || p1_3->head == E3 || p1_4->head == E3)
	{
		COORD R1_ = { 4, 27 };
		SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), R1_);
		if (p1_1->head == E3)printf("1"); if (p1_2->head == E3)printf("2"); if (p1_3->head == E3)printf("3"); if (p1_4->head == E3)printf("4");
		printf("★");
	}

	//아래
	if (p1_1->head == B1 || p1_2->head == B1 || p1_3->head == B1 || p1_4->head == B1)
	{
		COORD R1_ = { 18,27 };
		SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), R1_);
		if (p1_1->head == B1)printf("1"); if (p1_2->head == B1)printf("2"); if (p1_3->head == B1)printf("3"); if (p1_4->head == B1)printf("4");
		printf("★");
	}
	if (p1_1->head == B2 || p1_2->head == B2 || p1_3->head == B2 || p1_4->head == B2)
	{
		COORD R1_ = { 32, 27 };
		SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), R1_);
		if (p1_1->head == B2)printf("1"); if (p1_2->head == B2)printf("2"); if (p1_3->head == B2)printf("3"); if (p1_4->head == B2)printf("4");
		printf("★");
	}
	if (p1_1->head == B3 || p1_2->head == B3 || p1_3->head == B3 || p1_4->head == B3)
	{
		COORD R1_ = { 46, 27 };
		SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), R1_);
		if (p1_1->head == B3)printf("1"); if (p1_2->head == B3)printf("2"); if (p1_3->head == B3)printf("3"); if (p1_4->head == B3)printf("4");
		printf("★");
	}
	if (p1_1->head == B4 || p1_2->head == B4 || p1_3->head == B4 || p1_4->head == B4)
	{
		COORD R1_ = { 60, 27 };
		SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), R1_);
		if (p1_1->head == B4)printf("1"); if (p1_2->head == B4)printf("2"); if (p1_3->head == B4)printf("3"); if (p1_4->head == B4)printf("4");
		printf("★");
	}
	if (p1_1->head == LAST || p1_2->head == LAST || p1_3->head == LAST || p1_4->head == LAST)
	{
		COORD R1_ = { 74, 27 };
		SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), R1_);
		if (p1_1->head == LAST)printf("1"); if (p1_2->head == LAST)printf("2"); if (p1_3->head == LAST)printf("3"); if (p1_4->head == LAST)printf("4");
		printf("★");
	}

	//중앙 상단
	if (p1_1->head == RH1 || p1_2->head == RH1 || p1_3->head == RH1 || p1_4->head == RH1)
	{
		COORD R1_ = { 62, 6 };
		SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), R1_);
		if (p1_1->head == RH1)printf("1"); if (p1_2->head == RH1)printf("2"); if (p1_3->head == RH1)printf("3"); if (p1_4->head == RH1)printf("4");
		printf("★");
	}
	if (p1_1->head == RH2 || p1_2->head == RH2 || p1_3->head == RH2 || p1_4->head == RH2)
	{
		COORD R1_ = { 50,10 };
		SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), R1_);
		if (p1_1->head == RH2)printf("1"); if (p1_2->head == RH2)printf("2"); if (p1_3->head == RH2)printf("3"); if (p1_4->head == RH2)printf("4");
		printf("★");
	}
	if (p1_1->head == LH1 || p1_2->head == LH1 || p1_3->head == LH1 || p1_4->head == LH1)
	{
		COORD R1_ = { 16, 6 };
		SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), R1_);
		if (p1_1->head == LH1)printf("1"); if (p1_2->head == LH1)printf("2"); if (p1_3->head == LH1)printf("3"); if (p1_4->head == LH1)printf("4");
		printf("★");
	}
	if (p1_1->head == LH2 || p1_2->head == LH2 || p1_3->head == LH2 || p1_4->head == LH2)
	{
		COORD R1_ = { 28, 10 };
		SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), R1_);
		if (p1_1->head == LH2)printf("1"); if (p1_2->head == LH2)printf("2"); if (p1_3->head == LH2)printf("3"); if (p1_4->head == LH2)printf("4");
		printf("★");
	}
	if (p1_1->head == CENTER || p1_2->head == CENTER || p1_3->head == CENTER || p1_4->head == CENTER)
	{
		COORD R1_ = { 40, 14 };
		SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), R1_);
		if (p1_1->head == CENTER)printf("1"); if (p1_2->head == CENTER)printf("2"); if (p1_3->head == CENTER)printf("3"); if (p1_4->head == CENTER)printf("4");
		printf("★");
	}


	//중앙 하단
	if (p1_1->head == LB1 || p1_2->head == LB1 || p1_3->head == LB1 || p1_4->head == LB1)
	{
		COORD R1_ = { 28,18 };
		SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), R1_);
		if (p1_1->head == LB1)printf("1"); if (p1_2->head == LB1)printf("2"); if (p1_3->head == LB1)printf("3"); if (p1_4->head == LB1)printf("4");
		printf("★");
	}
	if (p1_1->head == LB2 || p1_2->head == LB2 || p1_3->head == LB2 || p1_4->head == LB2)
	{
		COORD R1_ = { 16, 22 };
		SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), R1_);
		if (p1_1->head == LB2)printf("1"); if (p1_2->head == LB2)printf("2"); if (p1_3->head == LB2)printf("3"); if (p1_4->head == LB2)printf("4");
		printf("★");
	}
	if (p1_1->head == RB1 || p1_2->head == RB1 || p1_3->head == RB1 || p1_4->head == RB1)
	{
		COORD R1_ = { 52,18 };
		SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), R1_);
		if (p1_1->head == RB1)printf("1"); if (p1_2->head == RB1)printf("2"); if (p1_3->head == RB1)printf("3"); if (p1_4->head == RB1)printf("4");
		printf("★");
	}
	if (p1_1->head == RB2 || p1_2->head == RB2 || p1_3->head == RB2 || p1_4->head == RB2)
	{
		COORD R1_ = { 62, 23 };
		SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), R1_);
		if (p1_1->head == RB2)printf("1"); if (p1_2->head == RB2)printf("2"); if (p1_3->head == RB2)printf("3"); if (p1_4->head == RB2)printf("4");
		printf("★");
	}


	//상대 말
	//말 기본 자리
	if (p2_1->head == Start2)
	{
		COORD R1_ = { 105, 25 };
		SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), R1_);
		printf("♡");
	}
	if (p2_2->head == Start2)
	{
		COORD R1_ = { 107, 25 };
		SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), R1_);
		printf("♡");
	}
	if (p2_3->head == Start2)
	{
		COORD R1_ = { 105, 26 };
		SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), R1_);
		printf("♡");
	}
	if (p2_4->head == Start2)
	{
		COORD R1_ = { 107, 26 };
		SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), R1_);
		printf("♡");
	}

	if (p2_1->head != Start2)
	{
		COORD R1_ = { 105, 25 };
		SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), R1_);
		printf("  ");
	}
	if (p2_2->head != Start2)
	{
		COORD R1_ = { 107, 25 };
		SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), R1_);
		printf("  ");
	}
	if (p2_3->head != Start2)
	{
		COORD R1_ = { 105, 26 };
		SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), R1_);
		printf("  ");
	}
	if (p2_4->head != Start2)
	{
		COORD R1_ = { 107, 26 };
		SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), R1_);
		printf("  ");
	}

	//오른쪽
	if (p2_1->head == R1 || p2_2->head == R1 || p2_3->head == R1 || p2_4->head == R1)
	{
		COORD R1_ = { 74, 22 };
		SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), R1_);
		if (p2_1->head == R1)printf("1"); if (p2_2->head == R1)printf("2"); if (p2_3->head == R1)printf("3"); if (p2_4->head == R1)printf("4");
		printf("♡");
	}
	if (p2_1->head == R2 || p2_2->head == R2 || p2_3->head == R2 || p2_4->head == R2)
	{
		COORD R1_ = { 74, 17 };
		SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), R1_);
		if (p2_1->head == R2)printf("1"); if (p2_2->head == R2)printf("2"); if (p2_3->head == R2)printf("3"); if (p2_4->head == R2)printf("4");
		printf("♡");
	}
	if (p2_1->head == R3 || p2_2->head == R3 || p2_3->head == R3 || p2_4->head == R3)
	{
		COORD R1_ = { 74, 12 };
		SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), R1_);
		if (p2_1->head == R3)printf("1"); if (p2_2->head == R3)printf("2"); if (p2_3->head == R3)printf("3"); if (p2_4->head == R3)printf("4");
		printf("♡");
	}
	if (p2_1->head == R4 || p2_2->head == R4 || p2_3->head == R4 || p2_4->head == R4)
	{
		COORD R1_ = { 74, 7 };
		SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), R1_);
		if (p2_1->head == R4)printf("1"); if (p2_2->head == R4)printf("2"); if (p2_3->head == R4)printf("3"); if (p2_4->head == R4)printf("4");
		printf("♡");
	}
	if (p2_1->head == E1 || p2_2->head == E1 || p2_3->head == E1 || p2_4->head == E1)
	{
		COORD R1_ = { 74, 2 };
		SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), R1_);
		if (p2_1->head == E1)printf("1"); if (p2_2->head == E1)printf("2"); if (p2_3->head == E1)printf("3"); if (p2_4->head == E1)printf("4");
		printf("♡");
	}

	//위
	if (p2_1->head == H1 || p2_2->head == H1 || p2_3->head == H1 || p2_4->head == H1)
	{
		COORD R1_ = { 60, 2 };
		SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), R1_);
		if (p2_1->head == H1)printf("1"); if (p2_2->head == H1)printf("2"); if (p2_3->head == H1)printf("3"); if (p2_4->head == H1)printf("4");
		printf("♡");
	}
	if (p2_1->head == H2 || p2_2->head == H2 || p2_3->head == H2 || p2_4->head == H2)
	{
		COORD R1_ = { 46, 2 };
		SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), R1_);
		if (p2_1->head == H2)printf("1"); if (p2_2->head == H2)printf("2"); if (p2_3->head == H2)printf("3"); if (p2_4->head == H2)printf("4");
		printf("♡");
	}
	if (p2_1->head == H3 || p2_2->head == H3 || p2_3->head == H3 || p2_4->head == H3)
	{
		COORD R1_ = { 32, 2 };
		SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), R1_);
		if (p2_1->head == H3)printf("1"); if (p2_2->head == H3)printf("2"); if (p2_3->head == H3)printf("3"); if (p2_4->head == H3)printf("4");
		printf("♡");
	}
	if (p2_1->head == H4 || p2_2->head == H4 || p2_3->head == H4 || p2_4->head == H4)
	{
		COORD R1_ = { 18, 2 };
		SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), R1_);
		if (p2_1->head == H4)printf("1"); if (p2_2->head == H4)printf("2"); if (p2_3->head == H4)printf("3"); if (p2_4->head == H4)printf("4");
		printf("♡");
	}
	if (p2_1->head == E2 || p2_2->head == E2 || p2_3->head == E2 || p2_4->head == E2)
	{
		COORD R1_ = { 4, 2 };
		SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), R1_);
		if (p2_1->head == E2)printf("1"); if (p2_2->head == E2)printf("2"); if (p2_3->head == E2)printf("3"); if (p2_4->head == E2)printf("4");
		printf("♡");
	}

	//왼쪽
	if (p2_1->head == L1 || p2_2->head == L1 || p2_3->head == L1 || p2_4->head == L1)
	{
		COORD R1_ = { 4,7 };
		SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), R1_);
		if (p2_1->head == L1)printf("1"); if (p2_2->head == L1)printf("2"); if (p2_3->head == L1)printf("3"); if (p2_4->head == L1)printf("4");
		printf("♡");
	}
	if (p2_1->head == L2 || p2_2->head == L2 || p2_3->head == L2 || p2_4->head == L2)
	{
		COORD R1_ = { 4, 12 };
		SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), R1_);
		if (p2_1->head == L2)printf("1"); if (p2_2->head == L2)printf("2"); if (p2_3->head == L2)printf("3"); if (p2_4->head == L2)printf("4");
		printf("♡");
	}
	if (p2_1->head == L3 || p2_2->head == L3 || p2_3->head == L3 || p2_4->head == L3)
	{
		COORD R1_ = { 4, 17 };
		SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), R1_);
		if (p2_1->head == L3)printf("1"); if (p2_2->head == L3)printf("2"); if (p2_3->head == L3)printf("3"); if (p2_4->head == L3)printf("4");
		printf("♡");
	}
	if (p2_1->head == L4 || p2_2->head == L4 || p2_3->head == L4 || p2_4->head == L4)
	{
		COORD R1_ = { 4, 22 };
		SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), R1_);
		if (p2_1->head == L4)printf("1"); if (p2_2->head == L4)printf("2"); if (p2_3->head == L4)printf("3"); if (p2_4->head == L4)printf("4");
		printf("♡");
	}
	if (p2_1->head == E3 || p2_2->head == E3 || p2_3->head == E3 || p2_4->head == E3)
	{
		COORD R1_ = { 4, 27 };
		SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), R1_);
		if (p2_1->head == E3)printf("1"); if (p2_2->head == E3)printf("2"); if (p2_3->head == E3)printf("3"); if (p2_4->head == E3)printf("4");
		printf("♡");
	}

	//아래
	if (p2_1->head == B1 || p2_2->head == B1 || p2_3->head == B1 || p2_4->head == B1)
	{
		COORD R1_ = { 18,27 };
		SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), R1_);
		if (p2_1->head == B1)printf("1"); if (p2_2->head == B1)printf("2"); if (p2_3->head == B1)printf("3"); if (p2_4->head == B1)printf("4");
		printf("♡");
	}
	if (p2_1->head == B2 || p2_2->head == B2 || p2_3->head == B2 || p2_4->head == B2)
	{
		COORD R1_ = { 32, 27 };
		SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), R1_);
		if (p2_1->head == B2)printf("1"); if (p2_2->head == B2)printf("2"); if (p2_3->head == B2)printf("3"); if (p2_4->head == B2)printf("4");
		printf("♡");
	}
	if (p2_1->head == B3 || p2_2->head == B3 || p2_3->head == B3 || p2_4->head == B3)
	{
		COORD R1_ = { 46, 27 };
		SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), R1_);
		if (p2_1->head == B3)printf("1"); if (p2_2->head == B3)printf("2"); if (p2_3->head == B3)printf("3"); if (p2_4->head == B3)printf("4");
		printf("♡");
	}
	if (p2_1->head == B4 || p2_2->head == B4 || p2_3->head == B4 || p2_4->head == B4)
	{
		COORD R1_ = { 60, 27 };
		SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), R1_);
		if (p2_1->head == B4)printf("1"); if (p2_2->head == B4)printf("2"); if (p2_3->head == B4)printf("3"); if (p2_4->head == B4)printf("4");
		printf("♡");
	}
	if (p2_1->head == LAST || p2_2->head == LAST || p2_3->head == LAST || p2_4->head == LAST)
	{
		COORD R1_ = { 74, 27 };
		SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), R1_);
		if (p2_1->head == LAST)printf("1"); if (p2_2->head == LAST)printf("2"); if (p2_3->head == LAST)printf("3"); if (p2_4->head == LAST)printf("4");
		printf("♡");
	}

	//중앙 상단
	if (p2_1->head == RH1 || p2_2->head == RH1 || p2_3->head == RH1 || p2_4->head == RH1)
	{
		COORD R1_ = { 62, 6 };
		SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), R1_);
		if (p2_1->head == RH1)printf("1"); if (p2_2->head == RH1)printf("2"); if (p2_3->head == RH1)printf("3"); if (p2_4->head == RH1)printf("4");
		printf("♡");
	}
	if (p2_1->head == RH2 || p2_2->head == RH2 || p2_3->head == RH2 || p2_4->head == RH2)
	{
		COORD R1_ = { 50,10 };
		SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), R1_);
		if (p2_1->head == RH2)printf("1"); if (p2_2->head == RH2)printf("2"); if (p2_3->head == RH2)printf("3"); if (p2_4->head == RH2)printf("4");
		printf("♡");
	}
	if (p2_1->head == LH1 || p2_2->head == LH1 || p2_3->head == LH1 || p2_4->head == LH1)
	{
		COORD R1_ = { 16, 6 };
		SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), R1_);
		if (p2_1->head == LH1)printf("1"); if (p2_2->head == LH1)printf("2"); if (p2_3->head == LH1)printf("3"); if (p2_4->head == LH1)printf("4");
		printf("♡");
	}
	if (p2_1->head == LH2 || p2_2->head == LH2 || p2_3->head == LH2 || p2_4->head == LH2)
	{
		COORD R1_ = { 28, 10 };
		SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), R1_);
		if (p2_1->head == LH2)printf("1"); if (p2_2->head == LH2)printf("2"); if (p2_3->head == LH2)printf("3"); if (p2_4->head == LH2)printf("4");
		printf("♡");
	}
	if (p2_1->head == CENTER || p2_2->head == CENTER || p2_3->head == CENTER || p2_4->head == CENTER)
	{
		COORD R1_ = { 40, 14 };
		SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), R1_);
		if (p2_1->head == CENTER)printf("1"); if (p2_2->head == CENTER)printf("2"); if (p2_3->head == CENTER)printf("3"); if (p2_4->head == CENTER)printf("4");
		printf("♡");
	}

	//중앙 하단
	if (p2_1->head == LB1 || p2_2->head == LB1 || p2_3->head == LB1 || p2_4->head == LB1)
	{
		COORD R1_ = { 28,18 };
		SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), R1_);
		if (p2_1->head == LB1)printf("1"); if (p2_2->head == LB1)printf("2"); if (p2_3->head == LB1)printf("3"); if (p2_4->head == LB1)printf("4");
		printf("♡");
	}
	if (p2_1->head == LB2 || p2_2->head == LB2 || p2_3->head == LB2 || p2_4->head == LB2)
	{
		COORD R1_ = { 16, 22 };
		SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), R1_);
		if (p2_1->head == LB2)printf("1"); if (p2_2->head == LB2)printf("2"); if (p2_3->head == LB2)printf("3"); if (p2_4->head == LB2)printf("4");
		printf("♡");
	}
	if (p2_1->head == RB1 || p2_2->head == RB1 || p2_3->head == RB1 || p2_4->head == RB1)
	{
		COORD R1_ = { 52,18 };
		SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), R1_);
		if (p2_1->head == RB1)printf("1"); if (p2_2->head == RB1)printf("2"); if (p2_3->head == RB1)printf("3"); if (p2_4->head == RB1)printf("4");
		printf("♡");
	}
	if (p2_1->head == RB2 || p2_2->head == RB2 || p2_3->head == RB2 || p2_4->head == RB2)
	{
		COORD R1_ = { 62, 23 };
		SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), R1_);
		if (p2_1->head == RB2)printf("1"); if (p2_2->head == RB2)printf("2"); if (p2_3->head == RB2)printf("3"); if (p2_4->head == RB2)printf("4");
		printf("♡");
	}

	//말이 없을 때 ||->&& 로바꿔야함
	//오른쪽
	if (p1_1->head != R1 && p1_2->head != R1 && p1_3->head != R1 && p1_4->head != R1 && p2_1->head != R1 && p2_2->head != R1 && p2_3->head != R1 && p2_4->head != R1)
	{
		COORD R1_ = { 74, 22 };
		SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), R1_);
		printf("      ");
	}
	if (p1_1->head != R2 && p1_2->head != R2 && p1_3->head != R2 && p1_4->head != R2 && p2_1->head != R2 && p2_2->head != R2 && p2_3->head != R2 && p2_4->head != R2)
	{
		COORD R1_ = { 74, 17 };
		SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), R1_);
		printf("      ");
	}
	if (p1_1->head != R3 && p1_2->head != R3 && p1_3->head != R3 && p1_4->head != R3 && p2_1->head != R3 && p2_2->head != R3 && p2_3->head != R3 && p2_4->head != R3)
	{
		COORD R1_ = { 74, 12 };
		SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), R1_);
		printf("      ");
	}
	if (p1_1->head != R4 && p1_2->head != R4 && p1_3->head != R4 && p1_4->head != R4 && p2_1->head != R4 && p2_2->head != R4 && p2_3->head != R4 && p2_4->head != R4)
	{
		COORD R1_ = { 74, 7 };
		SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), R1_);
		printf("      ");
	}
	if (p1_1->head != E1 && p1_2->head != E1 && p1_3->head != E1 && p1_4->head != E1 && p2_1->head != E1 && p2_2->head != E1 && p2_3->head != E1 && p2_4->head != E1)
	{
		COORD R1_ = { 74, 2 };
		SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), R1_);
		printf("      ");
	}

	//위
	if (p1_1->head != H1 && p1_2->head != H1 && p1_3->head != H1 && p1_4->head != H1 && p2_1->head != H1 && p2_2->head != H1 && p2_3->head != H1 && p2_4->head != H1)
	{
		COORD R1_ = { 60, 2 };
		SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), R1_);
		printf("      ");
	}
	if (p1_1->head != H2 && p1_2->head != H2 && p1_3->head != H2 && p1_4->head != H2 && p2_1->head != H2 && p2_2->head != H2 && p2_3->head != H2 && p2_4->head != H2)
	{
		COORD R1_ = { 46, 2 };
		SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), R1_);
		printf("      ");
	}
	if (p1_1->head != H3 && p1_2->head != H3 && p1_3->head != H3 && p1_4->head != H3 && p2_1->head != H3 && p2_2->head != H3 && p2_3->head != H3 && p2_4->head != H3)
	{
		COORD R1_ = { 32, 2 };
		SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), R1_);
		printf("      ");
	}
	if (p1_1->head != H4 && p1_2->head != H4 && p1_3->head != H4 && p1_4->head != H4 && p2_1->head != H4 && p2_2->head != H4 && p2_3->head != H4 && p2_4->head != H4)
	{
		COORD R1_ = { 18, 2 };
		SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), R1_);
		printf("      ");
	}
	if (p1_1->head != E2 && p1_2->head != E2 && p1_3->head != E2 && p1_4->head != E2 && p2_1->head != E2 && p2_2->head != E2 && p2_3->head != E2 && p2_4->head != E2)
	{
		COORD R1_ = { 4, 2 };
		SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), R1_);
		printf("      ");
	}

	//왼쪽
	if (p1_1->head != L1 && p1_2->head != L1 && p1_3->head != L1 && p1_4->head != L1 && p2_1->head != L1 && p2_2->head != L1 && p2_3->head != L1 && p2_4->head != L1)
	{
		COORD R1_ = { 4,7 };
		SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), R1_);
		printf("      ");
	}
	if (p1_1->head != L2 && p1_2->head != L2 && p1_3->head != L2 && p1_4->head != L2 && p2_1->head != L2 && p2_2->head != L2 && p2_3->head != L2 && p2_4->head != L2)
	{
		COORD R1_ = { 4, 12 };
		SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), R1_);
		printf("      ");
	}
	if (p1_1->head != L3 && p1_2->head != L3 && p1_3->head != L3 && p1_4->head != L3 && p2_1->head != L3 && p2_2->head != L3 && p2_3->head != L3 && p2_4->head != L3)
	{
		COORD R1_ = { 4, 17 };
		SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), R1_);
		printf("      ");
	}
	if (p1_1->head != L4 && p1_2->head != L4 && p1_3->head != L4 && p1_4->head != L4 && p2_1->head != L4 && p2_2->head != L4 && p2_3->head != L4 && p2_4->head != L4)
	{
		COORD R1_ = { 4, 22 };
		SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), R1_);
		printf("      ");
	}
	if (p1_1->head != E3 && p1_2->head != E3 && p1_3->head != E3 && p1_4->head != E3 && p2_1->head != E3 && p2_2->head != E3 && p2_3->head != E3 && p2_4->head != E3)
	{
		COORD R1_ = { 4, 27 };
		SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), R1_);
		printf("      ");
	}

	//아래
	if (p1_1->head != B1 && p1_2->head != B1 && p1_3->head != B1 && p1_4->head != B1 && p2_1->head != B1 && p2_2->head != B1 && p2_3->head != B1 && p2_4->head != B1)
	{
		COORD R1_ = { 18,27 };
		SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), R1_);
		printf("      ");
	}
	if (p1_1->head != B2 && p1_2->head != B2 && p1_3->head != B2 && p1_4->head != B2 && p2_1->head != B2 && p2_2->head != B2 && p2_3->head != B2 && p2_4->head != B2)
	{
		COORD R1_ = { 32, 27 };
		SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), R1_);
		printf("      ");
	}
	if (p1_1->head != B3 && p1_2->head != B3 && p1_3->head != B3 && p1_4->head != B3 && p2_1->head != B3 && p2_2->head != B3 && p2_3->head != B3 && p2_4->head != B3)
	{
		COORD R1_ = { 46, 27 };
		SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), R1_);
		printf("      ");
	}
	if (p1_1->head != B4 && p1_2->head != B4 && p1_3->head != B4 && p1_4->head != B4 && p2_1->head != B4 && p2_2->head != B4 && p2_3->head != B4 && p2_4->head != B4)
	{
		COORD R1_ = { 60, 27 };
		SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), R1_);
		printf("      ");
	}
	if (p1_1->head != LAST && p1_2->head != LAST && p1_3->head != LAST && p1_4->head != LAST && p2_1->head != LAST && p2_2->head != LAST && p2_3->head != LAST && p2_4->head != LAST)
	{
		COORD R1_ = { 74, 27 };
		SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), R1_);
		printf("      ");
	}

	//중앙 상단
	if (p1_1->head != RH1 && p1_2->head != RH1 && p1_3->head != RH1 && p1_4->head != RH1 && p2_1->head != RH1 && p2_2->head != RH1 && p2_3->head != RH1 && p2_4->head != RH1)
	{
		COORD R1_ = { 62, 6 };
		SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), R1_);
		printf("      ");
	}
	if (p1_1->head != RH2 && p1_2->head != RH2 && p1_3->head != RH2 && p1_4->head != RH2 && p2_1->head != RH2 && p2_2->head != RH2 && p2_3->head != RH2 && p2_4->head != RH2)
	{
		COORD R1_ = { 50,10 };
		SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), R1_);
		printf("      ");
	}
	if (p1_1->head != LH1 && p1_2->head != LH1 && p1_3->head != LH1 && p1_4->head != LH1 && p2_1->head != LH1 && p2_2->head != LH1 && p2_3->head != LH1 && p2_4->head != LH1)
	{
		COORD R1_ = { 16, 6 };
		SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), R1_);
		printf("      ");
	}
	if (p1_1->head != LH2 && p1_2->head != LH2 && p1_3->head != LH2 && p1_4->head != LH2 && p2_1->head != LH2 && p2_2->head != LH2 && p2_3->head != LH2 && p2_4->head != LH2)
	{
		COORD R1_ = { 28, 10 };
		SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), R1_);
		printf("      ");
	}
	if (p1_1->head != CENTER && p1_2->head != CENTER && p1_3->head != CENTER && p1_4->head != CENTER && p2_1->head != CENTER && p2_2->head != CENTER && p2_3->head != CENTER && p2_4->head != CENTER)
	{
		COORD R1_ = { 40, 14 };
		SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), R1_);
		printf("      ");
	}


	//중앙 하단
	if (p1_1->head != LB1 && p1_2->head != LB1 && p1_3->head != LB1 && p1_4->head != LB1 && p2_1->head != LB1 && p2_2->head != LB1 && p2_3->head != LB1 && p2_4->head != LB1)
	{
		COORD R1_ = { 28,18 };
		SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), R1_);
		printf("      ");
	}
	if (p1_1->head != LB2 && p1_2->head != LB2 && p1_3->head != LB2 && p1_4->head != LB2 && p2_1->head != LB2 && p2_2->head != LB2 && p2_3->head != LB2 && p2_4->head != LB2)
	{
		COORD R1_ = { 16, 22 };
		SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), R1_);
		printf("      ");
	}
	if (p1_1->head != RB1 && p1_2->head != RB1 && p1_3->head != RB1 && p1_4->head != RB1 && p2_1->head != RB1 && p2_2->head != RB1 && p2_3->head != RB1 && p2_4->head != RB1)
	{
		COORD R1_ = { 52,18 };
		SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), R1_);
		printf("      ");
	}
	if (p1_1->head != RB2 && p1_2->head != RB2 && p1_3->head != RB2 && p1_4->head != RB2 && p2_1->head != RB2 && p2_2->head != RB2 && p2_3->head != RB2 && p2_4->head != RB2)
	{
		COORD R1_ = { 62, 23 };
		SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), R1_);
		printf("      ");
	}
}

LinkedList_h* moveHorse(LinkedList_h *head, char *yut) //말 이동 함수 p1_1 형태로 매개변수 넣을것
{
	LinkedList_h *newList;
	newList = head;
	int num;
	newList->stopNum = 0; // 움직이는 동안에는 동적인 상태로 두어 상대말 못잡게함

	if (!strcmp(yut, "backDo")) //백도일 때 한칸 뒤로
	{
		newList->head = newList->head->pre;
	}
	else
	{
		if (!strcmp(yut, "do"))
		{
			num = 1;
		}
		else if (!strcmp(yut, "gae"))
		{
			num = 2;
		}
		else if (!strcmp(yut, "girl"))
		{
			num = 3;
		}
		else if (!strcmp(yut, "yut"))
		{
			num = 4;
		}
		else if (!strcmp(yut, "mo"))
		{
			num = 5;
		}

		if (newList->check == 0)
		{
			if (newList->head == RH1)
			{
				if (num > 2) // E1에서 중앙으로 향할시 올바른 길로 향하도록 따로 써줌
				{
					newList->head = newList->head->next;
					newList->head = newList->head->next;
					newList->head = newList->head->another;
					for (int i = 0; i < num - 3; i++)
					{
						newList->head = newList->head->next;
					}
				}
				else
				{
					for (int i = 0; i < num; i++)
					{
						newList->head = newList->head->next;
					}
					if (newList->head == E1 || newList->head == E2 || newList->head == CENTER) //특이지점에서 멈췄을 때
					{
						newList->check = 1;
					}
				}
			}
			else if (newList->head == RH2)
			{
				if (num > 1) // E1에서 중앙으로 향할시 올바른 길로 향하도록 따로 써줌
				{
					newList->head = newList->head->next;
					newList->head = newList->head->another;
					for (int i = 0; i < num - 2; i++)
					{
						newList->head = newList->head->next;
					}
				}
				else
				{
					for (int i = 0; i < num; i++)
					{
						newList->head = newList->head->next;
					}
					if (newList->head == E1 || newList->head == E2 || newList->head == CENTER) //특이지점에서 멈췄을 때
					{
						newList->check = 1;
					}
				}
			}
			else
			{
				for (int i = 0; i < num; i++)
				{
					newList->head = newList->head->next;
				}
				if (newList->head == E1 || newList->head == E2 || newList->head == CENTER) //특이지점에서 멈췄을 때
				{
					newList->check = 1;
				}

			}
		}
		else //newList->check==1일 때  ->말이 멈춘 장소가 가장자리나 중앙자리일 때
		{
			if (newList->head == E1)
			{
				if (num > 3) // E1에서 중앙으로 향할시 올바른 길로 향하도록 따로 써줌
				{
					newList->head = newList->head->another;
					newList->head = newList->head->next;
					newList->head = newList->head->next;
					newList->head = newList->head->another;
					for (int i = 0; i < num - 4; i++)
					{
						newList->head = newList->head->next;
					}

				}
				else
				{
					newList->head = newList->head->another;
					for (int i = 0; i < num - 1; i++)
					{
						newList->head = newList->head->next;
					}
				}
			}
			else if (newList->head == CENTER)
			{
				for (int i = 0; i < num; i++)
				{
					newList->head = newList->head->next;
				}
			}
			else
			{
				newList->head = newList->head->another;

				for (int i = 0; i < num - 1; i++)
				{
					newList->head = newList->head->next;
				}
			}

			if (newList->head == E1 || newList->head == E2 || newList->head == CENTER) //특이지점에서 멈췄을 때
			{
				newList->check = 1;
			}
			else
			{
				newList->check = 0;
			}

		}

		if (p1_1->head == Destination) //p1_2->head == Destination || p1_3->head == Destination || p1_4->head == Destination)
		{
			myCount1 = 1; //4 되면 승리하는 조건함수 소스파일에 필요
		}
		if (p1_2->head == Destination)
		{
			myCount2 = 1;
		}
		if (p1_3->head == Destination)
		{
			myCount3 = 1;
		}
		if (p1_4->head == Destination)
		{
			myCount4 = 1;
		}

		if (p2_1->head == Destination) //p1_2->head == Destination || p1_3->head == Destination || p1_4->head == Destination)
		{
			yourCount1 = 1; //4 되면 승리하는 조건함수 소스파일에 필요
		}
		if (p2_2->head == Destination)
		{
			yourCount2 = 1;
		}
		if (p2_3->head == Destination)
		{
			yourCount3 = 1;
		}
		if (p2_4->head == Destination)
		{
			yourCount4 = 1;
		}
		myCount = myCount1 + myCount2 + myCount3 + myCount4;
		yourCount = yourCount1 + yourCount2 + yourCount3 + yourCount4;

		newList->stopNum = 1; //말이 움직일만큼 다 움직인다음에 정적상태로 두며 이때 말을 잡거나 말이 잡힌다
	}
	return newList;
}


void catchHorse(int playerNum)   // 같은 공간 상대말 잡는 함수   x->stopNum=0 이면 동적상태로 말을 잡거나 잡지못하고, 1이면 정적상태도 말을 잡거나 잡힐 수 있다
{

	if (p1_1->head != Destination && p2_1->head != Destination) //도착지에 있는 말은 못잡도록 제한
	{
		//p1_1 경우
		if ((p1_1->stopNum == 1 && p2_1->stopNum == 1) && (p1_1->head == p2_1->head))
		{
			if (playerNum == 1)
			{
				p2_1->head = Start2;
				p2_1->check = 0;
			}
			else if (playerNum == 0)
			{
				p1_1->head = Start1;
				p1_1->check = 0;
			}
		}
	}

	if (p1_1->head != Destination && p2_2->head != Destination)
	{
		if ((p1_1->stopNum == 1 && p2_2->stopNum == 1) && (p1_1->head == p2_2->head))
		{
			if (playerNum == 1)
			{
				p2_2->head = Start2;
				p2_2->check = 0;
			}
			else if (playerNum == 0)
			{
				p1_1->head = Start1;
				p1_1->check = 0;
			}
		}
	}


	if (p1_1->head != Destination && p2_3->head != Destination)
	{
		if ((p1_1->stopNum == 1 && p2_3->stopNum == 1) && (p1_1->head == p2_3->head))
		{
			if (playerNum == 1)
			{
				p2_3->head = Start2;
				p2_3->check = 0;
			}
			else if (playerNum == 0)
			{
				p1_1->head = Start1;
				p1_1->check = 0;
			}
		}
	}


	if (p1_1->head != Destination && p2_4->head != Destination)
	{
		if ((p1_1->stopNum == 1 && p2_4->stopNum == 1) && (p1_1->head == p2_4->head))
		{
			if (playerNum == 1)
			{
				p2_4->head = Start2;
				p2_4->check = 0;
			}
			else if (playerNum == 0)
			{
				p1_1->head = Start1;
				p1_1->check = 0;
			}
		}
	}

	//p1_2 경우
	if (p1_2->head != Destination && p2_1->head != Destination)
	{
		if ((p1_2->stopNum == 1 && p2_1->stopNum == 1) && (p1_2->head == p2_1->head))
		{
			if (playerNum == 1)
			{
				p2_1->head = Start2;
				p2_1->check = 0;
			}
			else if (playerNum == 0)
			{
				p1_2->head = Start1;
				p1_2->check = 0;
			}
		}
	}

	if (p1_2->head != Destination && p2_2->head != Destination)
	{
		if ((p1_2->stopNum == 1 && p2_2->stopNum == 1) && (p1_2->head == p2_2->head))
		{
			if (playerNum == 1)
			{
				p2_2->head = Start2;
				p2_2->check = 0;
			}
			else if (playerNum == 0)
			{
				p1_2->head = Start1;
				p1_2->check = 0;
			}
		}
	}

	if (p1_2->head != Destination && p2_3->head != Destination)
	{
		if ((p1_2->stopNum == 1 && p2_3->stopNum == 1) && (p1_2->head == p2_3->head))
		{
			if (playerNum == 1)
			{
				p2_3->head = Start2;
				p2_3->check = 0;
			}
			else if (playerNum == 0)
			{
				p1_2->head = Start1;
				p1_2->check = 0;
			}
		}
	}

	if (p1_2->head != Destination && p2_4->head != Destination)
	{
		if ((p1_2->stopNum == 1 && p2_4->stopNum == 1) && (p1_2->head == p2_4->head))
		{
			if (playerNum == 1)
			{
				p2_4->head = Start2;
				p2_4->check = 0;
			}
			else if (playerNum == 0)
			{
				p1_2->head = Start1;
				p1_2->check = 0;
			}
		}
	}


	//p1_3경우
	if (p1_3->head != Destination && p2_1->head != Destination)
	{
		if ((p1_3->stopNum == 1 && p2_1->stopNum == 1) && (p1_3->head == p2_1->head))
		{
			if (playerNum == 1)
			{
				p2_1->head = Start2;
				p2_1->check = 0;
			}
			else if (playerNum == 0)
			{
				p1_3->head = Start1;
				p1_3->check = 0;
			}
		}
	}

	if (p1_3->head != Destination && p2_2->head != Destination)
	{
		if ((p1_3->stopNum == 1 && p2_2->stopNum == 1) && (p1_3->head == p2_2->head))
		{
			if (playerNum == 1)
			{
				p2_2->head = Start2;
				p2_2->check = 0;
			}
			else if (playerNum == 0)
			{
				p1_3->head = Start1;
				p1_3->check = 0;
			}
		}
	}

	if (p1_3->head != Destination && p2_3->head != Destination)
	{
		if ((p1_3->stopNum == 1 && p2_3->stopNum == 1) && (p1_3->head == p2_3->head))
		{
			if (playerNum == 1)
			{
				p2_3->head = Start2;
				p2_3->check = 0;
			}
			else if (playerNum == 0)
			{
				p1_3->head = Start1;
				p1_3->check = 0;
			}
		}
	}

	if (p1_3->head != Destination && p2_4->head != Destination)
	{
		if ((p1_3->stopNum == 1 && p2_4->stopNum == 1) && (p1_3->head == p2_4->head))
		{
			if (playerNum == 1)
			{
				p2_4->head = Start2;
				p2_4->check = 0;
			}
			else if (playerNum == 0)
			{
				p1_3->head = Start1;
				p1_3->check = 0;
			}
		}
	}

	//p1_4경우
	if (p1_4->head != Destination && p2_1->head != Destination)
	{
		if ((p1_4->stopNum == 1 && p2_1->stopNum == 1) && (p1_4->head == p2_1->head))
		{
			if (playerNum == 1)
			{
				p2_1->head = Start2;
				p2_1->check = 0;
			}
			else if (playerNum == 0)
			{
				p1_4->head = Start1;
				p1_4->check = 0;
			}
		}
	}

	if (p1_4->head != Destination && p2_2->head != Destination)
	{
		if ((p1_4->stopNum == 1 && p2_2->stopNum == 1) && (p1_4->head == p2_2->head))
		{
			if (playerNum == 1)
			{
				p2_2->head = Start2;
				p2_2->check = 0;
			}
			else if (playerNum == 0)
			{
				p1_4->head = Start1;
				p1_4->check = 0;
			}
		}
	}

	if (p1_4->head != Destination && p2_3->head != Destination)
	{
		if ((p1_4->stopNum == 1 && p2_3->stopNum == 1) && (p1_4->head == p2_3->head))
		{
			if (playerNum == 1)
			{
				p2_3->head = Start2;
				p2_3->check = 0;
			}
			else if (playerNum == 0)
			{
				p1_4->head = Start1;
				p1_4->check = 0;
			}
		}
	}


	if (p1_4->head != Destination && p2_4->head != Destination)
	{
		if ((p1_4->stopNum == 1 && p2_4->stopNum == 1) && (p1_4->head == p2_4->head))
		{
			if (playerNum == 1)
			{
				p2_4->head = Start2;
				p2_4->check = 0;
			}
			else if (playerNum == 0)
			{
				p1_4->head = Start1;
				p1_4->check = 0;
			}
		}
	}

}

void yutShape(char *yut) // 나온 윷에 따라 윷모양 조정
{
	if (!strcmp(yut, "backDo")) //뒷도
	{
		COORD SE1 = { 108, 14 };
		COORD SE2 = { 108, 15 };
		COORD SE3 = { 108, 16 };
		COORD SE4 = { 108, 17 };
		SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), SE1);
		printf("■");
		SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), SE2);
		printf("X");
		SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), SE3);
		printf("X");
		SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), SE4);
		printf("■");

		COORD SW1 = { 96, 14 };
		COORD SW2 = { 96, 15 };
		COORD SW3 = { 96, 16 };
		COORD SW4 = { 96, 17 };
		SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), SW1);
		printf("■");
		SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), SW2);
		printf("X");
		SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), SW3);
		printf("X");
		SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), SW4);
		printf("■");


		COORD NW1 = { 96, 5 };
		COORD NW2 = { 96, 6 };
		COORD NW3 = { 96, 7 };
		COORD NW4 = { 96, 8 };
		SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), NW1);
		printf("■");
		SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), NW2);
		printf("X");
		SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), NW3);
		printf("X");
		SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), NW4);
		printf("■");

		COORD NE1 = { 108, 5 };
		COORD NE2 = { 108, 6 };
		COORD NE3 = { 108, 7 };
		COORD NE4 = { 108, 8 };
		SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), NE1);
		printf("B");
		SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), NE2);
		printf("A");
		SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), NE3);
		printf("C");
		SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), NE4);
		printf("K");

	}
	else if (!strcmp(yut, "do")) //도
	{
		COORD SE1 = { 108, 14 };
		COORD SE2 = { 108, 15 };
		COORD SE3 = { 108, 16 };
		COORD SE4 = { 108, 17 };
		SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), SE1);
		printf("  ");
		SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), SE2);
		printf("  ");
		SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), SE3);
		printf("  ");
		SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), SE4);
		printf("  ");

		COORD SW1 = { 96, 14 };
		COORD SW2 = { 96, 15 };
		COORD SW3 = { 96, 16 };
		COORD SW4 = { 96, 17 };
		SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), SW1);
		printf("■");
		SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), SW2);
		printf("X");
		SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), SW3);
		printf("X");
		SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), SW4);
		printf("■");


		COORD NW1 = { 96, 5 };
		COORD NW2 = { 96, 6 };
		COORD NW3 = { 96, 7 };
		COORD NW4 = { 96, 8 };
		SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), NW1);
		printf("■");
		SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), NW2);
		printf("X");
		SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), NW3);
		printf("X");
		SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), NW4);
		printf("■");

		COORD NE1 = { 108, 5 };
		COORD NE2 = { 108, 6 };
		COORD NE3 = { 108, 7 };
		COORD NE4 = { 108, 8 };
		SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), NE1);
		printf("■");
		SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), NE2);
		printf("X");
		SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), NE3);
		printf("X");
		SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), NE4);
		printf("■");

	}
	else if (!strcmp(yut, "gae")) //개
	{
		COORD SE1 = { 108, 14 };
		COORD SE2 = { 108, 15 };
		COORD SE3 = { 108, 16 };
		COORD SE4 = { 108, 17 };
		SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), SE1);
		printf("  ");
		SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), SE2);
		printf("  ");
		SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), SE3);
		printf("  ");
		SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), SE4);
		printf("  ");

		COORD SW1 = { 96, 14 };
		COORD SW2 = { 96, 15 };
		COORD SW3 = { 96, 16 };
		COORD SW4 = { 96, 17 };
		SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), SW1);
		printf("  ");
		SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), SW2);
		printf("  ");
		SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), SW3);
		printf("  ");
		SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), SW4);
		printf("  ");


		COORD NW1 = { 96, 5 };
		COORD NW2 = { 96, 6 };
		COORD NW3 = { 96, 7 };
		COORD NW4 = { 96, 8 };
		SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), NW1);
		printf("■");
		SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), NW2);
		printf("X");
		SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), NW3);
		printf("X");
		SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), NW4);
		printf("■");

		COORD NE1 = { 108, 5 };
		COORD NE2 = { 108, 6 };
		COORD NE3 = { 108, 7 };
		COORD NE4 = { 108, 8 };
		SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), NE1);
		printf("■");
		SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), NE2);
		printf("X");
		SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), NE3);
		printf("X");
		SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), NE4);
		printf("■");
	}
	else if (!strcmp(yut, "girl")) //걸
	{
		COORD SE1 = { 108, 14 };
		COORD SE2 = { 108, 15 };
		COORD SE3 = { 108, 16 };
		COORD SE4 = { 108, 17 };
		SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), SE1);
		printf("  ");
		SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), SE2);
		printf("  ");
		SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), SE3);
		printf("  ");
		SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), SE4);
		printf("  ");

		COORD SW1 = { 96, 14 };
		COORD SW2 = { 96, 15 };
		COORD SW3 = { 96, 16 };
		COORD SW4 = { 96, 17 };
		SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), SW1);
		printf("  ");
		SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), SW2);
		printf("  ");
		SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), SW3);
		printf("  ");
		SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), SW4);
		printf("  ");


		COORD NW1 = { 96, 5 };
		COORD NW2 = { 96, 6 };
		COORD NW3 = { 96, 7 };
		COORD NW4 = { 96, 8 };
		SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), NW1);
		printf("  ");
		SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), NW2);
		printf("  ");
		SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), NW3);
		printf("  ");
		SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), NW4);
		printf("  ");

		COORD NE1 = { 108, 5 };
		COORD NE2 = { 108, 6 };
		COORD NE3 = { 108, 7 };
		COORD NE4 = { 108, 8 };
		SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), NE1);
		printf("■");
		SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), NE2);
		printf("X");
		SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), NE3);
		printf("X");
		SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), NE4);
		printf("■");
	}
	else if (!strcmp(yut, "yut")) //윷
	{
		COORD SE1 = { 108, 14 };
		COORD SE2 = { 108, 15 };
		COORD SE3 = { 108, 16 };
		COORD SE4 = { 108, 17 };
		SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), SE1);
		printf("  ");
		SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), SE2);
		printf("  ");
		SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), SE3);
		printf("  ");
		SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), SE4);
		printf("  ");

		COORD SW1 = { 96, 14 };
		COORD SW2 = { 96, 15 };
		COORD SW3 = { 96, 16 };
		COORD SW4 = { 96, 17 };
		SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), SW1);
		printf("  ");
		SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), SW2);
		printf("  ");
		SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), SW3);
		printf("  ");
		SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), SW4);
		printf("  ");


		COORD NW1 = { 96, 5 };
		COORD NW2 = { 96, 6 };
		COORD NW3 = { 96, 7 };
		COORD NW4 = { 96, 8 };
		SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), NW1);
		printf("  ");
		SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), NW2);
		printf("  ");
		SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), NW3);
		printf("  ");
		SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), NW4);
		printf("  ");

		COORD NE1 = { 108, 5 };
		COORD NE2 = { 108, 6 };
		COORD NE3 = { 108, 7 };
		COORD NE4 = { 108, 8 };
		SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), NE1);
		printf("  ");
		SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), NE2);
		printf("  ");
		SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), NE3);
		printf("  ");
		SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), NE4);
		printf("  ");
	}
	else if (!strcmp(yut, "mo")) //모
	{
		COORD SE1 = { 108, 14 };
		COORD SE2 = { 108, 15 };
		COORD SE3 = { 108, 16 };
		COORD SE4 = { 108, 17 };
		SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), SE1);
		printf("■");
		SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), SE2);
		printf("X");
		SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), SE3);
		printf("X");
		SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), SE4);
		printf("■");

		COORD SW1 = { 96, 14 };
		COORD SW2 = { 96, 15 };
		COORD SW3 = { 96, 16 };
		COORD SW4 = { 96, 17 };
		SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), SW1);
		printf("■");
		SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), SW2);
		printf("X");
		SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), SW3);
		printf("X");
		SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), SW4);
		printf("■");


		COORD NW1 = { 96, 5 };
		COORD NW2 = { 96, 6 };
		COORD NW3 = { 96, 7 };
		COORD NW4 = { 96, 8 };
		SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), NW1);
		printf("■");
		SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), NW2);
		printf("X");
		SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), NW3);
		printf("X");
		SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), NW4);
		printf("■");

		COORD NE1 = { 108, 5 };
		COORD NE2 = { 108, 6 };
		COORD NE3 = { 108, 7 };
		COORD NE4 = { 108, 8 };
		SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), NE1);
		printf("■");
		SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), NE2);
		printf("X");
		SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), NE3);
		printf("X");
		SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), NE4);
		printf("■");
	}
}

void printList(LinkedList_h *head) //이중연결리스트 확인용 출력 함수
{
	ListNode *p;
	int i = 0;
	printf("DL = (");
	p = head->head;
	while (p != LAST) {
		printf("%d. %s \n ", i + 1, p->data);
		p = p->next;
		i++;
	}
	printf("\n");
}
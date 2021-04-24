/*
 *  doubly-linked-list.c
 *
 *  Doubly Linked List
 *
 *  Data Structures
 *  Department of Computer Science
 *  at Chungbuk National University
 *
 */



#include<stdio.h>
#include<stdlib.h>
 /* 필요한 헤더파일 추가 if necessary */


typedef struct Node {
	int key; //노드의 값을 저장하는 key 선언
	struct Node* llink; //전위 노드를 가리키는 포인터형 link 선언
	struct Node* rlink; //후위 노드를 가리키는 포인터형 link 선언
} listNode; //노드를 생성하기 위한 구조체 Node 선언 후 listNode로 재정의



typedef struct Head {
	struct Node* first; //리스트의 맨 앞 노드를 가리키는 포인터형 first 선언
}headNode; //리스트의 맨 앞을 가리키기 위한 구조체 Head 선언 후 headNode로 재정의

/* 함수 리스트 */

/* note: initialize는 이중포인터를 매개변수로 받음
		 singly-linked-list의 initialize와 차이점을 이해 할것 */
int initialize(headNode** h); //리스트를 생성하거나 초기화하는 intialize 함수 선언

/* note: freeList는 싱글포인터를 매개변수로 받음
		- initialize와 왜 다른지 이해 할것
		- 이중포인터를 매개변수로 받아도 해제할 수 있을 것 */
int freeList(headNode* h); //리스트의 모든 노드에 대해 메모리를 해제하는 freeList 함수 선언

int insertNode(headNode* h, int key);
int insertLast(headNode* h, int key);
int insertFirst(headNode* h, int key);
int deleteNode(headNode* h, int key);
int deleteLast(headNode* h);
int deleteFirst(headNode* h);
int invertList(headNode* h);

void printList(headNode* h);


int main()
{
	char command;
	int key;
	headNode* headnode = NULL;

	do {
		printf("----------------------------------------------------------------\n");
		printf("                     Doubly Linked  List                        \n");
		printf("----------------------------------------------------------------\n");
		printf(" Initialize    = z           Print         = p \n");
		printf(" Insert Node   = i           Delete Node   = d \n");
		printf(" Insert Last   = n           Delete Last   = e\n");
		printf(" Insert First  = f           Delete First  = t\n");
		printf(" Invert List   = r           Quit          = q\n");
		printf("----------------------------------------------------------------\n");

		printf("Command = ");
		scanf(" %c", &command);

		switch (command) {
		case 'z': case 'Z':
			initialize(&headnode);
			break;
		case 'p': case 'P':
			printList(headnode);
			break;
		case 'i': case 'I':
			printf("Your Key = ");
			scanf("%d", &key);
			insertNode(headnode, key);
			break;
		case 'd': case 'D':
			printf("Your Key = ");
			scanf("%d", &key);
			deleteNode(headnode, key);
			break;
		case 'n': case 'N':
			printf("Your Key = ");
			scanf("%d", &key);
			insertLast(headnode, key);
			break;
		case 'e': case 'E':
			deleteLast(headnode);
			break;
		case 'f': case 'F':
			printf("Your Key = ");
			scanf("%d", &key);
			insertFirst(headnode, key);
			break;
		case 't': case 'T':
			deleteFirst(headnode);
			break;
		case 'r': case 'R':
			invertList(headnode);
			break;
		case 'q': case 'Q':
			freeList(headnode);
			break;
		default:
			printf("\n       >>>>>   Concentration!!   <<<<<     \n");
			break;
		}

	} while (command != 'q' && command != 'Q');

	return 1;
}


int initialize(headNode** h) {
	/*if (*h != NULL)
		freelist(*h);*/ //컴파일 오류 발생
	//headNode가 NULL이 아니면 freelist를 호출하여 할당된 메모리 모두 삭제

	headNode* temp = (headNode*)malloc(sizeof(headNode)); //headNode에 대한 메모리 할당
	temp->first = NULL; //첫 번째 노드가 NULL이 되도록 설정
	*h = temp; //리스트의 첫 번째 노드가 temp가 되도록 함

	return 1;
}

int freeList(headNode* h) {
	listNode* p = h->first; //포인터 p 선언 후 리스트의 맨 앞 노드를 가리키도록 초기화
	while (p->rlink) //후위 노드가 NULL일 때, 즉 리스트의 맨 끝에 도달할 때까지 반복
	{
		p = p->rlink; //p가 후위 노드를 가리킴
		free(p->llink); //p가 가리키는 노드의 전위 노드의 메모리 해제
	}
	free(h); //리스트의 맨 앞 노드의 메모리 해제
	return 0; 
}


void printList(headNode* h) {
	int i = 0;
	listNode* p;

	printf("\n---PRINT\n");

	if (h == NULL) {
		printf("Nothing to print....\n");
		return;
	}

	p = h->first;

	while (p != NULL) {
		printf("[ [%d]=%d ] ", i, p->key);
		p = p->rlink;
		i++;
	}

	printf("  items = %d\n", i);
}




/**
 * list에 key에 대한 노드하나를 추가
 */
int insertLast(headNode* h, int key) {


	return 0;
}



/**
 * list의 마지막 노드 삭제
 */
int deleteLast(headNode* h) {


	return 0;
}



/**
 * list 처음에 key에 대한 노드하나를 추가
 */
int insertFirst(headNode* h, int key) {
	return 0;
}

/**
 * list의 첫번째 노드 삭제
 */
int deleteFirst(headNode* h) {

	return 0;
}



/**
 * 리스트의 링크를 역순으로 재 배치
 */
int invertList(headNode* h) {

	return 0;
}



/* 리스트를 검색하여, 입력받은 key보다 큰값이 나오는 노드 바로 앞에 삽입 */
int insertNode(headNode* h, int key) {
	listNode* temp = h->first; //입력받은 key와 값을 비교할 노드를 가리키는 포인터 temp 선언 후 리스트의 맨 앞을 가리키도록 초기화
	listNode* insert = (listNode*)malloc(sizeof(listNode)); //입력받은 key 값을 리스트에 삽입하도록 insert 포인터 생성 후 메모리 할당
	insert->key = key; //입력받은 key 값을 insert의 key에 저장
	if (!h->first || temp->key > insert->key) //리스트가 비어있거나 key가 맨앞에 위치해야할 때
	{
		insertFirst(h, key); //리스트의 맨 앞에 key를 삽입하는 것과 같으므로 insertFirst 함수 호출
	}
	else //리스트가 비어있지 않을 때
	{
		while (temp != NULL)//리스트의 끝인 NULL이 되기 전까지 반복문 실행
		{
			if (temp->key > insert->key) //입력받은 key보다 큰 값이 나오는 노드를 발견
			{
				insert->rlink = temp; //insert의 오른쪽에 temp가 올 수 있도록 변경
				insert->llink = temp->llink;//insert의 왼쪽에 temp의 전위 노드가 올 수 있도록 변경
				temp->llink->rlink = insert; //temp의 전위 노드 오른쪽에 insert가 올 수 있도록 변경 
				temp->llink = insert; //temp의 왼쪽에 insert가 올 수 있도록 변경
				return 0; //insert가 가리키는 노드를 리스트에 삽입하면 함수 종료
			}
			temp = temp->rlink; //temp가 다음 노드를 가리킴
		}
		temp->llink = insert; //입력받은 key보다 큰 값을 리스트에서 찾지 못하면 마지막 노드가 insert가 됨
		insert->rlink = NULL; //insert의 rlink가 NULL을 가리켜 리스트의 끝을 알림
	}

	return 0;
}


/**
 * list에서 key에 대한 노드 삭제
 */
int deleteNode(headNode* h, int key) {

	return 1;
}




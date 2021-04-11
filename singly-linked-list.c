/*
 * singly linked list
 *
 *  Data Structures
 *  Department of Computer Science
 *  at Chungbuk National University
 */


#include<stdio.h>
#include<stdlib.h>

 /* 필요한 헤더파일 추가 */

typedef struct Node {
	int key;
	struct Node* link;
} listNode;

typedef struct Head {
	struct Node* first;
}headNode;


/* 함수 리스트 */
headNode* initialize(headNode* h);
int freeList(headNode* h);

int insertFirst(headNode* h, int key);
int insertNode(headNode* h, int key);
int insertLast(headNode* h, int key);

int deleteFirst(headNode* h);
int deleteNode(headNode* h, int key);
int deleteLast(headNode* h);
int invertList(headNode* h);

void printList(headNode* h);

int main()
{
	char command;
	int key;
	headNode* headnode = NULL;

	printf("----- [이승현] [2020039075] -----\n");	

		do {
			printf("----------------------------------------------------------------\n");
			printf("                     Singly Linked List                         \n");
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
				headnode = initialize(headnode);
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

headNode* initialize(headNode* h) {

	/* headNode가 NULL이 아니면, freeNode를 호출하여 할당된 메모리 모두 해제 */
	if (h != NULL)
		freeList(h);

	/* headNode에 대한 메모리를 할당하여 리턴 */
	headNode* temp = (headNode*)malloc(sizeof(headNode));
	temp->first = NULL;
	return temp;
}

int freeList(headNode* h) {
	/* h와 연결된 listNode 메모리 해제
	 * headNode도 해제되어야 함.
	 */
	listNode* p = h->first;

	listNode* prev = NULL;
	while (p != NULL) {
		prev = p;
		p = p->link;
		free(prev);
	}
	free(h);
	return 0;
}



/**
 * list 처음에 key에 대한 노드하나를 추가
 */
int insertFirst(headNode* h, int key) {

	listNode* node = (listNode*)malloc(sizeof(listNode));
	node->key = key;

	node->link = h->first;
	h->first = node;

	return 0;
}


/* 리스트를 검색하여, 입력받은 key보다 큰 값이 나오는 노드 바로 앞에 삽입 */
int insertNode(headNode* h, int key) { 
	listNode* temp = h->first; //입력받은 key와 값을 비교할 노드를 가리키는 포인터 temp 선언 후 리스트의 맨 앞을 가리키도록 초기화
	listNode* trail = h->first; //key 값이 temp가 가리키는 노드의 앞에 배치되도록 temp의 선행 노드를 가리키는 포인터 trail 선언 후 리스트의 맨앞을 가리키도록 초기화
	listNode* insert = (listNode*)malloc(sizeof(listNode)); //입력받은 key 값을 리스트에 삽입하도록 insert 포인터 생성 후 메모리 할당
	insert->key = key; //key 값을 insert의 key에 저장
	if (!h->first || temp->key > insert->key) //리스트가 비어있거나 key가 맨앞에 위치해야할 때
	{
		insertFirst(h, key); //리스트의 맨 앞에 key를 삽입해야 하므로 insertFirst 함수 호출
	}
	else //해당 조건문을 만족시키지 못하였을 때
	{
		while (temp != NULL)//노드의 link가 리스트의 끝인 NULL을 가리키기 전까지 반복문 실행
		{
			if (temp->key > insert->key) //입력받은 key보다 큰 값이 나오는 노드를 발견
			{
				insert->link = temp; //insert의 link가 temp를 가리켜 insert의 값이 temp가 가리키는 노드 앞에 오도록 배치
				trail->link = insert;//이전 노드를 가리키는 trail의 link가 insert를 가리켜 insert 노드가 trail 노드 뒤에 오도록 배치
				return 0; //insert를 리스트에 삽입하면 함수 종료
			}
			trail = temp; //temp가 다음 노드를 가리키기 전 trail에 저장하여 trail을 temp의 선행 노드로 취급
			temp = temp->link; //temp가 다음 노드를 가리킴
		}
		trail->link = insert; //입력받은 key보다 큰 값을 리스트에서 찾지 못하면 마지막 노드를 가리키는 포인터 trail의 link가 insert를 가리킴
		insert->link = NULL; //insert의 link가 NULL을 가리켜 리스트의 끝을 알림
	}
	return 0; //insert가 가리키는 노드를 리스트에 삽입하면 함수 종료
}

/**
 * list에 key에 대한 노드하나를 추가
 */
int insertLast(headNode* h, int key) {
	listNode* temp = h->first; //현재 검토할 노드를 가리키는 포인터 temp 선언 후 리스트의 맨 앞을 가리키도록 초기화
	listNode* insert = (listNode*)malloc(sizeof(listNode)); //입력받은 key 값을 리스트에 삽입하도록 insert 포인터 생성 후 메모리 할당
	insert->key = key; //key 값을 insert의 key에 저장
	if (!h->first) //리스트가 비어있을 때
	{
		insertFirst(h, key); //리스트의 맨 앞에 key를 삽입하는 것과 같으므로 insertFirst 함수 호출
	}
	else //해당 조건문을 만족시키지 못하였을 때
	{
		while (temp->link) //temp가 가리키는 다음 노드가 NULL, 즉 리스트의 끝이 아닐 때
		{
			temp = temp->link; //temp가 다음 노드를 가리킴
		}
		insert->link = temp->link; //temp가 마지막 노드를 가리킬 때 while문 종료 후 insert의 link가 NULL을 가리켜  리스트의 끝을 알림
		temp->link = insert; //temp의 link는 insert가 가리키는 노드를 가리켜 temp 노드 뒤에 insert 노드가 오도록 함
	}
	return 0; //insert가 가리키는 노드를 리스트의 맨 뒤에 삽입하면 함수 종료
}


/**
 * list의 첫번째 노드 삭제
 */
int deleteFirst(headNode* h) {
	listNode* temp = h->first; //삭제할 노드를 가리키는 포인터 temp 선언 후 리스트의 맨 앞을 가리키도록 초기화
	h->first = temp->link; //리스트의 맨 앞 노드가 temp의 link가 가리키는 노드, 즉 2번째 노드를 가리키도록 하여 temp 노드를 리스트에서 삭제
	free(temp); //리스트의 첫 번째 노드 삭제 후 temp의 메모리 해제

	return 0; //temp가 가리키는 노드를 삭제하면 함수 종료
}


/**
 * list에서 key에 대한 노드 삭제
 */
int deleteNode(headNode* h, int key) {

	return 0;

}

/**
 * list의 마지막 노드 삭제
 */
int deleteLast(headNode* h) {

	return 0;
}


/**
 * 리스트의 링크를 역순으로 재 배치
 */
int invertList(headNode* h) {

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
		p = p->link;
		i++;
	}

	printf("  items = %d\n", i);
}


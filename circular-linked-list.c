/*
 *  doubly circular linked list
 *
 *  Data Structures
 *
 *  Department of Computer Science
 *  at Chungbuk National University
 *
 */



#include<stdio.h>
#include<stdlib.h>
 /* 필요한 헤더파일 추가 */

typedef struct Node {
	int key;
	struct Node* llink;
	struct Node* rlink;
} listNode;

/* 함수 리스트 */
int initialize(listNode** h);
int freeList(listNode* h);
int insertLast(listNode* h, int key);
int deleteLast(listNode* h);
int insertFirst(listNode* h, int key);
int deleteFirst(listNode* h);
int invertList(listNode* h);

int insertNode(listNode* h, int key);
int deleteNode(listNode* h, int key);

void printList(listNode* h);



int main()
{
	char command;
	int key;
	listNode* headnode = NULL;

	do {
		printf("----------------------------------------------------------------\n");
		printf("                  Doubly Circular Linked List                   \n");
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


int initialize(listNode** h) {

	/* headNode가 NULL이 아니면, freeNode를 호출하여 할당된 메모리 모두 해제 */
	if (*h != NULL)
		freeList(*h);

	/* headNode에 대한 메모리를 할당하여 리턴 */
	*h = (listNode*)malloc(sizeof(listNode));
	(*h)->rlink = *h;
	(*h)->llink = *h;
	(*h)->key = -9999;
	return 1;
}

/* 메모리 해제 */
int freeList(listNode* h) {
	listNode* temp = h; //메모리를 해제하고자하는 노드를 가리키는 temp 선언 후 리스트의 헤드 노드를 가리킴
	listNode* lastNode = h->llink; //마지막 노드를 가리키는 lastNode 선언 후 리스트의 마지막 노드를 가리킴
	while (temp != lastNode) //마지막 노드를 가리키기 전까지 반복
	{
		temp = temp->rlink; //temp는 다음 노드를 가리킴
		free(temp->llink); //이전 노드에 대한 메모리 해제
	}
	free(lastNode); //마지막 노드의 메모리 해제
	return 0;
}



void printList(listNode* h) {
	int i = 0;
	listNode* p;

	printf("\n---PRINT\n");

	if (h == NULL) {
		printf("Nothing to print....\n");
		return;
	}

	p = h->rlink;

	while (p != NULL && p != h) {
		printf("[ [%d]=%d ] ", i, p->key);
		p = p->rlink;
		i++;
	}
	printf("  items = %d\n", i);


	/* print addresses */
	printf("\n---checking addresses of links\n");
	printf("-------------------------------\n");
	printf("head node: [llink]=%p, [head]=%p, [rlink]=%p\n", h->llink, h, h->rlink);

	i = 0;
	p = h->rlink;
	while (p != NULL && p != h) {
		printf("[ [%d]=%d ] [llink]=%p, [node]=%p, [rlink]=%p\n", i, p->key, p->llink, p, p->rlink);
		p = p->rlink;
		i++;
	}

}



/**
 * list에 key에 대한 노드하나를 추가
 */
int insertLast(listNode* h, int key) {
	listNode* insert = (listNode*)malloc(sizeof(listNode)); //입력받은 key 값을 삽입하기 위한 포인터 insert 선언 후 메모리 할당
	insert->key = key; //입력받은 key 값을 insert의 key에 저장
	insert->llink = h->llink; //insert의 왼쪽 링크가 리스트의 마지막 노드를 가리킴
	insert->rlink = h; //insert의 오른쪽 링크가 헤드 노드를 가리킴
	h->llink->rlink = insert; //리스트의 마지막 노드의 오른쪽 링크가 insert를 가리킴
	h->llink = insert; //헤드 노드의 왼쪽 링크가 insert를 가리키면 (삽입 전 마지막 노드)-insert-h 순으로 배치
	return 1;
}


/**
 * list의 마지막 노드 삭제
 */
int deleteLast(listNode* h) {
	if (h->rlink == h) //리스트가 비어있을 때
	{
		printf("List is empty!\n"); //리스트가 비어있다는 오류 메세지 출력
	}
	else //리스트가 비어있지 않을 때
	{
		listNode* delete = h->llink; //노드를 삭제하기 위한 포인터 delete 선언 후 마지막 노드를 가리키도록 초기화
		delete->llink->rlink = h; //delete의 왼쪽 노드의 오른쪽 링크가 헤드 노드를 가리킴
		h->llink = delete->llink; //헤드 노드의 왼쪽 링크가 delete의 왼쪽 노드를 가리키면 (삭제 전 delete의 왼쪽 노드)-h 순으로 배치
		free(delete); //delete가 가리키는 노드의 메모리 해제
	}
	return 1;
}


/**
 * list 처음에 key에 대한 노드하나를 추가
 */
int insertFirst(listNode* h, int key) {
	listNode* insert = (listNode*)malloc(sizeof(listNode)); //입력받은 key 값을 삽입하기 위한 포인터 insert 선언 후 메모리 할당
	insert->key = key; //입력받은 key 값을 insert의 key에 저장
	insert->llink = h; //insert의 왼쪽 링크가 리스트의 헤드 노드를 가리키도록 함
	insert->rlink = h->rlink; //insert의 오른쪽 링크가 헤드 노드를 제외한 첫 번째 노드를 가리키도록 함
	h->rlink->llink = insert; //헤드 노드를 제외한 첫 번째 노드의 왼쪽 링크가 insert를 가리키도록 함
	h->rlink = insert; //헤드 노드의 오른쪽 링크가 insert를 가리키면 h-insert-(삽입 전 h의 왼쪽 노드) 순으로 배치
	return 1;
}

/**
 * list의 첫번째 노드 삭제
 */
int deleteFirst(listNode* h) {
	if (h->rlink == h) //리스트가 비어있을 때
	{
		printf("List is empty!\n"); //리스트가 비어있다는 오류 메세지 출력
	}
	else //리스트가 비어있지 않을 때
	{
		listNode* delete = h->rlink; //노드를 삭제하기 위한 포인터 delete 선언 후 헤드 노드를 제외한 첫 번째 노드를 가리키도록 초기화
		delete->rlink->llink = h;  //delete의 오른쪽 노드의 왼쪽 링크가 헤드 노드를 가리킴
		h->rlink = delete->rlink; //헤드 노드의 오른쪽 링크가 delete의 오른쪽 노드를 가리키면 h-(삭제 전 delete의 오른쪽 노드) 순으로 배치
		free(delete); //delete가 가리키는 노드의 메모리 해제
	}
	return 1;
}


/**
 * 리스트의 링크를 역순으로 재 배치
 */
int invertList(listNode* h) {


	return 0;
}



/**
 *  리스트를 검색하여, 입력받은 key보다 큰값이 나오는 노드 바로 앞에 삽입
 **/
int insertNode(listNode* h, int key) {
	listNode* temp = h->rlink; //비교할 노드를 가리키는 포인터 temp 선언 후 헤드 노드를 제외한 첫 번째 노드를 가리키도록 초기화
	listNode* insert = (listNode*)malloc(sizeof(listNode)); //입력받은 key 값을 삽입하기 위한 포인터 insert 선언 후 메모리 할당
	insert->key = key; //입력받은 key 값을 insert의 key에 저장
	if (h->rlink == h) //리스트에 헤드 노드만 존재할 때
	{
		insertFirst(h, key);
	}
	else //리스트에 헤드 노드 이외의 노드가 존재할 때
	{
		while (temp != h) //temp를 이용하여 insert 노드를 마지막 노드와 비교 완료 할 때까지 반복
		{
			if (temp->key > insert->key) //입력받은 key보다 큰 값이 나오는 노드를 발견
			{
				insert->llink = temp->llink; //insert의 왼쪽 링크가 temp의 왼쪽 노드를 가리킴
				insert->rlink = temp; //insert의 오른쪽 링크가 temp를 가리킴
				temp->llink->rlink = insert; //temp의 왼쪽 노드의 오른쪽 링크가 insert를 가리킴
				temp->llink = insert; //temp의 왼쪽 노드가 insert를 가리키면 (삽입 전 temp의 왼쪽 노드)-insert-temp 순으로 배치
				return 0; //새 노드를 리스트에 삽입하면 함수 종료
			}
			temp = temp->rlink; //temp가 다음 노드를 가리킴
		}
		insertLast(h, key); //입력받은 key보다 큰 값을 리스트에서 찾지 못하면 insert 노드를 리스트의 끝에 배치
	}
	return 0;
}


/**
 * list에서 key에 대한 노드 삭제
 */
int deleteNode(listNode* h, int key) {

	return 0;
}


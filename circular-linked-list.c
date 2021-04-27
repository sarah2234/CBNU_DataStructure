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
	int key; //노드의 값을 저장하는 key 선언
	struct Node* llink; //전위 노드를 가리키는 포인터형 llink 선언
	struct Node* rlink; //후위 노드를 가리키는 포인터형 rlink 선언
} listNode; //노드를 생성하기 위한 구조체 Node 선언 후 listNode로 재정의

/* 함수 리스트 */
int initialize(listNode** h); //리스트를 생성하거나 초기화하는 intialize 함수 선언
int freeList(listNode* h); //리스트의 모든 노드에 대해 메모리를 해제하는 freeList 함수 선언
int insertLast(listNode* h, int key); //리스트의 마지막에 노드를 삽입하는 insertLast 함수 선언
int deleteLast(listNode* h); //리스트의 마지막 노드를 삭제하는 deleteLast 함수 선언
int insertFirst(listNode* h, int key); //리스트의 첫 번째에 노드를 삽입하는 insertFirst 함수 선언
int deleteFirst(listNode* h); //리스트의 첫 번째 노드를 삭제하는 deleteFirst 함수 선언
int invertList(listNode* h); //리스트의 순서를 역순으로 바꾸는 invertList 함수 선언

int insertNode(listNode* h, int key); //리스트에 있는 노드들과 key 값을 비교하여 노드를 삽입하는 inserNode 함수 선언
int deleteNode(listNode* h, int key); //리스트에 있는 노드들과 key 값을 대조하여 노드를 삭제하는 deleteNode 함수 선언

void printList(listNode* h); //리스트의 노드를 모두 출력하는 printList 함수 선언



int main()
{
	char command; //명령어를 입력받기 위한 command 변수 선언
	int key; //값을 입력받기 위한 key 변수 선언
	listNode* headnode = NULL; //리스트의 헤드 노드를 가리키는 포인터 headnode 선언 후 리스트 생성 전 NULL을 가리키도록 초기화

	printf("----- [이승현] [2020039075] -----\n");

	do { //반복문 최소 1번 이상 실행
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
		scanf(" %c", &command); //명령어를 입력받아 command에 저장 

		switch (command) {
		case 'z': case 'Z': //command가 'z' 또는 'Z'일 때
			initialize(&headnode); //intialize 함수 호출로 headnode에 메모리 할당하여 리스트 생성 (주소 전달로 함수 내에서 headnode의 값 변경)
			break;
		case 'p': case 'P': //command가 'p' 또는 'P'일 때
			printList(headnode); //printList 함수 호출로 리스트의 노드들을 출력
			break;
		case 'i': case 'I': //command가 'i' 또는 'I'일 때
			printf("Your Key = ");
			scanf("%d", &key); //삽입할 key 값 입력
			insertNode(headnode, key); //insertNode 함수 호출로 headnode가 가리키는 곳부터 시작하여 노드 간 key 값을 비교하여 새로운 노드 삽입 
			break;
		case 'd': case 'D': //command가 'd' 또는 'D'일 때
			printf("Your Key = ");
			scanf("%d", &key); //삭제할 key 값 입력
			deleteNode(headnode, key); //deleteNode 함수 호출로 headnode가 가리키는 곳부터 시작하여 입력받은 key 값을 가진 노드 삭제
			break;
		case 'n': case 'N': //command가 'n' 또는 'N'일 때
			printf("Your Key = ");
			scanf("%d", &key); //삽입할 key 값 입력
			insertLast(headnode, key); //insertLast 함수 호출로 headnode가 가리키는 곳부터 시작하여 리스트의 마지막에 새로운 노드 삽입
			break;
		case 'e': case 'E': //command가 'e' 또는 'E'일 때
			deleteLast(headnode); //deleteLast 함수 호출로 headnode가 가리키는 곳부터 시작하여 리스트의 마지막 노드 삭제
			break;
		case 'f': case 'F': //command가 'f' 또는 'F'일 때
			printf("Your Key = ");
			scanf("%d", &key); //삽입할 key 값 입력
			insertFirst(headnode, key); //insertFirst 함수 호출로 headnode가 가리키는 리스트의 맨 앞에 새로운 노드 삽입
			break;
		case 't': case 'T': //command가 't' 또는 'T'일 때
			deleteFirst(headnode); //deleteFirst 함수 호출로 headnode가 가리키는 리스트의 첫 번째 노드 삭제
			break;
		case 'r': case 'R': //command가 'r' 또는 'R'일 때
			invertList(headnode); //invertList 함수 호출로 headnode가 가리키는 리스트의 노드들의 순서를 역순으로 변경
			break;
		case 'q': case 'Q': //command가 'q' 또는 'Q'일 때
			freeList(headnode); //freeList 함수 호출로 headnode가 가리키는 리스트의 노드들 메모리 해제
			break;
		default: //command가 상단의 문자 이외의 값일 때
			printf("\n       >>>>>   Concentration!!   <<<<<     \n"); //오류 메세지 출력
			break;
		}

	} while (command != 'q' && command != 'Q'); //command에 'q' 또는 'Q'를 입력받으면 반복문 종료

	return 1;
}


int initialize(listNode** h) { //이중 포인터 h로 헤드 노드의 주소를 받아 헤드 노드의 값을 함수 내에서 변경 가능

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
	int i = 0; //순서를 나타내기 위해 i 선언 후 0으로 초기화
	listNode* p; //리스트의 노드를 가리킬 포인터 p 선언

	printf("\n---PRINT\n");

	if (h == NULL) { //리스트가 비어있을 때
		printf("Nothing to print....\n"); //오류 메세지 출력
		return; //함수 종료
	}

	p = h->rlink; //p가 헤드 노드를 제외한 리스트의 첫 번째 노드를 가리키도록 초기화

	while (p != NULL && p != h) { //p가 리스트의 마지막 노드에 도달하기 전까지 반복
		printf("[ [%d]=%d ] ", i, p->key); //i번째에 있는 노드의 key 값 출력 
		p = p->rlink; //p가 다음 노드를 가리킴
		i++; //다음 번째로 변경
	}
	printf("  items = %d\n", i); //노드의 총 갯수 출력


	/* print addresses */
	printf("\n---checking addresses of links\n");
	printf("-------------------------------\n");
	printf("head node: [llink]=%p, [head]=%p, [rlink]=%p\n", h->llink, h, h->rlink); //헤드 노드의 llink, 주소, rlink를 차례로 출력

	i = 0;
	p = h->rlink; //p가 헤드 노드를 제외한 리스트의 첫 번째 노드를 가리킴
	while (p != NULL && p != h) { //p가 리스트의 마지막 노드에 도달하기 전까지 반복
		printf("[ [%d]=%d ] [llink]=%p, [node]=%p, [rlink]=%p\n", i, p->key, p->llink, p, p->rlink); //i번째에 있는 노드의 key, llink, rlink를 차례로 출력
		p = p->rlink; //p가 다음 노드를 가리킴
		i++; //다음 번째로 변경
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
	listNode* temp, * trail; //노드를 가리키는 temp 포인터와 temp의 전위 노드를 가리킬 trail 포인터 선언
	temp = h; //temp가 리스트의 헤드 노드를 가리키도록 초기화
	if (h->rlink == h) //리스트가 비어있을 때
	{
		printf("List is empty!\n"); //오류 메세지 출력
	}
	else //리스트가 비어있지 않을 때
	{
		do { //반복문 최소 1번 이상 실행
			trail = temp->llink; //trail이 temp의 왼쪽 노드를 가리킴
			temp->llink = temp->rlink; //temp의 왼쪽 링크는 temp의 오른쪽 링크의 노드를 가리킴
			temp->rlink = trail; //temp의 오른쪽 링크는 temp의 왼쪽 노드를 가리킴
			temp = temp->llink; //temp가 다음 노드로 넘어감
		} while (temp != h); //temp가 헤드 노드가 될 때 반복문 종료
	}
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
			temp = temp->rlink; //입력받은 key보다 큰 값이 아니면 temp가 다음 노드를 가리킴
		}
		insertLast(h, key); //입력받은 key보다 큰 값을 리스트에서 찾지 못하면 insert 노드를 리스트의 끝에 배치
	}
	return 0;
}


/**
 * list에서 key에 대한 노드 삭제
 */
int deleteNode(listNode* h, int key) {
	listNode* delete = h->rlink; //노드를 삭제하기 위한 포인터 delete 선언 후 헤드 노드를 제외한 첫 번째 노드를 가리키도록 초기화
	if (h->rlink == h) //리스트가 비어있을 때
	{
		printf("List is empty!\n"); //리스트가 비어있다는 오류 메세지 출력
	}
	else //리스트가 비어있지 않을 때
	{
		while (delete != h) //delete 노드가 마지막 노드와 비교 완료 할 때까지 반복
		{
			if (delete->key == key) //key 값과 delete의 key 값이 동일할 때
			{
				//delete의 왼쪽 노드의 오른쪽 링크가 delete의 오른쪽 노드를 가리킴
				delete->llink->rlink = delete->rlink;
				//delete의 오른쪽 노드의 왼쪽 링크가 delete의 왼쪽 노드를 가리키면 (삭제 전 delete의 왼쪽 노드)-(삭제 전 delete의 오른쪽 노드) 순으로 배치
				delete->rlink->llink = delete->llink; 
				//delete가 가리키는 노드의 메모리 해제
				free(delete);
				//노드를 리스트에서 삭제하면 함수 종료
				return 0;
			}
			delete = delete->rlink; //입력받은 key와 일치하지 않으면 delete는 다음 노드로 이동
		}
		printf("Node with the value %d not found!\n", key); //입력받은 key 값을 리스트에서 찾지 못하면 오류 메세지 출력
	}
	return 0;
}


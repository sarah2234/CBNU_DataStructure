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
	int key; //노드의 값을 저장하는 key 선언
	struct Node* link; //다음 노드를 가리키는 포인터형 link 선언
} listNode; //노드를 생성하기 위한 구조체 Node 선언 후 listNode로 재정의

typedef struct Head {
	struct Node* first; //리스트의 맨 앞 노드를 가리키는 포인터형 first 선언
}headNode; //리스트의 맨 앞을 가리키기 위한 구조체 Head 선언 후 headNode로 재정의


/* 함수 리스트 */
headNode* initialize(headNode* h); //리스트를 생성하거나 초기화하는 intialize 함수 선언
int freeList(headNode* h); //리스트의 모든 노드에 대해 메모리를 해제하는 freeList 함수 선언

int insertFirst(headNode* h, int key); //리스트의 맨 앞 노드를 삽입하는 insertFirst 함수 선언
int insertNode(headNode* h, int key); //리스트에 있는 노드들과 key 값을 비교하여 노드를 삽입하는 inserNode 함수 선언
int insertLast(headNode* h, int key); //리스트의 맨 끝 노드를 삽입하는 insertLast 함수 선언

int deleteFirst(headNode* h); //리스트의 맨 앞 노드를 삭제하는 deleteFirst 함수 선언
int deleteNode(headNode* h, int key); //리스트에 있는 노드들과 key 값을 대조하여 노드를 삭제하는 deleteNode 함수 선언
int deleteLast(headNode* h); //리스트의 맨 끝 노드를 삭제하는 deleteLast 함수 선언
int invertList(headNode* h); //리스트의 순서를 역순으로 바꾸는 invertList 함수 선언

void printList(headNode* h); //리스트의 노드를 모두 출력하는 printList 함수 선언

int main()
{
	char command; //명령어를 입력받기 위한 command 변수 선언
	int key; //값을 입력받기 위한 key 변수 선언
	headNode* headnode = NULL; //리스트의 맨 앞을 가리키는 포인터 headnode 선언 후 리스트가 생성 전이므로 NULL을 가리키도록 초기화 

	printf("----- [이승현] [2020039075] -----\n");	

		do { //반복문 최소 1번 이상 실행
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
			scanf(" %c", &command); //명령어를 입력받아 command에 저장

			switch (command) {
			case 'z': case 'Z': //command가 'z' 또는 'Z'일 때
				headnode = initialize(headnode); //intialize 함수 호출로 headnode에 메모리 할당하여 리스트 생성
				break;
			case 'p': case 'P': //command가 'p' 또는 'P'일 때
				printList(headnode); //printList 함수 호출로 headnode가 가리키는 곳부터 시작하여 리스트의 노드를 출력
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
				insertLast(headnode, key); //insertLast 함수 호출로 headnode가 가리키는 곳부터 시작하여 리스트의 맨 끝에 새로운 노드 삽입
				break;
			case 'e': case 'E': //command가 'e' 또는 'E'일 때
				deleteLast(headnode); //deleteLast 함수 호출로 headnode가 가리키는 곳부터 시작하여 리스트의 맨 끝 노드 삭제
				break;
			case 'f': case 'F': //command가 'f' 또는 'F'일 때
				printf("Your Key = ");
				scanf("%d", &key); //삽입할 key 값 입력
				insertFirst(headnode, key); //insertFirst 함수 호출로 headnode가 가리키는 곳인 리스트의 맨 앞에 새로운 노드 삽입
				break;
			case 't': case 'T': //command가 't' 또는 'T'일 때
				deleteFirst(headnode); //deleteFirst 함수 호출로 headnode가 가리키는 곳인 리스트의 맨 앞 노드 삭제
				break;
			case 'r': case 'R': //command가 'r' 또는 'R'일 때
				invertList(headnode); //invertList 함수 호출로 headnode가 가리키는 곳부터 시작하여 차례로 리스트를 역순으로 변경
				break;
			case 'q': case 'Q': //command가 'q' 또는 'Q'일 때
				freeList(headnode); //freeList 함수 호출로 headnode가 가리키는 곳부터 시작하여 차례로 메모리 해제
				break;
			default: //command가 상단의 문자 이외의 값일 때
				printf("\n       >>>>>   Concentration!!   <<<<<     \n"); //오류 메세지 출력
				break;
			}

		} while (command != 'q' && command != 'Q'); //command에 'q' 또는 'Q'를 입력받으면 반복문 종료

		return 1; //main 함수 종료
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
	listNode* p = h->first; //포인터 p 선언 후 리스트의 맨 앞 노드를 가리키도록 초기화

	listNode* prev = NULL; //선행 노드 prev 선언
	while (p != NULL) { //p가 리스트의 맨 끝에 도달할 때까지 반복
		prev = p; //p가 다음 노드를 가리키기 전 prev가 p의 노드를 가리켜 prev를 선행 노드로 취급
		p = p->link; //p가 다음 노드를 가리킴
		free(prev); //prev가 가리키는 노드의 메모리 해제
	}
	free(h); //리스트의 맨 앞 노드의 메모리 해제
	return 0; //함수 정상 실행 후 종료
}



/**
 * list 처음에 key에 대한 노드하나를 추가
 */
int insertFirst(headNode* h, int key) {

	listNode* node = (listNode*)malloc(sizeof(listNode)); //입력받은 key 값을 삽입하기 위한 포인터 node 선언 후 메모리 할당
	node->key = key; //입력받은 key 값을 node의 key에 저장

	node->link = h->first; //node의 다음 노드가 현재 리스트의 맨 앞 노드를 가리키도록 함
	h->first = node; //리스트의 맨 앞 노드를 node가 가리키는 노드로 수정

	return 0; //함수 정상 실행 후 종료
}


/* 리스트를 검색하여, 입력받은 key보다 큰 값이 나오는 노드 바로 앞에 삽입 */
int insertNode(headNode* h, int key) { 
	listNode* temp = h->first; //입력받은 key와 값을 비교할 노드를 가리키는 포인터 temp 선언 후 리스트의 맨 앞을 가리키도록 초기화
	listNode* trail = h->first; //key 값이 temp가 가리키는 노드의 앞에 배치되도록 temp의 선행 노드를 가리키는 포인터 trail 선언 후 리스트의 맨앞을 가리키도록 초기화
	listNode* insert = (listNode*)malloc(sizeof(listNode)); //입력받은 key 값을 리스트에 삽입하도록 insert 포인터 생성 후 메모리 할당
	insert->key = key; //입력받은 key 값을 insert의 key에 저장
	if (!h->first || temp->key > insert->key) //리스트가 비어있거나 key가 맨앞에 위치해야할 때
	{
		insertFirst(h, key); //리스트의 맨 앞에 key를 삽입하는 것과 같으므로 insertFirst 함수 호출
	}
	else //리스트가 비어있지 않을 때
	{
		while (temp != NULL)//노드의 link가 리스트의 끝인 NULL을 가리키기 전까지 반복문 실행
		{
			if (temp->key > insert->key) //입력받은 key보다 큰 값이 나오는 노드를 발견
			{
				insert->link = temp; //insert의 link가 temp를 가리켜 insert의 값이 temp가 가리키는 노드 앞에 오도록 배치
				trail->link = insert;//이전 노드를 가리키는 trail의 link가 insert를 가리켜 insert 노드가 trail 노드 뒤에 오도록 배치
				return 0; //insert가 가리키는 노드를 리스트에 삽입하면 함수 종료
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
	else //리스트가 비어있지 않을 때
	{
		while (temp->link) //temp가 가리키는 다음 노드가 NULL, 즉 리스트의 끝에 도달하기 전까지 반복
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
	
	if (!h->first) //리스트가 비어있을 때
	{
		printf("List is empty!\n"); //리스트가 비어있다는 오류 메세지 출력
	}
	else //리스트가 비어있지 않을 때
	{
		listNode* temp = h->first; //삭제할 노드를 가리키는 포인터 temp 선언 후 리스트의 맨 앞을 가리키도록 초기화
		h->first = temp->link; //리스트의 맨 앞 노드가 temp의 link가 가리키는 노드, 즉 2번째 노드를 가리키도록 하여 temp 노드를 리스트에서 삭제
		free(temp); //리스트의 첫 번째 노드 삭제 후 temp의 메모리 해제
	}

	return 0; //함수 정상 실행 후 종료
}


/**
 * list에서 key에 대한 노드 삭제
 */
int deleteNode(headNode* h, int key) {
	listNode* temp = h->first; //삭제할 노드를 가리키는 포인터 temp 선언 후 리스트의 맨 앞을 가리키도록 초기화
	listNode* trail = h->first; //temp 노드 이전과 이후의 노드가 연결될 수 있도록 temp의 선행 노드를 가리키는 포인터 trail 선언 후 리스트의 맨 앞을 가리키도록 초기화
	
	if (!h->first) //리스트가 비어있을 때
	{
		printf("List is empty!\n"); //리스트가 비어있다는 오류 메세지 출력 
	}
	else if (temp->key == key)//삭제할 노드가 리스트의 맨 앞에 있을 때
	{
		deleteFirst(h, key); //리스트의 첫 번째 노드를 삭제하는 것과 같으므로 deleteFirst 함수 호출
	}
	else //리스트가 비어있지 않고 삭제할 노드가 리스트의 맨 앞에 있지 않을 때
	{
	while (temp->link) //temp가 가리키는 다음 노드가 NULL, 즉 리스트의 끝에 도달하기 전까지 반복
	{
		if (temp->key == key) // temp의 key가 입력한 key와 같은 값을 가질 때
		{
			trail->link = temp->link; //선행 노드 trail의 link가 temp의 다음 노드를 가리켜 temp 노드를 리스트에서 삭제
			free(temp); //리스트에서 temp 노드 삭제 후 temp 메모리 해제
			return 0; //temp가 가리키는 노드를 리스트에서 삭제하면 함수 종료
		}
		trail = temp; //temp가 다음 노드를 가리키기 전 trail에 저장하여 trail을 temp의 선행 노드로 취급
		temp = temp->link; //temp가 다음 노드를 가리킴
	}
	printf("Node with the value %d not found!\n", key); //입력받은 key 값을 리스트에서 찾지 못하면 오류 메세지 출력
	}
	return 0; //함수 정상 실행 후 종료

}

/**
 * list의 마지막 노드 삭제
 */
int deleteLast(headNode* h) {
	listNode* temp = h->first; //삭제할 노드를 가리키는 포인터 temp 선언 후 리스트의 맨 앞을 가리키도록 초기화
	listNode* trail = h->first; //temp의 선행 노드를 가리키는 포인터 trail 선언 후 리스트의 맨 앞을 가리키도록 초기화

	if (!h->first) //리스트가 비어있을 때
	{
		printf("List is empty!\n"); //리스트가 비어있다는 오류 메세지 출력 
	}
	else //리스트가 비어있지 않을 때
	{
		while (temp->link) //temp가 가리키는 다음 노드가 NULL, 즉 리스트의 끝에 도달하기 전까지 반복
		{
			trail = temp; //temp가 다음 노드를 가리키기 전 trail에 저장하여 trail을 temp의 선행 노드로 취급
			temp = temp->link; //temp가 다음 노드를 가리킴
		}
		trail->link = NULL; //temp가 마지막 노드를 가리킬 때 선행 노드를 가리키는 trail의 link가 NULL을 가리켜 리스트의 마지막 노드를 가리키도록 함
		free(temp); //리스트에서 temp 노드 삭제 후 temp 메모리 해제
	}

	return 0; //함수 정상 실행 후 종료
}


/**
 * 리스트의 링크를 역순으로 재 배치
 */
int invertList(headNode* h) {
	listNode* lead, *middle, *trail; //앞, 중간, 뒷 노드를 순서대로 가리킬 포인터 lead, middle, trail 선언
	lead = h->first; //lead가 리스트의 맨 앞 노드를 가리키도록 함
	middle = NULL; //middle이 아직 노드를 가리키지 않은 상태
	if (!h->first) //리스트가 비어있을 때
	{
		printf("List is empty!\n"); //오류 메세지 출력
	}
	else //리스트가 비어있지 않을 때
	{
		while (lead) //리스트 처음부터 끝에 도달하기 전까지 반복
		{
			trail = middle; //뒷 노드를 가리키는 trail이 중간 노드를 가리키는 middle이 가리키는 노드로 바꿈
			middle = lead; //중간 노드를 가리키는 middle이 앞 노드를 가리키는 lead가 가리키는 노드로 바꿈
			lead = lead->link; //lead는 그 다음 노드를 가리킴 
			middle->link = trail; //middle이 가리키는 노드 다음에 trail이 가리키는 노드가 올 수 있도록 수정
		}
		h->first = middle; //리스트의 맨 앞 노드가 바뀌었으므로 middle이 가리키는 노드가 리스트의 맨 앞인 것을 명시
	}
	return 0; //함수 정상 실행 후 종료
}


void printList(headNode* h) {
	int i = 0; //순서를 나타내기 위해 i 선언
	listNode* p; //리스트의 노드를 가리킬 포인터 p 선언

	printf("\n---PRINT\n");

	if (h == NULL) { //리스트가 비어있을 때
		printf("Nothing to print....\n"); //오류 메세지 출력
		return; //함수 종료
	}

	p = h->first; //p가 리스트의 맨 앞 노드를 가리키도록 변경

	while (p != NULL) { //p가 리스트의 맨 끝에 도달하기 전까지 반복
		printf("[ [%d]=%d ] ", i, p->key); //i번째에 있는 노드의 key 값 출력
		p = p->link; //p가 다음 노드를 가리킴
		i++; //다음 번째로 변경
	}

	printf("  items = %d\n", i); //리스트 내에 존재하는 노드 개수 출력
}


/*
 * Binary Search Tree #2
 *
 * Data Structures
 *
 * Department of Computer Science
 * at Chungbuk National University
 *
 */

#include <stdio.h>
#include <stdlib.h>



typedef struct node {
	int key; //노드의 값을 저장하는 key 선언
	struct node* left; //왼쪽 자식 노드를 가리키는 포인터 left 선언
	struct node* right; //오른쪽 자식 노드를 가리키는 포인터 right 선언
} Node; //노드를 생성하기 위한 구조체 node 선언 후 Node로 재정의

/* for stack */
#define MAX_STACK_SIZE		20 //스택이 최대로 저장할 수 있는 노드의 개수는 20
Node* stack[MAX_STACK_SIZE]; //노드를 저장하는 스택 생성 (반복적 중위 순회에 사용)
int top = -1; //스택의 위치를 알려주는 top 선언 후 -1로 초기화

Node* pop(); //스택의 노드를 삭제하는 함수
void push(Node* aNode); //스택에 aNode 노드를 삽입하는 함수

/* for queue */
#define MAX_QUEUE_SIZE		20 //큐가 최대로 저장할 수 있는 노드의 개수는 19
Node* queue[MAX_QUEUE_SIZE]; //노드를 저장하는 큐 생성 (레벨 순서 순회에 사용)
int front = -1; //큐에서 삭제할 위치를 가리키는 front 선언 후 -1로 초기화
int rear = -1; //큐에서 삽입할 위치를 가리키는 rear 선언 후 -1로 초기화

Node* deQueue(); //큐의 노드를 삭제하는 함수
void enQueue(Node* aNode); //큐에 aNode 노드를 삽입하는 함수


int initializeBST(Node** h); //트리를 초기화하는 함수

/* functions that you have to implement */
void recursiveInorder(Node* ptr);	  /* recursive inorder traversal */
void iterativeInorder(Node* ptr);     /* iterative inorder traversal */
void levelOrder(Node* ptr);	          /* level order traversal */
int insert(Node* head, int key);      /* insert a node to the tree */
int deleteNode(Node* head, int key);  /* delete the node for the key */
int freeBST(Node* head); /* free all memories allocated to the tree */

/* you may add your own defined functions if necessary */
int deleteChildNode(Node* parent, Node* child); //자식 노드를 삭제하기 위한 함수







int main()
{
	char command; //명령어를 입력받기 위한 command 변수 선언
	int key; //값을 입력받기 위한 key 변수 선언
	Node* head = NULL; //트리의 헤드 노드를 가리키는 포인터 head 선언 후 트리 생성 전 NULL을 가리키도록 초기화

	printf("----- [이승현] [2020039075] -----\n");

	do { //'q' 또는 'Q' 를 입력받을 때까지 최소 1회 이상 반복 실행
		printf("\n\n");
		printf("----------------------------------------------------------------\n");
		printf("                   Binary Search Tree #2                        \n");
		printf("----------------------------------------------------------------\n");
		printf(" Initialize BST       = z                                       \n");
		printf(" Insert Node          = i      Delete Node                  = d \n");
		printf(" Recursive Inorder    = r      Iterative Inorder (Stack)    = t \n");
		printf(" Level Order (Queue)  = l      Quit                         = q \n");
		printf("----------------------------------------------------------------\n");

		printf("Command = ");
		scanf(" %c", &command); //명령어를 입력받아 command에 저장

		switch (command) {
		case 'z': case 'Z': //command가 'z' 또는 'Z'일 때
			initializeBST(&head); //head에 메모리 할당하여 트리 생성
			break;
		case 'q': case 'Q': //command가 'q' 또는 'Q'일 때
			freeBST(head); //트리의 노드들 메모리 해제
			break;
		case 'i': case 'I': //command가 'i' 또는 'I'일 때
			printf("Your Key = ");
			scanf("%d", &key); //삽입할 값 입력
			insert(head, key); //트리에 해당 값을 가진 노드 삽입
			break;
		case 'd': case 'D': //command가 'd' 또는 'D'일 때
			printf("Your Key = ");
			scanf("%d", &key); //삭제할 값 입력
			deleteNode(head, key); //트리에서 해당 값을 가진 노드 삭제
			break;
		case 'r': case 'R': //command가 'r' 또는 'R'일 때
			recursiveInorder(head->left); //순환적 중위 순회를 사용하여 노드 출력
			break;
		case 't': case 'T': //command가 't' 또는 'T'일 때
			iterativeInorder(head->left); //반복적 중위 순회를 사용하여 노드 출력
			break;
		case 'l': case 'L': //command가 'l' 또는 'L'일 때
			levelOrder(head->left); //레벨 순서 순회를 사용하여 노드 출력
			break;


		default: //command가 상단의 문자 이외의 값일 때
			printf("\n       >>>>>   Concentration!!   <<<<<     \n"); //오류 메세지 출력
			break;
		}

	} while (command != 'q' && command != 'Q'); //command에 'q' 또는 'Q'를 입력받으면 반복문 종료

	return 1;
}

int initializeBST(Node** h) {

	/* if the tree is not empty, then remove all allocated nodes from the tree*/
	if (*h != NULL)
		freeBST(*h);

	/* create a head node */
	*h = (Node*)malloc(sizeof(Node));
	(*h)->left = NULL;	/* root */
	(*h)->right = *h;
	(*h)->key = -9999;

	top = -1;

	front = rear = -1;

	return 1;
}



void recursiveInorder(Node* ptr)
{
	if (ptr) {
		recursiveInorder(ptr->left);
		printf(" [%d] ", ptr->key);
		recursiveInorder(ptr->right);
	}
}

/**
 * textbook: p 224s
 */
void iterativeInorder(Node* node)
{
	for (;;) //공백 스택이 될 때까지 for문 반복
	{
		for (; node; node = node->left) //node를 왼쪽 자식 노드로 바꾸면서 NULL이 되기 전까지 반복
		{
			push(node); //node를 스택에 삽입
		}
		node = pop(); //스택에서 삭제한 후 결과값을 node에 저장
		if (!node) //node가 NULL, 즉 스택이 공백 상태일 때
			break; //for (;;)의 반복 종료
		printf(" [%d] ", node->key); //pop한 결과값을 저장한 node의 key 값 출력
		node = node->right; //node를 오른쪽 자식 노드로 바꿈
	}
}

/**
 * textbook: p 225
 */
void levelOrder(Node* ptr)
{
	if (!ptr) //트리가 공백일 때
	{
		return; //함수 종료
	}
	enQueue(ptr); //ptr 노드를 큐에 삽입
	for (;;) //노드가 큐에 존재하지 않아 함수 deQueue가 NULL을 반환할 때까지 for문 반복
	{
		ptr = deQueue(); //큐에서 노드를 삭제한 후 결과값을 ptr에 저장
		if (ptr) //ptr이 NULL이 아닐 때
		{
			printf(" [%d] ", ptr->key); //ptr의 key 값 출력
			if (ptr->left) //ptr의 왼쪽 자식 노드가 존재할 때
				enQueue(ptr->left); //왼쪽 자식 노드를 큐에 삽입
			if (ptr->right) //ptr의 오른쪽 자식 노드가 존재할 때
				enQueue(ptr->right); //오른쪽 자식 노드를 큐에 삽입
		}
		else //ptr이 NULL, 즉 더이상 큐에 노드가 존재하지 않을 때
		{
			break; //for (;;)의 반복 종료
		}
	}
}


int insert(Node* head, int key)
{
	Node* newNode = (Node*)malloc(sizeof(Node));
	newNode->key = key;
	newNode->left = NULL;
	newNode->right = NULL;

	if (head->left == NULL) {
		head->left = newNode;
		return 1;
	}

	/* head->left is the root */
	Node* ptr = head->left;

	Node* parentNode = NULL;
	while (ptr != NULL) {

		/* if there is a node for the key, then just return */
		if (ptr->key == key) return 1;

		/* we have to move onto children nodes,
		 * keep tracking the parent using parentNode */
		parentNode = ptr;

		/* key comparison, if current node's key is greater than input key
		 * then the new node has to be inserted into the right subtree;
		 * otherwise the left subtree.
		 */
		if (ptr->key < key)
			ptr = ptr->right;
		else
			ptr = ptr->left;
	}

	/* linking the new node to the parent */
	if (parentNode->key > key)
		parentNode->left = newNode;
	else
		parentNode->right = newNode;
	return 1;
}


int deleteNode(Node* head, int key)
{
	Node* temp = head; //입력받은 key 값과 비교할 노드를 가리키는 포인터 temp 선언 후 head로 초기화
	if (temp->right == temp) //temp가 헤드 노드를 가리킬 때
	{
		temp = temp->left; //temp가 루트 노드를 가리키도록 변경
	}

	if (temp->key == key) //루트 노드가 삭제하고자하는 노드에 해당할 때
	{
		deleteChildNode(head, temp); //루트 노드를 삭제하고자 deleteChildNode 호출
		return 0; //삭제 후 함수 종료
	}

	if ((temp->key > key) & (temp->left != NULL)) //삭제하고자하는 값보다 temp의 key값이 더 크고 temp의 왼쪽 서브 트리가 존재할 때, 왼쪽 자식 노드 조사
	{
		if(temp->left->key == key) //temp의 왼쪽 자식 노드가 삭제하고자하는 노드에 해당할 때
		{
			deleteChildNode(temp, temp->left); //왼쪽 자식 노드를 삭제하고자 deleteChildNode 호출
			return 0; //삭제 후 함수 종료
		}
		else //왼쪽 자식 노드가 삭제하고자하는 노드에 해당하지 않을 때
		{
			deleteNode(temp->left, key); //왼쪽 서브 트리를 조사하기 위해 deleteNode 호출
		}
	}

	else if ((temp->key < key) & (temp->right != NULL)) //삭제하고자하는 값보다 temp의 key값이 더 작고 temp의 오른쪽 서브 트리가 존재할 때, 오른쪽 자식 노드 조사
	{
		if (temp->right->key == key) //temp의 오른쪽 자식 노드가 삭제하고자하는 노드에 해당할 때
		{
			deleteChildNode(temp, temp->right); //오른쪽 자식 노드를 삭제하고자 deleteChildNode 호출
			return 0; //삭제 후 함수 종료
		}
		else //오른쪽 자식 노드가 삭제하고자하는 노드에 해당하지 않을 때
		{
			deleteNode(temp->right, key); //오른쪽 서브 트리를 조사하기 위해 deleteNode 호출
		}
	}

	else //temp가 리프 노드일 때
	{
		printf("The node [%d] does not exist.\n\n", key); //오류 메세지 출력
	}
}

int deleteChildNode(Node* parent, Node* child)
{
	//child가 삭제하고자하는 노드에 해당하고, parent는 child의 부모 노드
	
	if ((child->left == NULL) & (child->right == NULL)) //child가 리프 노드일 때
	{
		free(child); //삭제하려는 노드의 메모리 해제
		parent->left = NULL; //child의 부모 노드 parent의 왼쪽 링크는 NULL을 가리킴
		return 0; //삭제 후 함수 종료
	}

	else if ((child->right == NULL)) //child의 왼쪽 자식 노드가 있을 때
	{
		parent->left = child->left; //부모 노드 parent의 왼쪽 자식 노드는 child의 왼쪽 자식 노드가 됨
		free(child); //삭제하려는 노드의 메모리 해제
		return 0; //삭제 후 함수 종료
	}

	else if ((child->left == NULL)) //child의 오른쪽 자식 노드가 있을 때
	{
		parent->right = child->right; //부모 노드 parent의 오른쪽 자식 노드는 child의 오른쪽 자식 노드가 됨
		free(child); //삭제하려는 노드의 메모리 해제
		return 0; //삭제 후 함수 종료
	}

	else //child의 오른쪽과 왼쪽에 자식 노드가 있을 때
	{
		Node* linkNode = child->right; //child의 오른쪽 서브 트리에서 새로 연결해줄 노드를 찾고자 linkNode 선언 후 child->right로 초기화
		Node* previous = NULL; //linkNode 이전의 노드를 가리키는 포인터 previous 선언 후 NULL로 초기화

		for (; linkNode->left; linkNode = linkNode->left) //linkNode를 왼쪽 자식 노드로 옮겨가면서 linkNode의 왼쪽 자식 노드가 없을 때까지 for문 반복
		{
			previous = linkNode; //linkNode가 이전에 방문했던 노드를 가리키는 previous에 linkNode를 저장
		}
		//linkNode의 왼쪽 자식 노드가 없으면 해당 노드가 child의 오른쪽 서브 트리 중에서 최소값을 갖는 노드이다.
		//따라서 for 문은 실행되지 않고, previous는 처음에 초기화해주었던 NULL값을 계속 가지고 있게 된다.
		
		if (previous != NULL) //tempLeft의 오른쪽 자식 노드가 오른쪽 서브 트리에서 최소값을 가지지 않을 때
		{
			previous->left = linkNode->right; //linkNode 이전의 노드 previous의 왼쪽 자식 노드는 linkNode의 오른쪽 자식 노드가 됨
			linkNode->right = child->right; //linkNode의 오른쪽 자식 노드는 child의 오른쪽 자식 노드가 됨
			linkNode->left = child->left; //linkNode의 왼쪽 자식 노드는 child의 왼쪽 자식 노드가 됨
			if (parent->left == child)
			{
				parent->left = linkNode;
			}
			else
			{
				parent->right = linkNode;
			}
			free(child); //삭제하려는 노드의 메모리 해제
			return 0; //삭제 후 함수 종료
		}
		else //child의 오른쪽 자식 노드가 오른쪽 서브 트리에서 최소값을 가질 때
		{
			linkNode->left = child->left; //linkNode의 왼쪽 자식 노드는 child의 왼쪽 자식 노드가 됨
			if (parent->left == child) //child가 parent의 왼쪽 자식 노드일 때
			{
				parent->left = linkNode; //parent의 왼쪽 자식 노드는 linkNode가 됨
			}
			else //child가 parent의 오른쪽 자식 노드일 때
			{
				parent->right = linkNode; //parent의 오른쪽 자식 노드는 linkNode가 됨
			}
			free(child); //삭제하려는 노드의 메모리 해제
			return 0; //삭제 후 함수 종료
		}
	}
}

void freeNode(Node* ptr)
{
	if (ptr) {
		freeNode(ptr->left);
		freeNode(ptr->right);
		free(ptr);
	}
}

int freeBST(Node* head)
{

	if (head->left == head)
	{
		free(head);
		return 1;
	}

	Node* p = head->left;

	freeNode(p);

	free(head);
	return 1;
}



Node* pop()
{
	if (top == -1) //스택이 공백일 때
	{
		return NULL; //NULL 반환
	}
	Node* node = stack[top]; //포인터 node에 스택의 top에 해당하는 노드 저장
	stack[top--] = '\0'; //스택의 top에 해당하는 노드 삭제 후 top은 1 감소
	return node; //node 반환
}

void push(Node* aNode)
{
	if (top >= MAX_STACK_SIZE) //스택이 만원일 때
	{
		printf("Unable to insert [%d] into the stack.\n", aNode->key); //에러 메세지 출력
		return; //함수 종료
	}
	stack[++top] = aNode; //top을 증가시키면서 스택에 aNode 삽입
}



Node* deQueue()
{
	if (front == rear) //큐가 공백일 때
	{
		return NULL; //NULL 반환
	}
	front = (front + 1) % MAX_QUEUE_SIZE; //큐의 front를 1 증가시킴
	Node* node = queue[front]; //포인터 node에 큐의 front에 해당하는 노드 저장
	queue[front] = '\0'; //큐의 front에 해당하는 노드 삭제
	return node; //node 반환
}

void enQueue(Node* aNode)
{
	if (front == (rear + 1) % MAX_QUEUE_SIZE) //큐가 만원일 때
	{
		printf("Unable to insert [%d] into the queue.\n", aNode->key); //에러 메세지 출력
		return; //함수 종료
	}
	queue[++rear] = aNode; //rear을 1 증가한 후 큐에 aNode 삽입
}
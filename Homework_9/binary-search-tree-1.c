/*
 * Binary Search Tree #1
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
	struct node* right; //오른쪽 노드를 가리키는 포인터 right 선언
} Node; //노드를 생성하기 위한 구조체 node 선언 후 Node로 재정의

int initializeBST(Node** h); //트리를 초기화하는 intializeBST 함수 선언

/* functions that you have to implement */
void inorderTraversal(Node* ptr);	  /* recursive inorder traversal */
void preorderTraversal(Node* ptr);    /* recursive preorder traversal */
void postorderTraversal(Node* ptr);	  /* recursive postorder traversal */
int insert(Node* head, int key);  /* insert a node to the tree */
int deleteLeafNode(Node* head, int key);  /* delete the leaf node for the key */
Node* searchRecursive(Node* ptr, int key);  /* search the node for the key */
Node* searchIterative(Node* head, int key);  /* search the node for the key */
int freeBST(Node* head); /* free all memories allocated to the tree */

/* you may add your own defined functions if necessary */


int main()
{
	char command; //명령어를 입력받기 위한 command 변수 선언
	int key; //값을 입력받기 위한 key 변수 선언
	Node* head = NULL; //트리의 헤드 노드를 가리키는 포인터 head 선언 후 트리 생성 전 NULL을 가리키도록 초기화
	Node* ptr = NULL;	/* temp */

	printf("----- [이승현] [2020039075] -----\n");

	do { //반복문 최소 1번 이상 실행
		printf("\n\n");
		printf("----------------------------------------------------------------\n");
		printf("                   Binary Search Tree #1                        \n");
		printf("----------------------------------------------------------------\n");
		printf(" Initialize BST       = z                                       \n");
		printf(" Insert Node          = n      Delete Leaf Node             = d \n");
		printf(" Inorder Traversal    = i      Search Node Recursively      = s \n");
		printf(" Preorder Traversal   = p      Search Node Iteratively      = f\n");
		printf(" Postorder Traversal  = t      Quit                         = q\n");
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
		case 'n': case 'N': //command가 'n' 또는 'N'일 때
			printf("Your Key = ");
			scanf("%d", &key); //삽입할 값 입력
			insert(head, key); //트리에 해당 값을 가진 노드 삽입
			break;
		case 'd': case 'D': //command가 'd' 또는 'D'일 때
			printf("Your Key = ");
			scanf("%d", &key); //삭제할 값 입력
			deleteLeafNode(head, key); //트리에서 해당 값을 가진 노드 삭제
			break;
		case 'f': case 'F': //command가 'f' 또는 'F'일 때
			printf("Your Key = ");
			scanf("%d", &key); //검색할 값 입력
			ptr = searchIterative(head, key); //트리에서 해당 값을 가진 노드를 반복법으로 검색하여 결과를 ptr에 저장
			if (ptr != NULL) //트리에 해당 노드가 존재할 때
				printf("\n node [%d] found at %p\n", ptr->key, ptr); //ptr의 key 값과 주소 출력
			else //트리에 해당 노드가 존재하지 않을 때
				printf("\n Cannot find the node [%d]\n", key); //오류 메세지 출력
			break;
		case 's': case 'S': //command가 's' 또는 'S'일 때
			printf("Your Key = ");
			scanf("%d", &key); //검색할 값 입력
			ptr = searchRecursive(head->left, key); //트리에서 해당 값을 가진 노드를 순환법으로 검색하여 결과를 ptr에 저장
			if (ptr != NULL) //트리에 해당 노드가 존재할 때
				printf("\n node [%d] found at %p\n", ptr->key, ptr); //ptr의 key 값과 주소 출력
			else //트리에 해당 노드가 존재하지 않을 때
				printf("\n Cannot find the node [%d]\n", key); //오류 메세지 출력
			break;

		case 'i': case 'I': //command가 'i' 또는 'I'일 때
			inorderTraversal(head->left); //중위 순회 방식으로 노드 출력
			break;
		case 'p': case 'P': //command가 'p' 또는 'P'일 때
			preorderTraversal(head->left); //전위 순회 방식으로 노드 출력
			break;
		case 't': case 'T': //command가 't' 또는 'T'일 때
			postorderTraversal(head->left); //후위 순회 방식으로 노드 출력
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
	return 1;
}



void inorderTraversal(Node* ptr)
{
	if (ptr) { //더 이상 이동할 수 없을 때까지 recursive 방식으로 함수 호출
		inorderTraversal(ptr->left); //왼쪽 자식 노드로 이동
		printf("[%d] ", ptr->key); //해당 노드 방문
		inorderTraversal(ptr->right); //방문 후 오른쪽 자식 노드로 이동
	}
}

void preorderTraversal(Node* ptr)
{
	if (ptr) { //더 이상 이동할 수 없을 때까지 recursive 방식으로 함수 호출
		printf("[%d] ", ptr->key); //해당 노드 방문
		preorderTraversal(ptr->left); //왼쪽 자식 노드로 이동
		preorderTraversal(ptr->right); //방문 후 오른쪽 자식 노드로 이동
	}
}

void postorderTraversal(Node* ptr)
{
	if (ptr) { //더 이상 이동할 수 없을 때까지 recursive 방식으로 함수 호출
		postorderTraversal(ptr->left); //왼쪽 자식 노드로 이동
		postorderTraversal(ptr->right); //방문 후 오른쪽 자식 노드로 이동
		printf("[%d] ", ptr->key); //해당 노드 방문
	}
}


int insert(Node* head, int key)
{
	Node* insertNode = (Node*)malloc(sizeof(Node)); //새로운 노드를 삽입하기 위한 포인터 insertNode 선언 후 메모리 할당 
	insertNode->key = key; //삽입하고자하는 값을 insertNode의 key에 저장
	insertNode->left = NULL; //insertNode는 리프 노드이므로 왼쪽 링크는 NULL을 가리킴
	insertNode->right = NULL; //insertNode는 리프 노드이므로 오른쪽 링크는 NULL을 가리킴

	if (head->right == head) //head가 헤드 노드를 가리키는 포인터일 때
	{
		if (head->left == NULL) //루트 노드가 트리에 존재하지 않을 때
		{
			head->left = insertNode; //루트 노드로서 insertNode 노드 삽입
			return 0; //삽입 후 종료
		}
		else //루트 노드가 트리에 존재할 때
		{
			head = head->left; //head를 루트 노드로 변경 (temp로 이름을 바꾸기 위한 작업)
		}
	}
	
	Node* temp = head; //현재 조사하고자 하는 노드를 가리키는 포인터 temp 선언 후 head 값으로 초기화 

	if (temp->key > key) //temp의 key가 삽입하려는 값보다 클 때 temp의 왼쪽 서브 트리 조사
	{
		if (temp->left == NULL) //temp의 왼쪽 자식 노드가 존재하지 않을 때
		{
			temp->left = insertNode; //temp의 왼쪽 자식 노드로 새로운 노드 삽입
			return 0; //삽입 후 함수 종료
		}
		else //temp의 왼쪽 자식 노드가 존재할 때
			insert(temp->left, key); //temp의 왼쪽 서브 트리 조사
	}
	else //temp의 key가 삽입하려는 값보다 크지 않을 때 temp의 오른쪽 서브 트리 조사
	{
		if (temp->right == NULL) //temp의 오른쪽 자식 노드가 존재하지 않을 때
		{
			temp->right = insertNode; //temp의 오른쪽 자식 새로운 노드 삽입
			return 0; //삽입 후 함수 종료
		}
		else //temp의 오른쪽 자식 노드가 존재할 때
			insert(temp->right, key); //temp의 오른쪽 서브 트리 조사
	}
	return 0;
}

int deleteLeafNode(Node* head, int key)
{
	if (head->right == head)//head가 헤드 노드일 때
	{
		Node* root = head->left; //루트 노드를 가리킬 포인터 root 선언 후 head->left로 초기화
		if (root == NULL) //루트 노드가 존재하지 않을 때
		{
			printf("The node [%d] does not exist.\n\n", key); //오류 메세지 출력
			return 0; //함수 종료
		}
		else if ((root->left == NULL) & (root->right == NULL) & (root->key == key)) //루트 노드가 삭제하고자하는 값을 가지면서 리프 노드일 때
		{
			free(root); //루트 노드에 할당되었던 메모리 해제
			head->left = NULL; //헤드 노드의 왼쪽 링크는 NULL을 가리킴
			return 0; //함수 종료
		}
		else if(root->key == key) //루트 노드가 삭제하고자하는 값을 가지나 리프 노드에 해당되지 않을 때
		{
			printf("The node [%d] is not a leaf node.\n\n", key); //오류 메세지 출력
			return 0; //함수 종료
		}

		head = head->left; //head가 헤드 노드에 해당되면 루트 노드를 가리키도록 함
	}

	Node* temp = head; //삭제하고자하는 노드의 부모 노드를 가리키는 포인터 temp 선언 후 head 값으로 초기화 
	Node* tempLeft = temp->left; //temp의 왼쪽 자식 노드를 가리키는 포인터 tempLeft 선언 후 temp->left로 초기화
	Node* tempRight = temp->right; //temp의 오른쪽 자식 노드를 가리키는 포인터 tempRight 선언 후 temp->right로 초기화

	if ((temp->key > key) & (tempLeft != NULL)) //삭제하고자하는 값보다 temp의 key값이 더 크고 temp의 왼쪽 서브 트리가 존재할 때
	{
		if ((tempLeft->left == NULL) & (tempLeft->right == NULL) & (tempLeft->key == key)) //왼쪽 노드가 삭제하고자하는 값을 가지면서 리프 노드일 때
		{
			free(tempLeft); //왼쪽 자식 노드의 메모리 해제
			temp->left = NULL; //temp의 왼쪽 링크는 NULL을 가리킴
			return 0; //함수 종료
		}
		else if((tempLeft->left == NULL) & (tempLeft->right == NULL)) //왼쪽 자식 노드가 리프 노드인데 삭제하고자하는 값이 존재하지 않을 때
		{
			printf("The node [%d] does not exist.\n\n", key); //오류 메세지 출력
			return 0; //함수 종료
		}
		else if (tempLeft->key == key) //왼쪽 자식 노드가 삭제하고자하는 값을 가졌으나 리프 노드가 아닐 때
		{
			printf("The node [%d] is not a leaf node.\n\n", key); //오류 메세지 출력
			return 0; //함수 종료
		}
		else //왼쪽 자식 노드가 삭제하고자하는 값을 갖지 않고 리프 노드도 아닐 때
		{
			deleteLeafNode(tempLeft, key); //왼쪽 서브 트리를 조사하기 위해 deleteLeafNode 호출
		}
	}
	else if ((temp->key < key) & (tempRight != NULL)) //temp의 key값보다 삭제하고자하는 값이 더 크고 temp의 오른쪽 서브 트리가 존재할 때
	{
		if ((tempRight->left == NULL) & (tempRight->right == NULL) & (tempRight->key == key)) //오른쪽 자식 노드가 삭제하고자하는 값을 가지면서 리프 노드일 때
		{
			free(tempRight); //오른쪽 자식 노드의 메모리 해제
			temp->right = NULL; //temp의 오른쪽 링크는 NULL을 가리킴
			return 0; //함수 종료
		}
		else if ((tempRight->left == NULL) & (tempRight->right == NULL)) //오른쪽 자식 노드가 리프 노드인데 삭제하고자하는 값이 존재하지 않을 때
		{
			printf("The node [%d] does not exist.\n\n", key); //오류 메세지 출력
			return 0; //함수 종료
		}
		else if (tempRight->key == key) //오른쪽 자식 노드가 삭제하고자하는 값을 가졌으나 리프 노드가 아닐 때
		{
			printf("The node [%d] is not a leaf node.\n\n", key); //오류 메세지 출력
			return 0; //함수 종료
		}
		else //오른쪽 자식 노드가 삭제하고자하는 값을 갖지 않고 리프 노드도 아닐 때
		{
			deleteLeafNode(tempRight, key); //오른쪽 서브 트리를 조사하기 위해 deleteLeafNode 호출
		}
	}
	else //temp가 리프 노드일 때
	{
		printf("The node [%d] does not exist.\n\n", key); //오류 메세지 출력
	}
	return 0;
}



Node* searchRecursive(Node* ptr, int key)
{	
	Node* leftResult = NULL; //왼쪽 서브 트리의 결과를 저장할 포인터 leftResult 선언 후 NULL로 초기화
	Node* rightResult = NULL; //오른쪽 서브 트리의 결과를 저장할 포인터 RighttResult 선언 후 NULL로 초기화
	Node* finalResult = NULL; //최종 결과를 저장할 포인터 finalResult 선언 후 NULL로 초기화
	if (ptr) //ptr이 NULL이 아닐 때
	{
		if (ptr->key == key) //ptr의 key 값이 찾고자하는 값과 일치할 때
		{
			return ptr; //ptr을 반환하면서 함수 종료
		}

		leftResult = searchRecursive(ptr->left, key); //ptr의 왼쪽 서브 트리 조사
		rightResult = searchRecursive(ptr->right, key); //ptr의 오른쪽 서브 트리 조사
	}
	finalResult = (leftResult != NULL) ? leftResult : rightResult; //leftResult가 NULL이 아니면 finalResult에 leftResult를 저장, NULL이면 rightResult를 저장
	return finalResult; //최종 결과인 finalResult 반환하면서 함수 종료
}

Node* searchIterative(Node* head, int key)
{
	Node* search = head->left; //노드를 찾기 위한 포인터 search 선언 후 루트 노드를 가리키도록 초기화
	Node* temp = head->left; //현재 조사하고자 하는 노드를 가리키는 포인터 temp 선언 후 루트 노드를 가리키도록 초기화 
	for (; search; search = search->right) //search가 오른쪽 자식 노드로 이동하면서 NULL이 될 때까지 반복
	{
		for (temp = search; temp; temp = temp->left) //temp는 search 노드부터 시작하여 왼쪽으로 이동하면서 NULL이 될 때까지 key 값 검사 반복
		{
			if (temp->key == key) //temp의 key 값이 찾고자하는 값과 일치할 때
			{
				return temp; //temp를 반환하면서 함수 종료
			}
		}
	}
	return NULL; //값을 찾지 못하였을 경우 NULL을 반환하면서 함수 종료
}


int freeBST(Node* head) //후위 순회 방식으로 메모리 해제
{
	if (head) 
	{ //더 이상 이동할 수 없을 때까지 recursive 방식으로 함수 호출
		freeBST(head->left); //왼쪽 자식 노드로 이동
		if (head!=head->right) //헤드 노드가 아닐 때 (헤드 노드의 오른쪽 링크는 자기 자신을 가리킴)
			freeBST(head->right); //방문 후 오른쪽 자식 노드로 이동
		free(head); //해당 노드에 대한 메모리 해제
	}
}







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
	int key;
	struct node* left;
	struct node* right;
} Node;

int initializeBST(Node** h);

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
	char command;
	int key;
	Node* head = NULL;
	Node* ptr = NULL;	/* temp */

	printf("----- [이승현] [2020039075] -----\n");

	do {
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
		scanf(" %c", &command);

		switch (command) {
		case 'z': case 'Z':
			initializeBST(&head);
			break;
		case 'q': case 'Q':
			freeBST(head);
			break;
		case 'n': case 'N':
			printf("Your Key = ");
			scanf("%d", &key);
			insert(head, key);
			break;
		case 'd': case 'D':
			printf("Your Key = ");
			scanf("%d", &key);
			deleteLeafNode(head, key);
			break;
		case 'f': case 'F':
			printf("Your Key = ");
			scanf("%d", &key);
			ptr = searchIterative(head, key);
			if (ptr != NULL)
				printf("\n node [%d] found at %p\n", ptr->key, ptr);
			else
				printf("\n Cannot find the node [%d]\n", key);
			break;
		case 's': case 'S':
			printf("Your Key = ");
			scanf("%d", &key);
			ptr = searchRecursive(head->left, key);
			if (ptr != NULL)
				printf("\n node [%d] found at %p\n", ptr->key, ptr);
			else
				printf("\n Cannot find the node [%d]\n", key);
			break;

		case 'i': case 'I':
			inorderTraversal(head->left);
			break;
		case 'p': case 'P':
			preorderTraversal(head->left);
			break;
		case 't': case 'T':
			postorderTraversal(head->left);
			break;
		default:
			printf("\n       >>>>>   Concentration!!   <<<<<     \n");
			break;
		}

	} while (command != 'q' && command != 'Q');

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

	if (head->right == head) //head가 루트 노드를 가리키는 포인터일 때
	{
		if (head->left == NULL) //루트 노드가 트리에 존재하지 않을 때
		{
			head->left = insertNode; //루트 노드로서 insertNode 노드 삽입
			return 0; //삽입 후 종료
		}
		else //루트 노드가 트리에 존재할 때
		{
			head = head->left; //head를 head의 왼쪽 노드로 변경 (temp로 이름을 바꾸기 위한 작업)
		}
	}
	
	Node* temp = head; //현재 조사하고자 하는 노드를 가리키는 포인터 temp 선언 후 head 값으로 초기화 

	if (temp->key > key) //temp의 key가 삽입하려는 값보다 클 때 temp의 왼쪽 조사
	{
		if (temp->left == NULL) //temp의 왼쪽에 노드가 존재하지 않을 때
		{
			temp->left = insertNode; //temp의 왼쪽에 새로운 노드 삽입
			return 0; //삽입 후 함수 종료
		}
		else //temp의 왼쪽에 노드가 존재할 때
			insert(temp->left, key); //temp의 왼쪽 서브트리 조사
	}
	else //temp의 key가 삽입하려는 값보다 크지 않을 때 temp의 오른쪽 조사
	{
		if (temp->right == NULL) //temp의 오른쪽에 노드가 존재하지 않을 때
		{
			temp->right = insertNode; //temp의 오른쪽에 새로운 노드 삽입
			return 0; //삽입 후 함수 종료
		}
		else //temp의 오른쪽에 노드가 존재할 때
			insert(temp->right, key); //temp의 오른쪽 서브트리 조사
	}
	return 0;
}

int deleteLeafNode(Node* head, int key)
{//head가 헤드 노드일 때와 헤드 노드가 아닐 때를 구분
	if (head->right == head)//head가 헤드 노드일 때
	{
		Node* root = head->left; //루트 노드를 가리킬 포인터 root 선언 후 head의 왼쪽 노드로 초기화
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
	Node* tempLeft = temp->left; //temp의 왼쪽 노드를 가리키는 포인터 tempLeft 선언 후 temp->left로 초기화
	Node* tempRight = temp->right; //temp의 오른쪽 노드를 가리키는 포인터 tempRight 선언 후 temp->right로 초기화

	if ((temp->key > key) & (tempLeft != NULL)) //삭제하고자하는 값보다 temp의 key값이 더 크고 temp의 왼쪽 서브 트리가 존재할 때
	{
		if ((tempLeft->left == NULL) & (tempLeft->right == NULL) & (tempLeft->key == key)) //왼쪽 노드가 삭제하고자하는 값을 가지면서 리프 노드일 때
		{
			free(tempLeft); //왼쪽 노드의 메모리 해제
			temp->left = NULL; //temp의 왼쪽 링크는 NULL을 가리킴
			return 0; //함수 종료
		}
		else if((tempLeft->left == NULL) & (tempLeft->right == NULL)) //왼쪽 노드가 리프 노드인데 삭제하고자하는 값이 존재하지 않을 때
		{
			printf("The node [%d] does not exist.\n\n", key); //오류 메세지 출력
			return 0; //함수 종료
		}
		else if (tempLeft->key == key) //왼쪽 노드가 삭제하고자하는 값을 가졌으나 리프 노드가 아닐 때
		{
			printf("The node [%d] is not a leaf node.\n\n", key); //오류 메세지 출력
			return 0; //함수 종료
		}
		else //왼쪽 노드가 삭제하고자하는 값을 갖지 않고 리프 노드도 아닐 때
		{
			deleteLeafNode(tempLeft, key); //왼쪽 서브 트리를 조사하기 위해 deleteLeafNode 호출
		}
	}
	else if ((temp->key < key) & (tempRight != NULL)) //temp의 key값보다 삭제하고자하는 값이 더 크고 temp의 오른쪽 서브 트리가 존재할 때
	{
		if ((tempRight->left == NULL) & (tempRight->right == NULL) & (tempRight->key == key)) //오른쪽 노드가 삭제하고자하는 값을 가지면서 리프 노드일 때
		{
			free(tempRight); //오른쪽 노드의 메모리 해제
			temp->right = NULL; //temp의 오른쪽 링크는 NULL을 가리킴
			return 0; //함수 종료
		}
		else if ((tempRight->left == NULL) & (tempRight->right == NULL)) //오른쪽 노드가 리프 노드인데 삭제하고자하는 값이 존재하지 않을 때
		{
			printf("The node [%d] does not exist.\n\n", key); //오류 메세지 출력
			return 0; //함수 종료
		}
		else if (tempRight->key == key) //오른쪽 노드가 삭제하고자하는 값을 가졌으나 리프 노드가 아닐 때
		{
			printf("The node [%d] is not a leaf node.\n\n", key); //오류 메세지 출력
			return 0; //함수 종료
		}
		else //오른쪽 노드가 삭제하고자하는 값을 갖지 않고 리프 노드도 아닐 때
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

}

Node* searchIterative(Node* head, int key)
{

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







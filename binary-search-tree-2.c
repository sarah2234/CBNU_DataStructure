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
	int key;
	struct node* left;
	struct node* right;
} Node;

/* for stack */
#define MAX_STACK_SIZE		20
Node* stack[MAX_STACK_SIZE];
int top = -1;

Node* pop();
void push(Node* aNode);

/* for queue */
#define MAX_QUEUE_SIZE		20
Node* queue[MAX_QUEUE_SIZE];
int front = -1;
int rear = -1;

Node* deQueue();
void enQueue(Node* aNode);


int initializeBST(Node** h);

/* functions that you have to implement */
void recursiveInorder(Node* ptr);	  /* recursive inorder traversal */
void iterativeInorder(Node* ptr);     /* iterative inorder traversal */
void levelOrder(Node* ptr);	          /* level order traversal */
int insert(Node* head, int key);      /* insert a node to the tree */
int deleteNode(Node* head, int key);  /* delete the node for the key */
int freeBST(Node* head); /* free all memories allocated to the tree */

/* you may add your own defined functions if necessary */
int deleteLeftNode(Node* parent, Node* leftChild, int key); //���� �ڽ� ��带 �����ϱ� ���� �Լ�
int deleteRightNode(Node* parent, Node* rightChild, int key); //������ �ڽ� ��带 �����ϱ� ���� �Լ�


void printStack();



int main()
{
	char command;
	int key;
	Node* head = NULL;

	printf("----- [�̽���] [2020039075] -----\n");

	do {
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
		scanf(" %c", &command);

		switch (command) {
		case 'z': case 'Z':
			initializeBST(&head);
			break;
		case 'q': case 'Q':
			freeBST(head);
			break;
		case 'i': case 'I':
			printf("Your Key = ");
			scanf("%d", &key);
			insert(head, key);
			break;
		case 'd': case 'D':
			printf("Your Key = ");
			scanf("%d", &key);
			deleteNode(head, key);
			break;

		case 'r': case 'R':
			recursiveInorder(head->left);
			break;
		case 't': case 'T':
			iterativeInorder(head->left);
			break;

		case 'l': case 'L':
			levelOrder(head->left);
			break;

		case 'p': case 'P':
			printStack();
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
	for (;;) //���� ������ �� ������ for�� �ݺ�
	{
		for (; node; node = node->left) //node�� ���� �ڽ� ���� �ٲٸ鼭 NULL�� �Ǳ� ������ �ݺ�
		{
			push(node); //node�� ���ÿ� ����
		}
		node = pop(); //���ÿ��� ������ �� ������� node�� ����
		if (!node) //node�� NULL, �� ������ ���� ������ ��
			break; //for (;;)�� �ݺ� ����
		printf(" [%d] ", node->key); //pop�� ������� ������ node�� key �� ���
		node = node->right; //node�� ������ �ڽ� ���� �ٲ�
	}
}

/**
 * textbook: p 225
 */
void levelOrder(Node* ptr)
{
	if (!ptr) //Ʈ���� ������ ��
	{
		return; //�Լ� ����
	}
	enQueue(ptr); //ptr ��带 ť�� ����
	for (;;) //��尡 ť�� �������� �ʾ� �Լ� deQueue�� NULL�� ��ȯ�� ������ for�� �ݺ�
	{
		ptr = deQueue(); //ť���� ��带 ������ �� ������� ptr�� ����
		if (ptr) //ptr�� NULL�� �ƴ� ��
		{
			printf(" [%d] ", ptr->key); //ptr�� key �� ���
			if (ptr->left) //ptr�� ���� �ڽ� ��尡 ������ ��
				enQueue(ptr->left); //���� �ڽ� ��带 ť�� ����
			if (ptr->right) //ptr�� ������ �ڽ� ��尡 ������ ��
				enQueue(ptr->right); //������ �ڽ� ��带 ť�� ����
		}
		else //ptr�� NULL, �� ���̻� ť�� ��尡 �������� ���� ��
		{
			break; //for (;;)�� �ݺ� ����
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
	if (head->right == head) //head�� ��� ��带 ����ų ��
	{
		head = head->left; //head�� ��Ʈ ��带 ����Ű���� ����
	}
	Node* temp = head; //�Է¹��� key ���� ���� ��带 ����Ű�� ������ temp ���� �� head�� �ʱ�ȭ

	if (temp->key == key) //��� ���
	{

		return 0;
	}

	if ((temp->key > key) & (temp->left != NULL)) //�����ϰ����ϴ� ������ temp�� key���� �� ũ�� temp�� ���� ���� Ʈ���� ������ �� ���� �ڽ� ��� ����
	{
		if(temp->left->key == key) //temp�� ���� �ڽ� ��尡 �����ϰ����ϴ� ��忡 �ش��� ��
		{
			deleteLeftNode(temp, temp->left, key); //���� �ڽ� ��带 �����ϰ��� deleteLeftNode ȣ��
		}
		else //���� �ڽ� ��尡 �����ϰ����ϴ� ��忡 �ش����� ���� ��
		{
			deleteNode(temp->left, key); //���� ���� Ʈ���� �����ϱ� ���� deleteNode ȣ��
		}
	}
}

int deleteLeftNode(Node* parent, Node* leftChild, int key)
{
	//leftChild�� �����ϰ����ϴ� ��忡 �ش��ϰ�, parent�� leftChild�� �θ� ���
	
	if ((leftChild->left == NULL) & (leftChild->right == NULL)) //leftChild�� ���� ����� ��
	{
		free(leftChild); //�����Ϸ��� ����� �޸� ����
		parent->left = NULL; //leftChild�� �θ� ��� parent�� ���� ��ũ�� NULL�� ����Ŵ
		return 0; //���� �� �Լ� ����
	}

	else if ((leftChild->right == NULL)) //leftChild�� ���� �ڽ� ��尡 ���� ��
	{
		parent->left = leftChild->left; //�θ� ��� parent�� ���� �ڽ� ���� leftChild�� ���� �ڽ� ��尡 ��
		free(leftChild); //�����Ϸ��� ����� �޸� ����
		return 0; //���� �� �Լ� ����
	}

	else if ((leftChild->left == NULL)) //leftChild�� ������ �ڽ� ��尡 ���� ��
	{
		parent->right = leftChild->right; //�θ� ��� parent�� ������ �ڽ� ���� leftChild�� ������ �ڽ� ��尡 ��
		free(leftChild); //�����Ϸ��� ����� �޸� ����
		return 0; //���� �� �Լ� ����
	}

	else //leftChild�� �����ʰ� ���ʿ� �ڽ� ��尡 ���� ��
	{
		Node* linkNode = leftChild->right; //leftChild�� ������ ���� Ʈ������ ���� �������� ��带 ã���� linkNode ���� �� leftChild->right�� �ʱ�ȭ
		Node* previous = NULL; //linkNode ������ ��带 ����Ű�� ������ previous ���� �� NULL�� �ʱ�ȭ

		for (; linkNode->left; linkNode = linkNode->left) //linkNode�� ���� �ڽ� ���� �Űܰ��鼭 linkNode�� ���� �ڽ� ��尡 ���� ������ for�� �ݺ�
		{
			previous = linkNode; //linkNode�� ������ �湮�ߴ� ��带 ����Ű�� previous�� linkNode�� ����
		}
		//linkNode�� ���� �ڽ� ��尡 ������ �ش� ��尡 leftChild�� ������ ���� Ʈ�� �߿��� �ּҰ��� ���� ����̴�.
		//���� for ���� ������� �ʰ�, previous�� ó���� �ʱ�ȭ���־��� NULL���� ��� ������ �ְ� �ȴ�.
		
		if (previous != NULL) //tempLeft�� ������ �ڽ� ��尡 ������ ���� Ʈ������ �ּҰ��� ������ ���� ��
		{
			previous->left = linkNode->right; //linkNode ������ ��� previous�� ���� �ڽ� ���� linkNode�� ������ �ڽ� ��尡 ��
			linkNode->right = leftChild->right; //linkNode�� ������ �ڽ� ���� leftChild�� ������ �ڽ� ��尡 ��
			linkNode->left = leftChild->left; //linkNode�� ���� �ڽ� ���� leftChild�� ���� �ڽ� ��尡 ��
			parent->left = linkNode; //parent�� ���� �ڽ� ���� linkNode�� ��
			free(leftChild); //�����Ϸ��� ����� �޸� ����
			return 0; //���� �� �Լ� ����
		}
		else //tempLeft�� ������ �ڽ� ��尡 ������ ���� Ʈ������ �ּҰ��� ���� ��
		{
			linkNode->left = leftChild->left; //linkNode�� ���� �ڽ� ���� leftChild�� ���� �ڽ� ��尡 ��
			parent->left = linkNode; //parent�� ���� �ڽ� ���� linkNode�� ��
			free(leftChild); //�����Ϸ��� ����� �޸� ����
			return 0; //���� �� �Լ� ����
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
	if (top == -1) //������ ������ ��
	{
		return NULL; //NULL ��ȯ
	}
	Node* node = stack[top]; //������ node�� ������ top�� �ش��ϴ� ��� ����
	stack[top--] = '\0'; //������ top�� �ش��ϴ� ��� ���� �� top�� 1 ����
	return node; //node ��ȯ
}

void push(Node* aNode)
{
	if (top >= MAX_STACK_SIZE) //������ ������ ��
	{
		printf("Unable to insert [%d] into the stack.\n", aNode->key); //���� �޼��� ���
		return; //�Լ� ����
	}
	stack[++top] = aNode; //top�� ������Ű�鼭 ���ÿ� aNode ����
}



Node* deQueue()
{
	if (front == rear) //ť�� ������ ��
	{
		return NULL; //NULL ��ȯ
	}
	front = (front + 1) % MAX_QUEUE_SIZE; //ť�� front�� 1 ������Ŵ
	Node* node = queue[front]; //������ node�� ť�� front�� �ش��ϴ� ��� ����
	queue[front] = '\0'; //ť�� front�� �ش��ϴ� ��� ����
	return node; //node ��ȯ
}

void enQueue(Node* aNode)
{
	if (front == (rear + 1) % MAX_QUEUE_SIZE)
	{
		printf("Unable to insert [%d] into the queue.\n", aNode->key); //���� �޼��� ���
		return; //�Լ� ����
	}
	queue[++rear] = aNode; //rear�� 1 ������ �� ť�� aNode ����
}

void printStack()
{

}
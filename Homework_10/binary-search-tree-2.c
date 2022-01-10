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
	int key; //����� ���� �����ϴ� key ����
	struct node* left; //���� �ڽ� ��带 ����Ű�� ������ left ����
	struct node* right; //������ �ڽ� ��带 ����Ű�� ������ right ����
} Node; //��带 �����ϱ� ���� ����ü node ���� �� Node�� ������

/* for stack */
#define MAX_STACK_SIZE		20 //������ �ִ�� ������ �� �ִ� ����� ������ 20
Node* stack[MAX_STACK_SIZE]; //��带 �����ϴ� ���� ���� (���� ��ȸ�� ���)
int top = -1; //������ ��ġ�� �˷��ִ� top ���� �� -1�� �ʱ�ȭ

Node* pop(); //������ ��带 �����ϴ� �Լ�
void push(Node* aNode); //���ÿ� aNode ��带 �����ϴ� �Լ�

/* for queue */
#define MAX_QUEUE_SIZE		20 //ť�� �ִ�� ������ �� �ִ� ����� ������ 19
Node* queue[MAX_QUEUE_SIZE]; //��带 �����ϴ� ť ���� (���� ���� ��ȸ�� ���)
int front = -1; //ť���� ������ ��ġ�� ����Ű�� front ���� �� -1�� �ʱ�ȭ
int rear = -1; //ť���� ������ ��ġ�� ����Ű�� rear ���� �� -1�� �ʱ�ȭ

Node* deQueue(); //ť�� ��带 �����ϴ� �Լ�
void enQueue(Node* aNode); //ť�� aNode ��带 �����ϴ� �Լ�


int initializeBST(Node** h); //Ʈ���� �ʱ�ȭ�ϴ� �Լ�

/* functions that you have to implement */
void recursiveInorder(Node* ptr);	  /* recursive inorder traversal */
void iterativeInorder(Node* ptr);     /* iterative inorder traversal */
void levelOrder(Node* ptr);	          /* level order traversal */
int insert(Node* head, int key);      /* insert a node to the tree */
int deleteNode(Node* head, int key);  /* delete the node for the key */
int freeBST(Node* head); /* free all memories allocated to the tree */

/* you may add your own defined functions if necessary */
int deleteLeftChildNode(Node* parent, Node* leftChild); //���� �ڽ� ��带 �����ϱ� ���� �Լ�
int deleteRightChildNode(Node* parent, Node* rightChild); //������ �ڽ� ��带 �����ϱ� ���� �Լ�







int main()
{
	char command; //���ɾ �Է¹ޱ� ���� command ���� ����
	int key; //���� �Է¹ޱ� ���� key ���� ����
	Node* head = NULL; //Ʈ���� ��� ��带 ����Ű�� ������ head ���� �� Ʈ�� ���� �� NULL�� ����Ű���� �ʱ�ȭ

	printf("----- [�̽���] [2020039075] -----\n");

	do { //'q' �Ǵ� 'Q' �� �Է¹��� ������ �ּ� 1ȸ �̻� �ݺ� ����
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
		scanf(" %c", &command); //���ɾ �Է¹޾� command�� ����

		switch (command) {
		case 'z': case 'Z': //command�� 'z' �Ǵ� 'Z'�� ��
			initializeBST(&head); //head�� �޸� �Ҵ��Ͽ� Ʈ�� ����
			break;
		case 'q': case 'Q': //command�� 'q' �Ǵ� 'Q'�� ��
			freeBST(head); //Ʈ���� ���� �޸� ����
			break;
		case 'i': case 'I': //command�� 'i' �Ǵ� 'I'�� ��
			printf("Your Key = ");
			scanf("%d", &key); //������ �� �Է�
			insert(head, key); //Ʈ���� �ش� ���� ���� ��� ����
			break;
		case 'd': case 'D': //command�� 'd' �Ǵ� 'D'�� ��
			printf("Your Key = ");
			scanf("%d", &key); //������ �� �Է�
			deleteNode(head, key); //Ʈ������ �ش� ���� ���� ��� ����
			break;
		case 'r': case 'R': //command�� 'r' �Ǵ� 'R'�� ��
			recursiveInorder(head->left); //��ȯ�� ���� ��ȸ�� ����Ͽ� ��� ���
			break;
		case 't': case 'T': //command�� 't' �Ǵ� 'T'�� ��
			iterativeInorder(head->left); //�ݺ��� ���� ��ȸ�� ����Ͽ� ��� ���
			break;
		case 'l': case 'L': //command�� 'l' �Ǵ� 'L'�� ��
			levelOrder(head->left); //���� ���� ��ȸ�� ����Ͽ� ��� ���
			break;


		default: //command�� ����� ���� �̿��� ���� ��
			printf("\n       >>>>>   Concentration!!   <<<<<     \n"); //���� �޼��� ���
			break;
		}

	} while (command != 'q' && command != 'Q'); //command�� 'q' �Ǵ� 'Q'�� �Է¹����� �ݺ��� ����

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
	if (ptr) { //ptr�� NULL�� �ƴ� �� ��ȯ�� ���� ��ȸ ������� ��� ���
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
	Node* newNode = (Node*)malloc(sizeof(Node)); //Ʈ���� ������ ���ο� ��带 ����Ű�� newNode ���� �� �޸� �Ҵ�
	newNode->key = key;
	newNode->left = NULL; //newNode�� ���� ���μ� ���ԵǹǷ�, �ڽ� ��尡 �������� ����
	newNode->right = NULL;

	if (head->left == NULL) { //��Ʈ ��尡 �������� ���� ��
		head->left = newNode; //��Ʈ ���μ� newNode�� Ʈ���� ����
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
	Node* temp = head; //�Է¹��� key ���� ���� ��带 ����Ű�� ������ temp ���� �� head�� �ʱ�ȭ
	if (temp->right == temp) //temp�� ��� ��带 ����ų ��
	{
		temp = temp->left; //temp�� ��Ʈ ��带 ����Ű���� ����
	}

	if (temp->key == key) //��Ʈ ��尡 �����ϰ����ϴ� ��忡 �ش��� ��
	{
		deleteLeftChildNode(head, temp); //��Ʈ ��带 �����ϰ��� deleteLeftChildNode ȣ��
		return 0; //���� �� �Լ� ����
	}

	if ((temp->key > key) & (temp->left != NULL)) //�����ϰ����ϴ� ������ temp�� key���� �� ũ�� temp�� ���� ���� Ʈ���� ������ ��, ���� �ڽ� ��� ����
	{
		if(temp->left->key == key) //temp�� ���� �ڽ� ��尡 �����ϰ����ϴ� ��忡 �ش��� ��
		{
			deleteLeftChildNode(temp, temp->left); //���� �ڽ� ��带 �����ϰ��� deleteLeftChildNode ȣ��
			return 0; //���� �� �Լ� ����
		}
		else //���� �ڽ� ��尡 �����ϰ����ϴ� ��忡 �ش����� ���� ��
		{
			deleteNode(temp->left, key); //���� ���� Ʈ���� �����ϱ� ���� deleteNode ȣ��
		}
	}

	else if ((temp->key < key) & (temp->right != NULL)) //�����ϰ����ϴ� ������ temp�� key���� �� �۰� temp�� ������ ���� Ʈ���� ������ ��, ������ �ڽ� ��� ����
	{
		if (temp->right->key == key) //temp�� ������ �ڽ� ��尡 �����ϰ����ϴ� ��忡 �ش��� ��
		{
			deleteRightChildNode(temp, temp->right); //������ �ڽ� ��带 �����ϰ��� deleteRightChildNode ȣ��
			return 0; //���� �� �Լ� ����
		}
		else //������ �ڽ� ��尡 �����ϰ����ϴ� ��忡 �ش����� ���� ��
		{
			deleteNode(temp->right, key); //������ ���� Ʈ���� �����ϱ� ���� deleteNode ȣ��
		}
	}

	else //temp�� ���� ����� ��
	{
		printf("The node [%d] does not exist.\n\n", key); //���� �޼��� ���
	}
}

int deleteLeftChildNode(Node* parent, Node* leftChild)
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
		parent->left = leftChild->right; //�θ� ��� parent�� ���� �ڽ� ���� leftChild�� ������ �ڽ� ��尡 ��
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
		
		if (previous != NULL) //leftChild�� ������ �ڽ� ��尡 ������ ���� Ʈ������ �ּҰ��� ������ ���� ��
		{
			previous->left = linkNode->right; //linkNode ������ ��� previous�� ���� �ڽ� ���� linkNode�� ������ �ڽ� ��尡 ��
			linkNode->right = leftChild->right; //linkNode�� ������ �ڽ� ���� leftChild�� ������ �ڽ� ��尡 ��
			linkNode->left = leftChild->left; //linkNode�� ���� �ڽ� ���� leftChild�� ���� �ڽ� ��尡 ��
			parent->left = linkNode; //parent�� ���� �ڽ� ��尡 linkNode�� �ǵ��� ��
			free(leftChild); //�����Ϸ��� ����� �޸� ����
			return 0; //���� �� �Լ� ����
		}
		else //leftChild�� ������ �ڽ� ��尡 ������ ���� Ʈ������ �ּҰ��� ���� ��
		{
			linkNode->left = leftChild->left; //linkNode�� ���� �ڽ� ���� leftChild�� ���� �ڽ� ��尡 ��
			parent->left = linkNode; //parent�� ���� �ڽ� ���� linkNode�� ��
			free(leftChild); //�����Ϸ��� ����� �޸� ����
			return 0; //���� �� �Լ� ����
		}
	}
}

int deleteRightChildNode(Node* parent, Node* rightChild)
{
	//rightChild�� �����ϰ����ϴ� ��忡 �ش��ϰ�, parent�� rightChild�� �θ� ���

	if ((rightChild->left == NULL) & (rightChild->right == NULL)) //rightChild�� ���� ����� ��
	{
		free(rightChild); //�����Ϸ��� ����� �޸� ����
		parent->right = NULL; //rightChild�� �θ� ��� parent�� ������ ��ũ�� NULL�� ����Ŵ
		return 0; //���� �� �Լ� ����
	}

	else if ((rightChild->right == NULL)) //rightChild�� ���� �ڽ� ��尡 ���� ��
	{
		parent->right = rightChild->left; //�θ� ��� parent�� ������ �ڽ� ���� rightChild�� ���� �ڽ� ��尡 ��
		free(rightChild); //�����Ϸ��� ����� �޸� ����
		return 0; //���� �� �Լ� ����
	}

	else if ((rightChild->left == NULL)) //rightChild�� ������ �ڽ� ��尡 ���� ��
	{
		parent->right = rightChild->right; //�θ� ��� parent�� ������ �ڽ� ���� rightChild�� ������ �ڽ� ��尡 ��
		free(rightChild); //�����Ϸ��� ����� �޸� ����
		return 0; //���� �� �Լ� ����
	}

	else //rightChild�� �����ʰ� ���ʿ� �ڽ� ��尡 ���� ��
	{
		Node* linkNode = rightChild->right; //rightChild�� ������ ���� Ʈ������ ���� �������� ��带 ã���� linkNode ���� �� rightChild->right�� �ʱ�ȭ
		Node* previous = NULL; //linkNode ������ ��带 ����Ű�� ������ previous ���� �� NULL�� �ʱ�ȭ

		for (; linkNode->left; linkNode = linkNode->left) //linkNode�� ���� �ڽ� ���� �Űܰ��鼭 linkNode�� ���� �ڽ� ��尡 ���� ������ for�� �ݺ�
		{
			previous = linkNode; //linkNode�� ������ �湮�ߴ� ��带 ����Ű�� previous�� linkNode�� ����
		}
		//linkNode�� ���� �ڽ� ��尡 ������ �ش� ��尡 child�� ������ ���� Ʈ�� �߿��� �ּҰ��� ���� ����̴�.
		//���� for ���� ������� �ʰ�, previous�� ó���� �ʱ�ȭ���־��� NULL���� ��� ������ �ְ� �ȴ�.

		if (previous != NULL) //rightChild�� ������ �ڽ� ��尡 ������ ���� Ʈ������ �ּҰ��� ������ ���� ��
		{
			previous->left = linkNode->right; //linkNode ������ ��� previous�� ���� �ڽ� ���� linkNode�� ������ �ڽ� ��尡 ��
			linkNode->right = rightChild->right; //linkNode�� ������ �ڽ� ���� rightChild�� ������ �ڽ� ��尡 ��
			linkNode->left = rightChild->left; //linkNode�� ���� �ڽ� ���� rightChild�� ���� �ڽ� ��尡 ��
			parent->right = linkNode; //parent�� ������ �ڽ� ��尡 linkNode�� �ǵ��� ��
			free(rightChild); //�����Ϸ��� ����� �޸� ����
			return 0; //���� �� �Լ� ����
		}
		else //rightChild�� ������ �ڽ� ��尡 ������ ���� Ʈ������ �ּҰ��� ���� ��
		{
			linkNode->left = rightChild->left; //linkNode�� ���� �ڽ� ���� rightChild�� ���� �ڽ� ��尡 ��
			parent->right = linkNode; //parent�� ������ �ڽ� ���� linkNode�� ��
			free(rightChild); //�����Ϸ��� ����� �޸� ����
			return 0; //���� �� �Լ� ����
		}
	}
}

void freeNode(Node* ptr)
{
	if (ptr) { //ptr�� NULL�� �ƴ� ��
		freeNode(ptr->left); //ptr�� ���� ���� Ʈ���� �޸𸮸� �����ϰ��� freeNode ȣ��
		freeNode(ptr->right); //ptr�� ������ ���� Ʈ���� �޸𸮸� �����ϰ��� freeNode ȣ��
		free(ptr); //ptr�� �޸� ����
	}
}

int freeBST(Node* head)
{

	if (head->left == head) //head�� ��� ��带 ����ų ��
	{
		free(head); //��� ����� �޸� ����
		return 1; //�Լ� ����
	}

	Node* p = head->left; //p ���� �� head�� ���� �ڽ� ��带 ����Ű���� �ʱ�ȭ

	freeNode(p); //p�� p�� �ļ� ����� �޸𸮸� �����ϰ��� freeNode ȣ��

	free(head); //head�� �޸� ����
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
	if (front == (rear + 1) % MAX_QUEUE_SIZE) //ť�� ������ ��
	{
		printf("Unable to insert [%d] into the queue.\n", aNode->key); //���� �޼��� ���
		return; //�Լ� ����
	}
	rear = (rear + 1) % MAX_QUEUE_SIZE;
	queue[rear] = aNode; //rear�� 1 ������ �� ť�� aNode ����
}
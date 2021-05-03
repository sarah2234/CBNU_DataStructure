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

	printf("----- [�̽���] [2020039075] -----\n");

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
	if (ptr) { //�� �̻� �̵��� �� ���� ������ recursive ������� �Լ� ȣ��
		inorderTraversal(ptr->left); //���� �ڽ� ���� �̵�
		printf("[%d] ", ptr->key); //�ش� ��� �湮
		inorderTraversal(ptr->right); //�湮 �� ������ �ڽ� ���� �̵�
	}
}

void preorderTraversal(Node* ptr)
{
	if (ptr) { //�� �̻� �̵��� �� ���� ������ recursive ������� �Լ� ȣ��
		printf("[%d] ", ptr->key); //�ش� ��� �湮
		preorderTraversal(ptr->left); //���� �ڽ� ���� �̵�
		preorderTraversal(ptr->right); //�湮 �� ������ �ڽ� ���� �̵�
	}
}

void postorderTraversal(Node* ptr)
{
	if (ptr) { //�� �̻� �̵��� �� ���� ������ recursive ������� �Լ� ȣ��
		postorderTraversal(ptr->left); //���� �ڽ� ���� �̵�
		postorderTraversal(ptr->right); //�湮 �� ������ �ڽ� ���� �̵�
		printf("[%d] ", ptr->key); //�ش� ��� �湮
	}
}


int insert(Node* head, int key)
{
	Node* insertNode = (Node*)malloc(sizeof(Node)); //���ο� ��带 �����ϱ� ���� ������ insertNode ���� �� �޸� �Ҵ� 
	insertNode->key = key; //�����ϰ����ϴ� ���� insertNode�� key�� ����
	insertNode->left = NULL; //insertNode�� ���� ����̹Ƿ� ���� ��ũ�� NULL�� ����Ŵ
	insertNode->right = NULL; //insertNode�� ���� ����̹Ƿ� ������ ��ũ�� NULL�� ����Ŵ

	if (head->right == head) //head�� ��Ʈ ��带 ����Ű�� �������� ��
	{
		if (head->left == NULL) //��Ʈ ��尡 Ʈ���� �������� ���� ��
		{
			head->left = insertNode; //��Ʈ ���μ� insertNode ��� ����
			return 0; //���� �� ����
		}
		else //��Ʈ ��尡 Ʈ���� ������ ��
		{
			head = head->left; //head�� head�� ���� ���� ���� (temp�� �̸��� �ٲٱ� ���� �۾�)
		}
	}
	
	Node* temp = head; //���� �����ϰ��� �ϴ� ��带 ����Ű�� ������ temp ���� �� head ������ �ʱ�ȭ 

	if (temp->key > key) //temp�� key�� �����Ϸ��� ������ Ŭ �� temp�� ���� ����
	{
		if (temp->left == NULL) //temp�� ���ʿ� ��尡 �������� ���� ��
		{
			temp->left = insertNode; //temp�� ���ʿ� ���ο� ��� ����
			return 0; //���� �� �Լ� ����
		}
		else //temp�� ���ʿ� ��尡 ������ ��
			insert(temp->left, key); //temp�� ���� ����Ʈ�� ����
	}
	else //temp�� key�� �����Ϸ��� ������ ũ�� ���� �� temp�� ������ ����
	{
		if (temp->right == NULL) //temp�� �����ʿ� ��尡 �������� ���� ��
		{
			temp->right = insertNode; //temp�� �����ʿ� ���ο� ��� ����
			return 0; //���� �� �Լ� ����
		}
		else //temp�� �����ʿ� ��尡 ������ ��
			insert(temp->right, key); //temp�� ������ ����Ʈ�� ����
	}
	return 0;
}

int deleteLeafNode(Node* head, int key)
{//head�� ��� ����� ���� ��� ��尡 �ƴ� ���� ����
	if (head->right == head)//head�� ��� ����� ��
	{
		Node* root = head->left; //��Ʈ ��带 ����ų ������ root ���� �� head�� ���� ���� �ʱ�ȭ
		if (root == NULL) //��Ʈ ��尡 �������� ���� ��
		{
			printf("The node [%d] does not exist.\n\n", key); //���� �޼��� ���
			return 0; //�Լ� ����
		}
		else if ((root->left == NULL) & (root->right == NULL) & (root->key == key)) //��Ʈ ��尡 �����ϰ����ϴ� ���� �����鼭 ���� ����� ��
		{
			free(root); //��Ʈ ��忡 �Ҵ�Ǿ��� �޸� ����
			head->left = NULL; //��� ����� ���� ��ũ�� NULL�� ����Ŵ
			return 0; //�Լ� ����
		}
		else if(root->key == key) //��Ʈ ��尡 �����ϰ����ϴ� ���� ������ ���� ��忡 �ش���� ���� ��
		{
			printf("The node [%d] is not a leaf node.\n\n", key); //���� �޼��� ���
			return 0; //�Լ� ����
		}

		head = head->left; //head�� ��� ��忡 �ش�Ǹ� ��Ʈ ��带 ����Ű���� ��
	}

	Node* temp = head; //�����ϰ����ϴ� ����� �θ� ��带 ����Ű�� ������ temp ���� �� head ������ �ʱ�ȭ 
	Node* tempLeft = temp->left; //temp�� ���� ��带 ����Ű�� ������ tempLeft ���� �� temp->left�� �ʱ�ȭ
	Node* tempRight = temp->right; //temp�� ������ ��带 ����Ű�� ������ tempRight ���� �� temp->right�� �ʱ�ȭ

	if ((temp->key > key) & (tempLeft != NULL)) //�����ϰ����ϴ� ������ temp�� key���� �� ũ�� temp�� ���� ���� Ʈ���� ������ ��
	{
		if ((tempLeft->left == NULL) & (tempLeft->right == NULL) & (tempLeft->key == key)) //���� ��尡 �����ϰ����ϴ� ���� �����鼭 ���� ����� ��
		{
			free(tempLeft); //���� ����� �޸� ����
			temp->left = NULL; //temp�� ���� ��ũ�� NULL�� ����Ŵ
			return 0; //�Լ� ����
		}
		else if((tempLeft->left == NULL) & (tempLeft->right == NULL)) //���� ��尡 ���� ����ε� �����ϰ����ϴ� ���� �������� ���� ��
		{
			printf("The node [%d] does not exist.\n\n", key); //���� �޼��� ���
			return 0; //�Լ� ����
		}
		else if (tempLeft->key == key) //���� ��尡 �����ϰ����ϴ� ���� �������� ���� ��尡 �ƴ� ��
		{
			printf("The node [%d] is not a leaf node.\n\n", key); //���� �޼��� ���
			return 0; //�Լ� ����
		}
		else //���� ��尡 �����ϰ����ϴ� ���� ���� �ʰ� ���� ��嵵 �ƴ� ��
		{
			deleteLeafNode(tempLeft, key); //���� ���� Ʈ���� �����ϱ� ���� deleteLeafNode ȣ��
		}
	}
	else if ((temp->key < key) & (tempRight != NULL)) //temp�� key������ �����ϰ����ϴ� ���� �� ũ�� temp�� ������ ���� Ʈ���� ������ ��
	{
		if ((tempRight->left == NULL) & (tempRight->right == NULL) & (tempRight->key == key)) //������ ��尡 �����ϰ����ϴ� ���� �����鼭 ���� ����� ��
		{
			free(tempRight); //������ ����� �޸� ����
			temp->right = NULL; //temp�� ������ ��ũ�� NULL�� ����Ŵ
			return 0; //�Լ� ����
		}
		else if ((tempRight->left == NULL) & (tempRight->right == NULL)) //������ ��尡 ���� ����ε� �����ϰ����ϴ� ���� �������� ���� ��
		{
			printf("The node [%d] does not exist.\n\n", key); //���� �޼��� ���
			return 0; //�Լ� ����
		}
		else if (tempRight->key == key) //������ ��尡 �����ϰ����ϴ� ���� �������� ���� ��尡 �ƴ� ��
		{
			printf("The node [%d] is not a leaf node.\n\n", key); //���� �޼��� ���
			return 0; //�Լ� ����
		}
		else //������ ��尡 �����ϰ����ϴ� ���� ���� �ʰ� ���� ��嵵 �ƴ� ��
		{
			deleteLeafNode(tempRight, key); //������ ���� Ʈ���� �����ϱ� ���� deleteLeafNode ȣ��
		}
	}
	else //temp�� ���� ����� ��
	{
		printf("The node [%d] does not exist.\n\n", key); //���� �޼��� ���
	}
	return 0;
}



Node* searchRecursive(Node* ptr, int key)
{

}

Node* searchIterative(Node* head, int key)
{

}


int freeBST(Node* head) //���� ��ȸ ������� �޸� ����
{
	if (head) 
	{ //�� �̻� �̵��� �� ���� ������ recursive ������� �Լ� ȣ��
		freeBST(head->left); //���� �ڽ� ���� �̵�
		if (head!=head->right) //��� ��尡 �ƴ� �� (��� ����� ������ ��ũ�� �ڱ� �ڽ��� ����Ŵ)
			freeBST(head->right); //�湮 �� ������ �ڽ� ���� �̵�
		free(head); //�ش� ��忡 ���� �޸� ����
	}
}







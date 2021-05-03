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
	int key; //����� ���� �����ϴ� key ����
	struct node* left; //���� �ڽ� ��带 ����Ű�� ������ left ����
	struct node* right; //������ ��带 ����Ű�� ������ right ����
} Node; //��带 �����ϱ� ���� ����ü node ���� �� Node�� ������

int initializeBST(Node** h); //Ʈ���� �ʱ�ȭ�ϴ� intializeBST �Լ� ����

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
	char command; //��ɾ �Է¹ޱ� ���� command ���� ����
	int key; //���� �Է¹ޱ� ���� key ���� ����
	Node* head = NULL; //Ʈ���� ��� ��带 ����Ű�� ������ head ���� �� Ʈ�� ���� �� NULL�� ����Ű���� �ʱ�ȭ
	Node* ptr = NULL;	/* temp */

	printf("----- [�̽���] [2020039075] -----\n");

	do { //�ݺ��� �ּ� 1�� �̻� ����
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
		scanf(" %c", &command); //��ɾ �Է¹޾� command�� ����

		switch (command) {
		case 'z': case 'Z': //command�� 'z' �Ǵ� 'Z'�� ��
			initializeBST(&head); //head�� �޸� �Ҵ��Ͽ� Ʈ�� ����
			break;
		case 'q': case 'Q': //command�� 'q' �Ǵ� 'Q'�� ��
			freeBST(head); //Ʈ���� ���� �޸� ����
			break;
		case 'n': case 'N': //command�� 'n' �Ǵ� 'N'�� ��
			printf("Your Key = ");
			scanf("%d", &key); //������ �� �Է�
			insert(head, key); //Ʈ���� �ش� ���� ���� ��� ����
			break;
		case 'd': case 'D': //command�� 'd' �Ǵ� 'D'�� ��
			printf("Your Key = ");
			scanf("%d", &key); //������ �� �Է�
			deleteLeafNode(head, key); //Ʈ������ �ش� ���� ���� ��� ����
			break;
		case 'f': case 'F': //command�� 'f' �Ǵ� 'F'�� ��
			printf("Your Key = ");
			scanf("%d", &key); //�˻��� �� �Է�
			ptr = searchIterative(head, key); //Ʈ������ �ش� ���� ���� ��带 �ݺ������� �˻��Ͽ� ����� ptr�� ����
			if (ptr != NULL) //Ʈ���� �ش� ��尡 ������ ��
				printf("\n node [%d] found at %p\n", ptr->key, ptr); //ptr�� key ���� �ּ� ���
			else //Ʈ���� �ش� ��尡 �������� ���� ��
				printf("\n Cannot find the node [%d]\n", key); //���� �޼��� ���
			break;
		case 's': case 'S': //command�� 's' �Ǵ� 'S'�� ��
			printf("Your Key = ");
			scanf("%d", &key); //�˻��� �� �Է�
			ptr = searchRecursive(head->left, key); //Ʈ������ �ش� ���� ���� ��带 ��ȯ������ �˻��Ͽ� ����� ptr�� ����
			if (ptr != NULL) //Ʈ���� �ش� ��尡 ������ ��
				printf("\n node [%d] found at %p\n", ptr->key, ptr); //ptr�� key ���� �ּ� ���
			else //Ʈ���� �ش� ��尡 �������� ���� ��
				printf("\n Cannot find the node [%d]\n", key); //���� �޼��� ���
			break;

		case 'i': case 'I': //command�� 'i' �Ǵ� 'I'�� ��
			inorderTraversal(head->left); //���� ��ȸ ������� ��� ���
			break;
		case 'p': case 'P': //command�� 'p' �Ǵ� 'P'�� ��
			preorderTraversal(head->left); //���� ��ȸ ������� ��� ���
			break;
		case 't': case 'T': //command�� 't' �Ǵ� 'T'�� ��
			postorderTraversal(head->left); //���� ��ȸ ������� ��� ���
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

	if (head->right == head) //head�� ��� ��带 ����Ű�� �������� ��
	{
		if (head->left == NULL) //��Ʈ ��尡 Ʈ���� �������� ���� ��
		{
			head->left = insertNode; //��Ʈ ���μ� insertNode ��� ����
			return 0; //���� �� ����
		}
		else //��Ʈ ��尡 Ʈ���� ������ ��
		{
			head = head->left; //head�� ��Ʈ ���� ���� (temp�� �̸��� �ٲٱ� ���� �۾�)
		}
	}
	
	Node* temp = head; //���� �����ϰ��� �ϴ� ��带 ����Ű�� ������ temp ���� �� head ������ �ʱ�ȭ 

	if (temp->key > key) //temp�� key�� �����Ϸ��� ������ Ŭ �� temp�� ���� ���� Ʈ�� ����
	{
		if (temp->left == NULL) //temp�� ���� �ڽ� ��尡 �������� ���� ��
		{
			temp->left = insertNode; //temp�� ���� �ڽ� ���� ���ο� ��� ����
			return 0; //���� �� �Լ� ����
		}
		else //temp�� ���� �ڽ� ��尡 ������ ��
			insert(temp->left, key); //temp�� ���� ���� Ʈ�� ����
	}
	else //temp�� key�� �����Ϸ��� ������ ũ�� ���� �� temp�� ������ ���� Ʈ�� ����
	{
		if (temp->right == NULL) //temp�� ������ �ڽ� ��尡 �������� ���� ��
		{
			temp->right = insertNode; //temp�� ������ �ڽ� ���ο� ��� ����
			return 0; //���� �� �Լ� ����
		}
		else //temp�� ������ �ڽ� ��尡 ������ ��
			insert(temp->right, key); //temp�� ������ ���� Ʈ�� ����
	}
	return 0;
}

int deleteLeafNode(Node* head, int key)
{
	if (head->right == head)//head�� ��� ����� ��
	{
		Node* root = head->left; //��Ʈ ��带 ����ų ������ root ���� �� head->left�� �ʱ�ȭ
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
	Node* tempLeft = temp->left; //temp�� ���� �ڽ� ��带 ����Ű�� ������ tempLeft ���� �� temp->left�� �ʱ�ȭ
	Node* tempRight = temp->right; //temp�� ������ �ڽ� ��带 ����Ű�� ������ tempRight ���� �� temp->right�� �ʱ�ȭ

	if ((temp->key > key) & (tempLeft != NULL)) //�����ϰ����ϴ� ������ temp�� key���� �� ũ�� temp�� ���� ���� Ʈ���� ������ ��
	{
		if ((tempLeft->left == NULL) & (tempLeft->right == NULL) & (tempLeft->key == key)) //���� ��尡 �����ϰ����ϴ� ���� �����鼭 ���� ����� ��
		{
			free(tempLeft); //���� �ڽ� ����� �޸� ����
			temp->left = NULL; //temp�� ���� ��ũ�� NULL�� ����Ŵ
			return 0; //�Լ� ����
		}
		else if((tempLeft->left == NULL) & (tempLeft->right == NULL)) //���� �ڽ� ��尡 ���� ����ε� �����ϰ����ϴ� ���� �������� ���� ��
		{
			printf("The node [%d] does not exist.\n\n", key); //���� �޼��� ���
			return 0; //�Լ� ����
		}
		else if (tempLeft->key == key) //���� �ڽ� ��尡 �����ϰ����ϴ� ���� �������� ���� ��尡 �ƴ� ��
		{
			printf("The node [%d] is not a leaf node.\n\n", key); //���� �޼��� ���
			return 0; //�Լ� ����
		}
		else //���� �ڽ� ��尡 �����ϰ����ϴ� ���� ���� �ʰ� ���� ��嵵 �ƴ� ��
		{
			deleteLeafNode(tempLeft, key); //���� ���� Ʈ���� �����ϱ� ���� deleteLeafNode ȣ��
		}
	}
	else if ((temp->key < key) & (tempRight != NULL)) //temp�� key������ �����ϰ����ϴ� ���� �� ũ�� temp�� ������ ���� Ʈ���� ������ ��
	{
		if ((tempRight->left == NULL) & (tempRight->right == NULL) & (tempRight->key == key)) //������ �ڽ� ��尡 �����ϰ����ϴ� ���� �����鼭 ���� ����� ��
		{
			free(tempRight); //������ �ڽ� ����� �޸� ����
			temp->right = NULL; //temp�� ������ ��ũ�� NULL�� ����Ŵ
			return 0; //�Լ� ����
		}
		else if ((tempRight->left == NULL) & (tempRight->right == NULL)) //������ �ڽ� ��尡 ���� ����ε� �����ϰ����ϴ� ���� �������� ���� ��
		{
			printf("The node [%d] does not exist.\n\n", key); //���� �޼��� ���
			return 0; //�Լ� ����
		}
		else if (tempRight->key == key) //������ �ڽ� ��尡 �����ϰ����ϴ� ���� �������� ���� ��尡 �ƴ� ��
		{
			printf("The node [%d] is not a leaf node.\n\n", key); //���� �޼��� ���
			return 0; //�Լ� ����
		}
		else //������ �ڽ� ��尡 �����ϰ����ϴ� ���� ���� �ʰ� ���� ��嵵 �ƴ� ��
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
	Node* leftResult = NULL; //���� ���� Ʈ���� ����� ������ ������ leftResult ���� �� NULL�� �ʱ�ȭ
	Node* rightResult = NULL; //������ ���� Ʈ���� ����� ������ ������ RighttResult ���� �� NULL�� �ʱ�ȭ
	Node* finalResult = NULL; //���� ����� ������ ������ finalResult ���� �� NULL�� �ʱ�ȭ
	if (ptr) //ptr�� NULL�� �ƴ� ��
	{
		if (ptr->key == key) //ptr�� key ���� ã�����ϴ� ���� ��ġ�� ��
		{
			return ptr; //ptr�� ��ȯ�ϸ鼭 �Լ� ����
		}

		leftResult = searchRecursive(ptr->left, key); //ptr�� ���� ���� Ʈ�� ����
		rightResult = searchRecursive(ptr->right, key); //ptr�� ������ ���� Ʈ�� ����
	}
	finalResult = (leftResult != NULL) ? leftResult : rightResult; //leftResult�� NULL�� �ƴϸ� finalResult�� leftResult�� ����, NULL�̸� rightResult�� ����
	return finalResult; //���� ����� finalResult ��ȯ�ϸ鼭 �Լ� ����
}

Node* searchIterative(Node* head, int key)
{
	Node* search = head->left; //��带 ã�� ���� ������ search ���� �� ��Ʈ ��带 ����Ű���� �ʱ�ȭ
	Node* temp = head->left; //���� �����ϰ��� �ϴ� ��带 ����Ű�� ������ temp ���� �� ��Ʈ ��带 ����Ű���� �ʱ�ȭ 
	for (; search; search = search->right) //search�� ������ �ڽ� ���� �̵��ϸ鼭 NULL�� �� ������ �ݺ�
	{
		for (temp = search; temp; temp = temp->left) //temp�� search ������ �����Ͽ� �������� �̵��ϸ鼭 NULL�� �� ������ key �� �˻� �ݺ�
		{
			if (temp->key == key) //temp�� key ���� ã�����ϴ� ���� ��ġ�� ��
			{
				return temp; //temp�� ��ȯ�ϸ鼭 �Լ� ����
			}
		}
	}
	return NULL; //���� ã�� ���Ͽ��� ��� NULL�� ��ȯ�ϸ鼭 �Լ� ����
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







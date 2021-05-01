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
		printf("%d", ptr->key); //�ش� ��� �湮
		inorderTraversal(ptr->right); //�湮 �� ������ �ڽ� ���� �̵�
	}
}

void preorderTraversal(Node* ptr)
{
	if (ptr) { //�� �̻� �̵��� �� ���� ������ recursive ������� �Լ� ȣ��
		printf("%d", ptr->key); //�ش� ��� �湮
		inorderTraversal(ptr->left); //���� �ڽ� ���� �̵�
		inorderTraversal(ptr->right); //�湮 �� ������ �ڽ� ���� �̵�
	}
}

void postorderTraversal(Node* ptr)
{
	if (ptr) { //�� �̻� �̵��� �� ���� ������ recursive ������� �Լ� ȣ��
		inorderTraversal(ptr->left); //���� �ڽ� ���� �̵�
		inorderTraversal(ptr->right); //�湮 �� ������ �ڽ� ���� �̵�
		printf("%d", ptr->key); //�ش� ��� �湮
	}
}


int insert(Node* head, int key)
{
	if (head->left == NULL)
	{
		Node* insertKey = (Node*)malloc(sizeof(Node));
		insertKey->key = key;
		insertKey->left = NULL;
		insertKey->right = NULL;
		head->left = insertKey;
		return 0;
	}
	else if (head->right == NULL)
	{
		Node* insertKey = (Node*)malloc(sizeof(Node));
		insertKey->key = key;
		insertKey->left = NULL;
		insertKey->right = NULL;
		head->right = insertKey;
		return 0;
	}
	else
	{
		insert(head->left, key);
		insert(head->right, key);
	}
	return 0;
}

int deleteLeafNode(Node* head, int key)
{

}

Node* searchRecursive(Node* ptr, int key)
{

}

Node* searchIterative(Node* head, int key)
{

}


int freeBST(Node* head) //ȣ�� ��ȸ ������� �޸� ����
{
	if (head) { //�� �̻� �̵��� �� ���� ������ recursive ������� �Լ� ȣ��
		freeBST(head->left); //���� �ڽ� ���� �̵�
		if(head!=head->right) //����� ���!
			freeBST(head->right); //�湮 �� ������ �ڽ� ���� �̵�
		free(head); //�ش� ��忡 ���� �޸� ����
	}
}







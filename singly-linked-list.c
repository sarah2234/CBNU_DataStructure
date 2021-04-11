/*
 * singly linked list
 *
 *  Data Structures
 *  Department of Computer Science
 *  at Chungbuk National University
 */


#include<stdio.h>
#include<stdlib.h>

 /* �ʿ��� ������� �߰� */

typedef struct Node {
	int key;
	struct Node* link;
} listNode;

typedef struct Head {
	struct Node* first;
}headNode;


/* �Լ� ����Ʈ */
headNode* initialize(headNode* h);
int freeList(headNode* h);

int insertFirst(headNode* h, int key);
int insertNode(headNode* h, int key);
int insertLast(headNode* h, int key);

int deleteFirst(headNode* h);
int deleteNode(headNode* h, int key);
int deleteLast(headNode* h);
int invertList(headNode* h);

void printList(headNode* h);

int main()
{
	char command;
	int key;
	headNode* headnode = NULL;

	printf("----- [�̽���] [2020039075] -----\n");	

		do {
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
			scanf(" %c", &command);

			switch (command) {
			case 'z': case 'Z':
				headnode = initialize(headnode);
				break;
			case 'p': case 'P':
				printList(headnode);
				break;
			case 'i': case 'I':
				printf("Your Key = ");
				scanf("%d", &key);
				insertNode(headnode, key);
				break;
			case 'd': case 'D':
				printf("Your Key = ");
				scanf("%d", &key);
				deleteNode(headnode, key);
				break;
			case 'n': case 'N':
				printf("Your Key = ");
				scanf("%d", &key);
				insertLast(headnode, key);
				break;
			case 'e': case 'E':
				deleteLast(headnode);
				break;
			case 'f': case 'F':
				printf("Your Key = ");
				scanf("%d", &key);
				insertFirst(headnode, key);
				break;
			case 't': case 'T':
				deleteFirst(headnode);
				break;
			case 'r': case 'R':
				invertList(headnode);
				break;
			case 'q': case 'Q':
				freeList(headnode);
				break;
			default:
				printf("\n       >>>>>   Concentration!!   <<<<<     \n");
				break;
			}

		} while (command != 'q' && command != 'Q');

		return 1;
}

headNode* initialize(headNode* h) {

	/* headNode�� NULL�� �ƴϸ�, freeNode�� ȣ���Ͽ� �Ҵ�� �޸� ��� ���� */
	if (h != NULL)
		freeList(h);

	/* headNode�� ���� �޸𸮸� �Ҵ��Ͽ� ���� */
	headNode* temp = (headNode*)malloc(sizeof(headNode));
	temp->first = NULL;
	return temp;
}

int freeList(headNode* h) {
	/* h�� ����� listNode �޸� ����
	 * headNode�� �����Ǿ�� ��.
	 */
	listNode* p = h->first;

	listNode* prev = NULL;
	while (p != NULL) {
		prev = p;
		p = p->link;
		free(prev);
	}
	free(h);
	return 0;
}



/**
 * list ó���� key�� ���� ����ϳ��� �߰�
 */
int insertFirst(headNode* h, int key) {

	listNode* node = (listNode*)malloc(sizeof(listNode));
	node->key = key;

	node->link = h->first;
	h->first = node;

	return 0;
}


/* ����Ʈ�� �˻��Ͽ�, �Է¹��� key���� ū ���� ������ ��� �ٷ� �տ� ���� */
int insertNode(headNode* h, int key) { 
	listNode* temp = h->first; //�Է¹��� key�� ���� ���� ��带 ����Ű�� ������ temp ���� �� ����Ʈ�� �� ���� ����Ű���� �ʱ�ȭ
	listNode* trail = h->first; //key ���� temp�� ����Ű�� ����� �տ� ��ġ�ǵ��� temp�� ���� ��带 ����Ű�� ������ trail ���� �� ����Ʈ�� �Ǿ��� ����Ű���� �ʱ�ȭ
	listNode* insert = (listNode*)malloc(sizeof(listNode)); //�Է¹��� key ���� ����Ʈ�� �����ϵ��� insert ������ ���� �� �޸� �Ҵ�
	insert->key = key; //key ���� insert�� key�� ����
	if (!h->first || temp->key > insert->key) //����Ʈ�� ����ְų� key�� �Ǿտ� ��ġ�ؾ��� ��
	{
		insertFirst(h, key); //����Ʈ�� �� �տ� key�� �����ؾ� �ϹǷ� insertFirst �Լ� ȣ��
	}
	else //�ش� ���ǹ��� ������Ű�� ���Ͽ��� ��
	{
		while (temp != NULL)//����� link�� ����Ʈ�� ���� NULL�� ����Ű�� ������ �ݺ��� ����
		{
			if (temp->key > insert->key) //�Է¹��� key���� ū ���� ������ ��带 �߰�
			{
				insert->link = temp; //insert�� link�� temp�� ������ insert�� ���� temp�� ����Ű�� ��� �տ� ������ ��ġ
				trail->link = insert;//���� ��带 ����Ű�� trail�� link�� insert�� ������ insert ��尡 trail ��� �ڿ� ������ ��ġ
				return 0; //insert�� ����Ʈ�� �����ϸ� �Լ� ����
			}
			trail = temp; //temp�� ���� ��带 ����Ű�� �� trail�� �����Ͽ� trail�� temp�� ���� ���� ���
			temp = temp->link; //temp�� ���� ��带 ����Ŵ
		}
		trail->link = insert; //�Է¹��� key���� ū ���� ����Ʈ���� ã�� ���ϸ� ������ ��带 ����Ű�� ������ trail�� link�� insert�� ����Ŵ
		insert->link = NULL; //insert�� link�� NULL�� ������ ����Ʈ�� ���� �˸�
	}
	return 0; //insert�� ����Ű�� ��带 ����Ʈ�� �����ϸ� �Լ� ����
}

/**
 * list�� key�� ���� ����ϳ��� �߰�
 */
int insertLast(headNode* h, int key) {
	listNode* temp = h->first; //���� ������ ��带 ����Ű�� ������ temp ���� �� ����Ʈ�� �� ���� ����Ű���� �ʱ�ȭ
	listNode* insert = (listNode*)malloc(sizeof(listNode)); //�Է¹��� key ���� ����Ʈ�� �����ϵ��� insert ������ ���� �� �޸� �Ҵ�
	insert->key = key; //key ���� insert�� key�� ����
	if (!h->first) //����Ʈ�� ������� ��
	{
		insertFirst(h, key); //����Ʈ�� �� �տ� key�� �����ϴ� �Ͱ� �����Ƿ� insertFirst �Լ� ȣ��
	}
	else //�ش� ���ǹ��� ������Ű�� ���Ͽ��� ��
	{
		while (temp->link) //temp�� ����Ű�� ���� ��尡 NULL, �� ����Ʈ�� ���� �ƴ� ��
		{
			temp = temp->link; //temp�� ���� ��带 ����Ŵ
		}
		insert->link = temp->link; //temp�� ������ ��带 ����ų �� while�� ���� �� insert�� link�� NULL�� ������  ����Ʈ�� ���� �˸�
		temp->link = insert; //temp�� link�� insert�� ����Ű�� ��带 ������ temp ��� �ڿ� insert ��尡 ������ ��
	}
	return 0; //insert�� ����Ű�� ��带 ����Ʈ�� �� �ڿ� �����ϸ� �Լ� ����
}


/**
 * list�� ù��° ��� ����
 */
int deleteFirst(headNode* h) {
	listNode* temp = h->first; //������ ��带 ����Ű�� ������ temp ���� �� ����Ʈ�� �� ���� ����Ű���� �ʱ�ȭ
	h->first = temp->link; //����Ʈ�� �� �� ��尡 temp�� link�� ����Ű�� ���, �� 2��° ��带 ����Ű���� �Ͽ� temp ��带 ����Ʈ���� ����
	free(temp); //����Ʈ�� ù ��° ��� ���� �� temp�� �޸� ����

	return 0; //temp�� ����Ű�� ��带 �����ϸ� �Լ� ����
}


/**
 * list���� key�� ���� ��� ����
 */
int deleteNode(headNode* h, int key) {

	return 0;

}

/**
 * list�� ������ ��� ����
 */
int deleteLast(headNode* h) {

	return 0;
}


/**
 * ����Ʈ�� ��ũ�� �������� �� ��ġ
 */
int invertList(headNode* h) {

	return 0;
}


void printList(headNode* h) {
	int i = 0;
	listNode* p;

	printf("\n---PRINT\n");

	if (h == NULL) {
		printf("Nothing to print....\n");
		return;
	}

	p = h->first;

	while (p != NULL) {
		printf("[ [%d]=%d ] ", i, p->key);
		p = p->link;
		i++;
	}

	printf("  items = %d\n", i);
}


/*
 *  doubly-linked-list.c
 *
 *  Doubly Linked List
 *
 *  Data Structures
 *  Department of Computer Science
 *  at Chungbuk National University
 *
 */



#include<stdio.h>
#include<stdlib.h>
 /* �ʿ��� ������� �߰� if necessary */


typedef struct Node {
	int key; //����� ���� �����ϴ� key ����
	struct Node* llink; //���� ��带 ����Ű�� �������� link ����
	struct Node* rlink; //���� ��带 ����Ű�� �������� link ����
} listNode; //��带 �����ϱ� ���� ����ü Node ���� �� listNode�� ������



typedef struct Head {
	struct Node* first; //����Ʈ�� �� �� ��带 ����Ű�� �������� first ����
}headNode; //����Ʈ�� �� ���� ����Ű�� ���� ����ü Head ���� �� headNode�� ������

/* �Լ� ����Ʈ */

/* note: initialize�� ���������͸� �Ű������� ����
		 singly-linked-list�� initialize�� �������� ���� �Ұ� */
int initialize(headNode** h); //����Ʈ�� �����ϰų� �ʱ�ȭ�ϴ� intialize �Լ� ����

/* note: freeList�� �̱������͸� �Ű������� ����
		- initialize�� �� �ٸ��� ���� �Ұ�
		- ���������͸� �Ű������� �޾Ƶ� ������ �� ���� �� */
int freeList(headNode* h); //����Ʈ�� ��� ��忡 ���� �޸𸮸� �����ϴ� freeList �Լ� ����

int insertNode(headNode* h, int key); //����Ʈ�� �ִ� ����� key ���� ���Ͽ� ��带 �����ϴ� inserNode �Լ� ����
int insertLast(headNode* h, int key); ////����Ʈ�� �� ���� ��带 �����ϴ� insertLast �Լ� ����
int insertFirst(headNode* h, int key); //����Ʈ�� �� �տ� ��带 �����ϴ� insertFirst �Լ� ����
int deleteNode(headNode* h, int key); //����Ʈ�� �ִ� ����� key ���� �����Ͽ� ��带 �����ϴ� deleteNode �Լ� ����
int deleteLast(headNode* h); //����Ʈ�� �� �� ��带 �����ϴ� deleteFirst �Լ� ����
int deleteFirst(headNode* h); //����Ʈ�� �� �� ��带 �����ϴ� deleteLast �Լ� ����
int invertList(headNode* h);

void printList(headNode* h);


int main()
{
	char command;
	int key;
	headNode* headnode = NULL;

	do {
		printf("----------------------------------------------------------------\n");
		printf("                     Doubly Linked  List                        \n");
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
			initialize(&headnode);
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


int initialize(headNode** h) { //���� ������ h�� ��� ����� �ּҸ� �޾� ��� ��带 �Լ� ������ ���� ����
	if (*h != NULL) //����Ʈ�� ��尡 NULL�� �ƴ� �� ���ǹ� ����
		freeList(*h); //����Ʈ �� ������ �޸� ������ ���� freeList �Լ� ȣ�� (��� ����� �� ����)

	headNode* temp = (headNode*)malloc(sizeof(headNode)); //����Ʈ�� �ʱ�ȭ�� ���� ��� ��� temp ���� �� �޸� �Ҵ�
	temp->first = NULL; //temp�� NULL�� ����Ű���� ��
	*h = temp; //��尡 NULL�� ����Ű���� temp�� ������ ����

	return 1;
}

int freeList(headNode* h) { //��� ����� ���� �����ؾ��ϴ� intialize�� �޸� ���� ������ ���� ������ �Ǳ� ������ ���� ������ ���
	listNode* p = h->first; //������ p ���� �� ����Ʈ�� �� �� ��带 ����Ű���� �ʱ�ȭ
	while (p->rlink) //���� ��尡 NULL�� ��, �� ����Ʈ�� �� ���� ������ ������ �ݺ�
	{
		p = p->rlink; //p�� ���� ��带 ����Ŵ
		free(p->llink); //p�� ����Ű�� ����� ���� ����� �޸� ����
	}
	free(h); //����Ʈ�� �� �� ����� �޸� ����
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
		p = p->rlink;
		i++;
	}

	printf("  items = %d\n", i);
}




/**
 * list�� key�� ���� ����ϳ��� �߰�
 */
int insertLast(headNode* h, int key) {
	listNode* temp = h->first; //����Ʈ�� ��带 ������ ������ temp ���� �� ����Ʈ�� �� ���� ����Ű���� �ʱ�ȭ
	listNode* insert = (listNode*)malloc(sizeof(listNode)); //�Է¹��� key ���� ����Ʈ�� �����ϵ��� insert ������ ���� �� �޸� �Ҵ�
	insert->key = key; //key ���� insert�� key�� ����
	if (!h->first) //����Ʈ�� ������� �� ���ǹ� ����
	{
		insertFirst(h, key); //����Ʈ�� �� �տ� key�� �����ϴ� �Ͱ� �����Ƿ� insertFirst �Լ� ȣ��
	}
	else //����Ʈ�� ������� ���� �� else�� ����
	{
		while (temp->rlink) //temp�� ���� ��尡 NULL, �� ����Ʈ�� ���� �����ϱ� ������ �ݺ�
		{
			temp = temp->rlink; //temp�� ���� ��带 ����Ŵ
		}
		insert->rlink = NULL; //temp�� ������ ��带 ����ų �� while�� ���� �� insert�� rlink�� NULL�� ������  ����Ʈ�� ���� �˸�
		insert->llink = temp; //insert�� ���ʿ� temp ��尡 �� �� �ֵ��� ����
		temp->rlink = insert; //temp�� �����ʿ� insert ��尡 �� �� �ֵ��� ����
		
	}

	return 0;
}



/**
 * list�� ������ ��� ����
 */
int deleteLast(headNode* h) {
	listNode* temp = h->first; //������ ��带 ����Ű�� ������ temp ���� �� ����Ʈ�� �� ���� ����Ű���� �ʱ�ȭ

	if (!h->first) //����Ʈ�� ������� ��
	{
		printf("List is empty!\n"); //����Ʈ�� ����ִٴ� ���� �޼��� ��� 
	}
	else //����Ʈ�� ������� ���� ��
	{
		while (temp->rlink) //temp�� ���� ��尡 NULL, �� ����Ʈ�� ���� �����ϱ� ������ �ݺ�
		{
			temp = temp->rlink; //temp�� ���� ��带 ����Ŵ
		}
		temp->llink->rlink = NULL; //temp�� ������ ��带 ����ų �� temp�� ���� ��� ���ʿ� NULL�� ��ġ�Ͽ� ����Ʈ�� ���� �ǵ��� ����
		free(temp); //����Ʈ���� temp ��� ���� �� temp �޸� ����
	}

	return 0;
}



/**
 * list ó���� key�� ���� ����ϳ��� �߰�
 */
int insertFirst(headNode* h, int key) {
	listNode* insert = (listNode*)malloc(sizeof(listNode)); //�Է¹��� key ���� �����ϱ� ���� ������ insert ���� �� �޸� �Ҵ�
	insert->key = key; //�Է¹��� key ���� insert�� key�� ����

	insert->rlink = h->first; //insert�� �����ʿ� ���� ����Ʈ�� �� �� ��尡 �� �� �ֵ��� ����
	if (h->first) //����Ʈ�� ������ �ƴ� �� ���ǹ� ����
	{
		h->first->llink = insert; //���� ����Ʈ�� �� �� ����� ���ʿ� insert�� �� �� �ֵ��� ����
	}
	h->first = insert; //����Ʈ�� �� �� ��带 insert�� ����Ű�� ���� ����

	return 0;
}

/**
 * list�� ù��° ��� ����
 */
int deleteFirst(headNode* h) {
	if (!h->first) //����Ʈ�� ������� ��
	{
		printf("List is empty!\n"); //����Ʈ�� ����ִٴ� ���� �޼��� ���
	}
	else //����Ʈ�� ������� ���� ��
	{
		listNode* temp = h->first; //������ ��带 ����Ű�� ������ temp ���� �� ����Ʈ�� �� ���� ����Ű���� �ʱ�ȭ
		h->first = temp->rlink; //����Ʈ�� �� �� ��尡 temp�� rlink�� ����Ű�� ���, �� 2��° ��尡 �ǵ��� ����
		free(temp); //����Ʈ�� ù ��° ��� ���� �� temp�� �޸� ����
	}

	return 0;
}



/**
 * ����Ʈ�� ��ũ�� �������� �� ��ġ
 */
int invertList(headNode* h) {

	return 0;
}



/* ����Ʈ�� �˻��Ͽ�, �Է¹��� key���� ū���� ������ ��� �ٷ� �տ� ���� */
int insertNode(headNode* h, int key) {
	listNode* temp = h->first; //�Է¹��� key�� ���� ���� ��带 ����Ű�� ������ temp ���� �� ����Ʈ�� �� ���� ����Ű���� �ʱ�ȭ
	listNode* insert = (listNode*)malloc(sizeof(listNode)); //�Է¹��� key ���� ����Ʈ�� �����ϵ��� insert ������ ���� �� �޸� �Ҵ�
	insert->key = key; //�Է¹��� key ���� insert�� key�� ����
	if (!h->first || temp->key > insert->key) //����Ʈ�� ����ְų� key�� �Ǿտ� ��ġ�ؾ��� ��
	{
		insertFirst(h, key); //����Ʈ�� �� �տ� key�� �����ϴ� �Ͱ� �����Ƿ� insertFirst �Լ� ȣ��
	}
	else //����Ʈ�� ������� ���� ��
	{
		while (temp != NULL)//����Ʈ�� ���� NULL�� �Ǳ� ������ �ݺ��� ����
		{
			if (temp->key > insert->key) //�Է¹��� key���� ū ���� ������ ��带 �߰�
			{
				insert->rlink = temp; //insert�� �����ʿ� temp�� �� �� �ֵ��� ����
				insert->llink = temp->llink;//insert�� ���ʿ� temp�� ���� ��尡 �� �� �ֵ��� ����
				temp->llink->rlink = insert; //temp�� ���� ��� �����ʿ� insert�� �� �� �ֵ��� ���� 
				temp->llink = insert; //temp�� ���ʿ� insert�� �� �� �ֵ��� ����
				return 0; //insert�� ����Ű�� ��带 ����Ʈ�� �����ϸ� �Լ� ����
			}
			temp = temp->rlink; //temp�� ���� ��带 ����Ŵ
		}
		insertLast(h, key); //�Է¹��� key���� ū ���� ����Ʈ���� ã�� ���ϸ� insert ��带 ����Ʈ�� ���� ��ġ
	}

	return 0;
}


/**
 * list���� key�� ���� ��� ����
 */
int deleteNode(headNode* h, int key) {
	listNode* temp = h->first; //������ ��带 ����Ű�� ������ temp ���� �� ����Ʈ�� �� ���� ����Ű���� �ʱ�ȭ

	if (!h->first) //����Ʈ�� ������� ��
	{
		printf("List is empty!\n"); //����Ʈ�� ����ִٴ� ���� �޼��� ��� 
	}
	else if (temp->key == key)//������ ��尡 ����Ʈ�� �� �տ� ���� ��
	{
		deleteFirst(h); //����Ʈ�� ù ��° ��带 �����ϴ� �Ͱ� �����Ƿ� deleteFirst �Լ� ȣ��
	}
	else //����Ʈ�� ������� �ʰ� ������ ��尡 ����Ʈ�� �� �տ� ���� ���� ��
	{
		while (temp->rlink) //temp�� ���� ��尡 NULL, �� ����Ʈ�� ���� �����ϱ� ������ �ݺ�
		{
			if (temp->key == key) // temp�� key�� �Է��� key�� ���� ���� ���� ��
			{
				temp->llink->rlink = temp->rlink; //temp�� ���� ����� rlink�� temp�� ���� ��尡 ���� ����� �����ʿ� �� �� �ֵ��� ����
				temp->rlink->llink = temp->llink; //temp�� ���� ����� llink�� temp�� ���� ��尡 ���� ����� ���ʿ� �� �� �ֵ��� ����
				free(temp); //����Ʈ���� temp ��� ���� �� temp �޸� ����
				return 0; //temp�� ����Ű�� ��带 ����Ʈ���� �����ϸ� �Լ� ����
			}
			temp = temp->rlink; //temp�� ���� ��带 ����Ŵ
		}
		if (temp->key == key) //������ ����� key�� �����ϰ��� �ϴ� ���� ��
			deleteLast(h); //deleteLast �Լ� ȣ��� ������ ��� ����
		else //�����ϰ����ϴ� ���� ����Ʈ�� �������� ���� ��
			printf("Node with the value %d not found!\n", key); //���� �޼��� ���
	}

	return 1;
}




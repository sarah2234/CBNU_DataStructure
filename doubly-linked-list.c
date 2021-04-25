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
int invertList(headNode* h); //����Ʈ�� ������ �������� �ٲٴ� invertList �Լ� ����

void printList(headNode* h); //����Ʈ�� ��带 ��� ����ϴ� printList �Լ� ����


int main()
{
	char command; //��ɾ �Է¹ޱ� ���� command ���� ����
	int key; //���� �Է¹ޱ� ���� key ���� ����
	headNode* headnode = NULL; //����Ʈ�� �� �� ��带 ����Ű�� ������ headnode ���� �� ����Ʈ ���� �� NULL�� ����Ű���� �ʱ�ȭ

	printf("----- [�̽���] [2020039075] -----\n");

	do { //�ݺ��� �ּ� 1�� �̻� ����
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
		scanf(" %c", &command); //��ɾ �Է¹޾� command�� ���� 

		switch (command) {
		case 'z': case 'Z': //command�� 'z' �Ǵ� 'Z'�� ��
			initialize(&headnode); //intialize �Լ� ȣ��� headnode�� �޸� �Ҵ��Ͽ� ����Ʈ ���� (�ּ� ���޷� �Լ� ������ headnode�� �� ����)
			break;
		case 'p': case 'P': //command�� 'p' �Ǵ� 'P'�� ��
			printList(headnode); //printList �Լ� ȣ��� headnode�� ����Ű�� ������ �����Ͽ� ����Ʈ�� ��带 ���
			break;
		case 'i': case 'I': //command�� 'i' �Ǵ� 'I'�� ��
			printf("Your Key = ");
			scanf("%d", &key); //������ key �� �Է�
			insertNode(headnode, key); //insertNode �Լ� ȣ��� headnode�� ����Ű�� ������ �����Ͽ� ��� �� key ���� ���Ͽ� ���ο� ��� ���� 
			break;
		case 'd': case 'D': //command�� 'd' �Ǵ� 'D'�� ��
			printf("Your Key = ");
			scanf("%d", &key); //������ key �� �Է�
			deleteNode(headnode, key); //deleteNode �Լ� ȣ��� headnode�� ����Ű�� ������ �����Ͽ� �Է¹��� key ���� ���� ��� ����
			break;
		case 'n': case 'N': //command�� 'n' �Ǵ� 'N'�� ��
			printf("Your Key = ");
			scanf("%d", &key); //������ key �� �Է�
			insertLast(headnode, key); //insertLast �Լ� ȣ��� headnode�� ����Ű�� ������ �����Ͽ� ����Ʈ�� �� ���� ���ο� ��� ����
			break;
		case 'e': case 'E': //command�� 'e' �Ǵ� 'E'�� ��
			deleteLast(headnode); //deleteLast �Լ� ȣ��� headnode�� ����Ű�� ������ �����Ͽ� ����Ʈ�� �� �� ��� ����
			break;
		case 'f': case 'F': //command�� 'f' �Ǵ� 'F'�� ��
			printf("Your Key = ");
			scanf("%d", &key); //������ key �� �Է�
			insertFirst(headnode, key); //insertFirst �Լ� ȣ��� headnode�� ����Ű�� ���� ����Ʈ�� �� �տ� ���ο� ��� ����
			break;
		case 't': case 'T': //command�� 't' �Ǵ� 'T'�� ��	
			deleteFirst(headnode); //deleteFirst �Լ� ȣ��� headnode�� ����Ű�� ���� ����Ʈ�� �� �� ��� ����
			break;
		case 'r': case 'R': //command�� 'r' �Ǵ� 'R'�� ��
			invertList(headnode); //invertList �Լ� ȣ��� headnode�� ����Ű�� ������ �����Ͽ� ���ʷ� ����Ʈ�� �������� ����
			break;
		case 'q': case 'Q': //command�� 'q' �Ǵ� 'Q'�� ��
			freeList(headnode); //freeList �Լ� ȣ��� headnode�� ����Ű�� ������ �����Ͽ� ���ʷ� �޸� ����
			break;
		default: //command�� ����� ���� �̿��� ���� ��
			printf("\n       >>>>>   Concentration!!   <<<<<     \n"); //���� �޼��� ���
			break;
		}

	} while (command != 'q' && command != 'Q'); //command�� 'q' �Ǵ� 'Q'�� �Է¹����� �ݺ��� ����

	return 1;
}


int initialize(headNode** h) { //���� ������ h�� ��� ����� �ּҸ� �޾� ��� ��带 �Լ� ������ ���� ����
	if (*h != NULL) //����Ʈ�� ��尡 NULL�� �ƴ� �� ���ǹ� ����
		freeList(*h); //����Ʈ �� ������ �޸� ������ ���� freeList �Լ� ȣ�� (��� ����� �� ����)

	headNode* temp = (headNode*)malloc(sizeof(headNode)); //����Ʈ�� �ʱ�ȭ�� ���� ��� ��� temp ���� �� �޸� �Ҵ�
	temp->first = NULL; //temp�� NULL�� ����Ű���� ��
	*h = temp; //��� ��尡 temp�� ���� �������� ����

	return 1;
}

int freeList(headNode* h) { //��� ����� ���� �����ؾ��ϴ� intialize�� �޸� ���� ���� ���� ������ �Ǳ� ������ ���� ������ ���
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
	int i = 0; //������ ��Ÿ���� ���� i ���� �� 0���� �ʱ�ȭ
	listNode* p; //����Ʈ�� ��带 ����ų ������ p ����

	printf("\n---PRINT\n");

	if (h == NULL) { //����Ʈ�� ������� ��
		printf("Nothing to print....\n"); //���� �޼��� ���
		return; //�Լ� ����
	}

	p = h->first; //p�� ����Ʈ�� �� �� ��带 ����Ű���� �ʱ�ȭ


	while (p != NULL) { //p�� ����Ʈ�� �� ���� �����ϱ� ������ �ݺ�
		printf("[ [%d]=%d ] ", i, p->key); //i��°�� �ִ� ����� key �� ���
		p = p->rlink; //p�� ���� ��带 ����Ŵ
		i++; //���� ��°�� ����
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
		insert->llink = temp; //insert�� ���ʿ� temp ��尡 ������ ��
		temp->rlink = insert; //temp�� �����ʿ� insert ��尡 ������ ��
		
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

	insert->rlink = h->first; //insert�� �����ʿ� ���� ����Ʈ�� �� �� ��尡 ������ ��
	insert->llink = NULL; //insert ��尡 ù ��° ����̹Ƿ� insert ���ʿ��� NULL�� ������ ��
	if (h->first) //����Ʈ�� ������ �ƴ� �� ���ǹ� ����
	{
		h->first->llink = insert; //���� ����Ʈ�� �� �� ����� ���ʿ� insert�� ������ ��
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
 * ����Ʈ�� ��ũ�� �������� ���ġ
 */
int invertList(headNode* h) {
	listNode* temp, * trail; //��带 ����Ű�� temp �����Ϳ� temp�� ���� ��带 ����ų trail ������ ����
	temp = h->first; //temp�� ����Ʈ�� ��� ��带 ����Ű���� �ʱ�ȭ
	if (!h->first) //����Ʈ�� ������� ��
	{
		printf("List is empty!\n"); //���� �޼��� ���
	}
	else //����Ʈ�� ������� ���� ��
	{
		while (temp->rlink) //����Ʈ ó������ ���� �����ϱ� ������ �ݺ�
		{
			trail = temp->llink; //trail�� temp�� ���� ��带 ����Ű���� ��
			temp->llink = temp->rlink; //temp ����� ���� ��ũ�� ���� ��带 ����Ű���� ��
			temp->rlink = trail; //temp ����� ������ ��ũ�� ���� ��带 ����Ű���� �Ͽ� ��� �� ���� �ٲ�
			temp = temp->llink; //temp�� �� ���� ��带 ����Ŵ
		}
		//temp ���� ������ ����Ʈ ������ �������� ������ ��忡 �ش�
		temp->rlink = temp->llink; //temp ����� ������ ��ũ�� ���� ��带 ����Ű���� ��
		temp->llink = NULL; //temp ���� ���� ����Ʈ�� ��� ��尡 �ǹǷ� ���� ��ũ�� NULL�� ����Ű���� ��
		h->first = temp; //��� ��带 temp�� ����
	}

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
				insert->rlink = temp; //insert�� �����ʿ� temp�� �� �� �ֵ��� ��ġ
				insert->llink = temp->llink;//insert�� ���ʿ� temp�� ���� ��尡 ������ ��
				temp->llink->rlink = insert; //temp�� ���� ��� �����ʿ� insert�� ������ ��
				temp->llink = insert; //temp�� ���ʿ� insert�� ������ ��
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




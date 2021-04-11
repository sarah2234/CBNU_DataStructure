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
		insertFirst(h, key); //����Ʈ�� �� �տ� key�� �����ϴ� �Ͱ� �����Ƿ� insertFirst �Լ� ȣ��
	}
	else //����Ʈ�� ������� ���� ��
	{
		while (temp != NULL)//����� link�� ����Ʈ�� ���� NULL�� ����Ű�� ������ �ݺ��� ����
		{
			if (temp->key > insert->key) //�Է¹��� key���� ū ���� ������ ��带 �߰�
			{
				insert->link = temp; //insert�� link�� temp�� ������ insert�� ���� temp�� ����Ű�� ��� �տ� ������ ��ġ
				trail->link = insert;//���� ��带 ����Ű�� trail�� link�� insert�� ������ insert ��尡 trail ��� �ڿ� ������ ��ġ
				return 0; //insert�� ����Ű�� ��带 ����Ʈ�� �����ϸ� �Լ� ����
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
	else //����Ʈ�� ������� ���� ��
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
	
	if (!h->first) //����Ʈ�� ������� ��
	{
		printf("List is empty!\n"); //����Ʈ�� ����ִٴ� ���� �޼��� ���
	}
	else //����Ʈ�� ������� ���� ��
	{
		listNode* temp = h->first; //������ ��带 ����Ű�� ������ temp ���� �� ����Ʈ�� �� ���� ����Ű���� �ʱ�ȭ
		h->first = temp->link; //����Ʈ�� �� �� ��尡 temp�� link�� ����Ű�� ���, �� 2��° ��带 ����Ű���� �Ͽ� temp ��带 ����Ʈ���� ����
		free(temp); //����Ʈ�� ù ��° ��� ���� �� temp�� �޸� ����
	}

	return 0; //�Լ� ���� ���� �� ����
}


/**
 * list���� key�� ���� ��� ����
 */
int deleteNode(headNode* h, int key) {
	listNode* temp = h->first; //������ ��带 ����Ű�� ������ temp ���� �� ����Ʈ�� �� ���� ����Ű���� �ʱ�ȭ
	listNode* trail = h->first; //temp ��� ������ ������ ��尡 ����� �� �ֵ��� temp�� ���� ��带 ����Ű�� ������ trail ���� �� ����Ʈ�� �� ���� ����Ű���� �ʱ�ȭ
	
	if (!h->first) //����Ʈ�� ������� ��
	{
		printf("List is empty!\n"); //����Ʈ�� ����ִٴ� ���� �޼��� ��� 
	}
	else if (temp->key == key)//������ ��尡 ����Ʈ�� �� �տ� ���� ��
	{
		deleteFirst(h, key); //����Ʈ�� ù ��° ��带 �����ϴ� �Ͱ� �����Ƿ� deleteFirst �Լ� ȣ��
	}
	else //����Ʈ�� ������� �ʰ� ������ ��尡 ����Ʈ�� �� �տ� ���� ���� ��
	{
	while (temp->link) //temp�� ����Ű�� ���� ��尡 NULL, �� ����Ʈ�� ���� �ƴ� ��
	{
		if (temp->key == key) // temp�� key�� �Է��� key�� ���� ���� ���� ��
		{
			trail->link = temp->link; //���� ��� trail�� link�� temp�� ���� ��带 ������ temp ��带 ����Ʈ���� ����
			free(temp); //����Ʈ���� temp ��� ���� �� temp �޸� ����
			return 0; //temp�� ����Ű�� ��带 ����Ʈ���� �����ϸ� �Լ� ����
		}
		trail = temp; //temp�� ���� ��带 ����Ű�� �� trail�� �����Ͽ� trail�� temp�� ���� ���� ���
		temp = temp->link; //temp�� ���� ��带 ����Ŵ
	}
	printf("Node with the value %d not found!\n", key); //�Է¹��� key ���� ����Ʈ���� ã�� ���ϸ� ���� �޼��� ���
	}
	return 0; //�Լ� ���� ���� �� ����

}

/**
 * list�� ������ ��� ����
 */
int deleteLast(headNode* h) {
	listNode* temp = h->first; //������ ��带 ����Ű�� ������ temp ���� �� ����Ʈ�� �� ���� ����Ű���� �ʱ�ȭ
	listNode* trail = h->first; //temp�� ���� ��带 ����Ű�� ������ trail ���� �� ����Ʈ�� �� ���� ����Ű���� �ʱ�ȭ

	if (!h->first) //����Ʈ�� ������� ��
	{
		printf("List is empty!\n"); //����Ʈ�� ����ִٴ� ���� �޼��� ��� 
	}
	else //����Ʈ�� ������� ���� ��
	{
		while (temp->link) //temp�� ����Ű�� ���� ��尡 NULL, �� ����Ʈ�� ���� �ƴ� ��
		{
			trail = temp; //temp�� ���� ��带 ����Ű�� �� trail�� �����Ͽ� trail�� temp�� ���� ���� ���
			temp = temp->link; //temp�� ���� ��带 ����Ŵ
		}
		trail->link = NULL; //temp�� ������ ��带 ����ų �� ���� ��带 ����Ű�� trail�� link�� NULL�� ������ ����Ʈ�� ������ ��带 ����Ű���� ��
		free(temp); //����Ʈ���� temp ��� ���� �� temp �޸� ����
	}

	return 0; //�Լ� ���� ���� �� ����
}


/**
 * ����Ʈ�� ��ũ�� �������� �� ��ġ
 */
int invertList(headNode* h) {
	listNode* lead, *middle, *trail; //��, �߰�, �� ��带 ������� ����ų ������ lead, middle, trail ����
	lead = h->first; //lead�� ����Ʈ�� �� �� ��带 ����Ű���� ��
	middle = NULL; //middle�� ���� ��带 ����Ű�� ���� ����
	while (lead) //����Ʈ ó������ ���� ������ ������
	{
		trail = middle; //�� ��带 ����Ű�� trail�� �߰� ��带 ����Ű�� middle�� ����Ű�� ���� �ٲ�
		middle = lead; //�߰� ��带 ����Ű�� middle�� �� ��带 ����Ű�� lead�� ����Ű�� ���� �ٲ�
		lead = lead->link; //lead�� �� ���� ��带 ����Ŵ 
		middle->link = trail; //middle�� ����Ű�� ��� ������ trail�� ����Ű�� ��尡 �� �� �ֵ��� ����
	}
	h->first = middle; //����Ʈ�� �� �� ��尡 �ٲ�����Ƿ� middle�� ����Ű�� ��尡 ����Ʈ�� �� ���� ���� ���

	return 0; //�Լ� ���� �۵� �� ����
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


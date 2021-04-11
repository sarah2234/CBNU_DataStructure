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
	int key; //����� ���� �����ϴ� key ����
	struct Node* link; //���� ��带 ����Ű�� �������� link ����
} listNode; //��带 �����ϱ� ���� ����ü Node ���� �� listNode�� ������

typedef struct Head {
	struct Node* first; //����Ʈ�� �� �� ��带 ����Ű�� �������� first ����
}headNode; //����Ʈ�� �� ���� ����Ű�� ���� ����ü Head ���� �� headNode�� ������


/* �Լ� ����Ʈ */
headNode* initialize(headNode* h); //����Ʈ�� �����ϰų� �ʱ�ȭ�ϴ� intialize �Լ� ����
int freeList(headNode* h); //����Ʈ�� ��� ��忡 ���� �޸𸮸� �����ϴ� freeList �Լ� ����

int insertFirst(headNode* h, int key); //����Ʈ�� �� �� ��带 �����ϴ� insertFirst �Լ� ����
int insertNode(headNode* h, int key); //����Ʈ�� �ִ� ����� key ���� ���Ͽ� ��带 �����ϴ� inserNode �Լ� ����
int insertLast(headNode* h, int key); //����Ʈ�� �� �� ��带 �����ϴ� insertLast �Լ� ����

int deleteFirst(headNode* h); //����Ʈ�� �� �� ��带 �����ϴ� deleteFirst �Լ� ����
int deleteNode(headNode* h, int key); //����Ʈ�� �ִ� ����� key ���� �����Ͽ� ��带 �����ϴ� deleteNode �Լ� ����
int deleteLast(headNode* h); //����Ʈ�� �� �� ��带 �����ϴ� deleteLast �Լ� ����
int invertList(headNode* h); //����Ʈ�� ������ �������� �ٲٴ� invertList �Լ� ����

void printList(headNode* h); //����Ʈ�� ��带 ��� ����ϴ� printList �Լ� ����

int main()
{
	char command; //��ɾ �Է¹ޱ� ���� command ���� ����
	int key; //���� �Է¹ޱ� ���� key ���� ����
	headNode* headnode = NULL; //����Ʈ�� �� ���� ����Ű�� ������ headnode ���� �� ����Ʈ�� ���� ���̹Ƿ� NULL�� ����Ű���� �ʱ�ȭ 

	printf("----- [�̽���] [2020039075] -----\n");	

		do { //�ݺ��� �ּ� 1�� �̻� ����
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
			scanf(" %c", &command); //��ɾ �Է¹޾� command�� ����

			switch (command) {
			case 'z': case 'Z': //command�� 'z' �Ǵ� 'Z'�� ��
				headnode = initialize(headnode); //intialize �Լ� ȣ��� headnode�� �޸� �Ҵ��Ͽ� ����Ʈ ����
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

		return 1; //main �Լ� ����
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
	listNode* p = h->first; //������ p ���� �� ����Ʈ�� �� �� ��带 ����Ű���� �ʱ�ȭ

	listNode* prev = NULL; //���� ��� prev ����
	while (p != NULL) { //p�� ����Ʈ�� �� ���� ������ ������ �ݺ�
		prev = p; //p�� ���� ��带 ����Ű�� �� prev�� p�� ��带 ������ prev�� ���� ���� ���
		p = p->link; //p�� ���� ��带 ����Ŵ
		free(prev); //prev�� ����Ű�� ����� �޸� ����
	}
	free(h); //����Ʈ�� �� �� ����� �޸� ����
	return 0; //�Լ� ���� ���� �� ����
}



/**
 * list ó���� key�� ���� ����ϳ��� �߰�
 */
int insertFirst(headNode* h, int key) {

	listNode* node = (listNode*)malloc(sizeof(listNode)); //�Է¹��� key ���� �����ϱ� ���� ������ node ���� �� �޸� �Ҵ�
	node->key = key; //�Է¹��� key ���� node�� key�� ����

	node->link = h->first; //node�� ���� ��尡 ���� ����Ʈ�� �� �� ��带 ����Ű���� ��
	h->first = node; //����Ʈ�� �� �� ��带 node�� ����Ű�� ���� ����

	return 0; //�Լ� ���� ���� �� ����
}


/* ����Ʈ�� �˻��Ͽ�, �Է¹��� key���� ū ���� ������ ��� �ٷ� �տ� ���� */
int insertNode(headNode* h, int key) { 
	listNode* temp = h->first; //�Է¹��� key�� ���� ���� ��带 ����Ű�� ������ temp ���� �� ����Ʈ�� �� ���� ����Ű���� �ʱ�ȭ
	listNode* trail = h->first; //key ���� temp�� ����Ű�� ����� �տ� ��ġ�ǵ��� temp�� ���� ��带 ����Ű�� ������ trail ���� �� ����Ʈ�� �Ǿ��� ����Ű���� �ʱ�ȭ
	listNode* insert = (listNode*)malloc(sizeof(listNode)); //�Է¹��� key ���� ����Ʈ�� �����ϵ��� insert ������ ���� �� �޸� �Ҵ�
	insert->key = key; //�Է¹��� key ���� insert�� key�� ����
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
		while (temp->link) //temp�� ����Ű�� ���� ��尡 NULL, �� ����Ʈ�� ���� �����ϱ� ������ �ݺ�
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
	while (temp->link) //temp�� ����Ű�� ���� ��尡 NULL, �� ����Ʈ�� ���� �����ϱ� ������ �ݺ�
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
		while (temp->link) //temp�� ����Ű�� ���� ��尡 NULL, �� ����Ʈ�� ���� �����ϱ� ������ �ݺ�
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
	if (!h->first) //����Ʈ�� ������� ��
	{
		printf("List is empty!\n"); //���� �޼��� ���
	}
	else //����Ʈ�� ������� ���� ��
	{
		while (lead) //����Ʈ ó������ ���� �����ϱ� ������ �ݺ�
		{
			trail = middle; //�� ��带 ����Ű�� trail�� �߰� ��带 ����Ű�� middle�� ����Ű�� ���� �ٲ�
			middle = lead; //�߰� ��带 ����Ű�� middle�� �� ��带 ����Ű�� lead�� ����Ű�� ���� �ٲ�
			lead = lead->link; //lead�� �� ���� ��带 ����Ŵ 
			middle->link = trail; //middle�� ����Ű�� ��� ������ trail�� ����Ű�� ��尡 �� �� �ֵ��� ����
		}
		h->first = middle; //����Ʈ�� �� �� ��尡 �ٲ�����Ƿ� middle�� ����Ű�� ��尡 ����Ʈ�� �� ���� ���� ���
	}
	return 0; //�Լ� ���� ���� �� ����
}


void printList(headNode* h) {
	int i = 0; //������ ��Ÿ���� ���� i ����
	listNode* p; //����Ʈ�� ��带 ����ų ������ p ����

	printf("\n---PRINT\n");

	if (h == NULL) { //����Ʈ�� ������� ��
		printf("Nothing to print....\n"); //���� �޼��� ���
		return; //�Լ� ����
	}

	p = h->first; //p�� ����Ʈ�� �� �� ��带 ����Ű���� ����

	while (p != NULL) { //p�� ����Ʈ�� �� ���� �����ϱ� ������ �ݺ�
		printf("[ [%d]=%d ] ", i, p->key); //i��°�� �ִ� ����� key �� ���
		p = p->link; //p�� ���� ��带 ����Ŵ
		i++; //���� ��°�� ����
	}

	printf("  items = %d\n", i); //����Ʈ ���� �����ϴ� ��� ���� ���
}


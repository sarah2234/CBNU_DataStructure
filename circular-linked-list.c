/*
 *  doubly circular linked list
 *
 *  Data Structures
 *
 *  Department of Computer Science
 *  at Chungbuk National University
 *
 */



#include<stdio.h>
#include<stdlib.h>
 /* �ʿ��� ������� �߰� */

typedef struct Node {
	int key; //����� ���� �����ϴ� key ����
	struct Node* llink; //���� ��带 ����Ű�� �������� llink ����
	struct Node* rlink; //���� ��带 ����Ű�� �������� rlink ����
} listNode; //��带 �����ϱ� ���� ����ü Node ���� �� listNode�� ������

/* �Լ� ����Ʈ */
int initialize(listNode** h); //����Ʈ�� �����ϰų� �ʱ�ȭ�ϴ� intialize �Լ� ����
int freeList(listNode* h); //����Ʈ�� ��� ��忡 ���� �޸𸮸� �����ϴ� freeList �Լ� ����
int insertLast(listNode* h, int key); //����Ʈ�� �������� ��带 �����ϴ� insertLast �Լ� ����
int deleteLast(listNode* h); //����Ʈ�� ������ ��带 �����ϴ� deleteLast �Լ� ����
int insertFirst(listNode* h, int key); //����Ʈ�� ù ��°�� ��带 �����ϴ� insertFirst �Լ� ����
int deleteFirst(listNode* h); //����Ʈ�� ù ��° ��带 �����ϴ� deleteFirst �Լ� ����
int invertList(listNode* h); //����Ʈ�� ������ �������� �ٲٴ� invertList �Լ� ����

int insertNode(listNode* h, int key); //����Ʈ�� �ִ� ����� key ���� ���Ͽ� ��带 �����ϴ� inserNode �Լ� ����
int deleteNode(listNode* h, int key); //����Ʈ�� �ִ� ����� key ���� �����Ͽ� ��带 �����ϴ� deleteNode �Լ� ����

void printList(listNode* h); //����Ʈ�� ��带 ��� ����ϴ� printList �Լ� ����



int main()
{
	char command; //��ɾ �Է¹ޱ� ���� command ���� ����
	int key; //���� �Է¹ޱ� ���� key ���� ����
	listNode* headnode = NULL; //����Ʈ�� ��� ��带 ����Ű�� ������ headnode ���� �� ����Ʈ ���� �� NULL�� ����Ű���� �ʱ�ȭ

	printf("----- [�̽���] [2020039075] -----\n");

	do { //�ݺ��� �ּ� 1�� �̻� ����
		printf("----------------------------------------------------------------\n");
		printf("                  Doubly Circular Linked List                   \n");
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
			printList(headnode); //printList �Լ� ȣ��� ����Ʈ�� ������ ���
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
			insertLast(headnode, key); //insertLast �Լ� ȣ��� headnode�� ����Ű�� ������ �����Ͽ� ����Ʈ�� �������� ���ο� ��� ����
			break;
		case 'e': case 'E': //command�� 'e' �Ǵ� 'E'�� ��
			deleteLast(headnode); //deleteLast �Լ� ȣ��� headnode�� ����Ű�� ������ �����Ͽ� ����Ʈ�� ������ ��� ����
			break;
		case 'f': case 'F': //command�� 'f' �Ǵ� 'F'�� ��
			printf("Your Key = ");
			scanf("%d", &key); //������ key �� �Է�
			insertFirst(headnode, key); //insertFirst �Լ� ȣ��� headnode�� ����Ű�� ����Ʈ�� �� �տ� ���ο� ��� ����
			break;
		case 't': case 'T': //command�� 't' �Ǵ� 'T'�� ��
			deleteFirst(headnode); //deleteFirst �Լ� ȣ��� headnode�� ����Ű�� ����Ʈ�� ù ��° ��� ����
			break;
		case 'r': case 'R': //command�� 'r' �Ǵ� 'R'�� ��
			invertList(headnode); //invertList �Լ� ȣ��� headnode�� ����Ű�� ����Ʈ�� ������ ������ �������� ����
			break;
		case 'q': case 'Q': //command�� 'q' �Ǵ� 'Q'�� ��
			freeList(headnode); //freeList �Լ� ȣ��� headnode�� ����Ű�� ����Ʈ�� ���� �޸� ����
			break;
		default: //command�� ����� ���� �̿��� ���� ��
			printf("\n       >>>>>   Concentration!!   <<<<<     \n"); //���� �޼��� ���
			break;
		}

	} while (command != 'q' && command != 'Q'); //command�� 'q' �Ǵ� 'Q'�� �Է¹����� �ݺ��� ����

	return 1;
}


int initialize(listNode** h) { //���� ������ h�� ��� ����� �ּҸ� �޾� ��� ����� ���� �Լ� ������ ���� ����

	/* headNode�� NULL�� �ƴϸ�, freeNode�� ȣ���Ͽ� �Ҵ�� �޸� ��� ���� */
	if (*h != NULL)
		freeList(*h);

	/* headNode�� ���� �޸𸮸� �Ҵ��Ͽ� ���� */
	*h = (listNode*)malloc(sizeof(listNode));
	(*h)->rlink = *h;
	(*h)->llink = *h;
	(*h)->key = -9999;
	return 1;
}

/* �޸� ���� */
int freeList(listNode* h) {
	listNode* temp = h; //�޸𸮸� �����ϰ����ϴ� ��带 ����Ű�� temp ���� �� ����Ʈ�� ��� ��带 ����Ŵ
	listNode* lastNode = h->llink; //������ ��带 ����Ű�� lastNode ���� �� ����Ʈ�� ������ ��带 ����Ŵ
	while (temp != lastNode) //������ ��带 ����Ű�� ������ �ݺ�
	{
		temp = temp->rlink; //temp�� ���� ��带 ����Ŵ
		free(temp->llink); //���� ��忡 ���� �޸� ����
	}
	free(lastNode); //������ ����� �޸� ����
	return 0;
}



void printList(listNode* h) {
	int i = 0; //������ ��Ÿ���� ���� i ���� �� 0���� �ʱ�ȭ
	listNode* p; //����Ʈ�� ��带 ����ų ������ p ����

	printf("\n---PRINT\n");

	if (h == NULL) { //����Ʈ�� ������� ��
		printf("Nothing to print....\n"); //���� �޼��� ���
		return; //�Լ� ����
	}

	p = h->rlink; //p�� ��� ��带 ������ ����Ʈ�� ù ��° ��带 ����Ű���� �ʱ�ȭ

	while (p != NULL && p != h) { //p�� ����Ʈ�� ������ ��忡 �����ϱ� ������ �ݺ�
		printf("[ [%d]=%d ] ", i, p->key); //i��°�� �ִ� ����� key �� ��� 
		p = p->rlink; //p�� ���� ��带 ����Ŵ
		i++; //���� ��°�� ����
	}
	printf("  items = %d\n", i); //����� �� ���� ���


	/* print addresses */
	printf("\n---checking addresses of links\n");
	printf("-------------------------------\n");
	printf("head node: [llink]=%p, [head]=%p, [rlink]=%p\n", h->llink, h, h->rlink); //��� ����� llink, �ּ�, rlink�� ���ʷ� ���

	i = 0;
	p = h->rlink; //p�� ��� ��带 ������ ����Ʈ�� ù ��° ��带 ����Ŵ
	while (p != NULL && p != h) { //p�� ����Ʈ�� ������ ��忡 �����ϱ� ������ �ݺ�
		printf("[ [%d]=%d ] [llink]=%p, [node]=%p, [rlink]=%p\n", i, p->key, p->llink, p, p->rlink); //i��°�� �ִ� ����� key, llink, rlink�� ���ʷ� ���
		p = p->rlink; //p�� ���� ��带 ����Ŵ
		i++; //���� ��°�� ����
	}

}



/**
 * list�� key�� ���� ����ϳ��� �߰�
 */
int insertLast(listNode* h, int key) {
	listNode* insert = (listNode*)malloc(sizeof(listNode)); //�Է¹��� key ���� �����ϱ� ���� ������ insert ���� �� �޸� �Ҵ�
	insert->key = key; //�Է¹��� key ���� insert�� key�� ����
	insert->llink = h->llink; //insert�� ���� ��ũ�� ����Ʈ�� ������ ��带 ����Ŵ
	insert->rlink = h; //insert�� ������ ��ũ�� ��� ��带 ����Ŵ
	h->llink->rlink = insert; //����Ʈ�� ������ ����� ������ ��ũ�� insert�� ����Ŵ
	h->llink = insert; //��� ����� ���� ��ũ�� insert�� ����Ű�� (���� �� ������ ���)-insert-h ������ ��ġ
	return 1;
}


/**
 * list�� ������ ��� ����
 */
int deleteLast(listNode* h) {
	if (h->rlink == h) //����Ʈ�� ������� ��
	{
		printf("List is empty!\n"); //����Ʈ�� ����ִٴ� ���� �޼��� ���
	}
	else //����Ʈ�� ������� ���� ��
	{
		listNode* delete = h->llink; //��带 �����ϱ� ���� ������ delete ���� �� ������ ��带 ����Ű���� �ʱ�ȭ
		delete->llink->rlink = h; //delete�� ���� ����� ������ ��ũ�� ��� ��带 ����Ŵ
		h->llink = delete->llink; //��� ����� ���� ��ũ�� delete�� ���� ��带 ����Ű�� (���� �� delete�� ���� ���)-h ������ ��ġ
		free(delete); //delete�� ����Ű�� ����� �޸� ����
	}
	return 1;
}


/**
 * list ó���� key�� ���� ����ϳ��� �߰�
 */
int insertFirst(listNode* h, int key) {
	listNode* insert = (listNode*)malloc(sizeof(listNode)); //�Է¹��� key ���� �����ϱ� ���� ������ insert ���� �� �޸� �Ҵ�
	insert->key = key; //�Է¹��� key ���� insert�� key�� ����
	insert->llink = h; //insert�� ���� ��ũ�� ����Ʈ�� ��� ��带 ����Ű���� ��
	insert->rlink = h->rlink; //insert�� ������ ��ũ�� ��� ��带 ������ ù ��° ��带 ����Ű���� ��
	h->rlink->llink = insert; //��� ��带 ������ ù ��° ����� ���� ��ũ�� insert�� ����Ű���� ��
	h->rlink = insert; //��� ����� ������ ��ũ�� insert�� ����Ű�� h-insert-(���� �� h�� ���� ���) ������ ��ġ
	return 1;
}

/**
 * list�� ù��° ��� ����
 */
int deleteFirst(listNode* h) {
	if (h->rlink == h) //����Ʈ�� ������� ��
	{
		printf("List is empty!\n"); //����Ʈ�� ����ִٴ� ���� �޼��� ���
	}
	else //����Ʈ�� ������� ���� ��
	{
		listNode* delete = h->rlink; //��带 �����ϱ� ���� ������ delete ���� �� ��� ��带 ������ ù ��° ��带 ����Ű���� �ʱ�ȭ
		delete->rlink->llink = h;  //delete�� ������ ����� ���� ��ũ�� ��� ��带 ����Ŵ
		h->rlink = delete->rlink; //��� ����� ������ ��ũ�� delete�� ������ ��带 ����Ű�� h-(���� �� delete�� ������ ���) ������ ��ġ
		free(delete); //delete�� ����Ű�� ����� �޸� ����
	}
	return 1;
}


/**
 * ����Ʈ�� ��ũ�� �������� �� ��ġ
 */
int invertList(listNode* h) {
	listNode* temp, * trail; //��带 ����Ű�� temp �����Ϳ� temp�� ���� ��带 ����ų trail ������ ����
	temp = h; //temp�� ����Ʈ�� ��� ��带 ����Ű���� �ʱ�ȭ
	if (h->rlink == h) //����Ʈ�� ������� ��
	{
		printf("List is empty!\n"); //���� �޼��� ���
	}
	else //����Ʈ�� ������� ���� ��
	{
		do { //�ݺ��� �ּ� 1�� �̻� ����
			trail = temp->llink; //trail�� temp�� ���� ��带 ����Ŵ
			temp->llink = temp->rlink; //temp�� ���� ��ũ�� temp�� ������ ��ũ�� ��带 ����Ŵ
			temp->rlink = trail; //temp�� ������ ��ũ�� temp�� ���� ��带 ����Ŵ
			temp = temp->llink; //temp�� ���� ���� �Ѿ
		} while (temp != h); //temp�� ��� ��尡 �� �� �ݺ��� ����
	}
	return 0;
}



/**
 *  ����Ʈ�� �˻��Ͽ�, �Է¹��� key���� ū���� ������ ��� �ٷ� �տ� ����
 **/
int insertNode(listNode* h, int key) {
	listNode* temp = h->rlink; //���� ��带 ����Ű�� ������ temp ���� �� ��� ��带 ������ ù ��° ��带 ����Ű���� �ʱ�ȭ
	listNode* insert = (listNode*)malloc(sizeof(listNode)); //�Է¹��� key ���� �����ϱ� ���� ������ insert ���� �� �޸� �Ҵ�
	insert->key = key; //�Է¹��� key ���� insert�� key�� ����
	if (h->rlink == h) //����Ʈ�� ��� ��常 ������ ��
	{
		insertFirst(h, key);
	}
	else //����Ʈ�� ��� ��� �̿��� ��尡 ������ ��
	{
		while (temp != h) //temp�� �̿��Ͽ� insert ��带 ������ ���� �� �Ϸ� �� ������ �ݺ�
		{
			if (temp->key > insert->key) //�Է¹��� key���� ū ���� ������ ��带 �߰�
			{
				insert->llink = temp->llink; //insert�� ���� ��ũ�� temp�� ���� ��带 ����Ŵ
				insert->rlink = temp; //insert�� ������ ��ũ�� temp�� ����Ŵ
				temp->llink->rlink = insert; //temp�� ���� ����� ������ ��ũ�� insert�� ����Ŵ
				temp->llink = insert; //temp�� ���� ��尡 insert�� ����Ű�� (���� �� temp�� ���� ���)-insert-temp ������ ��ġ
				return 0; //�� ��带 ����Ʈ�� �����ϸ� �Լ� ����
			}
			temp = temp->rlink; //�Է¹��� key���� ū ���� �ƴϸ� temp�� ���� ��带 ����Ŵ
		}
		insertLast(h, key); //�Է¹��� key���� ū ���� ����Ʈ���� ã�� ���ϸ� insert ��带 ����Ʈ�� ���� ��ġ
	}
	return 0;
}


/**
 * list���� key�� ���� ��� ����
 */
int deleteNode(listNode* h, int key) {
	listNode* delete = h->rlink; //��带 �����ϱ� ���� ������ delete ���� �� ��� ��带 ������ ù ��° ��带 ����Ű���� �ʱ�ȭ
	if (h->rlink == h) //����Ʈ�� ������� ��
	{
		printf("List is empty!\n"); //����Ʈ�� ����ִٴ� ���� �޼��� ���
	}
	else //����Ʈ�� ������� ���� ��
	{
		while (delete != h) //delete ��尡 ������ ���� �� �Ϸ� �� ������ �ݺ�
		{
			if (delete->key == key) //key ���� delete�� key ���� ������ ��
			{
				//delete�� ���� ����� ������ ��ũ�� delete�� ������ ��带 ����Ŵ
				delete->llink->rlink = delete->rlink;
				//delete�� ������ ����� ���� ��ũ�� delete�� ���� ��带 ����Ű�� (���� �� delete�� ���� ���)-(���� �� delete�� ������ ���) ������ ��ġ
				delete->rlink->llink = delete->llink; 
				//delete�� ����Ű�� ����� �޸� ����
				free(delete);
				//��带 ����Ʈ���� �����ϸ� �Լ� ����
				return 0;
			}
			delete = delete->rlink; //�Է¹��� key�� ��ġ���� ������ delete�� ���� ���� �̵�
		}
		printf("Node with the value %d not found!\n", key); //�Է¹��� key ���� ����Ʈ���� ã�� ���ϸ� ���� �޼��� ���
	}
	return 0;
}


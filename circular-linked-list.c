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
	int key;
	struct Node* llink;
	struct Node* rlink;
} listNode;

/* �Լ� ����Ʈ */
int initialize(listNode** h);
int freeList(listNode* h);
int insertLast(listNode* h, int key);
int deleteLast(listNode* h);
int insertFirst(listNode* h, int key);
int deleteFirst(listNode* h);
int invertList(listNode* h);

int insertNode(listNode* h, int key);
int deleteNode(listNode* h, int key);

void printList(listNode* h);



int main()
{
	char command;
	int key;
	listNode* headnode = NULL;

	do {
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


int initialize(listNode** h) {

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
	int i = 0;
	listNode* p;

	printf("\n---PRINT\n");

	if (h == NULL) {
		printf("Nothing to print....\n");
		return;
	}

	p = h->rlink;

	while (p != NULL && p != h) {
		printf("[ [%d]=%d ] ", i, p->key);
		p = p->rlink;
		i++;
	}
	printf("  items = %d\n", i);


	/* print addresses */
	printf("\n---checking addresses of links\n");
	printf("-------------------------------\n");
	printf("head node: [llink]=%p, [head]=%p, [rlink]=%p\n", h->llink, h, h->rlink);

	i = 0;
	p = h->rlink;
	while (p != NULL && p != h) {
		printf("[ [%d]=%d ] [llink]=%p, [node]=%p, [rlink]=%p\n", i, p->key, p->llink, p, p->rlink);
		p = p->rlink;
		i++;
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
			temp = temp->rlink; //temp�� ���� ��带 ����Ŵ
		}
		insertLast(h, key); //�Է¹��� key���� ū ���� ����Ʈ���� ã�� ���ϸ� insert ��带 ����Ʈ�� ���� ��ġ
	}
	return 0;
}


/**
 * list���� key�� ���� ��� ����
 */
int deleteNode(listNode* h, int key) {

	return 0;
}


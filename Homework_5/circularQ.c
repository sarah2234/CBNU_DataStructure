/*
 * circularQ.c
 *
 *  Data Structures, Homework #5
 *  Department of Computer Science at Chungbuk National University
 */

#include <stdio.h>
#include <stdlib.h>

#define MAX_QUEUE_SIZE 4 //MAX_QUEUE_SIZE��� �̸����� 4�� ��ũ�� ����

typedef char element; //char�� element�� ������
typedef struct {
	element queue[MAX_QUEUE_SIZE]; //���̰� MAX_QUEUE_SIZE��ŭ�� element��(char��) �迭 ����
	int front, rear; //int�� ���� front�� rear ����
}QueueType; //�ش� ����ü�� QueueType�� ������


QueueType *createQueue(); //���� ť�� �����ϴ� �Լ� ����
int freeQueue(QueueType *cQ); //���� ť�� �Ҵ�� �޸𸮸� �����ϴ� �Լ� ����
int isEmpty(QueueType *cQ); //���� ť�� ����ִ��� Ȯ���ϴ� �Լ� ����
int isFull(QueueType *cQ); //���� ť�� á���� Ȯ���ϴ� �Լ� ����
void enQueue(QueueType *cQ, element item); //���� ť�� ���� �����ϴ� �Լ� ����
void deQueue(QueueType *cQ, element* item); //���� ť�� ����� ���� �����ϴ� �Լ� ����
void printQ(QueueType *cQ); //���� ť�� ����� ���� ����ϴ� �Լ� ����
void debugQ(QueueType *cQ); //���� ť�� ������ϴ� �Լ� ����
element getElement(); //���ڸ� �Է¹޴� �Լ� ����

int main(void)
{
	QueueType *cQ = createQueue(); //QueueType�� ������ cQ�� �����ϰ� createQueue�Լ��� ���� ���� ť ����
	element data; //���� ť�� �Է¹��� �����͸� ������ element��(char��) ���� data ����
	char command; //��ɾ �Է¹��� char�� ���� command ����

	printf("----- [�̽���] [2020039075] -----\n");

	do{
		printf("\n-----------------------------------------------------\n");
		printf("                     Circular Q                   \n");
		printf("------------------------------------------------------\n");
		printf(" Insert=i,  Delete=d,   PrintQ=p,   Debug=b,   Quit=q \n");
		printf("------------------------------------------------------\n");

		printf("Command = ");
		scanf(" %c", &command); //���ڸ� �Է¹޾� command�� ����

		switch(command) {
		case 'i': case 'I': //command�� 'i'�� 'I'�� ��
			data = getElement(); //getElement �Լ����� ���Ϲ��� ���� data�� ����
			enQueue(cQ, data); //cQ�� ���� �ּҰ��� data�� ���� ���ڷ� enQueue �Լ� ȣ���Ͽ� ���� ť�� rear�� ������ ����
			break;
		case 'd': case 'D': //command�� 'd'�� 'D'�� ��
			deQueue(cQ, &data); //cQ�� ���� �ּҰ��� data�� �ּҰ��� ���ڷ� deQueue �Լ� ȣ���Ͽ� ���� ť�� front���� ������ ����
			break;
		case 'p': case 'P': //command�� 'p'�� 'P'�� ��
			printQ(cQ); //cQ�� ���� �ּҰ��� ���ڷ� printQ �Լ� ȣ���Ͽ� cQ�� ����� ������ ���
			break;
		case 'b': case 'B': //command�� 'b'�� 'B'�� ��
			debugQ(cQ); //cQ�� ���� �ּҰ��� ���ڷ� debugQ �Լ� ȣ���Ͽ� cQ�� ���λ��� ���
			break;
		case 'q': case 'Q': //command�� 'q'�� 'Q'�� ��
   	        freeQueue(cQ); //cQ�� ���� �ּҰ��� ���ڷ� freeQueue �Լ� ȣ���Ͽ� cQ�� �޸� ����
			break;
		default: //command�� ��� �̿��� ������ ��
			printf("\n       >>>>>   Concentration!!   <<<<<     \n"); //���� �޼��� ���
			break;
		}

	}while(command != 'q' && command != 'Q'); //��� ���� �ڵ带 �ּ� �� �� ������ �� command�� 'q' �Ǵ� 'Q'�� �Է¹����� �ݺ��� ����


	return 1; //1�� �����ϰ� main �Լ� ����
}

QueueType *createQueue() 
{
	QueueType *cQ; //QueueType�� ������ cQ�� ����
	cQ = (QueueType *)malloc(sizeof(QueueType)); //cQ�� QueueType��ŭ �޸� �Ҵ�
	cQ->front = 0; //cQ�� front ������ 0�� ����. ��, cQ���� front�� ��ġ�� 0���� ����
	cQ->rear = 0; //cQ�� rear ������ 0�� ����. ��, cQ���� rear�� ��ġ�� 0���� ����
	for(int i=0;i<MAX_QUEUE_SIZE;i++)
	{
		cQ->queue[i]='\0'; //cQ�� ��� queue ���� �ʱ�ȭ (���α׷��� ó�� ������ �� �Ϻ� queue�� Ư�����ڸ� ����ϴ� ���� �����ϰ��� �߰��Ͽ����ϴ�.)
	}
	return cQ; //cQ�� ����
}

int freeQueue(QueueType *cQ) 
{
    if(cQ == NULL) return 1; //cQ�� NULL�� ����ų ��, �� cQ�� �̹� �޸� �����Ǿ������� 1�� ����
    free(cQ); //cQ�� �Ҵ�Ǿ��� �޸𸮸� ����
    return 1; //1�� ����
}

element getElement()
{
	element item; //���� ť�� ������ �����͸� ������ element��(char��) ���� item�� ����
	printf("Input element = "); 
	scanf(" %c", &item); //�Է¹��� ���ڸ� item�� ����
	return item; //item�� ����
}


/* complete the function */
int isEmpty(QueueType *cQ)
{
	if(cQ->front==cQ->rear) //cQ�� front�� cQ�� rear�� ���� ���� ��
	{
		return 1; //1�� ����
	}
    return 0; //if�� ������ ������Ű�� �ʴ´ٸ� 0�� ����
}

/* complete the function */
int isFull(QueueType *cQ) 
{
	if(cQ->front==(cQ->rear+1)%MAX_QUEUE_SIZE) //cQ�� front�� cQ�� rear�� ���� ���� ��
	{
		return 1; //1�� ����
	}
    return 0; //if�� ������ ������Ű�� �ʴ´ٸ� 0�� ����
}


/* complete the function */
void enQueue(QueueType *cQ, element item) 
{
	if(isFull(cQ)) //cQ�� ���� �ּҰ��� ���ڷ� isFull �Լ��� ȣ���Ͽ� ���� ť�� á���� Ȯ��
	{
		printf("Circular Queue is full!\n\n");
		return; //���� ť�� á�ٸ� ����� ���� ��� �� �Լ� ����
	}
	cQ->rear=(cQ->rear+1)%MAX_QUEUE_SIZE; //���� ť cQ���� rear�� 1 ������Ų ���� rear�� ���� (0<=rear<MAX_QUEUE_SIZE)
	cQ->queue[cQ->rear]=item; //cQ�� queue �迭���� rear��°�� ��ġ�� ���� item�� ���� ����
}

/* complete the function */
void deQueue(QueueType *cQ, element *item) 
{
	if(isEmpty(cQ)) //cQ�� ���� �ּҰ��� ���ڷ� isEmpty �Լ��� ȣ���Ͽ� ���� ť�� ������� Ȯ��
	{
		printf("Circular Queue is empty!\n\n");
		return; //���� ť�� ����ٸ� ����� ���� ��� �� �Լ� ����
	}
    cQ->front=(cQ->front+1)%MAX_QUEUE_SIZE; //���� ť cQ���� front�� 1 ������Ų ���� rear�� ���� (0<=front<MAX_QUEUE_SIZE)
	cQ->queue[cQ->front]='\0'; //cQ�� queue �迭���� front��°�� ��ġ�� ���� ������ ����
}


void printQ(QueueType *cQ) 
{
	int i, first, last; //int�� ���� i, first, last ����

	first = (cQ->front + 1)%MAX_QUEUE_SIZE; //���� ť cQ���� front�� 1 ������Ų ���� first�� ���� (0<=first<MAX_QUEUE_SIZE)
	last = (cQ->rear + 1)%MAX_QUEUE_SIZE; //���� ť cQ���� rear�� 1 ������Ų ���� last�� ���� (0<=last<MAX_QUEUE_SIZE)

	printf("Circular Queue : [");

	i = first; //i�� first �� ����
	while(i != last){ 
		printf("%3c", cQ->queue[i]); //i�� ���� first ������ �����Ͽ� last ���� �Ǳ� ������ cQ�� queue[i]�� ����� ���� ���ʷ� ���
		i = (i+1)%MAX_QUEUE_SIZE; //���� ť���� i�� ���� 1�� ���� (0<=i<MAX_QUEUE_SIZE)

	} //i�� last�� ���� �� �ݺ��� ����
	printf(" ]\n");
}


void debugQ(QueueType *cQ) 
{

	printf("\n---DEBUG\n");
	for(int i = 0; i < MAX_QUEUE_SIZE; i++) //i�� 0���� MAX_QUEUE_SIZE�� �Ǳ� ������ 1�� �����ϸ鼭 �ݺ��� ����
	{
		if(i == cQ->front) {
			printf("  [%d] = front\n", i); //i�� ���� cQ �� front�� ��ġ�� �߰��� ��� �ش� i�� ��(=front�� ��ġ) ���
			continue; //front�� ��ġ Ȯ�� �� �ϴ��� �ڵ� ���� �ǳʶٰ� �ݺ��� �̾ ����
		}
		printf("  [%d] = %c\n", i, cQ->queue[i]); //cQ�� queue �迭���� i��°�� ����� �� ���

	}
	printf("front = %d, rear = %d\n", cQ->front, cQ->rear); //cQ �� front�� rear�� ��ġ ���
}


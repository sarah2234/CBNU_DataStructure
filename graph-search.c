/*
 * Graph Search #2
 *
 * Data Structures
 *
 * Department of Computer Science
 * at Chungbuk National University
 *
 */

#include <stdio.h>
#include <stdlib.h>
#define MAX_VERTEX 10 //������ �ִ� ��

typedef struct node {
	int key; //����� �� ����
	struct node* link; //���� ��带 ����Ŵ
}Node; //���� ����Ʈ

int front = -1;
int rear = -1;

void initializeAdjLists(Node*** adjLists); //�׷����� ���� ����Ʈ�� �ʱ�ȭ�ϴ� �Լ�
void freeAdjLists(Node** node); //���� ����Ʈ�� �Ҵ�� �޸𸮸� �����ϴ� �Լ�
void insertVertex(Node** adjLists, int key); //�׷����� ������ �����ϴ� �Լ�
void insertEdge(int key); //�׷����� ������ �����ϴ� �Լ�
void depthFirstSearch(); //���� �켱 Ž������ ������ �湮�ϴ� �Լ�
void breathFirstSearch(); //�ʺ� �켱 Ž������ ������ �湮�ϴ� �Լ�
void printGraph(); //�׷����� ȭ�鿡 ����ϴ� �Լ�


int main()
{
	char command;
	int key;
	Node** adjLists = NULL; //���� ����Ʈ�� ����� �迭

	printf("----- [�̽���] [2020039075] -----\n");

	do {
		printf("\n\n");
		printf("----------------------------------------------------------------\n");
		printf("                         Graph Searches                         \n");
		printf("----------------------------------------------------------------\n");
		printf(" Initialize Graph       = z                                     \n");
		printf(" Insert Vertex          = v      Insert Edge                = e \n");
		printf(" Depth First Search     = d      Breath First Search        = b \n");
		printf(" Print Graph            = p      Quit                       = q \n");
		printf("----------------------------------------------------------------\n");

		printf("Command = ");
		scanf(" %c", &command);

		switch (command) {
		case 'z': case 'Z':
			initializeAdjLists(&adjLists);
			break;
		case 'q': case 'Q':
			freeAdjLists(adjLists);
			break;
		case 'v': case 'V':
			printf("Your Key = ");
			scanf("%d", &key);
			insertVertex(adjLists, key);
			break;
		case 'e': case 'E':
			insertEdge;
			break;

		case 'd': case 'D':
			depthFirstSearch();
			break;

		case 'b': case 'B':
			breathFirstSearch();
			break;

		case 'p': case 'P':
			printGraph();
			break;

		default:
			printf("\n       >>>>>   Concentration!!   <<<<<     \n");
			break;
		}

	} while (command != 'q' && command != 'Q');

	return 1;
}
void initializeAdjLists(Node*** adjLists)
{
	if (*adjLists != NULL) //�׷����� ������� ���� ��
	{
		freeAdjLists(*adjLists); //���� ����Ʈ�� �޸� ����
	}

	*adjLists = (Node**)malloc(MAX_VERTEX * sizeof(Node*)); //���� ����Ʈ���� ������ ������ ������ �ִ� 10
	for (int i = 0; i < MAX_VERTEX; i++) 
	{
		//main �Լ��� ���� ������ adjLists�� ��ķ� �����Ѵ�.
		*((*adjLists) + i) = NULL; //���� ����Ʈ���� ������ �����ϴ� �����Ͱ� NULL�� ����Ű���� ��(ù ��° ���� �ش�)
	}
}

void freeAdjLists(Node** adjLists) 
{
	for (int i = 0; (i < MAX_VERTEX) && (adjLists[i] != NULL); i++) //���� ����Ʈ���� ������ �����ϴ� �����Ͱ� NULL�̸� free()�� ����� �� ����
	{
		free(adjLists[i]); //������ ���� ������ ������ ������ ���� �迭 �޸� ����(adjLists�� �࿡ ���� �޸� ����)
	}
	free(adjLists); //���� ����Ʈ�� �޸� ���� �Ϸ�
}

void insertVertex(Node** adjLists, int key)
{
	for (int i = 0; i < MAX_VERTEX; i++)
	{
		if (adjLists[i] == NULL) //���� ����Ʈ�� �ش� ���� ���� ������ �������� �ʰ�, adjLists�� ����ִ� ���� �߰����� ��
		{
			adjLists[i] = (Node*)malloc(sizeof(Node)); //���� ����Ʈ�� �࿡ ���Ͽ� �޸� �Ҵ�
			adjLists[i]->key = key; //���� ����Ʈ�� �ش� ���� ���� ���� ���� �� �Լ� ����(adjLists�� ù ��° ���� ���� ����)
			return;
		}
		if (adjLists[i]->key == key) //���� ����Ʈ�� �ش� ���� ���� ������ ������ ��
		{
			printf("The vertex with the key [%d] already exists.\n\n", key); //���� �޼��� ��� �� �Լ� ����
			return; 
		}
	}
	printf("The graph is full!\n\n"); //���� �׷����� ���̻� ������ �߰��� �� ���� �� ���� �޼��� ���
}

void insertEdge(int edge)
{

}

void depthFirstSearch()
{

}

void breathFirstSearch()
{

}

void printGraph()
{

}
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

typedef struct graph {
	int totalVertex; //�׷��� �� ������ �� ����
	int vertex[MAX_VERTEX]; //�׷����� �ִ� ����
}Graph;

typedef struct node {
	int key; //����� �� ����
	struct node* link; //���� ��带 ����Ŵ
}Node; //���� ����Ʈ

int front = -1;
int rear = -1;

void initialize(Graph* graph, Node*** adjLists); //�׷����� ���� ����Ʈ�� �ʱ�ȭ�ϴ� �Լ�
void freeAdjLists(Node** node); //���� ����Ʈ�� �Ҵ�� �޸𸮸� �����ϴ� �Լ�
void insertVertex(int key); //�׷����� ������ �����ϴ� �Լ�
void insertEdge(int key); //�׷����� ������ �����ϴ� �Լ�
void depthFirstSearch(); //���� �켱 Ž������ ������ �湮�ϴ� �Լ�
void breathFirstSearch(); //�ʺ� �켱 Ž������ ������ �湮�ϴ� �Լ�
void printGraph(); //�׷����� ȭ�鿡 ����ϴ� �Լ�


int main()
{
	char command;
	int key;
	Node** adjLists = NULL; //���� ����Ʈ�� ����� �迭
	Graph graph;
	graph.totalVertex = 0;

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
			initialize(&graph, &adjLists);
			break;
		case 'q': case 'Q':
			freeAdjLists(adjLists);
			break;
		case 'v': case 'V':
			printf("Your Key = ");
			scanf("%d", &key);
			insertVertex(key);
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
void initialize(Graph* graph, Node*** adjLists)
{
	if (graph->totalVertex != 0) //�׷����� ������� ���� ��
	{
		graph->totalVertex = 0; //�׷��� �� ������ ���� 0���� ����
		freeAdjLists(*adjLists); //���� ����Ʈ�� �޸� ����
	}

	graph = (Graph*)malloc(sizeof(Graph)); //�׷����� �޸� �Ҵ�
	graph->totalVertex = 0; //�׷����� ������ ���� ����

	*adjLists = (Node**)malloc(MAX_VERTEX * sizeof(Node*)); //���� ����Ʈ���� ������ ������ ������ �ִ� 10
	(*adjLists) = NULL;
	(**adjLists) = NULL; //���� ����Ʈ�� ������ ������ ���� ������ ���� ����
}

void freeAdjLists(Node** adjLists) 
{
	for (int i = 0; (i < MAX_VERTEX) && (adjLists[i] != NULL); i++)
	{
		free(adjLists[i]); //������ ���� ������ ������ ������ ���� �迭 �޸� ����
	}
	free(adjLists); //���� ����Ʈ�� �޸� ���� �Ϸ�
}

void insertVertex(int vertex)
{

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
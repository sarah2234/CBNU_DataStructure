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
#define MAX_VERTEX 10 //정점의 최대 수

typedef struct graph {
	int totalVertex; //그래프 내 정점의 총 개수
	int vertex[MAX_VERTEX]; //그래프에 있는 정점
}Graph;

typedef struct node {
	int key; //노드의 값 저장
	struct node* link; //다음 노드를 가리킴
}Node; //인접 리스트

int front = -1;
int rear = -1;

void initialize(Graph* graph, Node*** adjLists); //그래프와 인접 리스트를 초기화하는 함수
void freeAdjLists(Node** node); //인접 리스트에 할당된 메모리를 해제하는 함수
void insertVertex(int key); //그래프에 정점을 삽입하는 함수
void insertEdge(int key); //그래프에 간선을 삽입하는 함수
void depthFirstSearch(); //깊이 우선 탐색으로 정점을 방문하는 함수
void breathFirstSearch(); //너비 우선 탐색으로 정점을 방문하는 함수
void printGraph(); //그래프를 화면에 출력하는 함수


int main()
{
	char command;
	int key;
	Node** adjLists = NULL; //연결 리스트가 요소인 배열
	Graph graph;
	graph.totalVertex = 0;

	printf("----- [이승현] [2020039075] -----\n");

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
	if (graph->totalVertex != 0) //그래프가 비어있지 않을 때
	{
		graph->totalVertex = 0; //그래프 내 정점의 수를 0으로 만듦
		freeAdjLists(*adjLists); //인접 리스트의 메모리 해제
	}

	graph = (Graph*)malloc(sizeof(Graph)); //그래프에 메모리 할당
	graph->totalVertex = 0; //그래프에 정점이 없는 상태

	*adjLists = (Node**)malloc(MAX_VERTEX * sizeof(Node*)); //인접 리스트에서 꼬리인 정점의 개수는 최대 10
	(*adjLists) = NULL;
	(**adjLists) = NULL; //인접 리스트에 정점과 간선에 대한 정보가 없는 상태
}

void freeAdjLists(Node** adjLists) 
{
	for (int i = 0; (i < MAX_VERTEX) && (adjLists[i] != NULL); i++)
	{
		free(adjLists[i]); //동일한 꼬리 정점을 가지는 간선에 대한 배열 메모리 해제
	}
	free(adjLists); //인접 리스트의 메모리 해제 완료
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
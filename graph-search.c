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

typedef struct node {
	int key; //노드의 값 저장
	struct node* link; //다음 노드를 가리킴
}Node; //인접 리스트

int front = -1;
int rear = -1;

void initializeAdjLists(Node*** adjLists); //그래프와 인접 리스트를 초기화하는 함수
void freeAdjLists(Node** node); //인접 리스트에 할당된 메모리를 해제하는 함수
void insertVertex(Node** adjLists, int key); //그래프에 정점을 삽입하는 함수
void insertEdge(int key); //그래프에 간선을 삽입하는 함수
void depthFirstSearch(); //깊이 우선 탐색으로 정점을 방문하는 함수
void breathFirstSearch(); //너비 우선 탐색으로 정점을 방문하는 함수
void printGraph(); //그래프를 화면에 출력하는 함수


int main()
{
	char command;
	int key;
	Node** adjLists = NULL; //연결 리스트가 요소인 배열

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
	if (*adjLists != NULL) //그래프가 비어있지 않을 때
	{
		freeAdjLists(*adjLists); //인접 리스트의 메모리 해제
	}

	*adjLists = (Node**)malloc(MAX_VERTEX * sizeof(Node*)); //인접 리스트에서 꼬리인 정점의 개수는 최대 10
	for (int i = 0; i < MAX_VERTEX; i++) 
	{
		//main 함수의 이중 포인터 adjLists를 행렬로 간주한다.
		*((*adjLists) + i) = NULL; //인접 리스트에서 꼬리를 저장하는 포인터가 NULL을 가리키도록 함(첫 번째 열에 해당)
	}
}

void freeAdjLists(Node** adjLists) 
{
	for (int i = 0; (i < MAX_VERTEX) && (adjLists[i] != NULL); i++) //인접 리스트에서 꼬리를 저장하는 포인터가 NULL이면 free()를 사용할 수 없음
	{
		free(adjLists[i]); //동일한 꼬리 정점을 가지는 간선에 대한 배열 메모리 해제(adjLists의 행에 대해 메모리 해제)
	}
	free(adjLists); //인접 리스트의 메모리 해제 완료
}

void insertVertex(Node** adjLists, int key)
{
	for (int i = 0; i < MAX_VERTEX; i++)
	{
		if (adjLists[i] == NULL) //인접 리스트에 해당 값을 가진 정점이 존재하지 않고, adjLists의 비어있는 행을 발견했을 때
		{
			adjLists[i] = (Node*)malloc(sizeof(Node)); //인접 리스트의 행에 대하여 메모리 할당
			adjLists[i]->key = key; //인접 리스트에 해당 값을 가진 정점 삽입 후 함수 종료(adjLists의 첫 번째 열에 정점 삽입)
			return;
		}
		if (adjLists[i]->key == key) //인접 리스트에 해당 값을 가진 정점이 존재할 때
		{
			printf("The vertex with the key [%d] already exists.\n\n", key); //오류 메세지 출력 후 함수 종료
			return; 
		}
	}
	printf("The graph is full!\n\n"); //인접 그래프에 더이상 정점을 추가할 수 없을 때 오류 메세지 출력
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
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
void insertEdge(Node** adjLists, int tail, int head); //그래프에 간선을 삽입하는 함수
void depthFirstSearch(); //깊이 우선 탐색으로 정점을 방문하는 함수
void breathFirstSearch(); //너비 우선 탐색으로 정점을 방문하는 함수
void printGraph(Node** adjLists); //그래프를 화면에 출력하는 함수


int main()
{
	char command;
	int key;
	int firstVertex, secondVertex;
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
			printf("First vertex: ");
			scanf("%d", &firstVertex);
			printf("Second vertex: ");
			scanf("%d", &secondVertex);
			insertEdge(adjLists, firstVertex, secondVertex);
			break;

		case 'd': case 'D':
			depthFirstSearch();
			break;

		case 'b': case 'B':
			breathFirstSearch();
			break;

		case 'p': case 'P':
			printGraph(adjLists);
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
		//main 함수의 이중 포인터 adjLists(인접 리스트)를 행렬로 간주한다.
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
			adjLists[i]->key = key;
			adjLists[i]->link = NULL; //인접 리스트에 해당 값을 가진 정점 삽입 후 함수 종료(adjLists의 첫 번째 열에 정점 삽입)
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

void insertEdge(Node** adjLists, int firstKey, int secondKey)
{
	Node* firstVertex = NULL, * secondVertex = NULL; //첫 번째로 입력받은 정점을 찾는 firstVertex와, 두 번째로 입력받은 정점을 찾는 secondVertex
	Node* firstEdge = NULL, * secondEdge = NULL; //firstVertex를 꼬리로 하여 간선을 추가하는 firstEdge와, secondVertex를 꼬리로 하여 간선을 추가하는 secondEdge
	
	for (int i = 0; (i < MAX_VERTEX) && *(adjLists + i); i++) //i가 0부터 그래프 내 정점의 개수까지 증가하며 반복문 실행
	{
		if ((*(adjLists + i))->key == firstKey) //인접 리스트 내 노드 중 첫 번째로 입력받은 정점의 값이 존재할 때
			firstVertex = *(adjLists + i); //firstVertex에 해당 노드 주소 저장
		if ((*(adjLists + i))->key == secondKey) //인접 리스트 내 노드 중 두 번째로 입력받은 정점의 값이 존재할 때
			secondVertex = *(adjLists + i); //secondVertex에 해당 노드 주소 저장
	}

	if (firstVertex != NULL && secondVertex != NULL) //입력받은 두 개의 값에 대한 정점이 그래프 내에 존재할 때
	{
		firstEdge = (Node*)malloc(sizeof(Node)); //첫 번째로 입력받은 정점을 꼬리로, 두 번째를 머리로 하는 간선 firstEdge의 메모리 할당
		firstEdge->key = secondKey; //firstEdge는 두 번째로 입력받은 정점에 대한 노드
		firstEdge->link = NULL; //동일한 꼬리(사용자에게 첫 번째로 입력받은 정점)를 가지는 간선에 대한 노드들 중 firstEdge는 마지막 노드로서 추가됨
		
		while (firstVertex->link)
		{
			firstVertex = firstVertex->link; //첫 번째로 입력받은 정점을 꼬리로 두는 간선에 대한 노드들 중 마지막 노드를 만날 때까지 반복문 실행
			
			if (firstVertex->key == secondKey) //삽입하려는 간선의 정보가 이미 그래프 내에 존재할 때
			{
				//무방향 그래프에서 (u, v)가 그래프에 존재하면 해당 간선은 (v, u)와 동일하므로 인접 리스트에서 v를 꼬리로 하는 간선들에 대하여 추가적으로 검사할 필요가 없다.
				printf("\nThe edge between [%d] and [%d] already exists.\n", firstKey, secondKey); //에러 메세지 출력
				free(firstEdge); //firstEdge 메모리 해제
				return; //함수 종료
			}
		}
		firstVertex->link = firstEdge; //첫 번째로 입력받은 정점을 꼬리로 하고 두 번째로 입력받은 정점를 머리로 두는 간선 추가

		secondEdge = (Node*)malloc(sizeof(Node)); //두 번째로 입력받은 정점을 꼬리로, 첫 번째를 머리로 하는 간선 secondEdge의 메모리 할당
		secondEdge->key = firstKey; //secondEdge는 첫 번째로 입력받은 정점에 대한 노드
		secondEdge->link = NULL; //동일한 꼬리(사용자에게 두 번째로 입력받은 정점)를 가지는 간선에 대한 노드들 중 secondEdge는 마지막 노드로서 추가됨
		while (secondVertex->link)
		{
			secondVertex = secondVertex->link; //두 번째로 입력받은 정점을 꼬리로 두는 간선에 대한 노드들 중 마지막 노드를 만날 때까지 반복문 실행
		}
		secondVertex->link = secondEdge; //두 번째로 입력받은 정점을 꼬리로 하고 첫 번째로 입력받은 정점을 머리로 두는 간선 추가
		return; //간선 추가 완료 후 함수 종료
	}
	if (firstVertex == NULL) //첫 번째로 입력받은 정점이 존재하지 않을 때
		printf("The vertex with the value [%d] does not exist.\n", firstKey); //에러 메세지 출력
	if (secondVertex==NULL) //두 번째로 입력받은 정점이 존재하지 않을 때
		printf("The vertex with the value [%d] does not exist.\n", secondKey); //에러 메세지 출력
	printf("\n");
}

void depthFirstSearch()
{

}

void breathFirstSearch()
{

}

void printGraph(Node** adjLists) //인접 리스트 형태로 그래프 출력
{
	Node* head = NULL; //머리를 저장하는 head

	for (int i = 0; (i < MAX_VERTEX) && adjLists[i]; i++) //인접 리스트의 행에 대해서 조사
	{
		printf("Tail: %d\n", adjLists[i]->key); //꼬리인 정점의 값 출력
		printf("List of Edges: ");

		//해당 정점에 부속하는 간선이 있을 때 아래의 반복문 실행
		for (head = adjLists[i]; head->link && head; head = head->link) //head가 꼬리를 저장하는 노드가 가리키는 곳부터 시작하여 NULL이 될 때까지 반복문 실행
		{
			printf("(%d, %d) ", adjLists[i]->key, head->link->key); //(꼬리, 머리) 출력				
		}
		
		if (!(adjLists[i]->link)) //해당 정점에 대한 간선이 존재하지 않을 때
		{
			printf("None"); //오류 메세지 출력
		}
		printf("\n\n");
	}
}
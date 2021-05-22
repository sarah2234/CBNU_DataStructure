/*
 * Graph Search
 *
 * Data Structures
 *
 * Department of Computer Science
 * at Chungbuk National University
 *
 */

#include <stdio.h>
#include <stdlib.h>
#define MAX_VERTICES 10 //정점의 최대 수
typedef int bool;
#define TRUE 1
#define FALSE 0

typedef struct node* nodePointer;

typedef struct node {
	int key; //노드의 값 저장
	nodePointer link; //다음 노드를 가리킴
}Node; //인접 리스트

bool visited[MAX_VERTICES]; //깊이 우선 탐색과 너비 우선 탐색에 사용되는 visited flag
Node* queue[MAX_VERTICES]; //너비 우선 탐색에 사용되는 큐
int front = -1, rear = -1; //큐에서 원소가 삭제되는 곳의 인덱스인 front, 원소가 삽입되는 곳의 인덱스인 rear

void initializeAdjLists(Node*** adjLists); //그래프와 인접 리스트를 초기화하는 함수
void freeAdjLists(Node** node); //인접 리스트에 할당된 메모리를 해제하는 함수
void insertVertex(Node** adjLists, int key); //그래프에 정점을 삽입하는 함수
void insertEdge(Node** adjLists, int tail, int head); //그래프에 간선을 삽입하는 함수
void depthFirstSearch(Node** adjLists, Node* current); //깊이 우선 탐색으로 정점을 방문하는 함수
void initializeVisited(); //visited 배열을 초기화하는 함수 (그래프를 탐색할 때 visited flag 사용)
void breathFirstSearch(Node** adjLists, Node* firstVertex); //너비 우선 탐색으로 정점을 방문하는 함수
void addq(Node*); //큐에 노드를 삽입하는 함수
Node* deleteq(); //큐에서 노드를 삭제하는 함수
void printGraph(Node** adjLists); //그래프를 화면에 출력하는 함수


int main()
{
	char command;
	int key;
	int firstVertex, secondVertex; //간선을 삽입할 때 입력받기 위한 firstVertex, secondVertex
	Node** adjLists = NULL; //인접 리스트는 이중 포인터로 선언 후 간선을 삽입할 때 연결 리스트로 사용

	printf("----- [이승현] [2020039075] -----\n");

	do { //'q'나 'Q'를 입력받으면 종료
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
		scanf(" %c", &command); //명령어 입력

		switch (command) {
		case 'z': case 'Z':
			initializeAdjLists(&adjLists); //'z'나 'Z'를 입력받으면 인접 리스트 초기화
			break;
		case 'q': case 'Q':
			freeAdjLists(adjLists); //'q'나 'Q'를 입력받으면 인접 리스트의 메모리 해제
			free(queue); //큐의 메모리 해제
			break;
		case 'v': case 'V':
			printf("Your Key = ");
			scanf("%d", &key);
			insertVertex(adjLists, key); //'v'나 'V'를 입력받으면 인접 리스트에 정점 삽입
			break;
		case 'e': case 'E':
			printf("First vertex: ");
			scanf("%d", &firstVertex);
			printf("Second vertex: ");
			scanf("%d", &secondVertex);
			insertEdge(adjLists, firstVertex, secondVertex); //'e'나 'E'를 입력받으면 인접 리스트에 간선 삽입
			break;

		case 'd': case 'D':
			for (int i = 0; i < MAX_VERTICES; i++) //'d'나 'D'를 입력받으면 존재하는 모든 정점을 깊이 우선 탐색으로 조사
			{
				if (*(adjLists + i)) //해당 정점이 존재할 때
				{
					depthFirstSearch(adjLists, *(adjLists + i)); //dfs 함수 호출
				}
			}
			initializeVisited(); //추후 탐색을 위해 visited 초기화
			break;

		case 'b': case 'B':
			for (int i = 0; i < MAX_VERTICES; i++) //'b'나 'B'를 입력받으면 존재하는 모든 정점을 너비 우선 탐색으로 조사
			{
				if (*(adjLists + i)) //해당 정점이 존재할 때
				{
					breathFirstSearch(adjLists, *(adjLists + i)); //dbs 함수 호출
				}
			}
			initializeVisited(); //추후 탐색을 위해 visited 초기화
			break;

		case 'p': case 'P':
			printGraph(adjLists); //'p'나 'P'를 입력받으면 그래프(화면에서는 인접 리스트 형식) 출력
			break;

		default: //이외의 값에 대해서는 에러 메세지 출력
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

	*adjLists = (Node**)malloc(MAX_VERTICES * sizeof(Node*)); //인접 리스트에서 꼬리인 정점의 개수는 최대 10
	for (int i = 0; i < MAX_VERTICES; i++)
	{
		//동일한 꼬리를 가지는 간선에 대한 연결 리스트를 생성한다.
		*((*adjLists) + i) = NULL; //인접 리스트에서 꼬리를 저장하는 포인터가 NULL을 가리키도록 함(첫 번째 열에 해당)
	}
}

void freeAdjLists(Node** adjLists)
{
	Node* prev = NULL; //선행 노드 prev
	Node* current = NULL; //prev 다음의 노드 current
	for (int i = 0; i < MAX_VERTICES; i++) //인접 리스트에서 꼬리를 저장하는 포인터가 NULL이면 free()를 사용할 수 없음
	{
		current = adjLists[i];
		while (current != NULL) //동일한 꼬리를 가지는 간선에 대한 연결 리스트 메모리 해제
		{
			prev = current;
			current = current->link;
			free(prev);
		}
	}
	free(adjLists); //인접 리스트의 메모리 해제 완료
}

void insertVertex(Node** adjLists, int key)
{
	if (adjLists[key] != NULL) //그래프 내 해당 값을 가진 정점이 이미 존재할 때
	{
		printf("The vertex with the key [%d] already exists.\n\n", key); //에러 메세지 출력
		return;  //함수 종료
	}

	Node* insert = (Node*)malloc(sizeof(Node)); //새로운 정점을 그래프에 삽입하기 위한 노드 insert
	insert->key = key; //insert는 입력받은 key 값을 저장
	insert->link = NULL; //insert는 새로운 정점이므로 부속된 간선이 존재하지 않음
	adjLists[key] = insert; //인접 리스트에 insert 삽입
}

void insertEdge(Node** adjLists, int firstKey, int secondKey)
{
	if (adjLists[firstKey] == NULL) //해당 정점이 그래프에 존재하지 않을 때
		printf("The vertex with the value [%d] does not exist.\n", firstKey); //에러 메세지 출력
	if (adjLists[secondKey] == NULL) //해당 정점이 그래프에 존재하지 않을 때
		printf("The vertex with the value [%d] does not exist.\n", secondKey); //에러 메세지 출력

	else if (adjLists[firstKey] && adjLists[secondKey])
	{
		Node* firstVertex = (Node*)malloc(sizeof(Node)); //첫 번째로 입력받은 정점을 firstVertex에 저장
		firstVertex->key = firstKey;
		firstVertex->link = NULL;
		Node* secondVertex = (Node*)malloc(sizeof(Node)); //두 번째로 입력받은 정점을 secondVertex에 저장
		secondVertex->key = secondKey;
		secondVertex->link = NULL;
		Node* firstEdge = adjLists[firstKey]; //firstVertex가 꼬리인 간선 연결 리스트에 새로운 간선을 넣기 위한 firstEdge
		Node* secondEdge = adjLists[secondKey]; //secondVertex가 꼬리인 간선 연결 리스트에 새로운 간선을 넣기 위한 secondEdge

//(firstVertex, secondVertex) 삽입
		while (firstEdge->link) //firstEdge가 마지막 노드에 도달할 때까지 반복문 실행
		{

			if (firstEdge->link->key == secondKey) //동일한 간선이 그래프에 이미 존재할 때
			{
				//무방향 그래프에서 (u, v)가 그래프에 존재하면 해당 간선은 (v, u)와 동일하므로 v를 꼬리로 하는 간선들에 대하여 추가적으로 검사할 필요가 없다.
				printf("\nThe edge between [%d] and [%d] already exists.\n", firstKey, secondKey); //에러 메세지 출력
				free(secondVertex);
				return; //함수 종료
			}

			else if (firstEdge->link->key > secondKey) //기존의 간선들 중 머리 노드의 값이 입력받은 값보다 더 클 때
			{
				secondVertex->link = firstEdge->link;
				firstEdge->link = secondVertex; //해당 노드가 새로운 노드 이후에 오도록 배치 (간선의 머리 정점들을 크기 순으로 배열)
				break; //반복문 종료
			}

			else //위의 두 조건을 만족시키지 않을 때
				firstEdge = firstEdge->link; //다음 노드로 이동
		}
		if (!firstEdge->link)
			firstEdge->link = secondVertex; //firstVertex가 꼬리인 간선 연결 리스트의 마지막에 새로운 간선 추가

//(secondVertex, firstVertex) 삽입
		while (secondEdge->link) //secondEdge가 마지막 노드에 도달할 때까지 반복문 실행
		{
			if (secondEdge->link->key > firstKey) //기존의 간선들 중 머리 노드의 값이 입력받은 값보다 더 클 때
			{
				firstVertex->link = secondEdge->link;
				secondEdge->link = firstVertex; //해당 노드가 새로운 노드 이후에 오도록 배치 (간선의 머리 정점들을 크기 순으로 배열)
				return; //함수 종료
			}

			else //위의 두 조건을 만족시키지 않을 때
				secondEdge = secondEdge->link; //다음 노드로 이동
		}
		if (!secondEdge->link)
			secondEdge->link = firstVertex; //secondVertex가 꼬리인 간선 연결 리스트의 마지막에 새로운 간선 추가
	}
}

void depthFirstSearch(Node** adjLists, Node* currentVertex) //현재 조사하고자하는 정점에 대한 노드를 가리키는 currentVertex
{
	Node* head = NULL; //currentVertex에 부속된 간선의 머리를 조사하기 위한 head

	if (visited[currentVertex->key] == TRUE) //currentVertex가 이미 조사한 적 있는 노드일 때
		return; //함수 종료

	visited[currentVertex->key] = TRUE; //조사를 완료한 노드이므로 TRUE 표시
	printf("%2d ", currentVertex->key); //조사 완료한 노드의 값 출력

	for (head = adjLists[currentVertex->key]; head; head = head->link) //currentVertex에 부속된 간선 조사
	{
		if (!visited[head->key]) //해당 간선의 머리 노드 중 아직 조사하지 않은 것이 있을 때
			depthFirstSearch(adjLists, head); //머리 노드를 순환법으로 조사하기 위한 depthFirstSearch 호출
	}
}

void initializeVisited()
{
	for (int i = 0; i < MAX_VERTICES; i++)
	{
		visited[i] = FALSE; //추후 노드 탐색을 다시 올바르게 호출할 수 있도록 visited의 모든 요소에 대하여 FALSE로 설정
	}
}

void breathFirstSearch(Node** adjLists, Node* currentVertex) //현재 조사하고자하는 정점에 대한 노드를 가리키는 currentVertex
{
	Node* adjVertex = NULL; //currentVertex와 인접하는 정점에 대한 노드 adjVertex
	front = rear = -1; //큐 초기화
	if (visited[currentVertex->key] == TRUE) //currentVertex가 이미 조사한 적 있는 노드일 때
		return; //함수 종료

	visited[currentVertex->key] = TRUE; //조사를 완료한 노드이므로 TRUE 표시
	printf("%2d ", currentVertex->key); //조사 완료한 노드의 값 출력

	addq(currentVertex); //조사 완료한 노드를 큐에 삽입
	while (TRUE) //큐가 공백 상태가 되어 더이상 조사할 노드가 없을 때까지 반복 (break로 반복문 종료)
	{
		currentVertex = deleteq(); //큐에서 front가 가리키는 곳의 노드를 꺼내 currentVertex에 저장
		
		if (!currentVertex) //큐가 공백 상태가 되어 조사할 노드가 없을 때
			return; //함수 종료
		
		for (adjVertex = adjLists[currentVertex->key]; adjVertex; adjVertex = adjVertex->link) //현재 조사하는 정점과 인접하는 다른 정점들에 대해 조사
		{
			if (!visited[adjVertex->key]) //currentVertex와 인접한 노드가 아직 조사되지 않았을 때
			{
				printf("%2d ", adjVertex->key); //해당 노드의 값 출력
				addq(adjVertex); //큐에 노드 삽입
				visited[adjVertex->key] = TRUE; //조사를 완료한 노드이므로 TRUE 표시
			}
		}
	}
}

void addq(Node* adjVertex)
{
	if (front == (rear + 1) % MAX_VERTICES) //큐가 만원 상태일 때
	/*단순 그래프에서 정점의 개수가 n일 때, 한 정점 당 부속하는 간선의 최대 개수는 n-1이다. 
	따라서 에러 메세지를 출력할 일은 없다.*/
	{
		printf("Unable to insert [%d] into the queue.\n", adjVertex->key); //에러 메세지 출력
		return; //함수 종료
	}
	rear = (rear + 1) % MAX_VERTICES; //큐 내에서 rear이 다음 공간을 가리키도록 함
	queue[rear] = adjVertex; //rear이 가리키는 곳에 노드 삽입
}

Node* deleteq()
{
	Node* vertex = NULL; //삭제한 노드를 저장하는 vertex
	if (front != rear) //큐가 공백 상태가 아닐 때
	{
		front = (front + 1) % MAX_VERTICES; //큐 내에서 front가 다음 공간을 가리키도록 함
		vertex = queue[front]; //큐에서 노드를 삭제하기 전에 vertex에 저장
		queue[front] = '\0'; //front가 가리키는 곳에 노드 삭제
	}
	return vertex; //큐가 공백이라면 NULL을, 공백이 아니라면 노드를 리턴
}

void printGraph(Node** adjLists) //인접 리스트 형태로 그래프 출력
{
	for (int i = 0; i < MAX_VERTICES; i++) //i는 0부터 9까지 1씩 증가하며 반복문 수행
	{
		if (adjLists[i]) //i의 값에 해당하는 정점(노드)가 있을 때
		{
			printf("Tail: %d\n", adjLists[i]->key); //꼬리로서 노드의 값 출력
			printf("List of Edges: ");
			for (Node* head = adjLists[i]->link; head; head = head->link) //머리 노드를 가리키는 head가 NULL이 될 때까지 반복문 수행
			{
				printf("(%d, %d) ", adjLists[i]->key, head->key); //(꼬리, 머리) 형식으로 간선 출력
			}
			printf("\n\n");
		}
	}
}
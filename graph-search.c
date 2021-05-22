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
#define MAX_VERTICES 10 //������ �ִ� ��
typedef int bool;
#define TRUE 1
#define FALSE 0

typedef struct node* nodePointer;

typedef struct node {
	int key; //����� �� ����
	nodePointer link; //���� ��带 ����Ŵ
}Node; //���� ����Ʈ

bool visited[MAX_VERTICES]; //���� �켱 Ž���� �ʺ� �켱 Ž���� ���Ǵ� visited flag
Node* queue[MAX_VERTICES]; //�ʺ� �켱 Ž���� ���Ǵ� ť
int front = -1, rear = -1; //ť���� ���Ұ� �����Ǵ� ���� �ε����� front, ���Ұ� ���ԵǴ� ���� �ε����� rear

void initializeAdjLists(Node*** adjLists); //�׷����� ���� ����Ʈ�� �ʱ�ȭ�ϴ� �Լ�
void freeAdjLists(Node** node); //���� ����Ʈ�� �Ҵ�� �޸𸮸� �����ϴ� �Լ�
void insertVertex(Node** adjLists, int key); //�׷����� ������ �����ϴ� �Լ�
void insertEdge(Node** adjLists, int tail, int head); //�׷����� ������ �����ϴ� �Լ�
void depthFirstSearch(Node** adjLists, Node* current); //���� �켱 Ž������ ������ �湮�ϴ� �Լ�
void initializeVisited(); //visited �迭�� �ʱ�ȭ�ϴ� �Լ� (�׷����� Ž���� �� visited flag ���)
void breathFirstSearch(Node** adjLists, Node* firstVertex); //�ʺ� �켱 Ž������ ������ �湮�ϴ� �Լ�
void addq(Node*); //ť�� ��带 �����ϴ� �Լ�
Node* deleteq(); //ť���� ��带 �����ϴ� �Լ�
void printGraph(Node** adjLists); //�׷����� ȭ�鿡 ����ϴ� �Լ�


int main()
{
	char command;
	int key;
	int firstVertex, secondVertex; //������ ������ �� �Է¹ޱ� ���� firstVertex, secondVertex
	Node** adjLists = NULL; //���� ����Ʈ�� ���� �����ͷ� ���� �� ������ ������ �� ���� ����Ʈ�� ���

	printf("----- [�̽���] [2020039075] -----\n");

	do { //'q'�� 'Q'�� �Է¹����� ����
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
		scanf(" %c", &command); //��ɾ� �Է�

		switch (command) {
		case 'z': case 'Z':
			initializeAdjLists(&adjLists); //'z'�� 'Z'�� �Է¹����� ���� ����Ʈ �ʱ�ȭ
			break;
		case 'q': case 'Q':
			freeAdjLists(adjLists); //'q'�� 'Q'�� �Է¹����� ���� ����Ʈ�� �޸� ����
			free(queue); //ť�� �޸� ����
			break;
		case 'v': case 'V':
			printf("Your Key = ");
			scanf("%d", &key);
			insertVertex(adjLists, key); //'v'�� 'V'�� �Է¹����� ���� ����Ʈ�� ���� ����
			break;
		case 'e': case 'E':
			printf("First vertex: ");
			scanf("%d", &firstVertex);
			printf("Second vertex: ");
			scanf("%d", &secondVertex);
			insertEdge(adjLists, firstVertex, secondVertex); //'e'�� 'E'�� �Է¹����� ���� ����Ʈ�� ���� ����
			break;

		case 'd': case 'D':
			for (int i = 0; i < MAX_VERTICES; i++) //'d'�� 'D'�� �Է¹����� �����ϴ� ��� ������ ���� �켱 Ž������ ����
			{
				if (*(adjLists + i)) //�ش� ������ ������ ��
				{
					depthFirstSearch(adjLists, *(adjLists + i)); //dfs �Լ� ȣ��
				}
			}
			initializeVisited(); //���� Ž���� ���� visited �ʱ�ȭ
			break;

		case 'b': case 'B':
			for (int i = 0; i < MAX_VERTICES; i++) //'b'�� 'B'�� �Է¹����� �����ϴ� ��� ������ �ʺ� �켱 Ž������ ����
			{
				if (*(adjLists + i)) //�ش� ������ ������ ��
				{
					breathFirstSearch(adjLists, *(adjLists + i)); //dbs �Լ� ȣ��
				}
			}
			initializeVisited(); //���� Ž���� ���� visited �ʱ�ȭ
			break;

		case 'p': case 'P':
			printGraph(adjLists); //'p'�� 'P'�� �Է¹����� �׷���(ȭ�鿡���� ���� ����Ʈ ����) ���
			break;

		default: //�̿��� ���� ���ؼ��� ���� �޼��� ���
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

	*adjLists = (Node**)malloc(MAX_VERTICES * sizeof(Node*)); //���� ����Ʈ���� ������ ������ ������ �ִ� 10
	for (int i = 0; i < MAX_VERTICES; i++)
	{
		//������ ������ ������ ������ ���� ���� ����Ʈ�� �����Ѵ�.
		*((*adjLists) + i) = NULL; //���� ����Ʈ���� ������ �����ϴ� �����Ͱ� NULL�� ����Ű���� ��(ù ��° ���� �ش�)
	}
}

void freeAdjLists(Node** adjLists)
{
	Node* prev = NULL; //���� ��� prev
	Node* current = NULL; //prev ������ ��� current
	for (int i = 0; i < MAX_VERTICES; i++) //���� ����Ʈ���� ������ �����ϴ� �����Ͱ� NULL�̸� free()�� ����� �� ����
	{
		current = adjLists[i];
		while (current != NULL) //������ ������ ������ ������ ���� ���� ����Ʈ �޸� ����
		{
			prev = current;
			current = current->link;
			free(prev);
		}
	}
	free(adjLists); //���� ����Ʈ�� �޸� ���� �Ϸ�
}

void insertVertex(Node** adjLists, int key)
{
	if (adjLists[key] != NULL) //�׷��� �� �ش� ���� ���� ������ �̹� ������ ��
	{
		printf("The vertex with the key [%d] already exists.\n\n", key); //���� �޼��� ���
		return;  //�Լ� ����
	}

	Node* insert = (Node*)malloc(sizeof(Node)); //���ο� ������ �׷����� �����ϱ� ���� ��� insert
	insert->key = key; //insert�� �Է¹��� key ���� ����
	insert->link = NULL; //insert�� ���ο� �����̹Ƿ� �μӵ� ������ �������� ����
	adjLists[key] = insert; //���� ����Ʈ�� insert ����
}

void insertEdge(Node** adjLists, int firstKey, int secondKey)
{
	if (adjLists[firstKey] == NULL) //�ش� ������ �׷����� �������� ���� ��
		printf("The vertex with the value [%d] does not exist.\n", firstKey); //���� �޼��� ���
	if (adjLists[secondKey] == NULL) //�ش� ������ �׷����� �������� ���� ��
		printf("The vertex with the value [%d] does not exist.\n", secondKey); //���� �޼��� ���

	else if (adjLists[firstKey] && adjLists[secondKey])
	{
		Node* firstVertex = (Node*)malloc(sizeof(Node)); //ù ��°�� �Է¹��� ������ firstVertex�� ����
		firstVertex->key = firstKey;
		firstVertex->link = NULL;
		Node* secondVertex = (Node*)malloc(sizeof(Node)); //�� ��°�� �Է¹��� ������ secondVertex�� ����
		secondVertex->key = secondKey;
		secondVertex->link = NULL;
		Node* firstEdge = adjLists[firstKey]; //firstVertex�� ������ ���� ���� ����Ʈ�� ���ο� ������ �ֱ� ���� firstEdge
		Node* secondEdge = adjLists[secondKey]; //secondVertex�� ������ ���� ���� ����Ʈ�� ���ο� ������ �ֱ� ���� secondEdge

//(firstVertex, secondVertex) ����
		while (firstEdge->link) //firstEdge�� ������ ��忡 ������ ������ �ݺ��� ����
		{

			if (firstEdge->link->key == secondKey) //������ ������ �׷����� �̹� ������ ��
			{
				//������ �׷������� (u, v)�� �׷����� �����ϸ� �ش� ������ (v, u)�� �����ϹǷ� v�� ������ �ϴ� �����鿡 ���Ͽ� �߰������� �˻��� �ʿ䰡 ����.
				printf("\nThe edge between [%d] and [%d] already exists.\n", firstKey, secondKey); //���� �޼��� ���
				free(secondVertex);
				return; //�Լ� ����
			}

			else if (firstEdge->link->key > secondKey) //������ ������ �� �Ӹ� ����� ���� �Է¹��� ������ �� Ŭ ��
			{
				secondVertex->link = firstEdge->link;
				firstEdge->link = secondVertex; //�ش� ��尡 ���ο� ��� ���Ŀ� ������ ��ġ (������ �Ӹ� �������� ũ�� ������ �迭)
				break; //�ݺ��� ����
			}

			else //���� �� ������ ������Ű�� ���� ��
				firstEdge = firstEdge->link; //���� ���� �̵�
		}
		if (!firstEdge->link)
			firstEdge->link = secondVertex; //firstVertex�� ������ ���� ���� ����Ʈ�� �������� ���ο� ���� �߰�

//(secondVertex, firstVertex) ����
		while (secondEdge->link) //secondEdge�� ������ ��忡 ������ ������ �ݺ��� ����
		{
			if (secondEdge->link->key > firstKey) //������ ������ �� �Ӹ� ����� ���� �Է¹��� ������ �� Ŭ ��
			{
				firstVertex->link = secondEdge->link;
				secondEdge->link = firstVertex; //�ش� ��尡 ���ο� ��� ���Ŀ� ������ ��ġ (������ �Ӹ� �������� ũ�� ������ �迭)
				return; //�Լ� ����
			}

			else //���� �� ������ ������Ű�� ���� ��
				secondEdge = secondEdge->link; //���� ���� �̵�
		}
		if (!secondEdge->link)
			secondEdge->link = firstVertex; //secondVertex�� ������ ���� ���� ����Ʈ�� �������� ���ο� ���� �߰�
	}
}

void depthFirstSearch(Node** adjLists, Node* currentVertex) //���� �����ϰ����ϴ� ������ ���� ��带 ����Ű�� currentVertex
{
	Node* head = NULL; //currentVertex�� �μӵ� ������ �Ӹ��� �����ϱ� ���� head

	if (visited[currentVertex->key] == TRUE) //currentVertex�� �̹� ������ �� �ִ� ����� ��
		return; //�Լ� ����

	visited[currentVertex->key] = TRUE; //���縦 �Ϸ��� ����̹Ƿ� TRUE ǥ��
	printf("%2d ", currentVertex->key); //���� �Ϸ��� ����� �� ���

	for (head = adjLists[currentVertex->key]; head; head = head->link) //currentVertex�� �μӵ� ���� ����
	{
		if (!visited[head->key]) //�ش� ������ �Ӹ� ��� �� ���� �������� ���� ���� ���� ��
			depthFirstSearch(adjLists, head); //�Ӹ� ��带 ��ȯ������ �����ϱ� ���� depthFirstSearch ȣ��
	}
}

void initializeVisited()
{
	for (int i = 0; i < MAX_VERTICES; i++)
	{
		visited[i] = FALSE; //���� ��� Ž���� �ٽ� �ùٸ��� ȣ���� �� �ֵ��� visited�� ��� ��ҿ� ���Ͽ� FALSE�� ����
	}
}

void breathFirstSearch(Node** adjLists, Node* currentVertex) //���� �����ϰ����ϴ� ������ ���� ��带 ����Ű�� currentVertex
{
	Node* adjVertex = NULL; //currentVertex�� �����ϴ� ������ ���� ��� adjVertex
	front = rear = -1; //ť �ʱ�ȭ
	if (visited[currentVertex->key] == TRUE) //currentVertex�� �̹� ������ �� �ִ� ����� ��
		return; //�Լ� ����

	visited[currentVertex->key] = TRUE; //���縦 �Ϸ��� ����̹Ƿ� TRUE ǥ��
	printf("%2d ", currentVertex->key); //���� �Ϸ��� ����� �� ���

	addq(currentVertex); //���� �Ϸ��� ��带 ť�� ����
	while (TRUE) //ť�� ���� ���°� �Ǿ� ���̻� ������ ��尡 ���� ������ �ݺ� (break�� �ݺ��� ����)
	{
		currentVertex = deleteq(); //ť���� front�� ����Ű�� ���� ��带 ���� currentVertex�� ����
		
		if (!currentVertex) //ť�� ���� ���°� �Ǿ� ������ ��尡 ���� ��
			return; //�Լ� ����
		
		for (adjVertex = adjLists[currentVertex->key]; adjVertex; adjVertex = adjVertex->link) //���� �����ϴ� ������ �����ϴ� �ٸ� �����鿡 ���� ����
		{
			if (!visited[adjVertex->key]) //currentVertex�� ������ ��尡 ���� ������� �ʾ��� ��
			{
				printf("%2d ", adjVertex->key); //�ش� ����� �� ���
				addq(adjVertex); //ť�� ��� ����
				visited[adjVertex->key] = TRUE; //���縦 �Ϸ��� ����̹Ƿ� TRUE ǥ��
			}
		}
	}
}

void addq(Node* adjVertex)
{
	if (front == (rear + 1) % MAX_VERTICES) //ť�� ���� ������ ��
	/*�ܼ� �׷������� ������ ������ n�� ��, �� ���� �� �μ��ϴ� ������ �ִ� ������ n-1�̴�. 
	���� ���� �޼����� ����� ���� ����.*/
	{
		printf("Unable to insert [%d] into the queue.\n", adjVertex->key); //���� �޼��� ���
		return; //�Լ� ����
	}
	rear = (rear + 1) % MAX_VERTICES; //ť ������ rear�� ���� ������ ����Ű���� ��
	queue[rear] = adjVertex; //rear�� ����Ű�� ���� ��� ����
}

Node* deleteq()
{
	Node* vertex = NULL; //������ ��带 �����ϴ� vertex
	if (front != rear) //ť�� ���� ���°� �ƴ� ��
	{
		front = (front + 1) % MAX_VERTICES; //ť ������ front�� ���� ������ ����Ű���� ��
		vertex = queue[front]; //ť���� ��带 �����ϱ� ���� vertex�� ����
		queue[front] = '\0'; //front�� ����Ű�� ���� ��� ����
	}
	return vertex; //ť�� �����̶�� NULL��, ������ �ƴ϶�� ��带 ����
}

void printGraph(Node** adjLists) //���� ����Ʈ ���·� �׷��� ���
{
	for (int i = 0; i < MAX_VERTICES; i++) //i�� 0���� 9���� 1�� �����ϸ� �ݺ��� ����
	{
		if (adjLists[i]) //i�� ���� �ش��ϴ� ����(���)�� ���� ��
		{
			printf("Tail: %d\n", adjLists[i]->key); //�����μ� ����� �� ���
			printf("List of Edges: ");
			for (Node* head = adjLists[i]->link; head; head = head->link) //�Ӹ� ��带 ����Ű�� head�� NULL�� �� ������ �ݺ��� ����
			{
				printf("(%d, %d) ", adjLists[i]->key, head->key); //(����, �Ӹ�) �������� ���� ���
			}
			printf("\n\n");
		}
	}
}
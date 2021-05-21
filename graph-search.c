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
void insertEdge(Node** adjLists, int tail, int head); //�׷����� ������ �����ϴ� �Լ�
void depthFirstSearch(); //���� �켱 Ž������ ������ �湮�ϴ� �Լ�
void breathFirstSearch(); //�ʺ� �켱 Ž������ ������ �湮�ϴ� �Լ�
void printGraph(Node** adjLists); //�׷����� ȭ�鿡 ����ϴ� �Լ�


int main()
{
	char command;
	int key;
	int firstVertex, secondVertex;
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
	if (*adjLists != NULL) //�׷����� ������� ���� ��
	{
		freeAdjLists(*adjLists); //���� ����Ʈ�� �޸� ����
	}

	*adjLists = (Node**)malloc(MAX_VERTEX * sizeof(Node*)); //���� ����Ʈ���� ������ ������ ������ �ִ� 10
	for (int i = 0; i < MAX_VERTEX; i++) 
	{
		//main �Լ��� ���� ������ adjLists(���� ����Ʈ)�� ��ķ� �����Ѵ�.
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
			adjLists[i]->key = key;
			adjLists[i]->link = NULL; //���� ����Ʈ�� �ش� ���� ���� ���� ���� �� �Լ� ����(adjLists�� ù ��° ���� ���� ����)
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

void insertEdge(Node** adjLists, int firstKey, int secondKey)
{
	Node* firstVertex = NULL, * secondVertex = NULL; //ù ��°�� �Է¹��� ������ ã�� firstVertex��, �� ��°�� �Է¹��� ������ ã�� secondVertex
	Node* firstEdge = NULL, * secondEdge = NULL; //firstVertex�� ������ �Ͽ� ������ �߰��ϴ� firstEdge��, secondVertex�� ������ �Ͽ� ������ �߰��ϴ� secondEdge
	
	for (int i = 0; (i < MAX_VERTEX) && *(adjLists + i); i++) //i�� 0���� �׷��� �� ������ �������� �����ϸ� �ݺ��� ����
	{
		if ((*(adjLists + i))->key == firstKey) //���� ����Ʈ �� ��� �� ù ��°�� �Է¹��� ������ ���� ������ ��
			firstVertex = *(adjLists + i); //firstVertex�� �ش� ��� �ּ� ����
		if ((*(adjLists + i))->key == secondKey) //���� ����Ʈ �� ��� �� �� ��°�� �Է¹��� ������ ���� ������ ��
			secondVertex = *(adjLists + i); //secondVertex�� �ش� ��� �ּ� ����
	}

	if (firstVertex != NULL && secondVertex != NULL) //�Է¹��� �� ���� ���� ���� ������ �׷��� ���� ������ ��
	{
		firstEdge = (Node*)malloc(sizeof(Node)); //ù ��°�� �Է¹��� ������ ������, �� ��°�� �Ӹ��� �ϴ� ���� firstEdge�� �޸� �Ҵ�
		firstEdge->key = secondKey; //firstEdge�� �� ��°�� �Է¹��� ������ ���� ���
		firstEdge->link = NULL; //������ ����(����ڿ��� ù ��°�� �Է¹��� ����)�� ������ ������ ���� ���� �� firstEdge�� ������ ���μ� �߰���
		
		while (firstVertex->link)
		{
			firstVertex = firstVertex->link; //ù ��°�� �Է¹��� ������ ������ �δ� ������ ���� ���� �� ������ ��带 ���� ������ �ݺ��� ����
			
			if (firstVertex->key == secondKey) //�����Ϸ��� ������ ������ �̹� �׷��� ���� ������ ��
			{
				//������ �׷������� (u, v)�� �׷����� �����ϸ� �ش� ������ (v, u)�� �����ϹǷ� ���� ����Ʈ���� v�� ������ �ϴ� �����鿡 ���Ͽ� �߰������� �˻��� �ʿ䰡 ����.
				printf("\nThe edge between [%d] and [%d] already exists.\n", firstKey, secondKey); //���� �޼��� ���
				free(firstEdge); //firstEdge �޸� ����
				return; //�Լ� ����
			}
		}
		firstVertex->link = firstEdge; //ù ��°�� �Է¹��� ������ ������ �ϰ� �� ��°�� �Է¹��� ������ �Ӹ��� �δ� ���� �߰�

		secondEdge = (Node*)malloc(sizeof(Node)); //�� ��°�� �Է¹��� ������ ������, ù ��°�� �Ӹ��� �ϴ� ���� secondEdge�� �޸� �Ҵ�
		secondEdge->key = firstKey; //secondEdge�� ù ��°�� �Է¹��� ������ ���� ���
		secondEdge->link = NULL; //������ ����(����ڿ��� �� ��°�� �Է¹��� ����)�� ������ ������ ���� ���� �� secondEdge�� ������ ���μ� �߰���
		while (secondVertex->link)
		{
			secondVertex = secondVertex->link; //�� ��°�� �Է¹��� ������ ������ �δ� ������ ���� ���� �� ������ ��带 ���� ������ �ݺ��� ����
		}
		secondVertex->link = secondEdge; //�� ��°�� �Է¹��� ������ ������ �ϰ� ù ��°�� �Է¹��� ������ �Ӹ��� �δ� ���� �߰�
		return; //���� �߰� �Ϸ� �� �Լ� ����
	}
	if (firstVertex == NULL) //ù ��°�� �Է¹��� ������ �������� ���� ��
		printf("The vertex with the value [%d] does not exist.\n", firstKey); //���� �޼��� ���
	if (secondVertex==NULL) //�� ��°�� �Է¹��� ������ �������� ���� ��
		printf("The vertex with the value [%d] does not exist.\n", secondKey); //���� �޼��� ���
	printf("\n");
}

void depthFirstSearch()
{

}

void breathFirstSearch()
{

}

void printGraph(Node** adjLists) //���� ����Ʈ ���·� �׷��� ���
{
	Node* head = NULL; //�Ӹ��� �����ϴ� head

	for (int i = 0; (i < MAX_VERTEX) && adjLists[i]; i++) //���� ����Ʈ�� �࿡ ���ؼ� ����
	{
		printf("Tail: %d\n", adjLists[i]->key); //������ ������ �� ���
		printf("List of Edges: ");

		//�ش� ������ �μ��ϴ� ������ ���� �� �Ʒ��� �ݺ��� ����
		for (head = adjLists[i]; head->link && head; head = head->link) //head�� ������ �����ϴ� ��尡 ����Ű�� ������ �����Ͽ� NULL�� �� ������ �ݺ��� ����
		{
			printf("(%d, %d) ", adjLists[i]->key, head->link->key); //(����, �Ӹ�) ���				
		}
		
		if (!(adjLists[i]->link)) //�ش� ������ ���� ������ �������� ���� ��
		{
			printf("None"); //���� �޼��� ���
		}
		printf("\n\n");
	}
}
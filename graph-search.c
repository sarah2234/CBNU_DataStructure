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
void depthFirstSearch(const Node** adjLists); //���� �켱 Ž������ ������ �湮�ϴ� �Լ�
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
			depthFirstSearch(adjLists);
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
	if (adjLists[9]) //�׷����� 10���� ������ ���� ��
	{
		printf("The graph is full!\n\n"); //���� �׷����� ���̻� ������ �߰��� �� ���� �� ���� �޼��� ���
		return; //�Լ� ����
	}

	for (int i = 0; i < MAX_VERTEX; i++)
	{
		//case 1: �׷��� �� �����ϴ� ��� �����麸�� ���� ū ������ ������ ��
		if (adjLists[i] == NULL) //adjLists �迭���� �� ������ �߰����� ��
		{
			adjLists[i] = (Node*)malloc(sizeof(Node)); //�׷����� ���� ���� ������ ���Ͽ� �޸� �Ҵ�
			adjLists[i]->key = key;
			adjLists[i]->link = NULL; //�ش� ���� ���� ���� ���� �� �Լ� ����
			return;
		}

		//case 2: �׷��� �� �������� ũ�� ���� �°� ���� ����Ʈ�� �߰��� ������ ������ ��
		if (adjLists[i]->key > key) //�����Ϸ��� ������ �׷����� �����ϴ� ������ ���� �� Ŭ ��
		{
			for (int j = MAX_VERTEX - 1; j != i; j--)
			{
				adjLists[j] = adjLists[j - 1]; //i ��°�� ���ο� ��带 ������ �� �ֵ��� adjLists�� ��带 ���� ���� �ű�� �۾� �ݺ�
			}
			adjLists[i] = (Node*)malloc(sizeof(Node)); //�׷����� ���� ���� ������ ���Ͽ� �޸� �Ҵ�
			adjLists[i]->key = key;
			adjLists[i]->link = NULL; //�ش� ���� ���� ���� ���� �� �Լ� ����
			return;
		}

		//case 3: �׷��� �� �ش� ���� ���� ������ �̹� ������ ��
		if (adjLists[i]->key == key)
		{
			printf("The vertex with the key [%d] already exists.\n\n", key); //���� �޼��� ��� �� �Լ� ����
			return; 
		}
	}
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

	//case 1: �Է¹��� �� ���� ���� ���� ������ �׷��� ���� ������ ��
	if (firstVertex != NULL && secondVertex != NULL)
	{
		//(firstVertex, secondVertex) �߰� �۾�
		firstEdge = (Node*)malloc(sizeof(Node)); //ù ��°�� �Է¹��� ������ ������, �� ��°�� �Ӹ��� �ϴ� ���� firstEdge�� �޸� �Ҵ�
		firstEdge->key = secondKey; //firstEdge�� �� ��°�� �Է¹��� ������ ���� ��� (ù ��°�� �߰��� ������ �Ӹ� ���)
		firstEdge->link = NULL; //������ ����(����ڿ��� ù ��°�� �Է¹��� ����)�� ������ ������ ���� ���� �� firstEdge�� ������ ���μ� �߰���
		
		while (firstVertex->link)
		{
			//A. �����Ϸ��� ������ �Ӹ� �������� ������ �����ϴ� �Ӹ� ������ ���� �� Ŭ ��
			if (firstVertex->link->key > secondKey)
			{
				firstEdge->link = firstVertex->link;
				firstVertex->link = firstEdge; //������ ���� ����Ʈ �߰��� ù ��° ���� ����
				break; //�ݺ��� ���� (ù ��° ���� ���� �Ϸ�, �� ��° ���� �����ؾ���)
			}
			
			//B. �����Ϸ��� ������ ������ �̹� �׷��� ���� ������ ��
			if (firstVertex->link->key == secondKey)
			{
				//������ �׷������� (u, v)�� �׷����� �����ϸ� �ش� ������ (v, u)�� �����ϹǷ� ���� ����Ʈ���� v�� ������ �ϴ� �����鿡 ���Ͽ� �߰������� �˻��� �ʿ䰡 ����.
				printf("\nThe edge between [%d] and [%d] already exists.\n", firstKey, secondKey); //���� �޼��� ���
				free(firstEdge); //firstEdge �޸� ����
				return; //�Լ� ����
			}
			
			firstVertex = firstVertex->link; //������ ������ �δ� ������ ���� ����Ʈ�� ���� �ٴٸ� ������ �ݺ��� ����
			
		}

		//C. �߰��Ϸ��� ������ �Ӹ��� ������ �Ӹ� ������ ������ Ŀ �������� ������ ��
		firstVertex->link = firstEdge; //ù ��°�� �Է¹��� ������ ������ �ϰ� �� ��°�� �Է¹��� ������ �Ӹ��� �δ� ���� �߰�
		//(firstVertex, secondVertex) �߰� �Ϸ�

		//(secondVertex, firstVertex) �߰� �۾�
		secondEdge = (Node*)malloc(sizeof(Node)); //�� ��°�� �Է¹��� ������ ������, ù ��°�� �Ӹ��� �ϴ� ���� secondEdge�� �޸� �Ҵ�
		secondEdge->key = firstKey; //secondEdge�� ù ��°�� �Է¹��� ������ ���� ��� (�� ��°�� �߰��� ������ �Ӹ� ���)
		secondEdge->link = NULL; //������ ����(����ڿ��� �� ��°�� �Է¹��� ����)�� ������ ������ ���� ���� �� secondEdge�� ������ ���μ� �߰���
		
		while (secondVertex->link)
		{
			//A. �����Ϸ��� ������ �Ӹ� �������� ������ �����ϴ� �Ӹ� ������ ���� �� Ŭ ��
			if (secondVertex->link->key > firstKey)
			{
				secondEdge->link = secondVertex->link; 
				secondVertex->link = secondEdge; //������ ���� ����Ʈ �߰��� �� ��° ���� ����
				return; //�Լ� ���� (��� ���� ���� �Ϸ�)
			}

			secondVertex = secondVertex->link; //������ ������ �δ� ������ ���� ����Ʈ�� ���� �ٴٸ� ������ �ݺ��� ����
		}

		//B. �߰��Ϸ��� ������ �Ӹ��� ������ �Ӹ� ������ ������ Ŀ �������� ������ ��
		secondVertex->link = secondEdge; //�� ��°�� �Է¹��� ������ ������ �ϰ� ù ��°�� �Է¹��� ������ �Ӹ��� �δ� ���� �߰�
		//(secondVertex, firstVertex) �߰� �Ϸ�

		return; //���� �߰� �Ϸ� �� �Լ� ����
	}

	//case 2: ù ��°�� �Է¹��� ������ �׷������� �������� ���� ��
	if (firstVertex == NULL)
		printf("The vertex with the value [%d] does not exist.\n", firstKey); //���� �޼��� ���

	//case 3: �� ��°�� �Է¹��� ������ �׷������� �������� ���� ��
	if (secondVertex==NULL)
		printf("The vertex with the value [%d] does not exist.\n", secondKey); //���� �޼��� ���
	printf("\n");
}

void depthFirstSearch(const Node** adjLists)
{
	Node* current = *adjLists;

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
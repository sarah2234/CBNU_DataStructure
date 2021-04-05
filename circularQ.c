/*
 * circularQ.c
 *
 *  Data Structures, Homework #5
 *  Department of Computer Science at Chungbuk National University
 */

#include <stdio.h>
#include <stdlib.h>

#define MAX_QUEUE_SIZE 4 //MAX_QUEUE_SIZE라는 이름으로 4의 매크로 정의

typedef char element; //char를 element로 재정의
typedef struct {
	element queue[MAX_QUEUE_SIZE]; //길이가 MAX_QUEUE_SIZE만큼인 element형(char형) 배열 선언
	int front, rear; //int형 변수 front와 rear 선언
}QueueType; //해당 구조체를 QueueType로 재정의


QueueType *createQueue(); //원형 큐를 생성하는 함수 선언
int freeQueue(QueueType *cQ); //원형 큐에 할당된 메모리를 해제하는 함수 선언
int isEmpty(QueueType *cQ); //원형 큐가 비어있는지 확인하는 함수 선언
int isFull(QueueType *cQ); //원형 큐가 찼는지 확인하는 함수 선언
void enQueue(QueueType *cQ, element item); //원형 큐에 값을 저장하는 함수 선언
void deQueue(QueueType *cQ, element* item); //원형 큐에 저장된 값을 삭제하는 함수 선언
void printQ(QueueType *cQ); //원형 큐에 저장된 값을 출력하는 함수 선언
void debugQ(QueueType *cQ); //원형 큐를 디버그하는 함수 선언
element getElement(); //문자를 입력받는 함수 선언

int main(void)
{
	QueueType *cQ = createQueue(); //QueueType형 포인터 cQ를 선언하고 createQueue함수를 통해 원형 큐 생성
	element data; //원형 큐에 입력받을 데이터를 저장할 element형(char형) 변수 data 선언
	char command; //명령어를 입력받을 char형 변수 command 선언

	printf("----- [이승현] [2020039075] -----\n");

	do{
		printf("\n-----------------------------------------------------\n");
		printf("                     Circular Q                   \n");
		printf("------------------------------------------------------\n");
		printf(" Insert=i,  Delete=d,   PrintQ=p,   Debug=b,   Quit=q \n");
		printf("------------------------------------------------------\n");

		printf("Command = ");
		scanf(" %c", &command); //문자를 입력받아 command에 저장

		switch(command) {
		case 'i': case 'I': //command가 'i'나 'I'일 때
			data = getElement(); //getElement 함수에서 리턴받은 값을 data에 저장
			enQueue(cQ, data); //cQ가 가진 주소값과 data의 값을 인자로 enQueue 함수 호출하여 원형 큐의 rear에 데이터 삽입
			break;
		case 'd': case 'D': //command가 'd'나 'D'일 때
			deQueue(cQ, &data); //cQ가 가진 주소값과 data의 주소값을 인자로 deQueue 함수 호출하여 원형 큐의 front에서 데이터 삭제
			break;
		case 'p': case 'P': //command가 'p'나 'P'일 때
			printQ(cQ); //cQ가 가진 주소값을 인자로 printQ 함수 호출하여 cQ에 저장된 데이터 출력
			break;
		case 'b': case 'B': //command가 'b'나 'B'일 때
			debugQ(cQ); //cQ가 가진 주소값을 인자로 debugQ 함수 호출하여 cQ의 세부사항 출력
			break;
		case 'q': case 'Q': //command가 'q'나 'Q'일 때
   	        freeQueue(cQ); //cQ가 가진 주소값을 인자로 freeQueue 함수 호출하여 cQ의 메모리 해제
			break;
		default: //command가 상단 이외의 문자일 때
			printf("\n       >>>>>   Concentration!!   <<<<<     \n"); //오류 메세지 출력
			break;
		}

	}while(command != 'q' && command != 'Q'); //블록 내의 코드를 최소 한 번 실행한 후 command가 'q' 또는 'Q'를 입력받으면 반복문 종료


	return 1; //1을 리턴하고 main 함수 종료
}

QueueType *createQueue() 
{
	QueueType *cQ; //QueueType형 포인터 cQ를 선언
	cQ = (QueueType *)malloc(sizeof(QueueType)); //cQ에 QueueType만큼 메모리 할당
	cQ->front = 0; //cQ의 front 변수에 0을 저장. 즉, cQ에서 front의 위치를 0으로 설정
	cQ->rear = 0; //cQ의 rear 변수에 0을 저장. 즉, cQ에서 rear의 위치를 0으로 설정
	for(int i=0;i<MAX_QUEUE_SIZE;i++)
	{
		cQ->queue[i]='\0'; //cQ의 모든 queue 값을 초기화 (프로그램을 처음 실행할 때 일부 queue가 특수문자를 출력하는 것을 방지하고자 추가하였습니다.)
	}
	return cQ; //cQ를 리턴
}

int freeQueue(QueueType *cQ) 
{
    if(cQ == NULL) return 1; //cQ가 NULL을 가리킬 때, 즉 cQ가 이미 메모리 해제되어있으면 1을 리턴
    free(cQ); //cQ에 할당되었던 메모리를 해제
    return 1; //1을 리턴
}

element getElement()
{
	element item; //원형 큐에 삽입할 데이터를 저장할 element형(char형) 변수 item을 선언
	printf("Input element = "); 
	scanf(" %c", &item); //입력받은 문자를 item에 저장
	return item; //item을 리턴
}


/* complete the function */
int isEmpty(QueueType *cQ)
{
	if(cQ->front==cQ->rear) //cQ의 front와 cQ의 rear가 값이 같을 때
	{
		return 1; //1을 리턴
	}
    return 0; //if의 조건을 충족시키지 않는다면 0을 리턴
}

/* complete the function */
int isFull(QueueType *cQ) 
{
	if(cQ->front==(cQ->rear+1)%MAX_QUEUE_SIZE) //cQ의 front와 cQ의 rear가 값이 같을 때
	{
		return 1; //1을 리턴
	}
    return 0; //if의 조건을 충족시키지 않는다면 0을 리턴
}


/* complete the function */
void enQueue(QueueType *cQ, element item) 
{
	if(isFull(cQ)) //cQ가 가진 주소값을 인자로 isFull 함수를 호출하여 원형 큐가 찼는지 확인
	{
		printf("Circular Queue is full!\n\n");
		return; //원형 큐가 찼다면 상단의 문자 출력 후 함수 종료
	}
	cQ->rear=(cQ->rear+1)%MAX_QUEUE_SIZE; //원형 큐 cQ에서 rear를 1 증가시킨 값을 rear에 저장 (0<=rear<MAX_QUEUE_SIZE)
	cQ->queue[cQ->rear]=item; //cQ의 queue 배열에서 rear번째에 위치한 곳에 item의 값을 저장
}

/* complete the function */
void deQueue(QueueType *cQ, element *item) 
{
	if(isEmpty(cQ)) //cQ가 가진 주소값을 인자로 isEmpty 함수를 호출하여 원형 큐가 비었는지 확인
	{
		printf("Circular Queue is empty!\n\n");
		return; //원형 큐가 비었다면 상단의 문자 출력 후 함수 종료
	}
    cQ->front=(cQ->front+1)%MAX_QUEUE_SIZE; //원형 큐 cQ에서 front를 1 증가시킨 값을 rear에 저장 (0<=front<MAX_QUEUE_SIZE)
	cQ->queue[cQ->front]='\0'; //cQ의 queue 배열에서 front번째에 위치한 곳에 데이터 삭제
}


void printQ(QueueType *cQ) 
{
	int i, first, last; //int형 변수 i, first, last 선언

	first = (cQ->front + 1)%MAX_QUEUE_SIZE; //원형 큐 cQ에서 front를 1 증가시킨 값을 first에 저장 (0<=first<MAX_QUEUE_SIZE)
	last = (cQ->rear + 1)%MAX_QUEUE_SIZE; //원형 큐 cQ에서 rear를 1 증가시킨 값을 last에 저장 (0<=last<MAX_QUEUE_SIZE)

	printf("Circular Queue : [");

	i = first; //i에 first 값 저장
	while(i != last){ 
		printf("%3c", cQ->queue[i]); //i의 값이 first 값부터 시작하여 last 값이 되기 전까지 cQ의 queue[i]에 저장된 값을 차례로 출력
		i = (i+1)%MAX_QUEUE_SIZE; //원형 큐에서 i의 값이 1씩 증가 (0<=i<MAX_QUEUE_SIZE)

	} //i가 last와 같을 때 반복문 종료
	printf(" ]\n");
}


void debugQ(QueueType *cQ) 
{

	printf("\n---DEBUG\n");
	for(int i = 0; i < MAX_QUEUE_SIZE; i++) //i가 0부터 MAX_QUEUE_SIZE가 되기 전까지 1씩 증가하면서 반복문 수행
	{
		if(i == cQ->front) {
			printf("  [%d] = front\n", i); //i를 통해 cQ 내 front의 위치를 발견할 경우 해당 i의 값(=front의 위치) 출력
			continue; //front의 위치 확인 후 하단의 코드 실행 건너뛰고 반복문 이어서 실행
		}
		printf("  [%d] = %c\n", i, cQ->queue[i]); //cQ의 queue 배열에서 i번째에 저장된 값 출력

	}
	printf("front = %d, rear = %d\n", cQ->front, cQ->rear); //cQ 내 front와 rear의 위치 출력
}


/*
 * hw12-sorting-hashing.c
 *
 *  Created on: May 22, 2021
 *
 *  Homework 12: Sorting & Hashing
 *  Department of Computer Science at Chungbuk National University
 *
 */

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define MAX_ARRAY_SIZE			13	/* prime number */
//홈 버킷이 어느 한 쪽으로 편중되지 않게 소수를 선택한다.
#define MAX_HASH_TABLE_SIZE 	MAX_ARRAY_SIZE 

/* 필요에 따라 함수 추가 가능 */
int initialize(int **a); //배열을 초기화하는 함수
int freeArray(int *a); //배열에 할당된 메모리를 해제하는 함수
void printArray(int *a); //배열 내 데이터를 출력하는 함수

int selectionSort(int *a); //선택 정렬 알고리즘을 통해 배열 내 데이터의 값을 오름차순으로 정렬하는 함수
int insertionSort(int *a); //삽입 정렬 알고리즘을 통해 배열 내 데이터의 값을 오름차순으로 정렬하는 함수
int bubbleSort(int *a); //버블 정렬 알고리즘을 통해 배열 내 데이터의 값을 오름차순으로 정렬하는 함수
int shellSort(int *a);
/* recursive function으로 구현 */
int quickSort(int *a, int n);


/* hash code generator, key % MAX_HASH_TABLE_SIZE */
int hashCode(int key);

/* array a에대 한 hash table을 만든다. */
int hashing(int *a, int **ht);

/* hash table에서 key를 찾아 hash table의 index return */
int search(int *ht, int key);


int main()
{
	char command;
	int *array = NULL; //정렬을 할 배열
	int *hashtable = NULL; //해싱에 쓰이는 해시 테이블
	int key = -1;
	int index = -1;

	srand(time(NULL));

	printf("[----- [이승현] [2020039075] -----]\n");

	do{
		printf("----------------------------------------------------------------\n");
		printf("                        Sorting & Hashing                       \n");
		printf("----------------------------------------------------------------\n");
		printf(" Initialize       = z           Quit             = q\n");
		printf(" Selection Sort   = s           Insertion Sort   = i\n");
		printf(" Bubble Sort      = b           Shell Sort       = l\n");
		printf(" Quick Sort       = k           Print Array      = p\n");
		printf(" Hashing          = h           Search(for Hash) = e\n");
		printf("----------------------------------------------------------------\n");

		printf("Command = ");
		scanf(" %c", &command); //명령어 입력

		switch(command) {
		case 'z': case 'Z':
			initialize(&array); //'z'나 'Z'를 입력받으면 배열 초기화(메모리 할당)
			break;
		case 'q': case 'Q':
			freeArray(array); //'q'나 'Q'를 입력받으면 배열의 메모리 해제
			break;
		case 's': case 'S':
			selectionSort(array); //'s'나 'S'를 입력받으면 선택 정렬로 배열 정렬
			break;
		case 'i': case 'I':
			insertionSort(array); //'i'나 'I'를 입력받으면 삽입 정렬로 배열 정렬
			break;
		case 'b': case 'B':
			bubbleSort(array); //'b'나 'B'를 입력받으면 버블 정렬로 배열 정렬
			break;
		case 'l': case 'L':
			shellSort(array); //'l'나 'L'를 입력받으면 셸 정렬로 배열 정렬
			break;
		case 'k': case 'K': //'k'나 'K'를 입력받으면 퀵 정렬로 배열 정렬
			printf("Quick Sort: \n");
			printf("----------------------------------------------------------------\n");
			printArray(array); //정렬 이전의 배열 출력
			quickSort(array, MAX_ARRAY_SIZE);
			printf("----------------------------------------------------------------\n");
			printArray(array); //퀵 정렬 후 배열 출력

			break;

		case 'h': case 'H':
			printf("Hashing: \n");
			printf("----------------------------------------------------------------\n");
			printArray(array); //해싱 이전의 배열 출력
			hashing(array, &hashtable); //'h'나 'H'를 입력받으면 해싱으로 배열 내부 변경
			printArray(hashtable); //해시 테이블 출력
			break;

		case 'e': case 'E':
			printf("Your Key = ");
			scanf("%d", &key);
			printArray(hashtable);
			index = search(hashtable, key); //'e'나 'E'를 입력받으면 해시 테이블에서 key의 주소 탐색
			printf("key = %d, index = %d,  hashtable[%d] = %d\n", key, index, index, hashtable[index]);
			break;

		case 'p': case 'P':
			printArray(array);
			break;
		default:
			printf("\n       >>>>>   Concentration!!   <<<<<     \n");
			break;
		}

	}while(command != 'q' && command != 'Q');

	return 1;
}

int initialize(int** a)
{
	int *temp = NULL;

	/* array가 NULL인 경우 메모리 할당 */
	if(*a == NULL) {
		temp = (int*)malloc(sizeof(int) * MAX_ARRAY_SIZE);
		*a = temp;  /* 할당된 메모리의 주소를 복사 --> main에서 배열을 control 할수 있도록 함*/
	} else
		temp = *a;

	/* 랜덤값을 배열의 값으로 저장 */
	for(int i = 0; i < MAX_ARRAY_SIZE; i++)
		temp[i] = rand() % MAX_ARRAY_SIZE;

	return 0;
}

int freeArray(int *a)
{
	if(a != NULL)
		free(a); //배열의 값에 할당된 메모리 해제
	return 0;
}

void printArray(int *a)
{
	if (a == NULL) {
		printf("nothing to print.\n"); //배열에 데이터가 존재하지 않을 경우 해당 메세지 출력
		return;
	}
	for(int i = 0; i < MAX_ARRAY_SIZE; i++)
		printf("a[%02d] ", i); //배열의 인덱스 출력
	printf("\n");
	for(int i = 0; i < MAX_ARRAY_SIZE; i++)
		printf("%5d ", a[i]); //배열 내 존재하는 데이터 출력
	printf("\n"); 
}


int selectionSort(int *a) //해당 회차에서 가장 작은 데이터 값이 제일 왼쪽에 배치되도록 두 데이터의 자리를 변경하여 정렬
//선택 정렬의 시간복잡도는 최악의 경우 O(n^2)
{
	int min; //배열 내 가장 작은 수를 저장할 min
	int minindex; //min의 인덱스 값을 저장할 minindex
	int i, j;

	printf("Selection Sort: \n");
	printf("----------------------------------------------------------------\n");

	printArray(a); //정렬 전 배열 출력

	for (i = 0; i < MAX_ARRAY_SIZE; i++)
	{
		minindex = i; //현재 비교하려는 숫자들 중 제일 왼쪽에 위치한 숫자가 최소라고 가정하고 minindex에 i 저장(=인덱스의 값이 제일 적음)
		min = a[i]; //minindex가 가리키는 인덱스의 데이터가 최소라고 가정하고 min에 해당 데이터 값 저장
		for(j = i+1; j < MAX_ARRAY_SIZE; j++) //min으로 설정한 값의 그다음 값부터 비교 시작
		{
			if (min > a[j])
			{
				min = a[j]; //min의 값보다 더 작은 값이 존재할 때 해당 값을 min에 저장
				minindex = j; //min의 인덱스를 minindex에 저장
			}
		}
		a[minindex] = a[i]; 
		a[i] = min; //비교하였던 값들 중 가장 작았던 값과, 현재 비교하였던 값들 중 맨 왼쪽에 있었던 값의 위치를 변경
		//자리를 바꾼 후 그다음 데이터를 시작으로 삼아 배열 내 데이터들의 값 비교하여 배열의 끝에 도달할 때까지 반복
	}

	printf("----------------------------------------------------------------\n");
	printArray(a); //정렬 후 배열 출력
	return 0;
}

int insertionSort(int *a) //배열의 앞에서부터 차례대로 정렬이 되어있는 부분과 비교하여 알맞은 위치에 데이터를 삽입하여 정렬
//삽입 정렬의 시간복잡도는 최악의 경우 O(n^2)
{
	int i, j, t;

	printf("Insertion Sort: \n");
	printf("----------------------------------------------------------------\n");

	printArray(a); //정렬 전 배열 출력

	for(i = 1; i < MAX_ARRAY_SIZE; i++)
	{
		t = a[i]; //두 번째 데이터부터 시작하여 오른쪽에서 왼쪽으로 차례대로 데이터를 비교하기 위해 비교하려는 데이터들 중 제일 오른쪽 데이터를 t에 저장(=인덱스의 값이 제일 큼)
		j = i; //비교하려는 데이터들 중 제일 오른쪽에 위치한 데이터의 인덱스 저장
		while (a[j-1] > t && j > 0) //배열의 첫 부분에 도달하거나 비교하는 데이터의 값이 t의 값보다 작을 때까지 반복
		{
			a[j] = a[j-1]; //t와 왼쪽 데이터를 비교하였을 때 왼쪽 데이터 값이 t보다 더 크면 왼족 데이터를 오른쪽으로 이동
			j--; //왼쪽 데이터와 비교
		}
		a[j] = t; //t의 값이 현재 위치에서의 왼쪽 데이터 값보다 크면 반복문 종료 후 해당 왼쪽 데이터의 오른쪽에 t를 삽입
		//혹은 왼쪽 끝까지 도달하였을 때 해당 자리에 데이터 삽입
	}

	printf("----------------------------------------------------------------\n");
	printArray(a); //정렬 후 배열 출력

	return 0;
}

int bubbleSort(int *a) //서로 인접한 두 데이터를 비교하여 정렬
//버블 정렬의 시간복잡도는 최악의 경우 O(n^2)
{
	int i, j, t;

	printf("Bubble Sort: \n");
	printf("----------------------------------------------------------------\n");

	printArray(a); //정렬 전 배열 출력

	for(i = 0; i < MAX_ARRAY_SIZE; i++)
	{
		for (j = 0; j < MAX_ARRAY_SIZE; j++)
		{
			if (a[j-1] > a[j]) //인접한 두 데이터 중 왼쪽 데이터의 값이 오른쪽 데이터보다 클 때
			{
				t = a[j-1];
				a[j-1] = a[j]; 
				a[j] = t; //두 데이터의 위치를 바꾼다.
			}
		}
	}

	printf("----------------------------------------------------------------\n");
	printArray(a); //정렬 후 배열 출력

	return 0;
}

int shellSort(int *a) //h만큼의 간격으로 떨어진 레코드를 삽입 정렬
//셸 정렬의 평균적인 시간 복잡도는 O(n^1.25)
{
	int i, j, k, h, v;

	printf("Shell Sort: \n");
	printf("----------------------------------------------------------------\n");

	printArray(a); //정렬 전 배열 출력

	for (h = MAX_ARRAY_SIZE/2; h > 0; h /= 2) //한 단계가 수행될 때마다 h가 1/2배로 감소하여 h /= 2 한 후 h가 0이 될 때까지 반복
	{
		for (i = 0; i < h; i++)
		{
			for(j = i + h; j < MAX_ARRAY_SIZE; j += h)
			{
				v = a[j]; //비교하려는 데이터들 중 가장 오른쪽에 위치한 데이터를 v에 저장
				k = j; //v의 인덱스 저장
				while (k > h-1 && a[k-h] > v) //k가 h보다 크거나 같고, 배열에 있는 데이터의 값이 삽입할 값보다 더 클 때 반복
				{
					a[k] = a[k-h]; //레코드를 h만큼 오른쪽으로 이동
					k -= h; //현재 k에서 h만큼 뺌
				}
				a[k] = v; //v의 값이 방금 비교한 데이터 값보다 크면 반복문 종료 후 해당 데이터의 오른쪽에 삽입
				//혹은 왼쪽 끝까지 도달하였을 때 해당 자리에 데이터 삽입
			}
		}
	}
	printf("----------------------------------------------------------------\n");
	printArray(a); //정렬 후 배열 출력

	return 0;
}

int quickSort(int *a, int n) //피벗 레코드를 선택하여 피벗의 왼쪽에는 피벗의 키보다 작거나 같고 피벗의 오른쪽에는 피벗의 키보다 크거나 같은 레코드들을 정렬
//퀵 정렬의 시간 복잡도는 최악의 경우 O(n^2), 평균 연산 시간은 O(nlogn)
{
	int v, t;
	int i, j;

	if (n > 1)
	{
		v = a[n-1]; //배열의 마지막 레코드를 피벗으로 설정
		i = -1; //i는 배열의 왼쪽부터 가리킴
		j = n - 1; //j는 배열의 오른쪽부터 가리킴

		while(1)
		{
			while(a[++i] < v); //피벗보다 크거나 같은 값이 나올 때까지 i 증가(왼쪽>오른쪽)
			while(a[--j] > v); //피벗보다 작거나 같은 값이 나올 때까지 j 감소(오른쪽>왼쪽)

			if (i >= j) break; //i와 j가 교차하면 while문 종료
			t = a[i];
			a[i] = a[j];
			a[j] = t; //i < j 일 때 오른쪽과 왼쪽의 레코드의 위치를 서로 바꿈
		}
		t = a[i];
		a[i] = a[n-1];
		a[n-1] = t; //i와 j가 교차하면 피벗과 a[i]의 레코드의 위치를 서로 바꿈

		quickSort(a, i); //피벗의 위치가 i로 바뀐 후 피벗의 왼쪽에 위치한 배열은 a[i-1]을 피벗으로 하는 퀵 정렬을 시행
		quickSort(a+i+1, n-i-1); //피벗의 오른쪽에 위치한 배열은 a[n-i-2]을 피벗으로 하는 퀵 정렬을 시행
	}


	return 0;
}

int hashCode(int key) {
   return key % MAX_HASH_TABLE_SIZE; //해시 테이블에서의 해당 key에 맞는 주소 리턴
}

int hashing(int *a, int **ht) //해시 함수를 통해 데이터를 해시 테이블 내 적절한 위치에 배치시켜 데이터를 빠르게 찾는 방법
{
	int *hashtable = NULL;

	/* hash table이 NULL인 경우 메모리 할당 */
	if(*ht == NULL) {
		hashtable = (int*)malloc(sizeof(int) * MAX_ARRAY_SIZE);
		*ht = hashtable;  /* 할당된 메모리의 주소를 복사 --> main에서 배열을 control 할수 있도록 함*/
	} else {
		hashtable = *ht;	/* hash table이 NULL이 아닌경우, table 재활용, reset to -1 */
	}

	for(int i = 0; i < MAX_HASH_TABLE_SIZE; i++)
		hashtable[i] = -1;

	/*
	for(int i = 0; i < MAX_HASH_TABLE_SIZE; i++)
		printf("hashtable[%d] = %d\n", i, hashtable[i]);
	*/

	int key = -1;
	int hashcode = -1;
	int index = -1;
	for (int i = 0; i < MAX_ARRAY_SIZE; i++)
	{
		key = a[i];
		hashcode = hashCode(key); //데이터의 key 값을 해시 함수를 통해 해시 테이블 주소로 변환
		/*
		printf("key = %d, hashcode = %d, hashtable[%d]=%d\n", key, hashcode, hashcode, hashtable[hashcode]);
		*/
		if (hashtable[hashcode] == -1) //해시 테이블에서 해당 주소가 비어있는 공간일 때 
		{
			hashtable[hashcode] = key; //해당 주소에 key 저장
		} else 	{ //해시 테이블에서 해당 주소에 데이터가 이미 들어있을 떄

			index = hashcode;

			while(hashtable[index] != -1)  //해시 테이블에서 빈 공간을 찾을 때까지 반복
			{
				index = (++index) % MAX_HASH_TABLE_SIZE; //해시 테이블 내에서 index를 1씩 증가하며 빈 공간 탐색
				/*
				printf("index = %d\n", index);
				*/
			}
			hashtable[index] = key; //해시 테이블 내 찾은 빈 공간에 key 저장
		}
	}

	return 0;
}

int search(int *ht, int key)
{
	int index = hashCode(key); //해시 함수를 통해 해당 key에 대한 해시 테이블의 주소를 얻음

    //case 1: 해시 함수의 key에 대한 연산 결과값(key의 예상 주소) == key의 실제 주소
	if(ht[index] == key) //해시 함수의 key에 대한 연산 결과값이 key의 주소와 동일할 때
		return index; //key의 주소 리턴

    //case 2: 해시 함수의 key에 대한 연산 결과값(key의 예상 주소) != key의 실제 주소
	while(ht[++index] != key) //해시 함수의 key에 대한 연산 결과괎과 key의 주소가 동일하지 않아 index를 1씩 증가시키며 key 탐색
	{
		index = index % MAX_HASH_TABLE_SIZE; //해시 테이블의 주소에 맞게 index 변환
	}
	return index; //해시 테이블에서 key를 찾았을 때 key의 주소 리턴
}




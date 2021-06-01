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
//Ȩ ��Ŷ�� ��� �� ������ ���ߵ��� �ʰ� �Ҽ��� �����Ѵ�.
#define MAX_HASH_TABLE_SIZE 	MAX_ARRAY_SIZE 

/* �ʿ信 ���� �Լ� �߰� ���� */
int initialize(int **a); //�迭�� �ʱ�ȭ�ϴ� �Լ�
int freeArray(int *a); //�迭�� �Ҵ�� �޸𸮸� �����ϴ� �Լ�
void printArray(int *a); //�迭 �� �����͸� ����ϴ� �Լ�

int selectionSort(int *a); //���� ���� �˰����� ���� �迭 �� �������� ���� ������������ �����ϴ� �Լ�
int insertionSort(int *a); //���� ���� �˰����� ���� �迭 �� �������� ���� ������������ �����ϴ� �Լ�
int bubbleSort(int *a); //���� ���� �˰����� ���� �迭 �� �������� ���� ������������ �����ϴ� �Լ�
int shellSort(int *a);
/* recursive function���� ���� */
int quickSort(int *a, int n);


/* hash code generator, key % MAX_HASH_TABLE_SIZE */
int hashCode(int key);

/* array a���� �� hash table�� �����. */
int hashing(int *a, int **ht);

/* hash table���� key�� ã�� hash table�� index return */
int search(int *ht, int key);


int main()
{
	char command;
	int *array = NULL; //������ �� �迭
	int *hashtable = NULL; //�ؽ̿� ���̴� �ؽ� ���̺�
	int key = -1;
	int index = -1;

	srand(time(NULL));

	printf("[----- [�̽���] [2020039075] -----]\n");

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
		scanf(" %c", &command); //��ɾ� �Է�

		switch(command) {
		case 'z': case 'Z':
			initialize(&array); //'z'�� 'Z'�� �Է¹����� �迭 �ʱ�ȭ(�޸� �Ҵ�)
			break;
		case 'q': case 'Q':
			freeArray(array); //'q'�� 'Q'�� �Է¹����� �迭�� �޸� ����
			break;
		case 's': case 'S':
			selectionSort(array); //'s'�� 'S'�� �Է¹����� ���� ���ķ� �迭 ����
			break;
		case 'i': case 'I':
			insertionSort(array); //'i'�� 'I'�� �Է¹����� ���� ���ķ� �迭 ����
			break;
		case 'b': case 'B':
			bubbleSort(array); //'b'�� 'B'�� �Է¹����� ���� ���ķ� �迭 ����
			break;
		case 'l': case 'L':
			shellSort(array); //'l'�� 'L'�� �Է¹����� �� ���ķ� �迭 ����
			break;
		case 'k': case 'K': //'k'�� 'K'�� �Է¹����� �� ���ķ� �迭 ����
			printf("Quick Sort: \n");
			printf("----------------------------------------------------------------\n");
			printArray(array); //���� ������ �迭 ���
			quickSort(array, MAX_ARRAY_SIZE);
			printf("----------------------------------------------------------------\n");
			printArray(array); //�� ���� �� �迭 ���

			break;

		case 'h': case 'H':
			printf("Hashing: \n");
			printf("----------------------------------------------------------------\n");
			printArray(array); //�ؽ� ������ �迭 ���
			hashing(array, &hashtable); //'h'�� 'H'�� �Է¹����� �ؽ����� �迭 ���� ����
			printArray(hashtable); //�ؽ� ���̺� ���
			break;

		case 'e': case 'E':
			printf("Your Key = ");
			scanf("%d", &key);
			printArray(hashtable);
			index = search(hashtable, key); //'e'�� 'E'�� �Է¹����� �ؽ� ���̺��� key�� �ּ� Ž��
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

	/* array�� NULL�� ��� �޸� �Ҵ� */
	if(*a == NULL) {
		temp = (int*)malloc(sizeof(int) * MAX_ARRAY_SIZE);
		*a = temp;  /* �Ҵ�� �޸��� �ּҸ� ���� --> main���� �迭�� control �Ҽ� �ֵ��� ��*/
	} else
		temp = *a;

	/* �������� �迭�� ������ ���� */
	for(int i = 0; i < MAX_ARRAY_SIZE; i++)
		temp[i] = rand() % MAX_ARRAY_SIZE;

	return 0;
}

int freeArray(int *a)
{
	if(a != NULL)
		free(a); //�迭�� ���� �Ҵ�� �޸� ����
	return 0;
}

void printArray(int *a)
{
	if (a == NULL) {
		printf("nothing to print.\n"); //�迭�� �����Ͱ� �������� ���� ��� �ش� �޼��� ���
		return;
	}
	for(int i = 0; i < MAX_ARRAY_SIZE; i++)
		printf("a[%02d] ", i); //�迭�� �ε��� ���
	printf("\n");
	for(int i = 0; i < MAX_ARRAY_SIZE; i++)
		printf("%5d ", a[i]); //�迭 �� �����ϴ� ������ ���
	printf("\n"); 
}


int selectionSort(int *a) //�ش� ȸ������ ���� ���� ������ ���� ���� ���ʿ� ��ġ�ǵ��� �� �������� �ڸ��� �����Ͽ� ����
//���� ������ �ð����⵵�� �־��� ��� O(n^2)
{
	int min; //�迭 �� ���� ���� ���� ������ min
	int minindex; //min�� �ε��� ���� ������ minindex
	int i, j;

	printf("Selection Sort: \n");
	printf("----------------------------------------------------------------\n");

	printArray(a); //���� �� �迭 ���

	for (i = 0; i < MAX_ARRAY_SIZE; i++)
	{
		minindex = i; //���� ���Ϸ��� ���ڵ� �� ���� ���ʿ� ��ġ�� ���ڰ� �ּҶ�� �����ϰ� minindex�� i ����(=�ε����� ���� ���� ����)
		min = a[i]; //minindex�� ����Ű�� �ε����� �����Ͱ� �ּҶ�� �����ϰ� min�� �ش� ������ �� ����
		for(j = i+1; j < MAX_ARRAY_SIZE; j++) //min���� ������ ���� �״��� ������ �� ����
		{
			if (min > a[j])
			{
				min = a[j]; //min�� ������ �� ���� ���� ������ �� �ش� ���� min�� ����
				minindex = j; //min�� �ε����� minindex�� ����
			}
		}
		a[minindex] = a[i]; 
		a[i] = min; //���Ͽ��� ���� �� ���� �۾Ҵ� ����, ���� ���Ͽ��� ���� �� �� ���ʿ� �־��� ���� ��ġ�� ����
		//�ڸ��� �ٲ� �� �״��� �����͸� �������� ��� �迭 �� �����͵��� �� ���Ͽ� �迭�� ���� ������ ������ �ݺ�
	}

	printf("----------------------------------------------------------------\n");
	printArray(a); //���� �� �迭 ���
	return 0;
}

int insertionSort(int *a) //�迭�� �տ������� ���ʴ�� ������ �Ǿ��ִ� �κа� ���Ͽ� �˸��� ��ġ�� �����͸� �����Ͽ� ����
//���� ������ �ð����⵵�� �־��� ��� O(n^2)
{
	int i, j, t;

	printf("Insertion Sort: \n");
	printf("----------------------------------------------------------------\n");

	printArray(a); //���� �� �迭 ���

	for(i = 1; i < MAX_ARRAY_SIZE; i++)
	{
		t = a[i]; //�� ��° �����ͺ��� �����Ͽ� �����ʿ��� �������� ���ʴ�� �����͸� ���ϱ� ���� ���Ϸ��� �����͵� �� ���� ������ �����͸� t�� ����(=�ε����� ���� ���� ŭ)
		j = i; //���Ϸ��� �����͵� �� ���� �����ʿ� ��ġ�� �������� �ε��� ����
		while (a[j-1] > t && j > 0) //�迭�� ù �κп� �����ϰų� ���ϴ� �������� ���� t�� ������ ���� ������ �ݺ�
		{
			a[j] = a[j-1]; //t�� ���� �����͸� ���Ͽ��� �� ���� ������ ���� t���� �� ũ�� ���� �����͸� ���������� �̵�
			j--; //���� �����Ϳ� ��
		}
		a[j] = t; //t�� ���� ���� ��ġ������ ���� ������ ������ ũ�� �ݺ��� ���� �� �ش� ���� �������� �����ʿ� t�� ����
		//Ȥ�� ���� ������ �����Ͽ��� �� �ش� �ڸ��� ������ ����
	}

	printf("----------------------------------------------------------------\n");
	printArray(a); //���� �� �迭 ���

	return 0;
}

int bubbleSort(int *a) //���� ������ �� �����͸� ���Ͽ� ����
//���� ������ �ð����⵵�� �־��� ��� O(n^2)
{
	int i, j, t;

	printf("Bubble Sort: \n");
	printf("----------------------------------------------------------------\n");

	printArray(a); //���� �� �迭 ���

	for(i = 0; i < MAX_ARRAY_SIZE; i++)
	{
		for (j = 0; j < MAX_ARRAY_SIZE; j++)
		{
			if (a[j-1] > a[j]) //������ �� ������ �� ���� �������� ���� ������ �����ͺ��� Ŭ ��
			{
				t = a[j-1];
				a[j-1] = a[j]; 
				a[j] = t; //�� �������� ��ġ�� �ٲ۴�.
			}
		}
	}

	printf("----------------------------------------------------------------\n");
	printArray(a); //���� �� �迭 ���

	return 0;
}

int shellSort(int *a) //h��ŭ�� �������� ������ ���ڵ带 ���� ����
//�� ������ ������� �ð� ���⵵�� O(n^1.25)
{
	int i, j, k, h, v;

	printf("Shell Sort: \n");
	printf("----------------------------------------------------------------\n");

	printArray(a); //���� �� �迭 ���

	for (h = MAX_ARRAY_SIZE/2; h > 0; h /= 2) //�� �ܰ谡 ����� ������ h�� 1/2��� �����Ͽ� h /= 2 �� �� h�� 0�� �� ������ �ݺ�
	{
		for (i = 0; i < h; i++)
		{
			for(j = i + h; j < MAX_ARRAY_SIZE; j += h)
			{
				v = a[j]; //���Ϸ��� �����͵� �� ���� �����ʿ� ��ġ�� �����͸� v�� ����
				k = j; //v�� �ε��� ����
				while (k > h-1 && a[k-h] > v) //k�� h���� ũ�ų� ����, �迭�� �ִ� �������� ���� ������ ������ �� Ŭ �� �ݺ�
				{
					a[k] = a[k-h]; //���ڵ带 h��ŭ ���������� �̵�
					k -= h; //���� k���� h��ŭ ��
				}
				a[k] = v; //v�� ���� ��� ���� ������ ������ ũ�� �ݺ��� ���� �� �ش� �������� �����ʿ� ����
				//Ȥ�� ���� ������ �����Ͽ��� �� �ش� �ڸ��� ������ ����
			}
		}
	}
	printf("----------------------------------------------------------------\n");
	printArray(a); //���� �� �迭 ���

	return 0;
}

int quickSort(int *a, int n) //�ǹ� ���ڵ带 �����Ͽ� �ǹ��� ���ʿ��� �ǹ��� Ű���� �۰ų� ���� �ǹ��� �����ʿ��� �ǹ��� Ű���� ũ�ų� ���� ���ڵ���� ����
//�� ������ �ð� ���⵵�� �־��� ��� O(n^2), ��� ���� �ð��� O(nlogn)
{
	int v, t;
	int i, j;

	if (n > 1)
	{
		v = a[n-1]; //�迭�� ������ ���ڵ带 �ǹ����� ����
		i = -1; //i�� �迭�� ���ʺ��� ����Ŵ
		j = n - 1; //j�� �迭�� �����ʺ��� ����Ŵ

		while(1)
		{
			while(a[++i] < v); //�ǹ����� ũ�ų� ���� ���� ���� ������ i ����(����>������)
			while(a[--j] > v); //�ǹ����� �۰ų� ���� ���� ���� ������ j ����(������>����)

			if (i >= j) break; //i�� j�� �����ϸ� while�� ����
			t = a[i];
			a[i] = a[j];
			a[j] = t; //i < j �� �� �����ʰ� ������ ���ڵ��� ��ġ�� ���� �ٲ�
		}
		t = a[i];
		a[i] = a[n-1];
		a[n-1] = t; //i�� j�� �����ϸ� �ǹ��� a[i]�� ���ڵ��� ��ġ�� ���� �ٲ�

		quickSort(a, i); //�ǹ��� ��ġ�� i�� �ٲ� �� �ǹ��� ���ʿ� ��ġ�� �迭�� a[i-1]�� �ǹ����� �ϴ� �� ������ ����
		quickSort(a+i+1, n-i-1); //�ǹ��� �����ʿ� ��ġ�� �迭�� a[n-i-2]�� �ǹ����� �ϴ� �� ������ ����
	}


	return 0;
}

int hashCode(int key) {
   return key % MAX_HASH_TABLE_SIZE; //�ؽ� ���̺����� �ش� key�� �´� �ּ� ����
}

int hashing(int *a, int **ht) //�ؽ� �Լ��� ���� �����͸� �ؽ� ���̺� �� ������ ��ġ�� ��ġ���� �����͸� ������ ã�� ���
{
	int *hashtable = NULL;

	/* hash table�� NULL�� ��� �޸� �Ҵ� */
	if(*ht == NULL) {
		hashtable = (int*)malloc(sizeof(int) * MAX_ARRAY_SIZE);
		*ht = hashtable;  /* �Ҵ�� �޸��� �ּҸ� ���� --> main���� �迭�� control �Ҽ� �ֵ��� ��*/
	} else {
		hashtable = *ht;	/* hash table�� NULL�� �ƴѰ��, table ��Ȱ��, reset to -1 */
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
		hashcode = hashCode(key); //�������� key ���� �ؽ� �Լ��� ���� �ؽ� ���̺� �ּҷ� ��ȯ
		/*
		printf("key = %d, hashcode = %d, hashtable[%d]=%d\n", key, hashcode, hashcode, hashtable[hashcode]);
		*/
		if (hashtable[hashcode] == -1) //�ؽ� ���̺��� �ش� �ּҰ� ����ִ� ������ �� 
		{
			hashtable[hashcode] = key; //�ش� �ּҿ� key ����
		} else 	{ //�ؽ� ���̺��� �ش� �ּҿ� �����Ͱ� �̹� ������� ��

			index = hashcode;

			while(hashtable[index] != -1)  //�ؽ� ���̺��� �� ������ ã�� ������ �ݺ�
			{
				index = (++index) % MAX_HASH_TABLE_SIZE; //�ؽ� ���̺� ������ index�� 1�� �����ϸ� �� ���� Ž��
				/*
				printf("index = %d\n", index);
				*/
			}
			hashtable[index] = key; //�ؽ� ���̺� �� ã�� �� ������ key ����
		}
	}

	return 0;
}

int search(int *ht, int key)
{
	int index = hashCode(key); //�ؽ� �Լ��� ���� �ش� key�� ���� �ؽ� ���̺��� �ּҸ� ����

    //case 1: �ؽ� �Լ��� key�� ���� ���� �����(key�� ���� �ּ�) == key�� ���� �ּ�
	if(ht[index] == key) //�ؽ� �Լ��� key�� ���� ���� ������� key�� �ּҿ� ������ ��
		return index; //key�� �ּ� ����

    //case 2: �ؽ� �Լ��� key�� ���� ���� �����(key�� ���� �ּ�) != key�� ���� �ּ�
	while(ht[++index] != key) //�ؽ� �Լ��� key�� ���� ���� ������� key�� �ּҰ� �������� �ʾ� index�� 1�� ������Ű�� key Ž��
	{
		index = index % MAX_HASH_TABLE_SIZE; //�ؽ� ���̺��� �ּҿ� �°� index ��ȯ
	}
	return index; //�ؽ� ���̺��� key�� ã���� �� key�� �ּ� ����
}




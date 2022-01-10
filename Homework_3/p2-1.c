#include <stdio.h>

#define MAX_SIZE 100
//���� 100�� ��ũ�� ��� MAX_SIZE�� �����Ѵ�.

float sum(float [], int);
//float�� 1���� �迭�� int�� ������ �Ű������� ���� �Լ� sum�� �����Ѵ�. sum�� float�� �Ǽ��� ��ȯ�Ѵ�.
float input[MAX_SIZE], answer;
//���� ������ MAX_SIZE��ŭ�� ���̸� ���� float�� 1���� �迭 input�� float�� answer�� �����Ѵ�.
int i;
//���� ������ int�� i�� �����Ѵ�.

void main(void)
{
    printf("[----- [�̽���] [2020039075] -----]\n");
    for(i=0;i<MAX_SIZE;i++)
    {
        input[i]=i;
        //i�� 0���� MAX_SIZE�� ������ 1�� ������ �� input[i]�� i�� ���� �����Ѵ�.
    }
    
    /*
    for checking call by reference
    */
    printf("address of input = %p\n", input);
    //input�� �ּҸ� ����Ѵ�. ���� input�� �ּҴ� 004070A0�̴�.

    answer=sum(input, MAX_SIZE);
    //sum �Լ��� input�� MAX_SIZE�� �Է��ϰ� sum �Լ��� �����ϴ� ���� answer�� �����Ѵ�.
    //input�� call by reference�� ���� input�� �ּҰ� sum �Լ��� list�� ����ȴ�.
    //MAX_SIZE�� call by value�� ���� MAX_SIZE�� ���� sum �Լ��� n�� ����ȴ�.
    printf("The sum is : %f\n", answer);
    //answer�� ���� 4950.000000�� ����Ѵ�.
}
float sum(float list[], int n)
//list���� input�� �ּҰ� ����Ǿ� �ְ�, n���� MAX_SIZE�� ���� ����Ǿ� �ִ�.
{
    
    printf("value of list = %p\n", list);
    //list�� ���� ����Ѵ�. list���� input�� �ּҰ� ����Ǿ� �����Ƿ� input�� �ּ��� 004070A0�� ����Ѵ�.
    printf("address of list = %p\n\n", &list);
    //list�� �ּҸ� ����Ѵ�. ���� list�� �ּҴ� 0061FF00�̴�.

    int i;
    //int�� i�� �����Ѵ�.
    float tempsum=0;
    //float�� tempsum�� �����ϰ� 0���� �ʱ�ȭ�Ѵ�.
    for(i=0;i<n;i++)
    {
        tempsum+=list[i];
        //i�� 0���� n���� 1�� ������ �� tempsum�� tempsum�� list[i]�� ���� ���� �����Ѵ�.
    }
    return tempsum;
    //tempsum�� �����ϸ鼭 sum �Լ��� �����Ѵ�.
}
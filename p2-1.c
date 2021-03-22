#include <stdio.h>

#define MAX_SIZE 100
//값이 100인 매크로 상수 MAX_SIZE를 선언한다.

float sum(float [], int);
//float형 1차원 배열과 int형 변수를 매개변수로 갖는 함수 sum을 선언한다. sum은 float형 실수를 반환한다.
float input[MAX_SIZE], answer;
//전역 변수로 MAX_SIZE만큼의 길이를 갖는 float형 1차원 배열 input와 float형 answer를 선언한다.
int i;
//전역 변수로 int형 i를 선언한다.

void main(void)
{
    printf("[----- [이승현] [2020039075] -----]\n");
    for(i=0;i<MAX_SIZE;i++)
    {
        input[i]=i;
        //i가 0부터 MAX_SIZE의 값까지 1씩 증가할 때 input[i]에 i의 값을 저장한다.
    }
    
    /*
    for checking call by reference
    */
    printf("address of input = %p\n", input);
    //input의 주소를 출력한다. 현재 input의 주소는 004070A0이다.

    answer=sum(input, MAX_SIZE);
    //sum 함수에 input과 MAX_SIZE를 입력하고 sum 함수가 리턴하는 값을 answer에 저장한다.
    //input은 call by reference에 의해 input의 주소가 sum 함수의 list에 복사된다.
    //MAX_SIZE은 call by value에 의해 MAX_SIZE의 값이 sum 함수의 n에 복사된다.
    printf("The sum is : %f\n", answer);
    //answer의 값인 4950.000000을 출력한다.
}
float sum(float list[], int n)
//list에는 input의 주소가 저장되어 있고, n에는 MAX_SIZE의 값이 저장되어 있다.
{
    
    printf("value of list = %p\n", list);
    //list의 값을 출력한다. list에는 input의 주소가 저장되어 있으므로 input의 주소인 004070A0를 출력한다.
    printf("address of list = %p\n\n", &list);
    //list의 주소를 출력한다. 현재 list의 주소는 0061FF00이다.

    int i;
    //int형 i를 선언한다.
    float tempsum=0;
    //float형 tempsum을 선언하고 0으로 초기화한다.
    for(i=0;i<n;i++)
    {
        tempsum+=list[i];
        //i가 0부터 n까지 1씩 증가할 때 tempsum에 tempsum과 list[i]를 더한 값을 저장한다.
    }
    return tempsum;
    //tempsum을 리턴하면서 sum 함수를 종료한다.
}
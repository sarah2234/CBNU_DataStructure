#include <stdio.h>

void print1(int* ptr, int rows);
//int형 포인터와 int형 변수를 매개변수로 갖는 void형 print1함수를 선언한다. 반환값은 없다.

int main()
{
    int one[]={0, 1, 2, 3, 4};
    //int형 1차원 배열 one을 선언하고 {0, 1, 2, 3, 4} 값을 차례로 넣어 초기화한다.

    printf("[----- [이승현] [2020039075] -----]\n");
    printf("one     = %p\n", one);
    //one의 주소를 출력한다. 현재 one의 주소는 0061FF0C이다.
    printf("&one    = %p\n", &one);
    //one의 주소를 & 연산자를 통해 출력한다.
    printf("&one[0] = %p\n", &one[0]);
    //one[0]의 주소를 & 연산자를 통해 출력한다. one[0]의 주소는 one의 주소와 동일하다.
    printf("\n");

    print1(&one[0], 5);
    //one[0]의 주소를 print1의 매개변수 ptr에 전달하고 5라는 값을 매개변수 rows에 전달하여 print1을 호출한다.

    return 0;
}
void print1(int* ptr, int rows)
{
    /*
    print out  a one-dimensional array using a pointer
    */
    int i;
    //int형 i를 선언한다.
    printf("Address \t Contents\n");
    for(i=0;i<rows;i++)
    {
        printf("%p \t %5d\n", ptr+i, *(ptr+i));
        //i가 0부터 rows까지 1씩 증가할 때 ptr+i의 값과 해당 포인터를 역참조한 값을 출력한다.
        //ptr가 i씩 증가할 때 ptr+i은 (ptr의 값이자 one[0]의 주소인 0061FF0C)+(int형 자료의 크기인 4 bytes)*i의 주소값을 가진다.
        //따라서 ptr+i은 one[i]을 가리키게 되어 *(ptr+i)을 하면 one[i]의 값이 출력된다.
    }
    printf("\n");
}
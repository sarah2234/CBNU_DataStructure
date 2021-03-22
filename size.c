#include <stdio.h>
#include <stdlib.h>

void main()
{
    int **x;
    //int형 이중 포인터 x를 선언한다.

    printf("[----- [이승현] [2020039075] -----]\n");
    printf("sizeof(x) = %lu\n", sizeof(x));
    //x의 메모리 크기를 출력한다. x는 주소를 저장하기 때문에 크기가 4 bytes이다. (32 bit 컴퓨터는 4 bytes로 주소 표헌)
    printf("sizeof(*x) = %lu\n", sizeof(*x));
    //*x의 메모리 크기를 출력한다. *x는 주소를 저장하기 때문에 크기가 4 bytes이다.
    printf("sizeof(**x) = %lu\n", sizeof(**x));
    //**x의 메모리 크기를 출력한다. **x는 int형 자료를 저장하기 때문에 크기가 4 bytes이다.
}
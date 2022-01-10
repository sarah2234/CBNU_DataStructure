#include <stdio.h>
#include <stdlib.h>

int main()
{
    int list[5];
    //크기가 5인 int형 1차원 배열 list를 선언한다.
    int *plist[5];
    //크기가 5인 포인터형 1차원 배열 plist를 선언한다.

    list[0]=10;
    //list[0]에 10을 저장한다.
    list[1]=11;
    //list[1]에 11을 저장한다.

    plist[0]=(int *)malloc(sizeof(int));
    //plist[0]에 int형 자료의 크기인 4 bytes만큼 메모리를 할당한다.
    //이때 plist[0]은 힙 영역의 주소값을 갖게 된다.

    printf("[----- [이승현] [2020039075] -----]\n");
    printf("list[0] \t= %d\n", list[0]);
    //list[0]에 저장된 값인 10을 출력한다.
    printf("address of list \t= %p\n", list);
    //list의 주소를 출력한다. 현재 list의 주소는 0061FF0C이다.
    printf("address of list[0] \t= %p\n", &list[0]);
    //list[0]의 주소를 & 연산자를 통해 출력한다. list[0]의 주소는 list의 주소와 같다.
    printf("address of list + 0 \t= %p\n", list+0);
    //list+0는 list[0]를 가리키는 포인터가 되어 list[0]의 주소를 출력한다.
    printf("address of list + 1 \t= %p\n", list+1);
    //list+1는 list[1]를 가리키는 포인터가 되어 (list[0]의 주소인 0061FF0C)+(int형 자료의 크기인 4 bytes)*1=0061FF10을 출력한다.
    printf("address of list + 2 \t= %p\n", list+2);
    //list+2는 list[2]를 가리키는 포인터가 되어 (list[0]의 주소인 0061FF0C)+(int형 자료의 크기인 4 bytes)*2=0061FF14을 출력한다.
    printf("address of list + 3 \t= %p\n", list+3);
    //list+3는 list[3]를 가리키는 포인터가 되어 (list[0]의 주소인 0061FF0C)+(int형 자료의 크기인 4 bytes)*3=0061FF18을 출력한다.
    printf("address of list + 4 \t= %p\n", list+4);
    //list+4는 list[4]를 가리키는 포인터가 되어 (list[0]의 주소인 0061FF0C)+(int형 자료의 크기인 4 bytes)*4=0061FF1C을 출력한다.
    printf("address of list[4] \t= %p\n", &list[4]);
    //list[4]의 주소를 & 연산자를 통해 출력한다. list[4]의 주소는 list+4의 주소와 같다.

    free(plist[0]);
    //동적 할당한 plist[0]의 메모리를 해제한다.

    return 0;
}
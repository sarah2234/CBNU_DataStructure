#include <stdio.h>
#include <stdlib.h>

int main()
{
    int list[5];
    //크기가 5인 int형 배열 list를 선언한다.
    int* plist[5]={NULL,};
    //크기가 5인 포인터형 배열 plist를 선언하고 모든 인덱스에 대해 NULL로 초기화한다.

    plist[0]=(int *)malloc(sizeof(int));
    //plist[0]에 int형 자료의 크기인 4 bytes만큼 메모리를 할당한다. 
    //이때 plist[0]는 힙 영역의 주소값을 갖게 된다.

    list[0]=1;
    //list[0]에 1을 저장한다.
    list[1]=100;
    //list[1]에 100을 저장한다.

    *plist[0]=200;
    //plist[0]가 가리키는 주소에 200을 저장한다.

    printf("[----- [이승현] [2020039075] -----]\n");
    printf("value of list[0]         = %d\n", list[0]);
    //list[0]에 저장된 값인 1을 출력한다.
    printf("address of list[0]       = %p\n",&list[0]);
    //list[0]의 주소를 출력한다. 현재 list[0]의 주소가 0061FF0C이다.
    printf("value of list            = %p\n", list);
    //list의 값, 즉 list의 주소를 출력한다. list의 주소는 list[0]의 주소와 동일하다.
    printf("address of list (&list)  = %p\n", &list);
    //list의 주소를 & 연산자를 통해 출력한다.

    printf("----------------------------------------\n\n");

    printf("value of list[1]   = %d\n", list[1]);
    //list[1]에 저장된 값인 100을 출력한다.
    printf("address of list[1] = %p\n", &list[1]);
    //list[1]의 주소인 0061FF10는 list[0]의 주소에 int형 자료의 크기인 4 bytes만큼 더한 값이다.
    printf("value of *(list+1) = %d\n", *(list+1));
    //list의 주소에 (int형 자료의 크기인 4 bytes)*1을 더하고 해당 주소에 저장된 100을 출력한다.
    printf("address of list+1  = %p\n", list+1);
    //(list+1)의 주소가 (list의 주소 0061FF0C)+(int형 자료의 크기인 4 bytes)*1=0061FF10이다.
    //따라서 list[1]의 주소와 동일하다.

    printf("----------------------------------------\n\n");

    printf("value of *plist[0] = %d\n", *plist[0]);
    //plist[0]가 가리키는 주소에 저장된 값인 200을 * 연산자를 통해 출력한다.
    printf("&plist[0]          = %p\n", &plist[0]);
    //plist[0]의 주소를 & 연산자를 통해 출력한다. 현재 plist[0]의 주소는 0061FEF8이다.
    printf("&plist             = %p\n", &plist);
    //plist의 주소를 & 연산자를 통해 출력한다. plist의 주소는 plist[0]의 주소와 동일하다.
    printf("plist              = %p\n", plist);
    //plist의 주소를 출력한다. plist가 배열이므로  plist에는 plist[0]가 저장되어 있다.
    printf("plist[0]           = %p\n", plist[0]);
    //plist[0]에 저장된 값, 즉 200이 저장되어 있는 주소를 출력한다.
    printf("plist[1]           = %p\n", plist[1]);
    //plist[0]에만 메모리 할당이 되어있으므로 plist[1]부터 plist[4]에는 NULL값이 들어갔다.
    printf("plist[2]           = %p\n", plist[2]);
    printf("plist[3]           = %p\n", plist[3]);
    printf("plist[4]           = %p\n", plist[4]);

    free(plist[0]);
    //동적 할당한 plist[0]의 메모리를 해제한다.

    return 0;
}

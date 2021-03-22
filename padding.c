#include <stdio.h>

struct student {
    char lastName[13];  /* 13 bytes */
    int studentId;      /* 4 bytes */
    short grade;        /* 2 bytes */
};
//구조체 student를 선언하고 내부에 char형, int형, short형 변수를 각각 선언한다.

int main()
{
    struct student pst;
    //구조체 변수 pst를 선언한다.

    printf("[----- [이승현] [2020039075] -----]\n");
    printf("size of student = %ld\n", sizeof(struct student));
    //구조체 student 내에서 padding을 하였으므로 student의 메모리 크기는 16+4+4=24 bytes이다.
    printf("size of int = %ld\n", sizeof(int));
    //int형 자료의 메모리 크기는 4 bytes이다.
    printf("size of short = %ld\n", sizeof(short));
    //short형 자료의 메모리 크기는 2 bytes이다.

    return 0;
}
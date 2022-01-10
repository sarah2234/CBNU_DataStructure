#include <stdio.h>

struct student {
    char lastName[13];  /* 13 bytes */
    int studentId;      /* 4 bytes */
    short grade;        /* 2 bytes */
};
//����ü student�� �����ϰ� ���ο� char��, int��, short�� ������ ���� �����Ѵ�.

int main()
{
    struct student pst;
    //����ü ���� pst�� �����Ѵ�.

    printf("[----- [�̽���] [2020039075] -----]\n");
    printf("size of student = %ld\n", sizeof(struct student));
    //����ü student ������ padding�� �Ͽ����Ƿ� student�� �޸� ũ��� 16+4+4=24 bytes�̴�.
    printf("size of int = %ld\n", sizeof(int));
    //int�� �ڷ��� �޸� ũ��� 4 bytes�̴�.
    printf("size of short = %ld\n", sizeof(short));
    //short�� �ڷ��� �޸� ũ��� 2 bytes�̴�.

    return 0;
}
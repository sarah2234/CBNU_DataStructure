#include <stdio.h>

struct student1 {
    char lastName;
    int studentId;
    char grade;
};
//����ü student1�� �����ϰ� ���ο� char��, int��, char�� ������ ���� �����Ѵ�.

typedef struct {
    char lastName;
    int studentId;
    char grade;
} student2;
//����ü student2�� �����ϰ� ���ο� char��, int��, char�� ������ ���� �����Ѵ�.
//�ش� ����ü ��Ī�� student2�� �����Ѵ�.

int main()
{
    struct student1 st1={'A', 100, 'A'};
    //����ü ���� st1�� �����ϰ� st1 �� ����� ���ʴ�� A, 100, A�� �����Ѵ�.

    printf("[----- [�̽���] [2020039075] -----]\n");
    printf("st1.lastName = %c\n", st1.lastName);
    //st1�� ��� lastName�� ���� A�� ����Ѵ�.
    printf("st1.studentId = %d\n", st1.studentId);
    //st1�� ��� studentId�� ���� 100�� ����Ѵ�.
    printf("st1.grade = %c\n", st1.grade);
    //st1�� ��� grade�� ���� A�� ����Ѵ�.

    student2 st2={'B', 200, 'B'};
    //typedef�� ������ ��Ī���� st2�� �����ϰ� st2 �� ����� ���ʴ�� B, 200. B�� �����Ѵ�.

    printf("\nst2.lastName = %c\n", st2.lastName);
    //st2�� ��� lastName�� ���� B�� ����Ѵ�.
    printf("st2.studentId = %d\n", st2.studentId);
    //st2�� ��� studentId�� ���� 200�� ����Ѵ�.
    printf("st2.grade = %c\n", st2.grade);
    //st2�� ��� grade�� ���� B�� ����Ѵ�.

    student2 st3;
    //typedef�� ������ ��Ī���� st3�� �����Ѵ�.

    st3=st2;
    //st2 ������� ���� st3 ����鿡�� �����Ѵ�. (���� ġȯ�� �����ϴ�.)

    printf("\nst3.lastName = %c\n", st3.lastName);
    //���� ġȯ�� ���� st2�� lastName�� st3�� lastName�� ���� ���� ������.
    printf("st3.studentId = %d\n", st3.studentId);
    //���� ġȯ�� ���� st2�� studentId�� st3�� studentId�� ���� ���� ������.
    printf("st3.grade = %c\n", st3.grade);
    //���� ġȯ�� ���� st2�� grade�� st3�� grade�� ���� ���� ������.

    /*equality test*/
    /*
    if (st3==st2)
        printf("equal\n");
    else
        printf("not equal\n");
    */
    //'==' �����ڸ� ���� ��ü ������ ��� �˻縦 �� �� ����, ������� ���� �񱳸� �ؾ� �Ѵ�.

    return 0;
}
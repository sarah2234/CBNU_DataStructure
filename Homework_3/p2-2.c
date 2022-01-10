#include <stdio.h>

void print1(int* ptr, int rows);
//int�� �����Ϳ� int�� ������ �Ű������� ���� void�� print1�Լ��� �����Ѵ�. ��ȯ���� ����.

int main()
{
    int one[]={0, 1, 2, 3, 4};
    //int�� 1���� �迭 one�� �����ϰ� {0, 1, 2, 3, 4} ���� ���ʷ� �־� �ʱ�ȭ�Ѵ�.

    printf("[----- [�̽���] [2020039075] -----]\n");
    printf("one     = %p\n", one);
    //one�� �ּҸ� ����Ѵ�. ���� one�� �ּҴ� 0061FF0C�̴�.
    printf("&one    = %p\n", &one);
    //one�� �ּҸ� & �����ڸ� ���� ����Ѵ�.
    printf("&one[0] = %p\n", &one[0]);
    //one[0]�� �ּҸ� & �����ڸ� ���� ����Ѵ�. one[0]�� �ּҴ� one�� �ּҿ� �����ϴ�.
    printf("\n");

    print1(&one[0], 5);
    //one[0]�� �ּҸ� print1�� �Ű����� ptr�� �����ϰ� 5��� ���� �Ű����� rows�� �����Ͽ� print1�� ȣ���Ѵ�.

    return 0;
}
void print1(int* ptr, int rows)
{
    /*
    print out  a one-dimensional array using a pointer
    */
    int i;
    //int�� i�� �����Ѵ�.
    printf("Address \t Contents\n");
    for(i=0;i<rows;i++)
    {
        printf("%p \t %5d\n", ptr+i, *(ptr+i));
        //i�� 0���� rows���� 1�� ������ �� ptr+i�� ���� �ش� �����͸� �������� ���� ����Ѵ�.
        //ptr�� i�� ������ �� ptr+i�� (ptr�� ������ one[0]�� �ּ��� 0061FF0C)+(int�� �ڷ��� ũ���� 4 bytes)*i�� �ּҰ��� ������.
        //���� ptr+i�� one[i]�� ����Ű�� �Ǿ� *(ptr+i)�� �ϸ� one[i]�� ���� ��µȴ�.
    }
    printf("\n");
}
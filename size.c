#include <stdio.h>
#include <stdlib.h>

void main()
{
    int **x;
    //int�� ���� ������ x�� �����Ѵ�.

    printf("[----- [�̽���] [2020039075] -----]\n");
    printf("sizeof(x) = %lu\n", sizeof(x));
    //x�� �޸� ũ�⸦ ����Ѵ�. x�� �ּҸ� �����ϱ� ������ ũ�Ⱑ 4 bytes�̴�. (32 bit ��ǻ�ʹ� 4 bytes�� �ּ� ǥ��)
    printf("sizeof(*x) = %lu\n", sizeof(*x));
    //*x�� �޸� ũ�⸦ ����Ѵ�. *x�� �ּҸ� �����ϱ� ������ ũ�Ⱑ 4 bytes�̴�.
    printf("sizeof(**x) = %lu\n", sizeof(**x));
    //**x�� �޸� ũ�⸦ ����Ѵ�. **x�� int�� �ڷḦ �����ϱ� ������ ũ�Ⱑ 4 bytes�̴�.
}
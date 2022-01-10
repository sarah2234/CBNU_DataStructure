#include <stdio.h>
#include <stdlib.h>

int main()
{
    int list[5];
    //ũ�Ⱑ 5�� int�� 1���� �迭 list�� �����Ѵ�.
    int *plist[5];
    //ũ�Ⱑ 5�� �������� 1���� �迭 plist�� �����Ѵ�.

    list[0]=10;
    //list[0]�� 10�� �����Ѵ�.
    list[1]=11;
    //list[1]�� 11�� �����Ѵ�.

    plist[0]=(int *)malloc(sizeof(int));
    //plist[0]�� int�� �ڷ��� ũ���� 4 bytes��ŭ �޸𸮸� �Ҵ��Ѵ�.
    //�̶� plist[0]�� �� ������ �ּҰ��� ���� �ȴ�.

    printf("[----- [�̽���] [2020039075] -----]\n");
    printf("list[0] \t= %d\n", list[0]);
    //list[0]�� ����� ���� 10�� ����Ѵ�.
    printf("address of list \t= %p\n", list);
    //list�� �ּҸ� ����Ѵ�. ���� list�� �ּҴ� 0061FF0C�̴�.
    printf("address of list[0] \t= %p\n", &list[0]);
    //list[0]�� �ּҸ� & �����ڸ� ���� ����Ѵ�. list[0]�� �ּҴ� list�� �ּҿ� ����.
    printf("address of list + 0 \t= %p\n", list+0);
    //list+0�� list[0]�� ����Ű�� �����Ͱ� �Ǿ� list[0]�� �ּҸ� ����Ѵ�.
    printf("address of list + 1 \t= %p\n", list+1);
    //list+1�� list[1]�� ����Ű�� �����Ͱ� �Ǿ� (list[0]�� �ּ��� 0061FF0C)+(int�� �ڷ��� ũ���� 4 bytes)*1=0061FF10�� ����Ѵ�.
    printf("address of list + 2 \t= %p\n", list+2);
    //list+2�� list[2]�� ����Ű�� �����Ͱ� �Ǿ� (list[0]�� �ּ��� 0061FF0C)+(int�� �ڷ��� ũ���� 4 bytes)*2=0061FF14�� ����Ѵ�.
    printf("address of list + 3 \t= %p\n", list+3);
    //list+3�� list[3]�� ����Ű�� �����Ͱ� �Ǿ� (list[0]�� �ּ��� 0061FF0C)+(int�� �ڷ��� ũ���� 4 bytes)*3=0061FF18�� ����Ѵ�.
    printf("address of list + 4 \t= %p\n", list+4);
    //list+4�� list[4]�� ����Ű�� �����Ͱ� �Ǿ� (list[0]�� �ּ��� 0061FF0C)+(int�� �ڷ��� ũ���� 4 bytes)*4=0061FF1C�� ����Ѵ�.
    printf("address of list[4] \t= %p\n", &list[4]);
    //list[4]�� �ּҸ� & �����ڸ� ���� ����Ѵ�. list[4]�� �ּҴ� list+4�� �ּҿ� ����.

    free(plist[0]);
    //���� �Ҵ��� plist[0]�� �޸𸮸� �����Ѵ�.

    return 0;
}
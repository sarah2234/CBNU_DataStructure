#include <stdio.h>
#include <stdlib.h>

int main()
{
    int list[5];
    //ũ�Ⱑ 5�� int�� �迭 list�� �����Ѵ�.
    int* plist[5]={NULL,};
    //ũ�Ⱑ 5�� �������� �迭 plist�� �����ϰ� ��� �ε����� ���� NULL�� �ʱ�ȭ�Ѵ�.

    plist[0]=(int *)malloc(sizeof(int));
    //plist[0]�� int�� �ڷ��� ũ���� 4 bytes��ŭ �޸𸮸� �Ҵ��Ѵ�. 
    //�̶� plist[0]�� �� ������ �ּҰ��� ���� �ȴ�.

    list[0]=1;
    //list[0]�� 1�� �����Ѵ�.
    list[1]=100;
    //list[1]�� 100�� �����Ѵ�.

    *plist[0]=200;
    //plist[0]�� ����Ű�� �ּҿ� 200�� �����Ѵ�.

    printf("[----- [�̽���] [2020039075] -----]\n");
    printf("value of list[0]         = %d\n", list[0]);
    //list[0]�� ����� ���� 1�� ����Ѵ�.
    printf("address of list[0]       = %p\n",&list[0]);
    //list[0]�� �ּҸ� ����Ѵ�. ���� list[0]�� �ּҰ� 0061FF0C�̴�.
    printf("value of list            = %p\n", list);
    //list�� ��, �� list�� �ּҸ� ����Ѵ�. list�� �ּҴ� list[0]�� �ּҿ� �����ϴ�.
    printf("address of list (&list)  = %p\n", &list);
    //list�� �ּҸ� & �����ڸ� ���� ����Ѵ�.

    printf("----------------------------------------\n\n");

    printf("value of list[1]   = %d\n", list[1]);
    //list[1]�� ����� ���� 100�� ����Ѵ�.
    printf("address of list[1] = %p\n", &list[1]);
    //list[1]�� �ּ��� 0061FF10�� list[0]�� �ּҿ� int�� �ڷ��� ũ���� 4 bytes��ŭ ���� ���̴�.
    printf("value of *(list+1) = %d\n", *(list+1));
    //list�� �ּҿ� (int�� �ڷ��� ũ���� 4 bytes)*1�� ���ϰ� �ش� �ּҿ� ����� 100�� ����Ѵ�.
    printf("address of list+1  = %p\n", list+1);
    //(list+1)�� �ּҰ� (list�� �ּ� 0061FF0C)+(int�� �ڷ��� ũ���� 4 bytes)*1=0061FF10�̴�.
    //���� list[1]�� �ּҿ� �����ϴ�.

    printf("----------------------------------------\n\n");

    printf("value of *plist[0] = %d\n", *plist[0]);
    //plist[0]�� ����Ű�� �ּҿ� ����� ���� 200�� * �����ڸ� ���� ����Ѵ�.
    printf("&plist[0]          = %p\n", &plist[0]);
    //plist[0]�� �ּҸ� & �����ڸ� ���� ����Ѵ�. ���� plist[0]�� �ּҴ� 0061FEF8�̴�.
    printf("&plist             = %p\n", &plist);
    //plist�� �ּҸ� & �����ڸ� ���� ����Ѵ�. plist�� �ּҴ� plist[0]�� �ּҿ� �����ϴ�.
    printf("plist              = %p\n", plist);
    //plist�� �ּҸ� ����Ѵ�. plist�� �迭�̹Ƿ�  plist���� plist[0]�� ����Ǿ� �ִ�.
    printf("plist[0]           = %p\n", plist[0]);
    //plist[0]�� ����� ��, �� 200�� ����Ǿ� �ִ� �ּҸ� ����Ѵ�.
    printf("plist[1]           = %p\n", plist[1]);
    //plist[0]���� �޸� �Ҵ��� �Ǿ������Ƿ� plist[1]���� plist[4]���� NULL���� ����.
    printf("plist[2]           = %p\n", plist[2]);
    printf("plist[3]           = %p\n", plist[3]);
    printf("plist[4]           = %p\n", plist[4]);

    free(plist[0]);
    //���� �Ҵ��� plist[0]�� �޸𸮸� �����Ѵ�.

    return 0;
}

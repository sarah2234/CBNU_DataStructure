#include <stdio.h>

struct student1 {
    char lastName;
    int studentId;
    char grade;
};
//구조체 student1을 선언하고 내부에 char형, int형, char형 변수를 각각 선언한다.

typedef struct {
    char lastName;
    int studentId;
    char grade;
} student2;
//구조체 student2을 선언하고 내부에 char형, int형, char형 변수를 각각 선언한다.
//해당 구조체 별칭을 student2로 지정한다.

int main()
{
    struct student1 st1={'A', 100, 'A'};
    //구조체 변수 st1을 선언하고 st1 내 멤버에 차례대로 A, 100, A를 저장한다.

    printf("[----- [이승현] [2020039075] -----]\n");
    printf("st1.lastName = %c\n", st1.lastName);
    //st1의 멤버 lastName의 값인 A를 출력한다.
    printf("st1.studentId = %d\n", st1.studentId);
    //st1의 멤버 studentId의 값인 100을 출력한다.
    printf("st1.grade = %c\n", st1.grade);
    //st1의 멤버 grade의 값인 A를 출력한다.

    student2 st2={'B', 200, 'B'};
    //typedef로 지정된 별칭으로 st2를 선언하고 st2 내 멤버에 차례대로 B, 200. B를 저장한다.

    printf("\nst2.lastName = %c\n", st2.lastName);
    //st2의 멤버 lastName의 값인 B를 출력한다.
    printf("st2.studentId = %d\n", st2.studentId);
    //st2의 멤버 studentId의 값인 200을 출력한다.
    printf("st2.grade = %c\n", st2.grade);
    //st2의 멤버 grade의 값인 B를 출력한다.

    student2 st3;
    //typedef로 지정된 별칭으로 st3를 선언한다.

    st3=st2;
    //st2 멤버들의 값을 st3 멤버들에게 복사한다. (구조 치환이 가능하다.)

    printf("\nst3.lastName = %c\n", st3.lastName);
    //구조 치환을 통해 st2의 lastName과 st3의 lastName이 같은 값을 가진다.
    printf("st3.studentId = %d\n", st3.studentId);
    //구조 치환을 통해 st2의 studentId와 st3의 studentId가 같은 값을 가진다.
    printf("st3.grade = %c\n", st3.grade);
    //구조 치환을 통해 st2의 grade와 st3의 grade가 같은 값을 가진다.

    /*equality test*/
    /*
    if (st3==st2)
        printf("equal\n");
    else
        printf("not equal\n");
    */
    //'==' 연산자를 통해 전체 구조의 동등성 검사를 할 수 없고, 멤버별로 각각 비교를 해야 한다.

    return 0;
}
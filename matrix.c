#include <stdio.h>
#include <stdlib.h>
#include <time.h>

/* Method Declaration */
int** create_matrix(int row, int col); //행렬을 동적 메모리할당 방식으로 생성하는 함수 선언
void print_matrix(int** matrix, int row, int col); //행렬을 출력하는 함수
int free_matrix(int** matrix, int row, int col); //행렬에 할당한 메모리를 해제하는 함수
int fill_data(int** matrix, int row, int col); //행렬의 성분값에 0~19 사이의 값을 랜덤하게 넣는 함수
int addition_matrix(int** matrix_a, int** matrix_b, int row, int col); //행렬 A + 행렬 B을 구현하는 함수
int subtraction_matrix(int** matrix_a, int** matrix_b, int row, int col); //행렬 A - 행렬 B을 구현하는 함수
int transpose_matrix(int** matrix, int** matrix_t, int row, int col); //행렬 A의 전치행렬 T를 구현하는 함수
int multiply_matrix(int** matrix_a, int** matrix_t, int row, int col); //행렬 A x 행렬 T를 구현하는 함수

int main()
{

    char command; //명령어를 입력받을 문자형 변수 char을 선언한다.
    printf("[----- 이승현  2020039075 -----]\n");

    int row, col; //행과 열의 길이를 입력받을 정수형 변수 row와 col을 선언한다.
    srand(time(NULL)); //시간을 seed 값으로 넣어 랜덤한 수를 생성한다.

    printf("Input row and col : ");
    scanf("%d %d", &row, &col); //행과 열의 수를 입력받아 각각 row와 col에 저장한다.
    int** matrix_a = create_matrix(row, col); //row와 col을 call by value로 create_matrix를 호출하여 matrix_a에 리턴받은 주소값을 저장한다. 
    int** matrix_b = create_matrix(row, col); //row와 col을 call by value로 create_matrix를 호출하여 matrix_b에 리턴받은 주소값을 저장한다.
    int** matrix_a_t = create_matrix(col, row); //row와 col을 call by value로 create_matrix를 호출하여 matrix_a_t에 리턴받은 주소값을 저장한다.

    printf("Matrix Created.\n");

    if (matrix_a == NULL || matrix_b == NULL) { return -1; } //행렬 A와 행렬 B가 생성되지 않으면(matrix_a와 matrix_b에 메모리가 할당되지 않았을 때) -1을 리턴한다.

    do {
        printf("----------------------------------------------------------------\n");
        printf("                     Matrix Manipulation                        \n");
        printf("----------------------------------------------------------------\n");
        printf(" Initialize Matrix   = z           Print Matrix        = p \n");
        printf(" Add Matrix          = a           Subtract Matrix     = s \n");
        printf(" Transpose matrix_a  = t           Multiply Matrix     = m \n");
        printf(" Quit                = q \n");
        printf("----------------------------------------------------------------\n");

        printf("Command = ");
        scanf(" %c", &command); //명령어를 입력받는다.

        switch (command) {
        case 'z': case 'Z': //'z'나 'Z'를 입력받았을 시
            printf("Matrix Initialized\n");
            fill_data(matrix_a, row, col); //matrix_a는 call by reference, row와 col은 call by value로 fill_data를 호출한다.
            fill_data(matrix_b, row, col); //matrix_b는 call by reference, row와 col은 call by value로 fill_data를 호출한다.
            break;
        case 'p': case 'P': //'p'나 'P'를 입력받았을 시
            printf("Print matrix\n");
            printf("matrix_a\n");
            print_matrix(matrix_a, row, col); //matrix_a는 call by reference, row와 col은 call by value로 print_matrix를 호출한다.
            printf("matrix_b\n");
            print_matrix(matrix_b, row, col); //matrix_b는 call by reference, row와 col은 call by value로 print_matrix를 호출한다.
            break;
        case 'a': case 'A': //'a'나 'A'를 입력받았을 시
            printf("Add two matrices\n");
            addition_matrix(matrix_a, matrix_b, row, col); //matrix_a와 matrix_b는 call by reference, row와 col은 call by value로 additional_matrix를 호출한다.
            break;
        case 's': case 'S': //'s'나 'S'를 입력받았을 시
            printf("Subtract two matrices \n");
            subtraction_matrix(matrix_a, matrix_b, row, col); //matrix_a와 matrix_b는 call by reference, row와 col은 call by value로 subtraction_matrix를 호출한다.
            break;
        case 't': case 'T': //'t'나 'T'를 입력받았을 시
            printf("Transpose matrix_a \n");
            printf("matrix_a\n");
            transpose_matrix(matrix_a, matrix_a_t, col, row); //matrix_a와 matrix_a_t는 call by reference, row와 col은 call by value로 transpose_matrix를 호출한다.
            print_matrix(matrix_a_t, col, row); //matrix_a_t는 call by reference, row와 col은 call by value로 print_matrix를 호출한다.
            break;
        case 'm': case 'M': //'m'나 'M'를 입력받았을 시
            printf("Multiply matrix_a with transposed matrix_a \n");
            transpose_matrix(matrix_a, matrix_a_t, col, row); //matrix_a와 matrix_a_t는 call by reference, row와 col은 call by value로 transpose_matrix를 호출한다.
            multiply_matrix(matrix_a, matrix_a_t, row, col); //matrix_a와 matrix_a_t는 call by reference, row와 col은 call by value로 multiply_matrix를 호출한다.
            break;
        case 'q': case 'Q': //'q'나 'Q'를 입력받았을 시
            printf("Free all matrices..\n");
            free_matrix(matrix_a_t, col, row); //matrix_a_t는 call by reference, row와 col은 call by value로 free_matrix를 호출한다.
            free_matrix(matrix_a, row, col); //matrix_a는 call by reference, row와 col은 call by value로 free_matrix를 호출한다.
            free_matrix(matrix_b, row, col); //matrix_b는 call by reference, row와 col은 call by value로 free_matrix를 호출한다.
            break;
        default: //상단의 문자 이외의 값을 입력받았을 시
            printf("\n       >>>>>   Concentration!!   <<<<<     \n");
            break;
        }

    } while (command != 'q' && command != 'Q'); //블록 내의 코드를 최소 한 번 실행한 후 command가 'q' 혹은 'Q'를 입력받으면 반복문을 종료한다.

    return 1;
}

/* create a 2d array whose size is row x col using malloc() */
int** create_matrix(int row, int col) //정수형 변수 row와 col 2개를 매개변수로 하고 이중 포인터의 주소값을 리턴하는 함수
{
    /* check pre conditions */
    if (row <= 0 || col <= 0) {
        printf("Check the sizes of row and col!\n"); //row나 col의 값으로 인해 행렬을 생성하지 못할 때 NULL을 리턴한다.
        return NULL;
    }

    int** matrix = NULL; //이중 포인터 matrix를 선언하고 NULL을 가리키도록 한다.
    matrix = (int**)malloc(sizeof(int*) * row); //matrix에 메모리 할당을 하여 row만큼 행을 생성한다. 
    for (int i = 0; i < row; i++)
    {
        matrix[i] = (int*)malloc(sizeof(int) * col); //i가 0부터 row 전까지 1씩 증가할 때 matrix[i]에 메모리 할당을 하여 col만큼 열을 생성한다.
    }

    /* check post conditions */
    if (matrix == NULL) {
        printf("Unexpected result. Try again.\n"); //row x col 크기의 2차원 배열이 생성되지 못하였을 경우 NULL을 리턴한다.
        return NULL;
    }
    return matrix; //matrix의 주소를 리턴한다.
}

/* print matrix whose size is row x col */
void print_matrix(int** matrix, int row, int col) //이중 포인터 matrix 1개와 정수형 변수 row와 col 2개를 매개변수로 하고 리턴값이 없는 함수
{
    for (int i = 0; i < row; i++)
    {
        for (int j = 0; j < col; j++)
        {
            printf("%3d ", matrix[i][j]); //j가 0부터 col 전까지 1씩 증가하면서 matrix[i][j]의 값을 출력한다.
        }
        printf("\n"); //i가 0부터 row 전까지 1씩 증가하면서 상단의 for 구문과 줄바꿈을 출력한다.
    }
    printf("\n");
}


/* free memory allocated by create_matrix() */
int free_matrix(int** matrix, int row, int col) //이중 포인터 matrix 1개와 정수형 변수 row와 col 2개를 매개변수로 하고 정수를 리턴하는 함수
{
    for (int i = 0; i < row; i++)
    {
        free(matrix[i]); //i가 0부터 row 전까지 1씩 증가하면서 matrix[i]에 할당되었던 메모리를 해제한다. 행렬에서 열에 해당하는 부분이다.
    }
    free(matrix); //matrix에 할당되었던 메모리를 해제한다. 행렬에서 행에 해당하는 부분이다.
    matrix = NULL; //matrix가 NULL을 가리키도록 한다.
    if (!matrix)
    {
        return 1; //matrix가 성공적으로 메모리 해제되었다면 1을 리턴한다.
    }
    return -1; //비정상 종료 시 -1을 리턴한다.
}


/* assign random values to the given matrix */
int fill_data(int** matrix, int row, int col) //이중 포인터 matrix 1개와 정수형 변수 row와 col 2개를 매개변수로 하고 정수를 리턴하는 함수
{
    int cnt = 0;
    for (int i = 0; i < row; i++)
    {
        for (int j = 0; j < col; j++)
        {
            matrix[i][j] = rand() % 20; //i는 0부터 row 전까지, j는 0부터 col 전까지 1씩 증가하면서 matrix[i][j]에 0~19 사이의 랜덤한 값을 저장한다.
            cnt++; //matrix[i][j]에 값이 저장된 후 cnt의 값을 1 증가한다.
        }
    }
    if (cnt == row * col)
    {
        return 1; //matrix의 모든 성분값이 성공적으로 정해진 경우 1을 리턴한다.
    }
    return -1; //비정상 종료 시 -1을 리턴한다.
}

/* matrix_sum = matrix_a + matrix_b */
int addition_matrix(int** matrix_a, int** matrix_b, int row, int col) //이중 포인터 matrix_a, matrix_b 2개와 정수형 변수 row와 col 2개를 매개변수로 하고 정수를 리턴하는 함수
{
    int** matrix_sum = create_matrix(row, col); //row와 col을 call by value로 create_matrix를 호출하여 matrix_sum에 리턴받은 주소값을 저장한다.
    int right_answer = 0;
    for (int i = 0; i < row; i++)
    {
        for (int j = 0; j < col; j++)
        {
            matrix_sum[i][j] = matrix_a[i][j] + matrix_b[i][j]; //i는 0부터 row 전까지, j는 0부터 col 전까지 1씩 증가하면서 matrix_sum[i][j]에 행렬 A와 행렬 B의 덧셈 결과를 저장한다.
            if (matrix_sum[i][j] == matrix_a[i][j] + matrix_b[i][j])
            {
                right_answer++; //덧셈 결과가 올바르면 right_answer의 값을 1 증가한다.
            }
        }
    }
    print_matrix(matrix_sum, row, col); //matrix_sum는 call by reference, row와 col은 call by value로 print_matrix를 호출한다.
    free_matrix(matrix_sum, row, col); //matrix_sum는 call by reference, row와 col은 call by value로 free_matrix를 호출한다.
    matrix_sum = NULL; //메모리 해제 후 matrix_sum이 NULL을 가리키도록 한다.
    if (!matrix_sum && right_answer == row*col)
    {
        return 1; //matrix_sum의 메모리가 성공적으로 해제되어있고 모든 성분에 대해 값이 올바르면 1을 리턴한다.
    }
    return -1; //비정상 종료 시 -1을 리턴한다.
}

/* matrix_sub = matrix_a - matrix_b */
int subtraction_matrix(int** matrix_a, int** matrix_b, int row, int col) //이중 포인터 matrix_a, matrix_b 2개와 정수형 변수 row와 col 2개를 매개변수로 하고 정수를 리턴하는 함수
{
    int** matrix_sub = create_matrix(row, col); //row와 col을 call by value로 create_matrix를 호출하여 matrix_sub에 리턴받은 주소값을 저장한다.
    int right_answer = 0;
    for (int i = 0; i < row; i++)
    {
        for (int j = 0; j < col; j++)
        {
            matrix_sub[i][j] = matrix_a[i][j] - matrix_b[i][j]; //i는 0부터 row 전까지, j는 0부터 col 전까지 1씩 증가하면서 matrix_sum[i][j]에 행렬 A와 행렬 B의 뺄셈 결과를 저장한다.
            if (matrix_sub[i][j] == matrix_a[i][j] - matrix_b[i][j])
            {
                right_answer++; //뺄셈 결과가 올바르면 right_answer의 값을 1 증가한다.
            }
        }
    }
    print_matrix(matrix_sub, row, col); //matrix_sub는 call by reference, row와 col은 call by value로 print_matrix를 호출한다.
    free_matrix(matrix_sub, row, col); //matrix_sub는 call by reference, row와 col은 call by value로 free_matrix를 호출한다.
    matrix_sub = NULL; //메모리 해제 후 matrix_sub이 NULL을 가리키도록 한다.
    if (!matrix_sub && right_answer == row * col) 
    {
        return 1; //matrix_sub의 메모리가 성공적으로 해제되어있고 모든 성분에 대해 값이 올바르면 1을 리턴한다. 
    }
    return -1; //비정상 종료 시 -1을 리턴한다.
}

/* transpose the matrix to matrix_t */
int transpose_matrix(int** matrix, int** matrix_t, int row, int col) //이중 포인터 matrix, matrix_t 2개와 정수형 변수 row와 col 2개를 매개변수로 하고 정수를 리턴하는 함수
{
    int right_answer = 0;
    for (int i = 0; i < row; i++)
    {
        for (int j = 0; j < col; j++)
        {
            matrix_t[i][j] = matrix[j][i]; //i는 0부터 row 전까지, j는 0부터 col 전까지 1씩 증가하면서 기존 행렬의 행과 열을 바꾼 성분값을 전치행렬에 저장한다.
            if (matrix_t[i][j] == matrix[j][i])
            {
                right_answer++; //전치행렬의 성분값이 올바르면 right_answer의 값을 1 증가한다.
            }
        }
    }
    if (right_answer == row * col)
    {
        return 1; //전치행렬의 모든 성분에 대해 값이 올바르면 1을 리턴한다.
    }
    return -1; //비정상 종료 시 -1을 리턴한다.
}

/* matrix_axt = matrix_a x matrix_t */
int multiply_matrix(int** matrix_a, int** matrix_t, int row, int col) //이중 포인터 matrix_a, matrix_t 2개와 정수형 변수 row와 col 2개를 매개변수로 하고 정수를 리턴하는 함수
{
    int** matrix_axt = create_matrix(row, row); //두 개의 row를 call by value로 create_matrix를 호출하여 matrix_axt에 리턴받은 주소값을 저장한다.
    int i, j, result, right_answer = 0;
    for (i = 0; i < row; i++)
    {
        for (j = 0; j < row; j++)
        {
            result = 0; //매 연산마다 초기 result의 값을 0으로 설정한다.
            for (int k = 0; k < col; k++)
            {
                result += (matrix_a[i][k] * matrix_t[k][j]); //i와 j의 값을 고정하고 k가 0부터 col 전까지 1씩 증가할 때 result에 matrix_a[i][k] * matrix_t[k][j] 값을 누적하여 합한다.
            }
            matrix_axt[i][j] = result; //result의 최종값을 matrix_axt[i][j]에 저장한다.
        }
    }
    //연산값을 검토하기 위해 상단의 연산을 다시 행한다.
    for (i = 0; i < row; i++)
    {
        for (j = 0; j < row; j++)
        {
            result = 0; //매 연산마다 초기 result의 값을 0으로 설정한다.
            for (int k = 0; k < col; k++)
            {
                result += (matrix_a[i][k] * matrix_t[k][j]); //i와 j의 값을 고정하고 k가 0부터 col 전까지 1씩 증가할 때 result에 matrix_a[i][k] * matrix_t[k][j] 값을 누적하여 합한다.
            }
            if (matrix_axt[i][j] == result)
            {
                right_answer++; //matrix_axt의 i 번째 행 j 번째 열 성분에 대해서 행렬의 곱이 제대로 행해졌다면 right_answer을 1 증가한다.
            }
        }
    }
    print_matrix(matrix_axt, row, row); //matrix_axt는 call by reference, 두 개의 row는 call by value로 print_matrix를 호출한다.
    free_matrix(matrix_axt, row, row); //matrix_axt는 call by reference, 두 개의 row는 call by value로 free_matrix를 호출한다.
    matrix_axt = NULL; //메모리 해제 후 matrix_axt가 NULL을 가리키도록 한다.
    if (!matrix_axt && right_answer == row * row)
    {
        return 1; //matrix_axt의 메모리가 성공적으로 해제되어있고 모든 성분에 대해 값이 올바르면 1을 리턴한다.
    }
    return -1; //비정상 종료 시 -1을 리턴한다.
}
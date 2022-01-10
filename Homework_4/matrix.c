#include <stdio.h>
#include <stdlib.h>
#include <time.h>

/* Method Declaration */
int** create_matrix(int row, int col); //����� ���� �޸��Ҵ� ������� �����ϴ� �Լ� ����
void print_matrix(int** matrix, int row, int col); //����� ����ϴ� �Լ�
int free_matrix(int** matrix, int row, int col); //��Ŀ� �Ҵ��� �޸𸮸� �����ϴ� �Լ�
int fill_data(int** matrix, int row, int col); //����� ���а��� 0~19 ������ ���� �����ϰ� �ִ� �Լ�
int addition_matrix(int** matrix_a, int** matrix_b, int row, int col); //��� A + ��� B�� �����ϴ� �Լ�
int subtraction_matrix(int** matrix_a, int** matrix_b, int row, int col); //��� A - ��� B�� �����ϴ� �Լ�
int transpose_matrix(int** matrix, int** matrix_t, int row, int col); //��� A�� ��ġ��� T�� �����ϴ� �Լ�
int multiply_matrix(int** matrix_a, int** matrix_t, int row, int col); //��� A x ��� T�� �����ϴ� �Լ�

int main()
{

    char command; //��ɾ �Է¹��� ������ ���� char�� �����Ѵ�.
    printf("[----- �̽���  2020039075 -----]\n");

    int row, col; //��� ���� ���̸� �Է¹��� ������ ���� row�� col�� �����Ѵ�.
    srand(time(NULL)); //�ð��� seed ������ �־� ������ ���� �����Ѵ�.

    printf("Input row and col : ");
    scanf("%d %d", &row, &col); //��� ���� ���� �Է¹޾� ���� row�� col�� �����Ѵ�.
    int** matrix_a = create_matrix(row, col); //row�� col�� call by value�� create_matrix�� ȣ���Ͽ� matrix_a�� ���Ϲ��� �ּҰ��� �����Ѵ�. 
    int** matrix_b = create_matrix(row, col); //row�� col�� call by value�� create_matrix�� ȣ���Ͽ� matrix_b�� ���Ϲ��� �ּҰ��� �����Ѵ�.
    int** matrix_a_t = create_matrix(col, row); //row�� col�� call by value�� create_matrix�� ȣ���Ͽ� matrix_a_t�� ���Ϲ��� �ּҰ��� �����Ѵ�.

    printf("Matrix Created.\n");

    if (matrix_a == NULL || matrix_b == NULL) { return -1; } //��� A�� ��� B�� �������� ������(matrix_a�� matrix_b�� �޸𸮰� �Ҵ���� �ʾ��� ��) -1�� �����Ѵ�.

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
        scanf(" %c", &command); //��ɾ �Է¹޴´�.

        switch (command) {
        case 'z': case 'Z': //'z'�� 'Z'�� �Է¹޾��� ��
            printf("Matrix Initialized\n");
            fill_data(matrix_a, row, col); //matrix_a�� call by reference, row�� col�� call by value�� fill_data�� ȣ���Ѵ�.
            fill_data(matrix_b, row, col); //matrix_b�� call by reference, row�� col�� call by value�� fill_data�� ȣ���Ѵ�.
            break;
        case 'p': case 'P': //'p'�� 'P'�� �Է¹޾��� ��
            printf("Print matrix\n");
            printf("matrix_a\n");
            print_matrix(matrix_a, row, col); //matrix_a�� call by reference, row�� col�� call by value�� print_matrix�� ȣ���Ѵ�.
            printf("matrix_b\n");
            print_matrix(matrix_b, row, col); //matrix_b�� call by reference, row�� col�� call by value�� print_matrix�� ȣ���Ѵ�.
            break;
        case 'a': case 'A': //'a'�� 'A'�� �Է¹޾��� ��
            printf("Add two matrices\n");
            addition_matrix(matrix_a, matrix_b, row, col); //matrix_a�� matrix_b�� call by reference, row�� col�� call by value�� additional_matrix�� ȣ���Ѵ�.
            break;
        case 's': case 'S': //'s'�� 'S'�� �Է¹޾��� ��
            printf("Subtract two matrices \n");
            subtraction_matrix(matrix_a, matrix_b, row, col); //matrix_a�� matrix_b�� call by reference, row�� col�� call by value�� subtraction_matrix�� ȣ���Ѵ�.
            break;
        case 't': case 'T': //'t'�� 'T'�� �Է¹޾��� ��
            printf("Transpose matrix_a \n");
            printf("matrix_a\n");
            transpose_matrix(matrix_a, matrix_a_t, col, row); //matrix_a�� matrix_a_t�� call by reference, row�� col�� call by value�� transpose_matrix�� ȣ���Ѵ�.
            print_matrix(matrix_a_t, col, row); //matrix_a_t�� call by reference, row�� col�� call by value�� print_matrix�� ȣ���Ѵ�.
            break;
        case 'm': case 'M': //'m'�� 'M'�� �Է¹޾��� ��
            printf("Multiply matrix_a with transposed matrix_a \n");
            transpose_matrix(matrix_a, matrix_a_t, col, row); //matrix_a�� matrix_a_t�� call by reference, row�� col�� call by value�� transpose_matrix�� ȣ���Ѵ�.
            multiply_matrix(matrix_a, matrix_a_t, row, col); //matrix_a�� matrix_a_t�� call by reference, row�� col�� call by value�� multiply_matrix�� ȣ���Ѵ�.
            break;
        case 'q': case 'Q': //'q'�� 'Q'�� �Է¹޾��� ��
            printf("Free all matrices..\n");
            free_matrix(matrix_a_t, col, row); //matrix_a_t�� call by reference, row�� col�� call by value�� free_matrix�� ȣ���Ѵ�.
            free_matrix(matrix_a, row, col); //matrix_a�� call by reference, row�� col�� call by value�� free_matrix�� ȣ���Ѵ�.
            free_matrix(matrix_b, row, col); //matrix_b�� call by reference, row�� col�� call by value�� free_matrix�� ȣ���Ѵ�.
            break;
        default: //����� ���� �̿��� ���� �Է¹޾��� ��
            printf("\n       >>>>>   Concentration!!   <<<<<     \n");
            break;
        }

    } while (command != 'q' && command != 'Q'); //��� ���� �ڵ带 �ּ� �� �� ������ �� command�� 'q' Ȥ�� 'Q'�� �Է¹����� �ݺ����� �����Ѵ�.

    return 1;
}

/* create a 2d array whose size is row x col using malloc() */
int** create_matrix(int row, int col) //������ ���� row�� col 2���� �Ű������� �ϰ� ���� �������� �ּҰ��� �����ϴ� �Լ�
{
    /* check pre conditions */
    if (row <= 0 || col <= 0) {
        printf("Check the sizes of row and col!\n"); //row�� col�� ������ ���� ����� �������� ���� �� NULL�� �����Ѵ�.
        return NULL;
    }

    int** matrix = NULL; //���� ������ matrix�� �����ϰ� NULL�� ����Ű���� �Ѵ�.
    matrix = (int**)malloc(sizeof(int*) * row); //matrix�� �޸� �Ҵ��� �Ͽ� row��ŭ ���� �����Ѵ�. 
    for (int i = 0; i < row; i++)
    {
        matrix[i] = (int*)malloc(sizeof(int) * col); //i�� 0���� row ������ 1�� ������ �� matrix[i]�� �޸� �Ҵ��� �Ͽ� col��ŭ ���� �����Ѵ�.
    }

    /* check post conditions */
    if (matrix == NULL) {
        printf("Unexpected result. Try again.\n"); //row x col ũ���� 2���� �迭�� �������� ���Ͽ��� ��� NULL�� �����Ѵ�.
        return NULL;
    }
    return matrix; //matrix�� �ּҸ� �����Ѵ�.
}

/* print matrix whose size is row x col */
void print_matrix(int** matrix, int row, int col) //���� ������ matrix 1���� ������ ���� row�� col 2���� �Ű������� �ϰ� ���ϰ��� ���� �Լ�
{
    for (int i = 0; i < row; i++)
    {
        for (int j = 0; j < col; j++)
        {
            printf("%3d ", matrix[i][j]); //j�� 0���� col ������ 1�� �����ϸ鼭 matrix[i][j]�� ���� ����Ѵ�.
        }
        printf("\n"); //i�� 0���� row ������ 1�� �����ϸ鼭 ����� for ������ �ٹٲ��� ����Ѵ�.
    }
    printf("\n");
}


/* free memory allocated by create_matrix() */
int free_matrix(int** matrix, int row, int col) //���� ������ matrix 1���� ������ ���� row�� col 2���� �Ű������� �ϰ� ������ �����ϴ� �Լ�
{
    for (int i = 0; i < row; i++)
    {
        free(matrix[i]); //i�� 0���� row ������ 1�� �����ϸ鼭 matrix[i]�� �Ҵ�Ǿ��� �޸𸮸� �����Ѵ�. ��Ŀ��� ���� �ش��ϴ� �κ��̴�.
    }
    free(matrix); //matrix�� �Ҵ�Ǿ��� �޸𸮸� �����Ѵ�. ��Ŀ��� �࿡ �ش��ϴ� �κ��̴�.
    matrix = NULL; //matrix�� NULL�� ����Ű���� �Ѵ�.
    if (!matrix)
    {
        return 1; //matrix�� ���������� �޸� �����Ǿ��ٸ� 1�� �����Ѵ�.
    }
    return -1; //������ ���� �� -1�� �����Ѵ�.
}


/* assign random values to the given matrix */
int fill_data(int** matrix, int row, int col) //���� ������ matrix 1���� ������ ���� row�� col 2���� �Ű������� �ϰ� ������ �����ϴ� �Լ�
{
    int cnt = 0;
    for (int i = 0; i < row; i++)
    {
        for (int j = 0; j < col; j++)
        {
            matrix[i][j] = rand() % 20; //i�� 0���� row ������, j�� 0���� col ������ 1�� �����ϸ鼭 matrix[i][j]�� 0~19 ������ ������ ���� �����Ѵ�.
            cnt++; //matrix[i][j]�� ���� ����� �� cnt�� ���� 1 �����Ѵ�.
        }
    }
    if (cnt == row * col)
    {
        return 1; //matrix�� ��� ���а��� ���������� ������ ��� 1�� �����Ѵ�.
    }
    return -1; //������ ���� �� -1�� �����Ѵ�.
}

/* matrix_sum = matrix_a + matrix_b */
int addition_matrix(int** matrix_a, int** matrix_b, int row, int col) //���� ������ matrix_a, matrix_b 2���� ������ ���� row�� col 2���� �Ű������� �ϰ� ������ �����ϴ� �Լ�
{
    int** matrix_sum = create_matrix(row, col); //row�� col�� call by value�� create_matrix�� ȣ���Ͽ� matrix_sum�� ���Ϲ��� �ּҰ��� �����Ѵ�.
    int right_answer = 0;
    for (int i = 0; i < row; i++)
    {
        for (int j = 0; j < col; j++)
        {
            matrix_sum[i][j] = matrix_a[i][j] + matrix_b[i][j]; //i�� 0���� row ������, j�� 0���� col ������ 1�� �����ϸ鼭 matrix_sum[i][j]�� ��� A�� ��� B�� ���� ����� �����Ѵ�.
            if (matrix_sum[i][j] == matrix_a[i][j] + matrix_b[i][j])
            {
                right_answer++; //���� ����� �ùٸ��� right_answer�� ���� 1 �����Ѵ�.
            }
        }
    }
    print_matrix(matrix_sum, row, col); //matrix_sum�� call by reference, row�� col�� call by value�� print_matrix�� ȣ���Ѵ�.
    free_matrix(matrix_sum, row, col); //matrix_sum�� call by reference, row�� col�� call by value�� free_matrix�� ȣ���Ѵ�.
    matrix_sum = NULL; //�޸� ���� �� matrix_sum�� NULL�� ����Ű���� �Ѵ�.
    if (!matrix_sum && right_answer == row*col)
    {
        return 1; //matrix_sum�� �޸𸮰� ���������� �����Ǿ��ְ� ��� ���п� ���� ���� �ùٸ��� 1�� �����Ѵ�.
    }
    return -1; //������ ���� �� -1�� �����Ѵ�.
}

/* matrix_sub = matrix_a - matrix_b */
int subtraction_matrix(int** matrix_a, int** matrix_b, int row, int col) //���� ������ matrix_a, matrix_b 2���� ������ ���� row�� col 2���� �Ű������� �ϰ� ������ �����ϴ� �Լ�
{
    int** matrix_sub = create_matrix(row, col); //row�� col�� call by value�� create_matrix�� ȣ���Ͽ� matrix_sub�� ���Ϲ��� �ּҰ��� �����Ѵ�.
    int right_answer = 0;
    for (int i = 0; i < row; i++)
    {
        for (int j = 0; j < col; j++)
        {
            matrix_sub[i][j] = matrix_a[i][j] - matrix_b[i][j]; //i�� 0���� row ������, j�� 0���� col ������ 1�� �����ϸ鼭 matrix_sum[i][j]�� ��� A�� ��� B�� ���� ����� �����Ѵ�.
            if (matrix_sub[i][j] == matrix_a[i][j] - matrix_b[i][j])
            {
                right_answer++; //���� ����� �ùٸ��� right_answer�� ���� 1 �����Ѵ�.
            }
        }
    }
    print_matrix(matrix_sub, row, col); //matrix_sub�� call by reference, row�� col�� call by value�� print_matrix�� ȣ���Ѵ�.
    free_matrix(matrix_sub, row, col); //matrix_sub�� call by reference, row�� col�� call by value�� free_matrix�� ȣ���Ѵ�.
    matrix_sub = NULL; //�޸� ���� �� matrix_sub�� NULL�� ����Ű���� �Ѵ�.
    if (!matrix_sub && right_answer == row * col) 
    {
        return 1; //matrix_sub�� �޸𸮰� ���������� �����Ǿ��ְ� ��� ���п� ���� ���� �ùٸ��� 1�� �����Ѵ�. 
    }
    return -1; //������ ���� �� -1�� �����Ѵ�.
}

/* transpose the matrix to matrix_t */
int transpose_matrix(int** matrix, int** matrix_t, int row, int col) //���� ������ matrix, matrix_t 2���� ������ ���� row�� col 2���� �Ű������� �ϰ� ������ �����ϴ� �Լ�
{
    int right_answer = 0;
    for (int i = 0; i < row; i++)
    {
        for (int j = 0; j < col; j++)
        {
            matrix_t[i][j] = matrix[j][i]; //i�� 0���� row ������, j�� 0���� col ������ 1�� �����ϸ鼭 ���� ����� ��� ���� �ٲ� ���а��� ��ġ��Ŀ� �����Ѵ�.
            if (matrix_t[i][j] == matrix[j][i])
            {
                right_answer++; //��ġ����� ���а��� �ùٸ��� right_answer�� ���� 1 �����Ѵ�.
            }
        }
    }
    if (right_answer == row * col)
    {
        return 1; //��ġ����� ��� ���п� ���� ���� �ùٸ��� 1�� �����Ѵ�.
    }
    return -1; //������ ���� �� -1�� �����Ѵ�.
}

/* matrix_axt = matrix_a x matrix_t */
int multiply_matrix(int** matrix_a, int** matrix_t, int row, int col) //���� ������ matrix_a, matrix_t 2���� ������ ���� row�� col 2���� �Ű������� �ϰ� ������ �����ϴ� �Լ�
{
    int** matrix_axt = create_matrix(row, row); //�� ���� row�� call by value�� create_matrix�� ȣ���Ͽ� matrix_axt�� ���Ϲ��� �ּҰ��� �����Ѵ�.
    int i, j, result, right_answer = 0;
    for (i = 0; i < row; i++)
    {
        for (j = 0; j < row; j++)
        {
            result = 0; //�� ���긶�� �ʱ� result�� ���� 0���� �����Ѵ�.
            for (int k = 0; k < col; k++)
            {
                result += (matrix_a[i][k] * matrix_t[k][j]); //i�� j�� ���� �����ϰ� k�� 0���� col ������ 1�� ������ �� result�� matrix_a[i][k] * matrix_t[k][j] ���� �����Ͽ� ���Ѵ�.
            }
            matrix_axt[i][j] = result; //result�� �������� matrix_axt[i][j]�� �����Ѵ�.
        }
    }
    //���갪�� �����ϱ� ���� ����� ������ �ٽ� ���Ѵ�.
    for (i = 0; i < row; i++)
    {
        for (j = 0; j < row; j++)
        {
            result = 0; //�� ���긶�� �ʱ� result�� ���� 0���� �����Ѵ�.
            for (int k = 0; k < col; k++)
            {
                result += (matrix_a[i][k] * matrix_t[k][j]); //i�� j�� ���� �����ϰ� k�� 0���� col ������ 1�� ������ �� result�� matrix_a[i][k] * matrix_t[k][j] ���� �����Ͽ� ���Ѵ�.
            }
            if (matrix_axt[i][j] == result)
            {
                right_answer++; //matrix_axt�� i ��° �� j ��° �� ���п� ���ؼ� ����� ���� ����� �������ٸ� right_answer�� 1 �����Ѵ�.
            }
        }
    }
    print_matrix(matrix_axt, row, row); //matrix_axt�� call by reference, �� ���� row�� call by value�� print_matrix�� ȣ���Ѵ�.
    free_matrix(matrix_axt, row, row); //matrix_axt�� call by reference, �� ���� row�� call by value�� free_matrix�� ȣ���Ѵ�.
    matrix_axt = NULL; //�޸� ���� �� matrix_axt�� NULL�� ����Ű���� �Ѵ�.
    if (!matrix_axt && right_answer == row * row)
    {
        return 1; //matrix_axt�� �޸𸮰� ���������� �����Ǿ��ְ� ��� ���п� ���� ���� �ùٸ��� 1�� �����Ѵ�.
    }
    return -1; //������ ���� �� -1�� �����Ѵ�.
}
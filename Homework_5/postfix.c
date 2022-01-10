/*
 * postfix.c
 *
 *  Data Structures, Homework #5
 *  Department of Computer Science at Chungbuk National University
 */

#include<stdio.h>
#include<stdlib.h>
#include<string.h>

#define MAX_STACK_SIZE 10 //MAX_STACK_SIZE��� �̸����� 10�� ��ũ�� ����
#define MAX_EXPRESSION_SIZE 20 //MAX_EXPRESSION_SIZE��� �̸����� 20�� ��ũ�� ����

 /* stack ������ �켱����, lparen = 0 ���� ���� */
typedef enum {
	lparen = 0,  /* ( ���� ��ȣ */
	rparen = 9,  /* ) ������ ��ȣ */
	times = 7,   /* * ���� */
	divide = 6,  /* / ������ */
	plus = 5,    /* + ���� */
	minus = 4,   /* - ���� */
	operand = 1 /* �ǿ����� */
} precedence; //����ü enum�� precedence�� ������

char infixExp[MAX_EXPRESSION_SIZE];   	/* infix expression�� �����ϴ� �迭 */
char postfixExp[MAX_EXPRESSION_SIZE];	/* postfix�� ����� ���ڿ��� �����ϴ� �迭 */
char postfixStack[MAX_STACK_SIZE];	/* postfix�� ��ȯ�� ���� �ʿ��� ���� */
int evalStack[MAX_STACK_SIZE];		/* ����� ���� �ʿ��� ���� */

int postfixStackTop = -1;  /* postfixStack�� top */
int evalStackTop = -1;	   /* evalStack��top */

int evalResult = 0;	   /* ��� ����� ���� */

void postfixPush(char x); //���� �ϳ��� ���޹޾� postfixStack�� �����ϴ� �Լ� ����
char postfixPop(); //postfixStack�� top�� ����� ���� �����ϴ� �Լ� ����
void evalPush(int x); //evalStack�� x�� ���� �����ϴ� �Լ� ����
int evalPop(); //evalStack�� top�� ����� ���� �����ϴ� �Լ� ����
void getInfix(); //������ ���� ǥ������� �Է¹޾� infixExp�� �����ϴ� �Լ� ����
precedence getToken(char symbol); //�Է¹��� ������ Ÿ���� �˻��ϴ� �Լ� ����
precedence getPriority(char x); //�Է¹��� ������ �켱����(isp)�� �˻��ϴ� �Լ� ����
void charCat(char* c); //���� �ϳ��� ���޹޾� postfixExp�� �����ϴ� �Լ� ����
void toPostfix(); //infixExp�� ���� ǥ������� ����� ������ postfixStack�� �̿��Ͽ� ���� ǥ������� �ٲٴ� �Լ� ����
void debug(); //���� ����� ����� ����ϴ� �Լ� ����
void reset(); //���� ����� ����� �ʱ�ȭ�ϴ� �Լ� ����
void evaluation(); //postfixExp�� evalStack�� �̿��Ͽ� ������ �����ϴ� �Լ� ����

int main()
{
	char command; //��ɾ �Է¹޾� ������ char�� ���� command ����

	printf("----- [�̽���] [2020039075] -----\n");

	do {
		printf("----------------------------------------------------------------\n");
		printf("               Infix to Postfix, then Evaluation               \n");
		printf("----------------------------------------------------------------\n");
		printf(" Infix=i,   Postfix=p,  Eval=e,   Debug=d,   Reset=r,   Quit=q \n");
		printf("----------------------------------------------------------------\n");

		printf("Command = ");
		scanf(" %c", &command); //���ڸ� �Է¹޾� command�� ����

		switch (command) {
		case 'i': case 'I': //command�� i�� I�� ��
			getInfix(); //���� ǥ���(infix notation)���� ����ڰ� ���� �Է�
			break;
		case 'p': case 'P': //command�� p�� P�� ��
			toPostfix(); //�Է¹��� ���Ŀ� ���� ���� ǥ���(postfix notation)���� ��ȯ
			break;
		case 'e': case 'E': //command�� e�� E�� ��
			evaluation(); //���� ǥ������� ��ȯ�� ���Ŀ� ���Ͽ� ����
			break;
		case 'd': case 'D': //command�� d�� D�� ��
			debug(); //������� ����� ����� ���
			break;
		case 'r': case 'R': //command�� r�̳� R�� ��
			reset(); //������� ����� ����� ����
			break;
		case 'q': case 'Q': //command�� q�� Q�� ��
			break; //�޴� ��� ����
		default: //command�� ��� �̿��� ������ ��
			printf("\n       >>>>>   Concentration!!   <<<<<     \n"); //���� �޼��� ���
			break;
		}

	} while (command != 'q' && command != 'Q'); //command�� 'q'�� 'Q'�� �� ���α׷� ����

	return 1; //1�� �����ϰ� ���α׷� ����
}

void postfixPush(char x) 
{
	postfixStack[++postfixStackTop] = x; //postfixStack���� Top�� 1 ������Ų �ڸ��� x ������ push
}

char postfixPop() 
{
	char x; //postfixStack���κ��� ���ڸ� ���� ������ char�� ���� ����
	if (postfixStackTop == -1)
		return '\0'; //postfixStack���� ��ȯ�ؾ��ϴ� �����Ͱ� �������� �ʾ� '\0' ����
	else {
		x = postfixStack[postfixStackTop--]; //postfixStack���� Top�� ����Ű�� ���� �����͸� x�� �����ϰ� Top�� 1 ����
	}
	return x; //postfixStack�� ������ pop
}

void evalPush(int x) 
{
	evalStack[++evalStackTop] = x; //evalStack���� Top�� 1 ������Ų �ڸ��� x ������ push
}

int evalPop() 
{
	if (evalStackTop == -1)
		return -1; //evalStack���� ��ȯ�ؾ��ϴ� �����Ͱ� �������� �ʾ� '\0' ����
	else
		return evalStack[evalStackTop--]; //evalStack���� Top�� ����Ű�� ���� �����͸� pop�ϰ� Top�� 1 ����
}

/**
 * infix expression�� �Է¹޴´�.
 * infixExp���� �Էµ� ���� �����Ѵ�.
 */
void getInfix() //�Ű������� ���ϰ��� ���� �Լ�
{
	printf("Type the expression >>> ");
	scanf("%s", infixExp); //����ڿ��� ���� ǥ������� ���� �Է¹���
}

precedence getToken(char symbol) 
{
	switch (symbol) {
	case '(': return lparen; //symbol�� '('�� �� lparen(�켱����: 0) ����
	case ')': return rparen; //symbol�� ')'�� �� rparen(�켱����: 9) ����
	case '+': return plus; //symbol�� '+'�� �� plus(�켱����: 5) ����
	case '-': return minus; //symbol�� '-'�� �� minus(�켱����: 4) ����
	case '/': return divide; //symbol�� '/'�� �� divide(�켱����: 6) ����
	case '*': return times; //symbol�� '*'�� �� times(�켱����: 7) ����
	default: return operand; //symbol�� ��� �̿��� ������ ��, �� �ǿ������� �� operand(�켱����: 1) ����
	}
}

precedence getPriority(char x) 
{
	return getToken(x); //x�� ���ڷ� getToken �Լ� ȣ���� �� getPriority �Լ� ����
	//isp�� ���� �� �������� �켱���� �ο�
}

/**
 * ���� �ϳ��� ���޹޾�, postfixExp�� �߰�
 */
void charCat(char* c) 
{
	if (postfixExp == '\0')
		strncpy(postfixExp, c, 1); //postfixExp�� �����Ͱ� �������� ������ c�� ���� �ϳ��� postfixExp�� ����
	else
		strncat(postfixExp, c, 1); //postfixExp�� c�� ���� �ϳ��� �̾� ����
}

/**
 * infixExp�� ���ڸ� �ϳ��� �о�鼭 stack�� �̿��Ͽ� postfix�� �����Ѵ�.
 * ����� postfix�� postFixExp�� ����ȴ�.
 */
void toPostfix() 
{
	/* infixExp�� ���� �ϳ����� �б� ���� ������ */
	char* exp = infixExp; 
	char x; /* ���� �ϳ��� �ӽ÷� �����ϱ� ���� ���� */

	/* exp�� �������Ѱ��鼭, ���ڸ� �а� postfix�� ���� */
	while (*exp != '\0')
	{
		switch(getToken(*exp))
		{
			case operand: //*exp�� �ǿ������� ��
				charCat(exp); //�ش� �����ڸ� postfixExp�� ����
				break;
			case rparen: //*exp�� ')' �� ��
				while (getToken(postfixStack[postfixStackTop]) != lparen)
				//postfixStack���� Top�� '('�� �ִ� ���� ����Ű�� ������ �ݺ��� ����
				{
					x = postfixPop(); //postfixStack���� Top�� ����Ű�� ���� �����͸� pop�Ͽ� x�� ����
					charCat(&x); //x�� postfixExp�� ����
				}
				postfixPop(); //���� ��ȣ ������
				break;
			case lparen: //*exp�� '('�� ��
				postfixPush(*exp); //'('�� postfixStack�� push
				break;
			default: //*exp�� '+', '-', '*', '/' �� �ϳ��� ��
				while (postfixStackTop != -1 && (getPriority(*exp) <= getPriority(postfixStack[postfixStackTop]))) 
				//postfixStack�� ������� �ʰ� postfixStack���� Top�� ����Ű�� ���� �켱������ *exp�� �켱�������� ���ų� ���� �� �ݺ��� ����
				{
					x = postfixPop(); //postfixStack���� Top�� ����Ű�� ���� �����͸� pop�Ͽ� x�� ����
					charCat(&x); //x�� postfixExp�� ����
				}
				postfixPush(*exp);
				//postfixStack�� ����ְų� postfixStack���� Top�� ����Ű�� ���� �켱������ *exp�� �켱�������� ���� ��*exp�� postfixStack�� push
				break;
		}
		exp++; //exp�� ������Ű�鼭 infixExp�� ����� ���ڸ� �ϳ��� �˻�
	}
	while (postfixStackTop != -1) //postfixStack�� ��� �����Ͱ� pop�Ǳ� ������ �ݺ��� ����
	{
		x = postfixPop(); //postfixStack���� Top�� ����Ű�� ���� �����͸� pop�Ͽ� x�� ����
		charCat(&x); //x�� postfixExp�� ����
	}

}
void debug()
{
	printf("\n---DEBUG\n"); 
	printf("infixExp =  %s\n", infixExp); //���� ǥ����� ���� ���
	printf("postExp =  %s\n", postfixExp); //���� ǥ����� ���� ���
	printf("eval result = %d\n", evalResult); //���� ��� ���

	printf("postfixStack : ");
	for (int i = 0; i < MAX_STACK_SIZE; i++)
		printf("%c  ", postfixStack[i]); //postfixStack �� �����ϴ� ��� �� ���

	printf("\n");

}

void reset()
{
	infixExp[0] = '\0'; //infixExp�� �� �ʱ�ȭ
	postfixExp[0] = '\0'; //postfixExp�� �� �ʱ�ȭ

	for (int i = 0; i < MAX_STACK_SIZE; i++)
		postfixStack[i] = '\0'; //postfixStack �� �����ϴ� ��� �� �ʱ�ȭ

	postfixStackTop = -1; //postfixStack������ Top�� -1�� ����Ű�� �Ͽ� postfixStack�� �� �������� ����
	evalStackTop = -1; //evalStack������ Top�� -1�� ����Ű�� �Ͽ� evalStack�� �� �������� ����
	evalResult = 0; //evalResult�� �� �ʱ�ȭ
}

void evaluation()
{
	/* postfixExp, evalStack�� �̿��� ��� */
	precedence token; //postfixExp ���� ���ڸ� �˻��ϱ� ���� precedence��(������) ���� token ����
	char* exp = postfixExp; //postfixExp�� ���ڸ� �ϳ��� �б� ���� char�� ������ exp ����
	int op1, op2; //�����ڸ� �����ϱ� ���� int�� ���� op1, op2 ����
	while (*exp != '\0') //postfixExp�� ��� ���ڸ� ���� ������ exp�� ������Ű�� �ݺ��� ����
	{
		token = getToken(*exp); //getToken �Լ��� ȣ���Ͽ� *exp�� ���� �˻��� ���� token�� ����
		if (token == operand) 
		{
			evalPush(*exp - '0'); //token�� �ǿ������� ��(*exp�� �ǿ�����) evalStack�� ����� push�ϵ��� (*exp�� ASCII �ڵ尪)-('0'�� ASCII �ڵ尪)�� evalPush�� �Է�
		}
		else //token�� �����ڶ��
		{
			op2 = evalPop(); //evalStack���� Top�� ����Ű�� ���� �ǿ����ڸ� op2�� ����
			op1 = evalPop(); //evalStack���� Top�� ����Ű�� ���� �ǿ����ڸ� op1�� ���� (�̶��� Top�� op2�� ������ ���� Top���� 1 ���� ���� ����Ŵ)
			switch (token)
			{
			case times: //token�� times�� �� (*exp=='*')
				evalPush(op1 * op2); //op1�� op2�� ���� ����� evalStack�� push
				break;
			case divide: //token�� divide�� �� (*exp=='/')
				evalPush(op1 / op2); //op1�� op2�� ���� ����� evalStack�� push
				break;
			case plus: //token�� plus�� �� (*exp=='+')
				evalPush(op1 + op2); //op1�� op2�� ���� ����� evalStack�� push
				break;
			case minus: //token�� minus�� �� (*exp=='-')
				evalPush(op1 - op2); //op1�� op2�� �� ����� evalStack�� push
				break;
			}
		}
		exp++; //exp�� ������Ű�鼭 postfixExp�� ����� ���ڸ� �ϳ��� �˻�
	}
	evalResult = evalStack[0]; //evalResult�� ���� ��갪�� evalStack[0] ����
}
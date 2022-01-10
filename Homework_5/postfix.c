/*
 * postfix.c
 *
 *  Data Structures, Homework #5
 *  Department of Computer Science at Chungbuk National University
 */

#include<stdio.h>
#include<stdlib.h>
#include<string.h>

#define MAX_STACK_SIZE 10 //MAX_STACK_SIZE라는 이름으로 10의 매크로 정의
#define MAX_EXPRESSION_SIZE 20 //MAX_EXPRESSION_SIZE라는 이름으로 20의 매크로 정의

 /* stack 내에서 우선순위, lparen = 0 가장 낮음 */
typedef enum {
	lparen = 0,  /* ( 왼쪽 괄호 */
	rparen = 9,  /* ) 오른쪽 괄호 */
	times = 7,   /* * 곱셈 */
	divide = 6,  /* / 나눗셈 */
	plus = 5,    /* + 덧셈 */
	minus = 4,   /* - 뺄셈 */
	operand = 1 /* 피연산자 */
} precedence; //구조체 enum을 precedence로 재정의

char infixExp[MAX_EXPRESSION_SIZE];   	/* infix expression을 저장하는 배열 */
char postfixExp[MAX_EXPRESSION_SIZE];	/* postfix로 변경된 문자열을 저장하는 배열 */
char postfixStack[MAX_STACK_SIZE];	/* postfix로 변환을 위해 필요한 스택 */
int evalStack[MAX_STACK_SIZE];		/* 계산을 위해 필요한 스택 */

int postfixStackTop = -1;  /* postfixStack용 top */
int evalStackTop = -1;	   /* evalStack용top */

int evalResult = 0;	   /* 계산 결과를 저장 */

void postfixPush(char x); //문자 하나를 전달받아 postfixStack에 저장하는 함수 선언
char postfixPop(); //postfixStack의 top에 저장된 값을 리턴하는 함수 선언
void evalPush(int x); //evalStack에 x의 값을 저장하는 함수 선언
int evalPop(); //evalStack의 top에 저장된 값을 리턴하는 함수 선언
void getInfix(); //수식을 중위 표기법으로 입력받아 infixExp에 저장하는 함수 선언
precedence getToken(char symbol); //입력받은 문자의 타입을 검사하는 함수 선언
precedence getPriority(char x); //입력받은 문자의 우선순위(isp)를 검사하는 함수 선언
void charCat(char* c); //문자 하나를 전달받아 postfixExp에 저장하는 함수 선언
void toPostfix(); //infixExp에 중위 표기법으로 저장된 수식을 postfixStack을 이용하여 후위 표기법으로 바꾸는 함수 선언
void debug(); //현재 진행된 결과를 출력하는 함수 선언
void reset(); //현재 진행된 결과를 초기화하는 함수 선언
void evaluation(); //postfixExp와 evalStack을 이용하여 수식을 연산하는 함수 선언

int main()
{
	char command; //명령어를 입력받아 저장할 char형 변수 command 선언

	printf("----- [이승현] [2020039075] -----\n");

	do {
		printf("----------------------------------------------------------------\n");
		printf("               Infix to Postfix, then Evaluation               \n");
		printf("----------------------------------------------------------------\n");
		printf(" Infix=i,   Postfix=p,  Eval=e,   Debug=d,   Reset=r,   Quit=q \n");
		printf("----------------------------------------------------------------\n");

		printf("Command = ");
		scanf(" %c", &command); //문자를 입력받아 command에 저장

		switch (command) {
		case 'i': case 'I': //command가 i나 I일 때
			getInfix(); //중위 표기법(infix notation)으로 사용자가 수식 입력
			break;
		case 'p': case 'P': //command가 p나 P일 때
			toPostfix(); //입력받은 수식에 대해 후위 표기법(postfix notation)으로 변환
			break;
		case 'e': case 'E': //command가 e나 E일 때
			evaluation(); //후위 표기법으로 변환된 수식에 대하여 연산
			break;
		case 'd': case 'D': //command가 d나 D일 때
			debug(); //현재까지 진행된 결과값 출력
			break;
		case 'r': case 'R': //command가 r이나 R일 때
			reset(); //현재까지 진행된 결과값 리셋
			break;
		case 'q': case 'Q': //command가 q나 Q일 때
			break; //메뉴 출력 종료
		default: //command가 상단 이외의 문자일 때
			printf("\n       >>>>>   Concentration!!   <<<<<     \n"); //오류 메세지 출력
			break;
		}

	} while (command != 'q' && command != 'Q'); //command가 'q'나 'Q'일 때 프로그램 종료

	return 1; //1을 리턴하고 프로그램 종료
}

void postfixPush(char x) 
{
	postfixStack[++postfixStackTop] = x; //postfixStack에서 Top을 1 증가시킨 자리에 x 데이터 push
}

char postfixPop() 
{
	char x; //postfixStack으로부터 문자를 받을 임의의 char형 변수 선언
	if (postfixStackTop == -1)
		return '\0'; //postfixStack에서 반환해야하는 데이터가 존재하지 않아 '\0' 리턴
	else {
		x = postfixStack[postfixStackTop--]; //postfixStack에서 Top이 가리키는 곳의 데이터를 x에 저장하고 Top을 1 감소
	}
	return x; //postfixStack의 데이터 pop
}

void evalPush(int x) 
{
	evalStack[++evalStackTop] = x; //evalStack에서 Top을 1 증가시킨 자리에 x 데이터 push
}

int evalPop() 
{
	if (evalStackTop == -1)
		return -1; //evalStack에서 반환해야하는 데이터가 존재하지 않아 '\0' 리턴
	else
		return evalStack[evalStackTop--]; //evalStack에서 Top이 가리키는 곳의 데이터를 pop하고 Top을 1 감소
}

/**
 * infix expression을 입력받는다.
 * infixExp에는 입력된 값을 저장한다.
 */
void getInfix() //매개변수와 리턴값이 없는 함수
{
	printf("Type the expression >>> ");
	scanf("%s", infixExp); //사용자에게 중위 표기법으로 수식 입력받음
}

precedence getToken(char symbol) 
{
	switch (symbol) {
	case '(': return lparen; //symbol이 '('일 때 lparen(우선순위: 0) 리턴
	case ')': return rparen; //symbol이 ')'일 때 rparen(우선순위: 9) 리턴
	case '+': return plus; //symbol이 '+'일 때 plus(우선순위: 5) 리턴
	case '-': return minus; //symbol이 '-'일 때 minus(우선순위: 4) 리턴
	case '/': return divide; //symbol이 '/'일 때 divide(우선순위: 6) 리턴
	case '*': return times; //symbol이 '*'일 때 times(우선순위: 7) 리턴
	default: return operand; //symbol이 상단 이외의 문자일 때, 즉 피연산자일 때 operand(우선순위: 1) 리턴
	}
}

precedence getPriority(char x) 
{
	return getToken(x); //x를 인자로 getToken 함수 호출한 후 getPriority 함수 종료
	//isp에 따라 각 데이터의 우선순위 부여
}

/**
 * 문자 하나를 전달받아, postfixExp에 추가
 */
void charCat(char* c) 
{
	if (postfixExp == '\0')
		strncpy(postfixExp, c, 1); //postfixExp에 데이터가 존재하지 않으면 c의 문자 하나를 postfixExp에 복사
	else
		strncat(postfixExp, c, 1); //postfixExp에 c의 문자 하나를 이어 붙임
}

/**
 * infixExp의 문자를 하나씩 읽어가면서 stack을 이용하여 postfix로 변경한다.
 * 변경된 postfix는 postFixExp에 저장된다.
 */
void toPostfix() 
{
	/* infixExp의 문자 하나씩을 읽기 위한 포인터 */
	char* exp = infixExp; 
	char x; /* 문자 하나를 임시로 저장하기 위한 변수 */

	/* exp을 증가시켜가면서, 문자를 읽고 postfix로 변경 */
	while (*exp != '\0')
	{
		switch(getToken(*exp))
		{
			case operand: //*exp가 피연산자일 때
				charCat(exp); //해당 연산자를 postfixExp에 저장
				break;
			case rparen: //*exp가 ')' 일 때
				while (getToken(postfixStack[postfixStackTop]) != lparen)
				//postfixStack에서 Top이 '('가 있는 곳을 가리키기 전까지 반복문 수행
				{
					x = postfixPop(); //postfixStack에서 Top이 가리키는 곳의 데이터를 pop하여 x에 저장
					charCat(&x); //x를 postfixExp에 저장
				}
				postfixPop(); //왼쪽 괄호 버리기
				break;
			case lparen: //*exp가 '('일 때
				postfixPush(*exp); //'('를 postfixStack에 push
				break;
			default: //*exp가 '+', '-', '*', '/' 중 하나일 때
				while (postfixStackTop != -1 && (getPriority(*exp) <= getPriority(postfixStack[postfixStackTop]))) 
				//postfixStack이 비어있지 않고 postfixStack에서 Top이 가리키는 곳의 우선순위가 *exp의 우선순위보다 높거나 같을 때 반복문 수행
				{
					x = postfixPop(); //postfixStack에서 Top이 가리키는 곳의 데이터를 pop하여 x에 저장
					charCat(&x); //x를 postfixExp에 저장
				}
				postfixPush(*exp);
				//postfixStack이 비어있거나 postfixStack에서 Top이 가리키는 곳의 우선순위가 *exp의 우선순위보다 낮을 때*exp를 postfixStack에 push
				break;
		}
		exp++; //exp를 증가시키면서 infixExp에 저장된 문자를 하나씩 검사
	}
	while (postfixStackTop != -1) //postfixStack의 모든 데이터가 pop되기 전까지 반복문 수행
	{
		x = postfixPop(); //postfixStack에서 Top이 가리키는 곳의 데이터를 pop하여 x에 저장
		charCat(&x); //x를 postfixExp에 저장
	}

}
void debug()
{
	printf("\n---DEBUG\n"); 
	printf("infixExp =  %s\n", infixExp); //중위 표기법의 수식 출력
	printf("postExp =  %s\n", postfixExp); //후위 표기법의 수식 출력
	printf("eval result = %d\n", evalResult); //연산 결과 출력

	printf("postfixStack : ");
	for (int i = 0; i < MAX_STACK_SIZE; i++)
		printf("%c  ", postfixStack[i]); //postfixStack 내 존재하는 모든 값 출력

	printf("\n");

}

void reset()
{
	infixExp[0] = '\0'; //infixExp의 값 초기화
	postfixExp[0] = '\0'; //postfixExp의 값 초기화

	for (int i = 0; i < MAX_STACK_SIZE; i++)
		postfixStack[i] = '\0'; //postfixStack 내 존재하는 모든 값 초기화

	postfixStackTop = -1; //postfixStack에서의 Top이 -1을 가리키게 하여 postfixStack을 빈 공간으로 설정
	evalStackTop = -1; //evalStack에서의 Top이 -1을 가리키게 하여 evalStack을 빈 공간으로 설정
	evalResult = 0; //evalResult의 값 초기화
}

void evaluation()
{
	/* postfixExp, evalStack을 이용한 계산 */
	precedence token; //postfixExp 내의 문자를 검사하기 위해 precedence형(열거형) 변수 token 선언
	char* exp = postfixExp; //postfixExp의 문자를 하나씩 읽기 위해 char형 포인터 exp 선언
	int op1, op2; //연산자를 저장하기 위한 int형 변수 op1, op2 선언
	while (*exp != '\0') //postfixExp의 모든 문자를 읽을 때까지 exp를 증가시키며 반복문 수행
	{
		token = getToken(*exp); //getToken 함수를 호출하여 *exp의 값을 검사한 것을 token에 저장
		if (token == operand) 
		{
			evalPush(*exp - '0'); //token이 피연산자일 때(*exp가 피연산자) evalStack에 상수를 push하도록 (*exp의 ASCII 코드값)-('0'의 ASCII 코드값)을 evalPush에 입력
		}
		else //token이 연산자라면
		{
			op2 = evalPop(); //evalStack에서 Top이 가리키는 곳의 피연산자를 op2에 저장
			op1 = evalPop(); //evalStack에서 Top이 가리키는 곳의 피연산자를 op1에 저장 (이때의 Top은 op2에 저장할 때의 Top보다 1 작은 곳을 가리킴)
			switch (token)
			{
			case times: //token이 times일 때 (*exp=='*')
				evalPush(op1 * op2); //op1과 op2를 곱한 결과를 evalStack에 push
				break;
			case divide: //token이 divide일 때 (*exp=='/')
				evalPush(op1 / op2); //op1을 op2로 나눈 결과를 evalStack에 push
				break;
			case plus: //token이 plus일 때 (*exp=='+')
				evalPush(op1 + op2); //op1과 op2를 더한 결과를 evalStack에 push
				break;
			case minus: //token이 minus일 때 (*exp=='-')
				evalPush(op1 - op2); //op1을 op2로 뺀 결과를 evalStack에 push
				break;
			}
		}
		exp++; //exp를 증가시키면서 postfixExp에 저장된 문자를 하나씩 검사
	}
	evalResult = evalStack[0]; //evalResult에 최종 계산값인 evalStack[0] 저장
}
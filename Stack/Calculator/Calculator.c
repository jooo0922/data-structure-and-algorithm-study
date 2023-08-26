#include "Calculator.h"

// 피연산자 토큰 생성에 사용할 십진수 문자들이 담긴 배열 선언
// 배열은 선언 및 초기화 시점에 요소를 한방에 지정할 땐, {} 로 지정해주면 됨.
// 마지막에 추가한 '.' 은 피연산자가 정수가 아닌 실수일 경우에 표현하기 위한 것이겠군.
char NUMBER[] = { '0', '1', '2', '3', '4', '5', '6', '7', '8', '9', '.' };

// 토큰이 피연산자인지 검사
int IsNumber(char Cipher)
{

}

// 다음 토큰에 대한 중위표기식 문자열 상의 인덱스를 반환, 다음 토큰 및 토큰 타입 업데이트
unsigned int GetNextToken(char* Expression, char* Token, int* TYPE)
{

}

// 각 연산자 우선순위를 정수형으로 반환
int GetPriority(char Operator, int InStack)
{

}

// 스택의 최상위 노드 연산자 토큰과 현재 연산자 토큰의 우선순위 비교
int IsPrior(char OperatorInStack, char OperatorInToken)
{

}

// 중위표기식 > 후위표기식으로 변환
void GetPostfix(char* InfixExpression, char* PostfixExpression)
{

}

// 변환된 후위표기식을 계산하여 결과값 반환
double Calculate(char* PostfixExpression)
{

}

int main()
{
    return 0;
}
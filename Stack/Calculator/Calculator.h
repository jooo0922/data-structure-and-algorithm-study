#ifndef CALCULATOR_H
#define CALCULATOR_H
/*
	여기서 사용된 #ifndef ~ #endif 전처리기는
	헤더파일인 ArrayStack.h 의 헤더가드를 처리해주는 방법 중 하나였지?

	cpp-study > TBCppStudy > Chapter1_12 > add.h 필기 참고!
*/

#include <stdlib.h>
#include "LinkedListStack.h" // 링크드리스트 기반 스택으로 중위표현식 계산기 구현

// 각 토큰 타입을 enum 으로 선언
// c 언어에서 enum 에는 정수형 외에 단일 문자 타입으로도 초기화할 수 있음.
typedef enum
{
	LEFT_PARENTHESIS = '(', 
	RIGHT_PARENTHESIS =')',
	PLUS = '+',
	MINUS = '-',
	MULTIPLY = '*',
	DIVIDE = '/',
	SPACE = ' ',
	OPERAND
} SYMBOL; // 토큰 이넘의 별명을 SYMBOL 로 선언

// 함수 원형 선언
int IsNumber(char Cipher); // 토큰이 피연산자인지 검사
unsigned int GetNextToken(char* Expression, char* Token, int* Type); // 다음 토큰에 대한 중위표기식 문자열 상의 인덱스를 반환, 다음 토큰 및 토큰 타입 업데이트
int IsPrior(char Operator1, char Operator2); // 두 연산자 토큰의 우선순위 비교
void GetPostFix(char* InfixExpression, char* PostfixExpression); // 중위표기식 > 후위표기식으로 변환
double Calculate(char* PostrixExpression); // 변환된 후위표기식을 계산하여 결과값 반환

#endif // !CALCULATOR_H


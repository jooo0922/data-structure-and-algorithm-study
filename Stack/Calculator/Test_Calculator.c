#include <stdio.h>
#include <string.h>
#include "Calculator.h"

/*
	scanf(), strcat(), gcvt() 함수 사용 시,
	버퍼 오버플로우 에러가 계속 발생해서 
	대체하는 함수(버퍼 사이즈를 인자로 전달하는 함수들)를 사용하려 했는데,
	
	대체하는 함수를 사용할 때마다 에러가 계속 발생함.

	그래서 그냥 기존 함수를 쓰되,
	현재 Calculator 프로젝트의
	SDL 검사를 꺼버리면 에러 없이 컴파일됨.
*/

int main()
{
	// 중위표기식과 후위표기식 문자열을 각각 저장할 문자열 버퍼 배열 변수 선언
	// 각각 넉넉하게 100자까지 저장할 수 있도록 선언
	char InfixExpression[100];
	char PostfixExpression[100];

	double Result = 0.0; // 후위표기식 계산 결과를 저장할 변수 초기화

	// 각 중위표기식과 후위표기식 문자열 배열 버퍼 초기화
	/*
		void *memset(void *ptr, int value, size_t num);

		'memory set' 의 줄임말로,
		주로 배열이나 구조체와 같은 데이터 구조의 메모리 영역을
		지정해준 값으로 초기화하는 데 사용됨.

		ptr: 초기화할 메모리 영역의 시작 포인터
		value: 메모리 영역을 초기화할 값
		num: 초기화할 바이트 수

		ptr이 가리키는 메모리 영역을 
		value 값으로 num 바이트만큼 채운다고 이해하면 됨.
	*/
	// 각 문자열 배열의 요소들을 0으로 초기화함.
	// char 타입은 문자를 저장할 수도 있지만, 1 byte 단위의 아주 작은 정수형을 메모리에 저장할 수 있음.
	memset(InfixExpression, 0, sizeof(InfixExpression));
	memset(PostfixExpression, 0, sizeof(PostfixExpression));

	/*
		scanf("%s", char 타입 배열 변수)

		scanf() 는 c++ 에서 cin() 같은 개념.
		콘솔에서 값을 입력받게 해주는 함수.

		이때, 형식지정자 "%s" 를 전달하면
		문자열을 입력받을 수 있도록 함.

		입력받은 문자열을 중위표기식 문자열 변수 
		InfixExpression 에 저장함.
	*/
	printf("Enter Infix Expression:");
	//scanf_s("%s", InfixExpression, sizeof(InfixExpression)); // scanf() 는 deprecated 되었으므로, scanf_s() 를 사용하도록 함.
	scanf("%s", InfixExpression);

	// 중위표기식을 후위표기식으로 변환하여 저장
	GetPostfix(InfixExpression, PostfixExpression);

	// 중위표기식과 후위표기식을 각각 출력
	printf("Infix:%s\nPostfix:%s\n", 
			InfixExpression,
			PostfixExpression);

	// 후위표기식 계산결과를 변수에 저장
	Result = Calculate(PostfixExpression);

	// 후위표기식 계산 결과 출력
	printf("Calculation Result : %f\n", Result);

	return 0;
}
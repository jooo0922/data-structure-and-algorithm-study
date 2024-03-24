#include <stdio.h> // printf(), scanf() 같은 입출력 함수 선언이 포함된 헤더파일

// 거듭 제곱 연산 결과를 담을 수 있는 충분히 큰 사이즈의 부호가 없는 정수형 타입 정의
typedef unsigned long ULONG;

// 분할 정복으로 거듭 제곱 계산 알고리즘 (곱셈의 횟수를 줄이는 재귀 방정식)
ULONG Power(int Base, int Exponent)
{
	if (Exponent == 1)
	{
		// 지수가 1이면 밑을 그대로 반환하고 함수 종료
		return Base;
	}
	else if (Base == 0)
	{
		// 밑이 0이면 1을 반환하고 함수 종료
		return 1;
	}

	if (Exponent % 2 == 0)
	{
		// 지수가 짝수일 때의 재귀 방정식 구현 (p.534 참고)
		ULONG NewBase = Power(Base, Exponent / 2);
		return NewBase * NewBase;
	}
	else
	{
		// 지수가 홀수일 때의 재귀 방정식 구현 (p.534 참고)
		ULONG NewBase = Power(Base, (Exponent - 1) / 2);
		return (NewBase * NewBase) * Base;
	}
}

int main()
{
	// 거듭제곱의 밑 초기화
	int Base = 2;

	// 거듭제곱의 지수 초기화
	int Exponent = 30;

	// 거듭제곱 알고리즘 계산 결과 출력
	printf("%d^%d = %lu\n", Base, Exponent, Power(Base, Exponent));

	return 0;
}
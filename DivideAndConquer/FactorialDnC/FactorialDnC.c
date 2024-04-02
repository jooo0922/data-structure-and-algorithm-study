#include <stdio.h> // printf(), scanf() 같은 입출력 함수 선언이 포함된 헤더파일
#include <stdlib.h> // malloc(), free() 같은 함수 선언이 포함된 헤더파일

// 팩토리얼 연산 결과를 담을 수 있는 충분히 큰 사이즈의 부호가 없는 정수형 타입 정의
typedef unsigned long ULONG;

int Factorial(int N)
{
	// n = 0 일 때의 재귀방정식(기저 사례) 구현
	if (N == 0) return 1;

	/* 재귀방정식 n * (n - 1)! 구현 */

	// 팩토리얼 n! 을 n 과 (n-1)! 로 분할한 뒤, (n-1)! 먼저 계산
	int SmallerFactorial = Factorial(N - 1);

	// 분할된 팩토리얼의 각 부분인 n 과 (n-1)! 의 해답을 결합하여 최종 결과 계산
	return N * SmallerFactorial;
}

int main()
{
	int N = 7;

	// 7!(7 팩토리얼)를 분할 정복으로 계산
	ULONG Result = Factorial(N);

	// 7! 팩토리얼 출력
	printf("Factorial(%d) = %lu\n", N, Result);

	return 0;
}
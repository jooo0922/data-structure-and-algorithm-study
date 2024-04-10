#include <stdio.h> // printf(), scanf() 같은 입출력 함수 선언이 포함된 헤더파일
#include <stdlib.h> // malloc(), free() 같은 메모리 할당 함수 선언이 포함된 헤더파일

// 피보나치 수 연산 결과를 담을 수 있는 충분히 큰 사이즈의 부호가 없는 정수형 타입 정의
typedef unsigned long ULONG;

// n 번째 피보나치 수 계산 함수 (동적 계획법)
ULONG Fibonacci(int N)
{
	// 반복문 순회에 사용할 인덱스 변수 선언
	int i;

	// 동적 계획법의 연산 결과를 할당할 변수 선언
	ULONG Result;

	// 부분 문제의 해를 저장할 테이블 변수 선언
	ULONG* FibonacciTable;

	// p.551 점화식처럼 0번째와 1번째 피보나치 수는 정해져 있으므로, 그대로 반환
	if (N == 0 || N == 1)
	{
		return N;
	}

	// 0번째 ~ N번째 피보나치 수(부분 문제의 해)를 저장할 수 있는 크기의 메모리를 테이블에 동적 할당
	FibonacciTable = (ULONG*)malloc(sizeof(ULONG) * (N + 1));

	// 이미 정의되어 있는 0번째와 1번째 피보나치 수를 테이블에 바로 저장
	FibonacciTable[0] = 0;
	FibonacciTable[1] = 1;

	// 가장 작은 부분 문제인 Fibonacci(2) 부터 최상위 부분 문제인 Fibonacci(N) 의 해를 차례대로 풀어나감
	for (i = 2; i <= N; i++)
	{
		// 계산된 부분 문제의 해는 반드시 테이블에 저장! -> 다음 부분 문제를 풀 때 사용
		FibonacciTable[i] = FibonacciTable[i - 1] + FibonacciTable[i - 2];
	}

	// 최상위 문제의 해 Fibonacci(N) 을 Result 변수에 저장
	Result = FibonacciTable[N];

	// 전체 문제의 해를 구한 뒤 테이블 메모리 반납
	free(FibonacciTable);

	return Result;
}

int main()
{
	// 46번째 피보나치 수를 동적 계획법으로 계산
	int N = 46;
	ULONG Result = Fibonacci(N);

	// 46번째 피보나치 수 출력
	printf("Fibonacci(%d) = %lu \n", N, Result);

	return 0;
}
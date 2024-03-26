#include <stdio.h> // printf(), scanf() 같은 입출력 함수 선언이 포함된 헤더파일

// 거듭 제곱 연산 결과를 담을 수 있는 충분히 큰 사이즈의 부호가 없는 정수형 타입 정의
typedef unsigned long ULONG;

// ULONG 타입의 성분들로 구성된 2*2 행렬 구조체 선언
typedef struct tagMatrix2x2
{
	// 2차원 배열로 선언
	ULONG Data[2][2];
} Matrix2x2;
#include <stdio.h> // printf(), scanf() 같은 입출력 함수 선언이 포함된 헤더파일

// 거듭 제곱 연산 결과를 담을 수 있는 충분히 큰 사이즈의 부호가 없는 정수형 타입 정의
typedef unsigned long ULONG;

// ULONG 타입의 성분들로 구성된 2*2 행렬 구조체 선언
typedef struct tagMatrix2x2
{
	// 2차원 배열로 선언
	ULONG Data[2][2];
} Matrix2x2;

// 2*2 정방행렬 곱셈 계산 함수
Matrix2x2 Matrix2x2_Multiply(Matrix2x2 A, Matrix2x2 B)
{
	Matrix2x2 C;

	C.Data[0][0] = A.Data[0][0] * B.Data[0][0] + A.Data[0][1] * B.Data[1][0];
	C.Data[0][1] = A.Data[0][0] * B.Data[1][0] + A.Data[0][1] * B.Data[1][1];

	C.Data[1][0] = A.Data[1][0] * B.Data[0][0] + A.Data[1][1] * B.Data[1][0];
	C.Data[1][1] = A.Data[1][0] * B.Data[1][0] + A.Data[1][1] * B.Data[1][1];

	return C;
}

// 분할 정복으로 피보나치 수 계산 알고리즘 (Fibonacci() 함수 호출을 줄이는 행렬 재귀 방정식)
/*
	매개변수 설명

	- Matrix2x2 A : 재귀를 돌며 거듭제곱이 수행되는 2*2 정방행렬 
	- int n : n 번째 피보나치 수를 나타내는 값

	아래부터는 최초의 행렬 [[1, 1], [1, 0]] 는 a 로 나타낼 것임.
*/
Matrix2x2 Matrix2x2_Power(Matrix2x2 A, int n)
{
	if (n > 1)
	{
		/*
			아래의 Matrix2x2_Power() 재귀 호출과 
			행렬 거듭제곱에 의해,

			n 이 짝수이면,
			aⁿ/² * aⁿ/² 가 계산될 것이고,

			n 이 홀수이면,
			aⁿ⁻¹ 이 계산될 것임. 
			(자세한 설명은 본문 p.542 참고)
		*/
		A = Matrix2x2_Power(A, n / 2);
		A = Matrix2x2_Multiply(A, A);

		// 비트 AND 연산자로 n 의 짝수 / 홀수 여부 검사
		if (n & 1)
		{
			/*
				n 이 홀수로 판정되면,
				행렬 B 에 최초의 행렬 a 를 추가로 생성하고,

				위에서 재귀 호출로 계산된 행렬 A 에
				추가로 곱해줌.

				이때, n 이 홀수이므로,
				행렬 A 에는 aⁿ⁻¹ 이 계산되어 있을 것임.

				즉, n 이 홀수일 때에는 
				aⁿ⁻¹ * a 가 계산되는 것! 
				(자세한 설명은 p.542 본문 참고)
			*/
			Matrix2x2 B;
			B.Data[0][0] = 1;
			B.Data[0][1] = 1;
			B.Data[1][0] = 1;
			B.Data[1][1] = 0;

			A = Matrix2x2_Multiply(A, B);
		}
	}

	// n = 1 이면, 최초의 행렬 a 을 그대로 반환
	return A;
}

// n 번째 피보나치 수 계산 함수
ULONG Fibonacci(int N)
{
	Matrix2x2 A;

	// 최초의 행렬 [[1, 1], [1, 0]] 초기화
	A.Data[0][0] = 1;
	A.Data[0][1] = 1;
	A.Data[1][0] = 1;
	A.Data[1][1] = 0;

	// 분할 정복으로 n 번째 피보나치 수 계산
	A = Matrix2x2_Power(A, N);

	/*
		최초의 행렬 A 를 분할 정복으로 거듭제곱한 결과인
		[[Fₙ₊₁, Fₙ], [Fₙ, Fₙ₋₁]] 의 1행 2열의 성분값인 Fₙ 반환
	*/
	return A.Data[0][1];
}
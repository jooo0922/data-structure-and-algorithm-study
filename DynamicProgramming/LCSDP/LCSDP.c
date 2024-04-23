#include <stdio.h> // printf(), scanf() 같은 입출력 함수 선언이 포함된 헤더파일
#include <string.h> // strlen(), strcpy() 같은 문자열 처리 함수 선언이 포함된 헤더파일
#include <stdlib.h> // malloc(), free() 같은 메모리 할당 함수 선언이 포함된 헤더파일

// LCS 테이블 구조체 선언
typedef struct structLCSTable
{
	/*
		테이블을 2차원 배열로 선언하기 위해
		이중 포인터 사용

		-> [[int 타입 요소를 담는 배열] 들을 담는 배열]
		의 첫 번째 요소를 가리키는 포인터 변수
	*/
	int** Data;
} LCSTable;

// LCS(최장 공통 부분 수열)의 길이를 저장하는 LCS 테이블 구축 함수 (동적 계획법)
/*
	매개변수 정리

	- char* X, char* Y : 최장 공통 부분 수열을 비교할 두 문자열
	- int i, int j : 두 문자열 X, Y 의 길이이자, LCS 테이블 상에서 최장 공통 부분 수열의 길이값이 저장된 위치
	- LCSTable* Table : LCS 알고리즘을 최적 부분 구조로 풀기 위해, 부분 문제들의 해를 저장해 둘 테이블
*/
int LCS(char* X, char* Y, int i, int j, LCSTable* Table)
{
	// 현재 순회 중인 테이블 셀의 위치를 0으로 초기화
	int m = 0;
	int n = 0;

	/*
		LCS 알고리즘의 첫 번째 점화식을 사용하여 
		가장 작은 부분 문제의 해를 LCS 테이블의 첫 번째 행과 열에 각각 채움
	*/
	for ( m = 0; m <= i; m++)
	{
		// LCS 테이블의 첫 번째 열을 채움
		Table->Data[m][0] = 0;
	}

	for (n = 0; n <= i; n++)
	{
		// LCS 테이블의 첫 번째 행을 채움
		Table->Data[0][n] = 0;
	}

	/*
		이후의 상위 문제의 해부터는
		테이블의 두 번째 행과 열부터 각각 채워나감
	*/
	for ( m = 0; m <= i; m++)
	{
		for (n = 0; n <= j; n++)
		{
			// 두 번째 점화식의 조건에 따라 부분 문제의 해를 채움
			if (X[m - 1] == Y[m - 1])
			{
				/*
					아래와 같이 테이블에 저장되어 있는
					이전 단계의 부분 문제의 해를 참조하여 상위 부분 문제의 해를 구함
					
					-> 이러한 구조를 '최적 부분 구조'를 갖추었다고 하고,
					동적 계획법 알고리즘의 가장 큰 특징!
				*/
				Table->Data[m][n] = Table->Data[m - 1][n - 1] + 1;
			}
			else
			{
				// 세 번째 점화식의 조건에 따라 부분 문제의 해를 채움
				if (Table->Data[m][n - 1] >= Table->Data[m - 1][n])
				{
					Table->Data[m][n] = Table->Data[m][n - 1];
				}
				else
				{
					Table->Data[m][n] = Table->Data[m - 1][n];
				}
			}
		}
	}

	/*
		테이블을 모두 구축하고 난 후,
		테이블의 가장 오른쪽 아래 모서리 요소에 저장된
		최장 공통 부분 수열(LCS)의 길이 (== 전체 문제의 최적해) 를 반환
	*/
	return Table->Data[i][j];
}
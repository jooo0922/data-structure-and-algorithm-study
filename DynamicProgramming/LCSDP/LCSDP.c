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

// LCS 테이블을 거꾸로 추적하여 LCS 문자열을 구하는 함수
/*
	매개변수 정리

	- char* X, char* Y : 최장 공통 부분 수열을 비교할 두 문자열
	- int m, int n : LCS 테이블 상에서 현재 순회중인 셀의 위치값
	- LCSTable* Table : LCS 알고리즘을 최적 부분 구조로 풀기 위해, 부분 문제들의 해를 저장해 둘 테이블
	- LCS : LCS 테이블을 역추척하며 LCS 문자열 요소를 저장할 동적 배열
*/
void LCS_TraceBack(char* X, char* Y, int m, int n, LCSTable* Table, char* LCS)
{
	// 가장 작은 부분 문제의 해가 담긴 셀 (첫 번째 행과 열)에 도달하면 재귀 호출 종료
	if (m == 0 || n == 0)
	{
		return;
	}

	if (Table->Data[m][n] > Table->Data[m][n - 1]
		&& Table->Data[m][n] > Table->Data[m - 1][n]
		&& Table->Data[m][n] > Table->Data[m - 1][n - 1])
	{
		/*
			현재 셀이 왼쪽, 위쪽, 왼쪽 위 셀보다 크면,
			현재 셀의 요소를 LCS 배열에 삽입하고,
			왼쪽 위 셀로 이동하여 재귀 호출

			참고로, 현재 셀은 Table->Data[m][n] 을 의미!
		*/

		// 기존 LCS 문자열을 정적 배열에 임시 저장
		char TempLCS[100];
		strcpy(TempLCS, LCS);

		// 현재 셀에 저장된 길이값에 해당하는 문자 요소를 LCS 문자열에 추가
		/*
			참고로, 새로 추가할 문자 요소를
			sprintf() 를 사용하여 기존 문자열 '앞'에 붙이는 이유는,
			LCS 테이블을 '오른쪽 아래 -> 왼쪽 위' 방향으로 순회하므로,
			문자 요소를 추가하는 순서 또한 거꾸로 되어야 함!
		*/
		sprintf(LCS, "%c%s", X[m - 1], TempLCS);

		// 왼쪽 위 셀로 이동하여 재귀 순회
		LCS_TraceBack(X, Y, m - 1, n - 1, Table, LCS);
	}
	else if (Table->Data[m][n] > Table->Data[m - 1][n]
		&& Table->Data[m][n] == Table->Data[m][n - 1])
	{
		/*
			현재 셀이 위쪽 셀보다 크고, 왼쪽 셀과는 같을 경우,
			왼쪽 셀로 이동하여 재귀 순회
		*/
		LCS_TraceBack(X, Y, m, n - 1, Table, LCS);
	}
	else
	{
		/*
			p.563 의 2번, 3번 과정의 조건 중 어느 하나에도 해당되지 않으면,
			위쪽 셀로 이동하여 재귀 순회
		*/
		LCS_TraceBack(X, Y, m - 1, n, Table, LCS);
	}
}

/*
	sprintf()

	포맷 지정자로 새로운 문자열을 생성한 후,
	생성한 문자열을 첫 번째 매개변수로 전달받은 문자열 버퍼에 저장함.

	위 예제 코드에서는 
	sprintf(LCS, "%c%s", X[m-1], TempLCS); 와 같이 사용됨.

	첫 번째 매개변수 LCS: 생성된 문자열이 저장될 버퍼.
	두 번째 매개변수 "%c%s": 생성될 문자열의 서식을 지정하는 포맷 문자열.
	세 번째 매개변수 X[m-1]와 네 번째 매개변수 TempLCS: 포맷 문자열에서 %c와 %s에 해당하는 데이터. %c에는 X[m-1]에 해당하는 문자가, %s에는 TempLCS에 해당하는 문자열이 삽입됨.
*/
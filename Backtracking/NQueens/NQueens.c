#include "NQueens.h"

// 백트래킹으로 N개의 퀸의 모든 해 탐색
void FindSolutionForQueen(int Columns[], int Row, int NumberOfQueens, int* SolutionCount)
{
	if (IsThreatened(Columns, Row))
	{
		/*
			새로 놓인 퀸의 위치(=새로운 부분해)가
			기존에 놓인 퀸(=이전 상위 부분해)를 위협하면,
			함수를 반환해서 제어 흐름을 상위 부분해로 넘김. 
			
			-> BackTracking!
		*/
		return;
	}

	// 새로 놓인 퀸이 마지막 행이고, 검사를 통과했다면? -> 마지막 부분해를 찾았다는 뜻!
	if (Row == NumberOfQueens - 1)
	{
		// 모든 해의 개수가 담긴 변수의 주소값(포인터 변수)를 de-referencing 하여 증가시킴
		printf("Solution #%d : \n", ++(*SolutionCount));

		// 마지막 부분해를 찾았다면, 진짜 해를 하나 찾았다는 뜻이므로 출력함.
		PrintSolution(Columns, NumberOfQueens);
	}
	else // 새로 놓인 퀸이 마지막 행이 아니라면? -> 마지막 부분해가 아니라는 뜻!
	{
		int i;

		// 마지막 부분해가 아니라면, 다음 부분 후보해 목록(= 다음 행의 체스칸들)을 재귀 순회하며 검사
		for (i = 0; i < NumberOfQueens; i++)
		{
			// 새로운 행(Row + 1)에 새 퀸의 위치(i, 다음 부분 후보해)를 입력
			Columns[Row + 1] = i;

			// 새로운 부분해(=새로 놓인 퀸)에 대해 재귀 호출하여 이전 상위 부분해(=이전에 놓인 퀸)의 위협 여부 검사
			FindSolutionForQueen(Columns, Row + 1, NumberOfQueens, SolutionCount);
		}
	}
}

// 새로 놓은 퀸(새로운 부분해)가 기존에 놓인 퀸(이전 상위 부분해)을 위협하는지 여부 검사
int IsThreatened(int Columns[], int NewRow)
{
	// 현재 순회 중인 행
	int CurrentRow = 0;

	// 새로 놓인 퀸의 위협 여부를 저장한 결과값. 0 또는 1
	int Threatened = 0;

	// 첫 번째 행에서 새 퀸이 놓이기 직전까지의 행 순회
	while (CurrentRow < NewRow)
	{
		if (Columns[NewRow] == Columns[CurrentRow] // 수직 방향 위협 검사
			|| abs(Columns[NewRow] - Columns[CurrentRow]) == abs(NewRow - CurrentRow)) // 대각선 방향 위협 검사
		{
			// 위협이 감지되면 결과값을 변경하고 반복문 종료
			Threatened = 1;
			break;
		}

		// 위협이 감지되지 않았다면 다음 행 검사
		CurrentRow++;
	}

	// 위협 여부를 저장한 결과값 반환
	return Threatened;
}

// 백트래킹으로 찾은 N개의 퀸 해 출력
void PrintSolution(int Columns[], int NumberOfQueens)
{
	// N * N 칸의 체스칸을 순회할 때 사용할 인덱스 값 초기화
	int i = 0;
	int j = 0;

	// 이중 for-loop 를 돌려서 N * N 칸의 체스칸 전체 순회
	for (i = 0; i < NumberOfQueens; i++)
	{
		for (j = 0; j < NumberOfQueens; j++)
		{
			if (Columns[i] == j)
			{
				/*
					N개의 퀸의 진짜 해가 저장된 Columns 배열에서
					현재 순회 중인 i행 j열이 저장되어 있다면,

					해당 칸에 퀸이 배치되어 있다는 뜻이므로,
					이 부분을 "Q" 라는 문자로 표시
				*/
				printf("Q");
			}
			else
			{
				/*
					현재 순회 중인 i행 j열이
					Columns 배열에 저장되어 있지 않다면,

					해당 칸에는 퀸이 배치되어 있지 않다는 뜻이므로,
					빈칸이라는 의미에서 "." 라는 문자로 표시
				*/
				printf(".");
			}
		}

		// 각 행(i)에 대한 순회가 끝날 때마다 개행
		printf("\n");
	}

	// 이후에 또 진짜 해가 발견되어 출력해야 할 수 있으므로, 출력된 현재 해와 구분을 위해 개행
	printf("\n");
}
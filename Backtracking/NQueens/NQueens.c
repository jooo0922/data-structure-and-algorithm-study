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

}

// 백트래킹으로 찾은 N개의 퀸 해 출력
void PrintSolution(int Columns[], int NumberOfQueens)
{

}
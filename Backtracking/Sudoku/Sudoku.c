#include "Sudoku.h"

// 백트래킹으로 찾은 스도쿠 해 출력
void PrintSolution(int Board[N][N])
{
	// N*N 크기의 2차원 배열을 이중 for-loop 로 순회하며 스도쿠 보드 출력
	for (int row = 0; row < N; row++)
	{
		for (int col = 0; col < N; col++)
		{
			printf("%d", Board[row][col]);
		}

		// 하나의 행(row)을 모두 출력한 뒤에는 개행
		printf("\n");
	}
}

// [1, 9] 사이의 숫자 중 하나(= num)를 특정 칸(= (row, col))에 놓을 수 있는 지 검사
// -> NQueens 예제 코드로 치면 IsThreatened() 함수와 동일한 역할
bool IsSafe(int Board[N][N], int row, int col, int num)
{
	/*
		해당 행(row)과 해당 열(col)에 대한 
		9개의 각 상대 열(x), 상대 행(x)을 순회하며

		각 행과 열에 중복된 숫자가 존재하는지 검사
	*/
	for (int x = 0; x < N; x++)
	{
		// 해당 행(row)에 입력하고자 하는 숫자(num)와 중복된 숫자가 존재하는지 검사
		if (Board[row][x] == num)
		{
			return false;
		}

		// 해당 열(col)에 입력하고자 하는 숫자(num)와 중복된 숫자가 존재하는지 검사
		if (Board[x][col] == num)
		{
			return false;
		}
	}


	/*
		해당 3*3 서브 그리드에
		중복된 숫자가 존재하는지 검사
	*/

	// 해당 칸(= (row, col))이 속한 3*3 서브 그리드의 첫 번째 칸(= (startRow, startCol))의 위치 계산
	int startRow = row - row % 3;
	int startCol = col - col % 3;

	// 이중 for-loop 로 3*3 서브 그리드를 순회하며 중복된 숫자가 존재하는지 검사
	for (int i = 0; i < 3; i++)
	{
		for (int j = 0; j < 3; j++)
		{
			if (Board[i + startRow][j + startCol] == num)
			{
				return false;
			}
		}
	}

	// 각 행, 각 열, 3*3 서브 그리드에 중복된 숫자가 없음을 모두 확인했다면 true 반환
	return true;
}

// 백트래킹으로 스도쿠의 진짜 해 탐색
bool FindSolutionForSudoku(int Board[N][N])
{
	// 현재 순회중인 셀의 행과 열 위치 초기화
	int row = -1;
	int col = -1;

	// 전체 스도쿠 보드에 빈 셀(= 0) 존재 여부 상태값 초기화
	bool isEmpty = false;

	// 전체 스도쿠 보드를 이중 for-loop 로 순회하면서 빈 셀 찾기
	for (int i = 0; i < N; i++)
	{
		for (int j = 0; j < N; j++)
		{
			/*
				가장 먼저 마주친 빈 셀의 위치값을 row, col 에 저장하고,
				빈 셀을 발견했기 때문에 isEmpty 상태값을 true 로 변경하고,
				안쪽 for-loop 를 탈출함.
			*/
			if (Board[i][j] == 0)
			{
				row = i;
				col = j;
				isEmpty = true;
				break;
			}
		}

		// 안쪽 for-loop 를 돌면서 빈 셀을 발견해서 탈출했다면, 바깥 쪽 for-loop 도 바로 탈출
		if (isEmpty)
		{
			break;
		}
	}

	// 전체 스도쿠 보드에서 빈 셀이 없다면, 스도쿠가 완성된 것이므로 true 반환
	if (!isEmpty)
	{
		return true;
	}
	
	// [1, 9] 범위의 숫자를 순회하며 발견된 빈 셀에 입력 시도
	for (int num = 1; num < 9; num++)
	{
		// 현재 순회 중인 숫자를 빈 셀(= 부분해)에 입력했을 때, 부분해가 조건을 만족하는지 검사
		// -> 여기서 조건이란, 해당 행, 해당 열, 해당 3*3 서브그리드에 중복된 숫자가 없어야 한다는 것! 
		if (IsSafe(Board, row, col, num))
		{
			// 현재 부분해가 조건을 만족한다면, 빈 셀에 현재 순회 중인 숫자를 입력함.
			Board[row][col] = num;

			// 다음 부분해 목록(= 다음 빈 셀)에 대해 재귀 순회하며 조건을 만족하는 부분해 검사
			if (FindSolutionForSudoku(Board))
			{
				// 조건을 만족하는 다음 부분해가 존재한다면, true 반환하고 함수 종료 
				return true;
			}

			/*
				조건을 만족하는 다음 부분해를 찾지 못해 여기까지 왔다면,
				현재 부분해를 다시 빈 셀(= 0)로 초기화
			*/
			Board[row][col] = 0;
		}
	}

	/*
		조건을 만족하는 다음 부분해를 찾지 못해 여기까지 왔다면,
		false 를 반환하면서 제어 흐름을 상위 부분해(= 이전 빈 셀)로 넘기기.
		-> BackTracking!
	*/
	return false;
}

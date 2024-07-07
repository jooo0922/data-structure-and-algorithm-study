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
bool isSafe(int Board[N][N], int row, int col, int num)
{

}

// 백트래킹으로 스도쿠의 진짜 해 탐색
void FindSolutionForSudoku(int Board[N][N])
{

}

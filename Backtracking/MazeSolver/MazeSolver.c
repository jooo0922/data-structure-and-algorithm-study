#include "MazeSolver.h"

// 미로 데이터의 시작점 S 탐색 및 MoveTo() 재귀 호출의 entry point
int Solve(MazeInfo* Maze)
{
	// 미로 데이터의 각 행과 열을 순회할 인덱스 초기화
	int i = 0;
	int j = 0;

	// 미로 데이터의 시작점 S 탐색 여부 초기화
	int StartFound = FAIL;

	// 백트래킹으로 미로 데이터의 진짜 해(탈출 경로) 탐색 여부 초기화
	int Result = FAIL;

	// 미로 데이터의 시작점 S 위치값 변수 초기화
	Position Start;

	// 2차원 배열의 미로 데이터를 순회하며 시작점 S 탐색
	for (i = 0; i < Maze->RowSize; i++)
	{
		for (j = 0; j < Maze->ColumnSize; j++)
		{
			/*
				미로 데이터를 이중 for 문을 순회하면서,
				문자열 'S' 를 발견했을 경우, 해당 요소가 미로의 시작점이므로,
				해당 요소의 인덱스를 시작점 S 의 위치값으로 저장
			*/
			if (Maze->Data[i][j] == START)
			{
				Start.X = j; // Column
				Start.Y = i; // Row

				// 미로 데이터 시작점 S 탐색에 성공했으니, ENUM 값을 변경하고 이중 for 문 순회 종료
				StartFound = SUCCEED;
				break;
			}
		}
	}

	// 미로 데이터의 시작점을 찾지 못했다면, 백트래킹이 불가하므로 함수 종료
	if (StartFound == FAIL)
	{
		return FAIL;
	}

	/*
		탐색한 시작점 S 에서
		북, 남, 동, 서 방향 순으로 MoveTo() 함수를 호출시켜서
		현 위치에서 선택 가능한 다음 부분해(= 이동 가능한 경로)를 검사함.

		-> 각 방향에서의 MoveTo() 재귀 실행 중,
		어느 한 방향에서라도 SUCCEED 를 반환받았을 경우,
		해당 방향으로 백트래킹의 해가 존재한다(= 탈출로가 존재한다)는 뜻이므로,
		백트래킹의 해를 하나라도 먼저 발견할 시,
		if ~ else if 블록을 탈출하도록 조건문 블록을 구성함.

		-> 참고로, 북쪽 방향에 대한 MoveTo() 함수를 가장 먼저 호출시킴으로써,
		현 시작점 S 로부터 첫 이동방향을 북쪽으로 지정하게 됨.
	*/
	if (MoveTo(Maze, &Start, NORTH))
	{
		Result = SUCCEED;
	}
	else if (MoveTo(Maze, &Start, SOUTH))
	{
		Result = SUCCEED;
	}
	else if (MoveTo(Maze, &Start, EAST))
	{
		Result = SUCCEED;
	}
	else if (MoveTo(Maze, &Start, WEST))
	{
		Result = SUCCEED;
	}

	/*
		위 MoveTo() 호출에 의해 이동 가능한 경로가 발견되었다면,
		현재 미로 데이터의 시작점이 MARKED('+')로 덮어쓰였을 것이므로,
		
		최종적으로 탈출로 탐색 여부를 반환하기 전에
		미로 데이터의 시작점을 다시 START('S')로 rollback 한 것!
	*/
	Maze->Data[Start.Y][Start.X] = START;

	// 백트래킹의 진짜 해(탈출로) 발견 여부 반환
	return Result;
}

/*
	현 위치에서 다음 부분해 목록(= 다음 이동 경로)들의
	이동 가능 여부를 재귀적으로 검사함.

	이동 가능한 부분해가 존재하지 않을 경우,
	백트래킹을 실행함.
*/
int MoveTo(MazeInfo* Maze, Position* Current, int Direction)
{

}

// 각 후보해들(= 다음 이동 경로)의 이동 가능 여부를 실제로 검사
int GetNextStep(MazeInfo* Maze, Position* Current, int Direction, Position* Next)
{

}

// 미로 데이터 파일을 입력받아 MazeInfo 구조체에 데이터를 복사
int GetMaze(char* FilePath, MazeInfo* Maze)
{

}

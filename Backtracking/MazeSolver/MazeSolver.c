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
	// 현 위치에서 이동 가능한 다음 부분해 목록을 순회할 때 사용할 인덱스 초기화
	int i = 0;

	// 현 위치에서 이동 가능한 모든 방향(북, 남, 동, 서 순서)의 enum 을 배열로 저장
	int Dirs[] = { NORTH, SOUTH, EAST, WEST };

	// GetNextStep() 함수에서 다음 경로의 위치값을 캐싱하기 위해 넘겨줄 Position 구조체 변수 생성
	Position Next;

	/*
		현재 위치가 출구인 경우(= 진짜 해를 찾은 경우),
		MoveTo() 함수의 재귀 호출을 return 하여 Backtracking 수행

		-> p.613 ~ 614, p.616 4번 과정 참고
	*/
	if (Maze->Data[Current->Y][Current->X] == GOAL)
	{
		return SUCCEED;
	}

	/*
		현재 위치는 이미 지나온 경로에 해당하므로,
		현재 위치는 MARKED('+') 로 표시함.

		-> 이래야 GetNextStep() 함수에서 새로운 이동 경로를 찾을 때,
		이미 지나온 경로를 피해갈 수 있음.
	*/
	Maze->Data[Current->Y][Current->X] = MARKED;

	// 현 위치의 북, 남, 동, 서 방향으로 순회하며 이동 가능한 다음 부분해를 검사함
	for (i = 0; i < 4; i++)
	{
		if (GetNextStep(Maze, Current, Dirs[i], &Next) == FAIL)
		{
			/*
				각 방향의 후보해(= 다음 이동 경로)를 검사해서 FAIL 이 나왔다면, 
				어떤 이유에 의해서건 해당 방향은 이동 불가 판정을 받은 것이므로,
				다음 방향을 검사할 수 있도록 for 문의 다음 순회로 넘어감.

				-> p.616 2, 3번 과정에 해당
			*/
			continue;
		}

		/*
			for 문의 다음 순회로 넘어가지 않고 여기까지 왔다는 것은,
			방금 검사한 후보해(= 다음 이동 경로)가 이동 가능한 방향임이 확인되었다는 뜻이므로,

			해당 방향으로 이동
			(참고로, GetNextStep() 함수에 의해 
			Next 에 이미 이동한 위치값이 덮어쓰여 있음)
			해서 MoveTo() 함수를 재귀 호출함

			-> p.616 3번 과정에 해당

			(근데 int Direction 매개변수는 함수 내에서 아예 사용 자체를 안하는데,
			왜 NORTH 로 넘겨준거지? P.616 의 1번 과정을 의식한건가...
			아무튼 별 의미 없는 매개변수 전달인 것 같음...)					
		*/
		if (MoveTo(Maze, &Next, NORTH) == SUCCEED)
		{
			return SUCCEED;
		}
	}

	/*
		위 for 문을 모두 순회하고 나서도
		return SUCCEED 를 하지 못했다는 것은,

		현재 위치(Current)의 북, 남, 동, 서 방향 모두 
		이동 불가한 경로라는 뜻이므로, 현재 위치는 '막다른 길' 이라고 보면 됨.

		따라서, 현재 위치를 다시 WAY(' ')로 표시하고,
		return FAIL; 로 재귀 호출을 종료함으로써,
		상위 부분해로 Backtracking 을 수행함 -> p.614 참고
	*/
	Maze->Data[Current->Y][Current->X] = WAY;

	return FAIL;
}

// 각 후보해들(= 다음 이동 경로)의 이동 가능 여부를 실제로 검사
int GetNextStep(MazeInfo* Maze, Position* Current, int Direction, Position* Next)
{

}

// 미로 데이터 파일을 입력받아 MazeInfo 구조체에 데이터를 복사
int GetMaze(char* FilePath, MazeInfo* Maze)
{

}

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
	/*
		현재 위치(Current)로부터 이동할 
		다음 이동 경로(Direction)를 검사했을 때,

		미로 데이터의 경계 부분(즉, 미로 데이터의 끝부분)에 해당한다면,
		이동 불가한 경로이므로 FAIL 을 반환함.
	*/
	switch (Direction)
	{
	case NORTH:
		// 후보해(다음 이동 경로)의 위치값 계산
		Next->X = Current->X;
		Next->Y = Current->Y - 1;

		// 만약, 다음 경로가 미로 데이터의 북쪽 끝에 해당한다면, 이동 불가 경로 처리
		if (Next->Y == -1)
		{
			return FAIL;
		}

		break;
	case SOUTH:
		// 후보해(다음 이동 경로)의 위치값 계산
		Next->X = Current->X;
		Next->Y = Current->Y + 1;

		// 만약, 다음 경로가 미로 데이터의 남쪽 끝에 해당한다면, 이동 불가 경로 처리
		if (Next->Y == Maze->RowSize)
		{
			return FAIL;
		}

		break;
	case EAST:
		// 후보해(다음 이동 경로)의 위치값 계산
		Next->X = Current->X + 1;
		Next->Y = Current->Y;

		// 만약, 다음 경로가 미로 데이터의 동쪽 끝에 해당한다면, 이동 불가 경로 처리
		if (Next->Y == Maze->ColumnSize)
		{
			return FAIL;
		}

		break;
	case WEST:
		// 후보해(다음 이동 경로)의 위치값 계산
		Next->X = Current->X - 1;
		Next->Y = Current->Y;

		// 만약, 다음 경로가 미로 데이터의 서쪽 끝에 해당한다면, 이동 불가 경로 처리
		if (Next->Y == -1)
		{
			return FAIL;
		}

		break;
	}

	// 다음 경로가 벽('#')이거나 이미 지나온 경로('+')라면, 이동 불가 경로 처리
	if (Maze->Data[Next->Y][Next->X] == WALL)
	{
		return FAIL;
	}
	if (Maze->Data[Next->Y][Next->X] == MARKED)
	{
		return FAIL;
	}

	// 후보해(다음 이동 경로)의 이동 가능 여부 검사를 모두 통과했다면 SUCCEED 반환
	return SUCCEED;
}

// 미로 데이터 파일을 입력받아 MazeInfo 구조체에 데이터를 복사
int GetMaze(char* FilePath, MazeInfo* Maze)
{
	// 파일에서 읽어들인 미로 데이터의 행과 열을 순회할 때 사용할 인덱스 초기화
	int i = 0;
	int j = 0;

	// 입력된 파일로부터 읽어들인 미로 데이터의 전체 행과 열 개수를 저장할 변수 초기화
	int RowSize = 0;
	int ColumnSize = INIT_VALUE;

	// C언어에서 파일 입출력을 다룰 때 사용하는 파일 구조체 포인터 변수 선언
	FILE* fp;

	// 입력된 파일로부터 미로 데이터를 한 번에 읽어들일 수 있는 최대 길이만큼의 문자열 버퍼 메모리 할당
	char buffer[MAX_BUFFER];


	/* 파일 열기 */

	// 입력받은 파일 경로를 '읽기 모드("r"('R'ead mode))'로 열기 시도
	if (fopen_s(&fp, FilePath, "r") != 0)
	{
		/*
			파일 열기 성공 시,
			fopen_s() 함수가 0을 반환하고,
			실패하면 에러 코드를 반환하므로,

			반환값이 0이 아닐 경우의 예외 처리 적용
		*/
		printf("Cannot open file:%s\n", FilePath);
		return FAIL;
	}


	/* 파일 읽기 (미로 데이터의 전체 행과 열 개수 계산) */

	// 파일 포인터 fp 가 가리키는 파일에서 한 줄 크기(MAX_BUFFER)만큼 문자열을 읽어와서 buffer 정적 배열에 저장
	// 더 이상 읽어올 문자열이 없을 때까지(즉, 반환값이 NULL 일 때까지) 문자열 읽기를 반복
	while (fgets(buffer, MAX_BUFFER, fp) != NULL)
	{
		// 한 줄씩 읽을 때마다 미로 데이터의 전체 행 개수를 증가시킴
		RowSize++;

		if (ColumnSize == INIT_VALUE)
		{
			/*
				아직 미로 데이터의 전체 열 개수가 아직 초기값이라면, 
				읽어들인 문자열 한 줄의 길이(strlen(buffer) -1)를 
				전체 열 개수로 초기화함
			*/
			ColumnSize = strlen(buffer) - 1;
		}
		else if (ColumnSize != strlen(buffer) - 1)
		{
			/*
				전체 열 개수가 초기값이 아님에도,
				현재 읽어들인 한 줄 크기의 문자열이 기존 문자열 길이와 다르다면,
				현재 미로 데이터의 포맷이 잘못되었다는 뜻!

				-> 파일 포인터 fp 가 가리키는 파일 닫고 함수 종료
			*/
			printf("Maze data in file:%s is not valid.\n", FilePath);
			fclose(fp);
			return FAIL;
		}
	}

	// MazeInfo 구조체에 파일로부터 읽어들인 미로 데이터의 전체 행과 열 개수 입력
	Maze->RowSize = RowSize;
	Maze->ColumnSize = ColumnSize;

	// MazeInfo 구조체에 미로 데이터를 저장할 2차원 배열의 바깥쪽 배열 메모리 동적 할당
	Maze->Data = (char**)malloc(sizeof(char*) * RowSize);

	// MazeInfo 구조체에 미로 데이터를 저장할 2차원 배열의 안쪽 배열 메모리 동적 할당
	for (i = 0; i < RowSize; i++)
	{
		Maze->Data[i] = (char*)malloc(sizeof(char) * ColumnSize);
	}


	/* 파일 되감기 */

	/*
		이미 한 번 파일을 처음부터 끝까지 읽었으므로,
		파일을 다시 읽기 위해 파일 포인터를 파일의 시작으로 되돌림.
	*/
	rewind(fp);


	/* 파일 다시 읽기 */


	// 파일 내의 미로 데이터들을 동적 할당된 MazeInfo 구조체의 2차원 배열에 복사
	for (i = 0; i < RowSize; i++)
	{
		// 되감기한 파일로부터 한 줄 크기(MAX_BUFFER)만큼 문자열을 읽어오기
		fgets(buffer, MAX_BUFFER, fp);

		// 2차원 배열에 읽어온 문자열을 하나씩 복사하기
		for (j = 0; j < ColumnSize; j++)
		{
			Maze->Data[i][j] = buffer[j];
		}
	}


	/* 파일 닫기 */
	fclose(fp);

	return SUCCEED;
}

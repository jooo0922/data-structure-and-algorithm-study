#include <stdio.h>
#include "MazeSolver.h"

/*
	명령줄 인수를 선언하여
	CLI 입력으로 .dat 파일 경로를 전달받음.
	  \
	참고로, 터미널에서 .exe 실행 파일을 실행함과 동시에,
	.dat 파일 경로를 입력해야 하므로,
	두 파일 모두 하나의 디렉토리에 위치시키는 게 좋겠지!

	int argc : 입력받은 명령줄 인수의 개수
	char* argv : 입력받은 명령줄 인수들의 배열

	https://github.com/jooo0922/cpp-study/blob/main/TBCppChapter7/Chapter7_15/Chapter7_15.cpp 참고!
*/
int main(int argc, char* argv[])
{
	// 미로 데이터를 순회할 때 사용할 인덱스 변수 초기화
	int i = 0;
	int j = 0;

	// 미로 데이터 구조체 변수 선언
	MazeInfo Maze;

	/*
		입력받은 명령줄 인수가 2개보다 작으면
		필요한 인수들보다 적게 입력한 것이므로,

		터미널에 어떻게 입력해야 하는 지 출력해 줌.

		참고로,
		명령줄 인수의 첫번째, 즉, argv[0] 은
		항상 '실행파일 이름'이기 때문에,

		우리가 1개의 명령줄 인수를 입력받아야 한다면,
		명령줄 인수 갯수는 총 2개가 되어야 함.
	*/
	if (argc < 2)
	{
		printf("Usage: MazeSolver <MazeFile>\n");
		return 0;
	}

	// 미로 데이터 파일을 입력받아 MazeInfo 구조체에 데이터를 복사
	if (GetMaze(argv[1], &Maze) == FAIL)
	{
		return 0;
	}

	// 백트래킹으로 미로 데이터의 최종해(탈출 경로) 탐색
	if (Solve(&Maze) == FAIL)
	{
		return 0;
	}

	// 최종해(탈출 경로)가 표시된 미로 데이터 출력
	for (i = 0; i < Maze.RowSize; i++)
	{
		for (j = 0; j < Maze.ColumnSize; j++)
		{
			printf("%c", Maze.Data[i][j]);
		}
		printf("\n");
	}

	return 0;
}
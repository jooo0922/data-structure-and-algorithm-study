#include "NQueens.h"

/*
	명령줄 인수를 선언하여
	CLI 입력으로 .dat 파일 경로를 전달받음.
	
	int argc : 입력받은 명령줄 인수의 개수
	char* argv : 입력받은 명령줄 인수들의 배열

	https://github.com/jooo0922/cpp-study/blob/main/TBCppChapter7/Chapter7_15/Chapter7_15.cpp 참고!
*/
int main(int argc, char* argv[])
{
	// 첫 번째 퀸의 위치에 대한 부분해(= 첫 번째 행의 n 번째 열)를 담는 변수 초기화
	int i = 0;

	// N개의 퀸 개수 초기화
	int NumberOfQueens = 0;

	// 백트래킹으로 발견한 N개의 퀸의 모든 해 개수 초기화
	int SolutionCount = 0;

	// N개의 퀸의 진짜 해를 담는 1차원 동적 배열 초기화
	int* Columns;

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
		printf("Usage: %s <Number Of Queens>", argv[0]);
		return 1;
	}

	// atoi()(= Ascii to Integer)를 사용해서 문자로 입력된 N개의 퀸 개수를 int 타입으로 변환하여 저장 
	NumberOfQueens = atoi(argv[1]);

	// calloc() 을 사용하여 N개의 퀸 개수만큼 int 타입의 배열을 동적으로 할당하고, 메모리 값을 0으로 초기화.
	Columns = (int*)calloc(NumberOfQueens, sizeof(int));

	/*
		첫 번째 행에서 첫 번째 퀸의 위치에 대한
		각각의 부분해(i열)에 대해 백트래킹으로 재귀순회하여
		조건을 만족하는 진짜 해가 있는지 탐색함.

		-> p.626 이미지에 보이는 첫 번째 퀸의 위치에 대한 4개의 부분해를 
		각각 백트래킹하는 과정을 코드로 구현한 것.
	*/
	for (i = 0; i < NumberOfQueens; i++)
	{
		// 첫 번째 퀸의 위치에 대한 각각의 부분해만 저장
		Columns[0] = i;

		// 첫 번째 퀸의 위치에 대한 각 부분해에 대해 백트래킹 시도
		FindSolutionForQueen(Columns, 0, NumberOfQueens, &SolutionCount);
	}

	// 백트래킹 재귀 순회가 끝났으면 동적 할당한 배열의 메모리 반납
	free(Columns);

	return 0;
}
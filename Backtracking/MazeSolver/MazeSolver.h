#ifndef MAZESOLVER
#define MAZESOLVER
/*
	여기서 사용된 #ifndef ~ #endif 전처리기는
	헤더파일의 헤더가드를 처리해주는 방법 중 하나였지?

	cpp-study > TBCppStudy > Chapter1_12 > add.h 필기 참고!
*/

#include <stdio.h> // printf(), scanf() 같은 입출력 함수 선언이 포함된 헤더파일
#include <stdlib.h> // malloc(), free() 같은 메모리 할당 함수 선언이 포함된 헤더파일
#include <string.h> // strlen(), strcpy() 같은 문자열 처리 함수 선언이 포함된 헤더파일


/* 매크로 상수 선언 */

// 입력된 파일로부터 미로 데이터를 한 번에 읽어들일 수 있는 최대 길이 (fgets() 로 읽음!)
#define MAX_BUFFER 1024

// 입력된 파일로부터 읽어들인 미로 데이터의 전체 열(ColunmSize) 개수를 저장하는 변수의 초기값
#define INIT_VALUE -1


/* 미로 데이터를 시각화할 문자열 매크로 상수 선언 */

// 시작점
#define START 'S'

// 탈출구
#define GOAL 'G'

// 길
#define WAY ' '

// 벽
#define WALL '#'

// 탈출구로 향하는 길 표식(즉, 백트래킹의 '진짜 해')
#define MARKED '+'


/* enum 선언 */

// 미로 내의 이동 방향
enum DIRECTION { NORTH, SOUTH, EAST, WEST };

// 각 후보해(= 미로 내 경로)들의 이동 가능 여부를 검사한 결과값
enum RESULT { FAIL, SUCCEED };


/* 구조체 선언 */

// 미로 상의 위치 자료구조에 대한 구조체 선언
typedef struct tagPosition
{
	int X;
	int Y;
} Position;

// 미로 데이터 구조체 선언
typedef struct tagMazeInfo
{
	int ColumnSize; // 미로 데이터 너비
	int RowSize; // 미로 데이터 높이

	/*
		행(row) * 열(column) 방향으로 각 문자들을 출력해서
		미로 데이터를 시각화할 것이므로, 

		각 방향의 문자열들을 각각 저장하기 위해
		char 타입 2차원 배열을 이중 포인터 멤버변수로 선언함.
	*/
	char** Data;
} MazeInfo;


/* 함수 프로토타입 선언 */

// 미로 데이터의 시작점 S 탐색 및 MoveTo() 재귀 호출의 entry point
int Solve(MazeInfo* Maze);

/*
	현 위치에서 다음 부분해 목록(= 다음 이동 경로)들의 
	이동 가능 여부를 재귀적으로 검사함.

	이동 가능한 부분해가 존재하지 않을 경우,
	백트래킹을 실행함.
*/
int MoveTo(MazeInfo* Maze, Position* Current, int Direction);

// 각 후보해들(= 다음 이동 경로)의 이동 가능 여부를 실제로 검사
int GetNextStep(MazeInfo* Maze, Position* Current, int Direction, Position* Next);

// 미로 데이터 파일을 입력받아 MazeInfo 구조체에 데이터를 복사
int GetMaze(char* FilePath, MazeInfo* Maze);

#endif // !MAZESOLVER

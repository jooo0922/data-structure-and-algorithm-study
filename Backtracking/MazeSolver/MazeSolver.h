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

#endif // !MAZESOLVER

#ifndef NQUEENS_H
#define NQUEENS_H
/*
	여기서 사용된 #ifndef ~ #endif 전처리기는
	헤더파일의 헤더가드를 처리해주는 방법 중 하나였지?

	cpp-study > TBCppStudy > Chapter1_12 > add.h 필기 참고!
*/

#include <stdio.h> // printf(), scanf() 같은 입출력 함수 선언이 포함된 헤더파일
#include <stdlib.h> // malloc(), free() 같은 메모리 할당 함수 선언이 포함된 헤더파일

/* 함수 프로토타입 선언 */

// 백트래킹으로 찾은 N개의 퀸 해 출력
void PrintSolution(int Columns[], int NumberOfQueens);

// 새로 놓은 퀸(새로운 부분해)가 기존에 놓인 퀸(이전 상위 부분해)을 위협하는지 여부 검사
int IsThreatened(int Columns[], int NewRow);

// 백트래킹으로 N개의 퀸의 모든 해 탐색
void FindSolutionForQueen(int Columns[], int Row, int NumberOfQueens, int* SolutionCount);

#endif // !NQUEENS_H

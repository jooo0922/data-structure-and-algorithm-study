#ifndef SUDOKU_H
#define SUDOKU_H
/*
	여기서 사용된 #ifndef ~ #endif 전처리기는
	헤더파일의 헤더가드를 처리해주는 방법 중 하나였지?

	cpp-study > TBCppStudy > Chapter1_12 > add.h 필기 참고!
*/

#include <stdio.h> // printf(), scanf() 같은 입출력 함수 선언이 포함된 헤더파일

/* 함수 프로토타입 선언 */

/*
	참고로, 배열 자체는 '포인터 변수' 이기 때문에,
	매개변수를 아래와 같이 int Board[N][N] 으로 선언한다고 해서,
	매개변수로 2차원 배열이 전달될 때마다 2차원 배열의 값이 복사되는 게 아님!

	단지, 해당 2차원 배열이 저장된 메모리 블록의 첫 번째 요소의 주소값만 전달될 뿐!

	왜냐? C/C++ 에서 배열은 항상 포인터 변수로 취급되니까!

	즉, 2차원 배열로 선언된 매개변수가 전달될 때마다 
	Deep Copy 가 발생할 걱정을 하지 않아도 된다는 뜻!

	아래 깃허브 링크 참고
	https://github.com/jooo0922/cpp-study/blob/main/TBCppStudy/Chapter6_08/Chapter6_08.cpp
*/

// 백트래킹으로 찾은 스도쿠 해 출력
void PrintSolution(int Board[9][9]);

// [1, 9] 사이의 숫자 중 하나(= num)를 특정 칸(= (row, col))에 놓을 수 있는 지 검사
bool isSafe(int Board[9][9], int row, int col, int num);

// 백트래킹으로 스도쿠의 진짜 해 탐색
void FindSolutionForSudoku(int Board[9][9]);

#endif // !SUDOKU_H

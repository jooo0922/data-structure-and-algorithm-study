#include <stdio.h> // printf(), scanf() 같은 입출력 함수 선언이 포함된 헤더파일
#include <string.h> // strlen(), strcpy() 같은 문자열 처리 함수 선언이 포함된 헤더파일
#include <stdlib.h> // malloc(), free() 같은 메모리 할당 함수 선언이 포함된 헤더파일

// LCS 테이블 구조체 선언
typedef struct structLCSTable
{
	/*
		테이블을 2차원 배열로 선언하기 위해
		이중 포인터 사용

		-> [[int 타입 요소를 담는 배열] 들을 담는 배열]
		의 첫 번째 요소를 가리키는 포인터 변수
	*/
	int** Data;
} LCSTable;

// LCS(최장 공통 부분 수열)의 길이를 저장하는 LCS 테이블 구축 함수 (동적 계획법)
/*
	매개변수 정리

	- char* X, char* Y : 최장 공통 부분 수열을 비교할 두 문자열
	- int i, int j : 두 문자열 X, Y 의 길이이자, LCS 테이블 상에서 최장 공통 부분 수열의 길이값이 저장된 위치
	- LCSTable* Table : LCS 알고리즘을 최적 부분 구조로 풀기 위해, 부분 문제들의 해를 저장해 둘 테이블
*/
int LCS(char* X, char* Y, int i, int j, LCSTable* Table)
{

}
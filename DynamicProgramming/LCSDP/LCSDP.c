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
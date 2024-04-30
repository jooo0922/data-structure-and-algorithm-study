#ifndef MAKING_CHANGE
#define MAKING_CHANGE
/*
	여기서 사용된 #ifndef ~ #endif 전처리기는
	헤더파일의 헤더가드를 처리해주는 방법 중 하나였지?

	cpp-study > TBCppStudy > Chapter1_12 > add.h 필기 참고!
*/

#include <stdio.h> // printf(), scanf() 같은 입출력 함수 선언이 포함된 헤더파일
#include <stdlib.h> // malloc(), free() 같은 메모리 할당 함수 선언이 포함된 헤더파일
// -> 헤더파일에 포함되어 있어야, 이를 가져다 쓰는 .c 파일들에서 사용할 때 에러가 안남.

void GetChange(int Price, int Pay, int CoinUnits[], int Change[], int Size); // 거스름돈 계산 함수 (해 선택)
int CountCoins(int Amount, int CoinUnit); // 거스름돈 계산 시, 각 동전 단위별 갯수 반환 함수 (실행 가능성 검사 및 해 검사)
void PrintChange(int CoinUnits[], int Change[], int Size); // 거스름돈 출력 함수

#endif // !MAKING_CHANGE

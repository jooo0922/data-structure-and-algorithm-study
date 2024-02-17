#ifndef BOYREMOORE_H
#define BOYREMOORE_H
/*
	여기서 사용된 #ifndef ~ #endif 전처리기는
	헤더파일의 헤더가드를 처리해주는 방법 중 하나였지?

	cpp-study > TBCppStudy > Chapter1_12 > add.h 필기 참고!
*/

// 보이어 무어 알고리즘
int BoyreMoore(char* Text, int TextSize, int Start, char* Pattern, int PatternSize, int* BadCharTable, int* GoodSuffTable, int* PosOfBorder);

// 나쁜 문자 이동 테이블 구축
void BuildBCT(char* Pattern, int PatternSize, int* BadCharTable);

// 착한 접미부 이동 테이블 구축
void BuildGST(char* Pattern, int PatternSize, int* PosOfBorder, int* GoodSuffTable);

// 더 큰 이동거리 비교 함수
int Max(int A, int B);

#endif // !BOYREMOORE_H

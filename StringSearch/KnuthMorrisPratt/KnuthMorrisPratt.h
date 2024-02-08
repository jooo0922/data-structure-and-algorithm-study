#ifndef KNUTHMORRISPRATT_H
#define KNUTHMORRISPRATT_H
/*
	여기서 사용된 #ifndef ~ #endif 전처리기는
	헤더파일의 헤더가드를 처리해주는 방법 중 하나였지?

	cpp-study > TBCppStudy > Chapter1_12 > add.h 필기 참고!
*/

// KMP 알고리즘
int KnuthMorrisPratt(char* Text, int TextSize, int Start, char* Pattern, int PatternSize);

// 최대 경계 너비 테이블 구축
void Preprocess(char* Pattern, int PatternSize, int* Border);

#endif // !KNUTHMORRISPRATT_H
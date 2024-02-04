#ifndef KARPRABIN_H
#define KARPRABIN_H
/*
	여기서 사용된 #ifndef ~ #endif 전처리기는
	헤더파일의 헤더가드를 처리해주는 방법 중 하나였지?

	cpp-study > TBCppStudy > Chapter1_12 > add.h 필기 참고!
*/

// 카프-라빈 알고리즘
int KarpRabin(char* Text, int TextSize, int Start, char* Pattern, int PatternSize);

// p.463 기존 해시 함수 
// (패턴의 해시값과 최초의 하위 문자열 해시값 계산)
int Hash(char* String, int Size);

// p.465 최적화된 해시 함수 
// (이전 하위 문자열 해시값 Hᵢ₋₁ 을 사용하여 현재 탐색할 하위 문자열 해시값 Hᵢ 계산)
int ReHash(char* String, int Start, int Size, int HashPrev, int Coefficient);

#endif // !KARPRABIN_H

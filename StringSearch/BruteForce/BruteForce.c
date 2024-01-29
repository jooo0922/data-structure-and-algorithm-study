#include "BruteForce.h"

// 고지식한 탐색 알고리즘
/*
	매개변수는 다음과 같음

	1. Text : 본문 문자열
	2. TextSize : 본문 문자열 크기
	3. Start : 본문 문자열을 탐색할 위치
	4. Pattern : 탐색할 단어 문자열
	5. PatternSize : 탐색할 단어 문자열 크기
*/
int BruteForce(char* Text, int TextSize, int Start, char* Pattern, int PatternSize)
{
	// 본문 위치 인덱스 초기화
	int i = 0;

	// 패턴 위치 인덱스 초기화
	int j = 0; 

	// '본문 크기 - 패턴 크기' 위치까지만 본문 문자열을 순회하며 탐색
	for (i = Start; i < TextSize - PatternSize; i++)
	{
		// '패턴 크기' 위치까지 패턴의 모든 문자열(Pattern[j])과 
		// 패턴의 각 문자열 위치에 대응되는, i 부터 시작해서 i + j 까지의 본문의 모든 문자열(Text[i + j]) 을 비교함.
		for (j = 0; j < PatternSize; j++)
		{
			if (Text[i + j] != Pattern[j])
			{
				/*
					본문과 패턴의 각 문자를 비교했을 때, 
					서로 다르면 반복문을 중단함.
				*/
				break;
			}
		}

		/*
			반복문 종료 후,
			j 가 패턴의 크기 이상이라면,
			패턴 내의 모든 문자열 비교를 통과했다는 뜻!

			따라서, 본문 상에서 문자 비교를 시작한 위치 i 를 반환!
		*/
		if (j >= PatternSize)
		{
			return i;
		}
	}

	// 이중 for-loop 를 모두 순회해도 패턴을 찾지 못했다면 -1 반환
	return -1;
}

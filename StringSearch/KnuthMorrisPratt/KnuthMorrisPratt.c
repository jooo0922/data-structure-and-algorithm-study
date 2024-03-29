#include "KnuthMorrisPratt.h"
#include <stdlib.h> // calloc() 을 사용하기 위해 포함

// 최대 경계 너비 테이블 구축
/*
	참고로, 최대 경계 너비 테이블 구축 함수를 구현한 코드는
	p.474 ~ 475 에서 설명한 과정이 직관적으로 보이지 않을 수 있음.

	왜냐하면, p.474 ~ 475 에서 설명한 과정과 달리,
	'고정 패턴', '이동 패턴' 이라는 두 개의 개념을 도입하여
	코드로 구현된 것이기 때문에,

	두 패턴을 탐색하며 불일치가 발생할 때마다,
	최대 경계 너비값에 해당하는 위치로 움직이는 '이동 패턴'이 있다고
	상상하고 코드를 이해해야 함.

	완벽하게 이해가 가지 않더라도,
	p.474 ~ 475 의 예시를 Preprocess() 코드에 대입해서
	머릿속으로 상상해보면 왜 이렇게 짠 것인지 이해가 될 것임.
*/
void Preprocess(char* Pattern, int PatternSize, int* Border)
{
	// 고정 패턴의 탐색 위치
	int i = 0;

	// 이동 패턴의 탐색 위치
	int j = -1;

	// 최대 경계 너비 테이블의 첫 번째 경계 너비는 항상 -1 로 초기화
	Border[0] = -1;

	// 고정 패턴의 각 문자들을 순회하며 최대 경계 너비 캐싱
	while (i < PatternSize)
	{
		/*
			1. 이동 패턴의 탐색 위치(j)가 -1 보다는 크다는 전제 하에,

			2. 고정 패턴의 현재 문자(Pattern[i])와
			이동 패턴의 현재 문자(Pattern[j])를 비교하여 불일치가 발생했다면,

			불일치가 발생한 지점의 최대 경계 너비값으로
			이동 패턴의 탐색 위치를 초기화함
		*/
		while (j > -1 && Pattern[i] != Pattern[j])
		{
			j = Border[j];

			/*
				이동 패턴의 탐색 위치(j) 초기화 이후,
				
				이동 패턴의 탐색 위치가 다시 -1 로 초기화 되었거나,

				고정 패턴의 현재 문자(Pattern[i])와
				이동 패턴의 현재 문자(Pattern[j]) 가 같아질 때까지
				
				이동 패턴의 탐색 위치(j) 를 계속 초기화하면서 이동시킴!
			*/
		}

		/*
			안쪽 while 문에 의해
			이동 패턴의 탐색 문자와 
			고정 패턴의 탐색 문자가 비로소 같아졌다면,

			두 패턴의 탐색 위치를 1씩 증가시킴
		*/
		i++;
		j++;

		// 현재 고정 패턴의 탐색 위치에 최대 경계 너비를 저장해 둠.
		Border[i] = j;
	}
}

// KMP 알고리즘
/*
	매개변수는 다음과 같음

	1. Text : 본문 문자열
	2. TextSize : 본문 문자열 크기
	3. Start : 본문 문자열을 탐색할 위치
	4. Pattern : 탐색할 단어 문자열
	5. PatternSize : 탐색할 단어 문자열 크기
*/
int KnuthMorrisPratt(char* Text, int TextSize, int Start, char* Pattern, int PatternSize)
{
	// 본문 상의 탐색 위치
	int i = Start;

	// 패턴 상의 탐색 위치
	int j = 0;

	// 문자열이 일치하는 지점의 본문 위치를 저장할 변수 초기화
	int Position = -1;

	// 최대 경계 너비 테이블을 구축할 동적 배열 메모리 할당
	int* Border = (int*)calloc(PatternSize + 1, sizeof(int));

	// 최대 경계 너비 테이블 구축
	Preprocess(Pattern, PatternSize, Border);

	// 본문의 각 문자들을 순회하며 탐색
	while (i < TextSize)
	{
		/*
			본문과 각 문자(Text[i])와 
			패턴의 각 문자(Pattern[j])를 비교하다가
			불일치하는 지점을 마주쳤을 때,

			패턴 상의 탐색 위치(j)를
			불일치가 발생한 지점의 최대 경계 너비값으로 초기화함.
		*/
		while (j >= 0 && Text[i] != Pattern[j])
		{
			/*
				p.472 의 예제로 치면,
				불일치가 발생한 5번 위치에서 (즉, i, j 모두 5일 때)
				
				최대 경계 너비 테이블의 5번 위치에 저장된 
				경계 너비 2로 패턴 탐색 위치(j) 를 초기화한 것!

				-> 이 상태에서 다시 본문의 문자(Text[i])와 
				패턴의 문자(Pattern[j])가 일치할 때까지
				안쪽 while 문을 계속 순회해야 하기 때문에,

				다음 안쪽 while 문 순회에서는
				Text[5] 와 Pattern[2] 를 비교하기 시작하겠지!

				-> 이것이 p.473 에서 본문과 패턴에서 이미
				일치하는 문자들의 비교는 건너뛰고, 5번 위치부터
				검색을 재개하는 것과 동일한 상황임!
			*/
			j = Border[j];
		}

		/*
			본문과 패턴의 두 문자가 일치하면,
			다음 문자들을 탐색하기 위해 각각의 탐색 위치를 1씩 증가시킴.
		*/
		i++;
		j++;

		/*
			패턴의 탐색 위치(j)가 패턴의 길이(PatternSize) 와 같다면,
			
			불일치 발생으로 인한 
			패턴의 탐색 위치(j) 초기화(즉, j = Border[j];) 없이,
			패턴의 모든 문자들 순회를 완수했다는 뜻임.

			즉, 패턴과 일치하는 부분 문자열을 찾았다는 뜻!
		*/
		if (j == PatternSize)
		{
			/*
				패턴과 일치하는 문자열의 시작 위치를 계산하기 위해,
				'본문 탐색 위치(i) - 패턴 탐색 위치(j)' 를 계산해 줌!

				주! p.475 의 '이동거리 = 일치 접두부의 길이 - 최대 경계 너비'
				와 무관한 공식임!
			*/
			Position = i - j;
			break;
		}
	}

	// 최대 경계 너비 테이블 메모리 제거
	free(Border);

	// 패턴과 일치하는 문자열 탐색 위치 반환
	return Position;
}

/*
	calloc() vs malloc()

	
	두 함수 모두 힙 메모리 영역에
	동적으로 메모리를 할당하는 기능을 수행함.

	그러나, 크게 두 가지 차이점이 있는데,

	1. calloc() 은 할당된 메모리를 모두 0으로 초기화하는 반면,
	malloc() 은 할당된 메모리를 초기화하지 않음 -> 그래서 malloc() 이 좀 더 빠름!

	2. calloc() 은 매개변수로 
	힙 메모리에 할당할 동적 배열의 개수와
	동적 배열에 추가되는 단일 요소의 메모리 크기를 받는 반면,

	malloc() 은 오로지 할당할 전체 메모리의 크기만
	매개변수로 받게 되어 있음.

	물론, 둘 다 동적 배열을 힙 메모리에 할당할 수 있지만,

	아무래도 매개변수 구조 상 calloc() 이 
	'동적 배열의 메모리'를 할당하기 위한 구조화가 
	더 잘 되어있다고 볼 수 있음.
*/
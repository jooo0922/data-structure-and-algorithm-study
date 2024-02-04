#include "KarpRabin.h"
#include <stdio.h>
#include <math.h> // pow() 를 사용하기 위해 포함

// 카프-라빈 알고리즘
/*
	매개변수는 다음과 같음

	1. Text : 본문 문자열
	2. TextSize : 본문 문자열 크기
	3. Start : 본문 문자열을 탐색할 위치
	4. Pattern : 탐색할 단어 문자열
	5. PatternSize : 탐색할 단어 문자열 크기
*/
int KarpRabin(char* Text, int TextSize, int Start, char* Pattern, int PatternSize)
{
	// 본문 위치 인덱스 초기화
	int i = 0;

	// 패턴 위치 인덱스 초기화
	int j = 0;

	// p.465 의 최적화된 해시 함수의 계수 2ᵐ⁻¹ 을 미리 계산하여 초기화한 변수
	// 프로그래밍에서 Coefficient 는 미리 계산할 수 있는 계수나 상수에 대한 통상적 표현
	int Coefficient = pow(2, PatternSize - 1);

	// 패턴의 해시값과 최초의 하위 문자열 해시값을 계산하여 초기화
	int HashText = Hash(Text, PatternSize);
	int HashPattern = Hash(Pattern, PatternSize);

	// '본문 크기 - 패턴 크기' 위치까지만 본문 문자열을 순회하며 탐색
	for (i = Start; i < TextSize - PatternSize; i++)
	{
		/*
			이제 위에서 계산된 기존 해시값을 알고 있으므로, 
			
			기존 해시값 HashText(이전 하위 문자열 해시값 Hᵢ₋₁) 을 사용하여

			현재 탐색할 하위 문자열 해시값 Hᵢ 을 계산하여 반환받은 후,
			HashText 에 할당된 해시값을 업데이트함.
		*/
		HashText = ReHash(Text, i, PatternSize, HashText, Coefficient);

		/*
			현재 탐색중인 하위 문자열 해시값 Hᵢ(HashText) 이 
			패턴 문자열의 해시값 HashPattern 과 일치하는지 검사
		*/
		if (HashPattern == HashText)
		{
			/*
				해시값이 일치한다고 하더라도,
				
				해시 충돌로 인해 서로 다른 문자열임에도
				같은 해시값이 튀어나온 것일 수도 있으므로,

				현재 탐색중인 하위 문자열과 
				패턴 문자열을 직접 비교하여 일치하는지 재검증함.

				(문자열 직접 비교는 BruteForce 알고리즘의 코드를 그대로 가져옴.)
			*/
			for ( j = 0; j < PatternSize; j++)
			{
				// '패턴 크기' 위치까지 패턴의 모든 문자(Pattern[j])들과 
				// 패턴의 각 문자 위치에 대응되는, i 부터 시작해서 i + j 까지의 본문의 모든 문자(Text[i + j]) 들을 비교함.
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
	}

	// 이중 for-loop 를 모두 순회해도 패턴을 찾지 못했다면 -1 반환
	return -1;
}

// p.463 기존 해시 함수 
// (패턴의 해시값과 최초의 하위 문자열 해시값 H₀ 계산)
int Hash(char* String, int Size)
{
	// 하위 문자열을 순회할 때 사용할 인덱스 값 초기화
	int i = 0;

	// p.463 기존 해시 함수로 계산된 해시값을 저장할 변수 초기화
	int HashValue = 0;

	/*
		for 문을 이용하여 p.463 기존 해시 함수를 코드로 구현

		왜 아래 코드처럼 구현된 것인지는
		노란색 필기노트에 정리해 둠.
	*/
	/*
		이 예제에서 구현된 Hash 함수들은
		해시 테이블의 사이즈 q, 즉, 최대 해시값을
		32 bits signed int 타입으로 표현할 수 있는 최대 정수값인
		'2,147,483,647' 로 가정함.

		따라서, 이 최대 해시값 q 를 넘는 해시값이 계산될 경우,
		그냥 overflow 된 최대 해시값 q 를 그대로 반환해도 아무런 문제가 없음.
		따라서, 최대 해시값 q 에 대한 나머지 연산(== 나눗셈법)을 생략함.

		왜냐하면, 카프-라빈 문자열 탐색에서
		해시 함수를 사용하는 목적은 문자열을 더 빠르게 비교하기 위함이지,

		실제 해시 테이블 자료구조처럼 해시 충돌, 테이블 크기 overflow 등의
		케이스를 엄밀하게 처리할 필요가 없기 때문임.
	*/
	for (i = 0; i < Size; i++)
	{
		HashValue = String[i] + (HashValue * 2);
	}

	// 계산된 해시값 최종 반환
	return HashValue;
}

// p.465 최적화된 해시 함수 
// (이전 하위 문자열 해시값 Hᵢ₋₁ 을 사용하여 현재 탐색할 하위 문자열 해시값 Hᵢ 계산)
/*
	매개변수는 다음과 같음

	1. String : 본문 문자열
	2. Start : 현재 탐색중인 하위 문자열의 시작 위치
	3. Size : 현재 탐색중인 하위 문자열의 길이 (== 패턴 문자열의 길이)
	4. HashPrev : 이전 하위 문자열의 해시값 Hᵢ₋₁
	5. Coefficient : p.465 최적화된 해시 함수 내의 계수 2ᵐ⁻¹ 를 미리 계산하여 전달할 매개변수
*/
int ReHash(char* String, int Start, int Size, int HashPrev, int Coefficient)
{
	if (Start == 0)
	{
		/*
			하위 문자열의 시작 위치가 0이면,
			결국 최초의 하위 문자열 해시값 H₀ 을 구하려는 것이므로,
			
			그냥 이전 하위 문자열의 해시값 (HashPrev)을 반환함.

			그런데, 애초에 최초의 하위 문자열 해시값 H₀ 의
			이전 하위 문자열 해시값 H₀₋₁ 자체는 존재하지 않는 값이므로,
			애초부터 int Start 매개변수에 0을 넘겨주면 안됨.
		
			애초에 최초의 하위 문자열 해시값 H₀ 은 ReHash() 함수가 아닌,
			Hash() 함수로 구해야 하므로, 이 block 은 일종의 예외처리 부분이라고 보면 됨.
		*/
		return HashPrev;
	}

	/*
		p.465 최적화된 해시 함수 코드로 구현

		참고로, Hash() 함수에서와 마찬가지로
		최대 해시값 q 에 대한 나머지 연산 mod q 를 생략함.
	*/
	return String[Start + Size - 1] +
		((HashPrev - Coefficient * String[Start - 1]) * 2);
}

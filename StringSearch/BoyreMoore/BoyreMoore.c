#include "BoyreMoore.h"
#include <stdlib.h> // calloc() 을 사용하기 위해 포함

// 보이어 무어 알고리즘
/*
	매개변수는 다음과 같음

	1. Text : 본문 문자열
	2. TextSize : 본문 문자열 크기
	3. Start : 본문 문자열을 탐색할 위치
	4. Pattern : 탐색할 단어 문자열
	5. PatternSize : 탐색할 단어 문자열 크기
*/
int BoyreMoore(char* Text, int TextSize, int Start, char* Pattern, int PatternSize)
{
	// 나쁜 문자 이동 테이블 메모리 할당 (정적 배열)
	int BadCharTable[128];

	/*
		착한 접미부 이동 테이블 메모리 할당 (동적 배열)

		calloc() 을 사용하여 
		할당된 배열의 메모리의 값들을 0으로 초기화함.
		
		또한, p.485 테이블처럼
		패턴 맨 끝에 빈 문자열에 대한 테이블도 구성해야 하므로,
		실제 패턴 크기보다 1만큼 더 크게 메모리를 할당함.
	*/
	// 이동 거리
	int* GoodSuffTable = (int*)calloc(PatternSize + 1, sizeof(int));
	// 각 접미부 X 의 가장 넓은 경계의 시작 위치
	int* PosOfBorder = (int*)calloc(PatternSize + 1, sizeof(int));

	// 본문 탐색 위치
	int i = Start;

	// 패턴 탐색 위치
	int j = 0;

	// 패턴과 일치하는 본문 상의 시작 위치를 저장할 변수 초기화
	int Position = -1;
	
	// 나쁜 문자 이동 테이블 구축
	BuildBCT(Pattern, PatternSize, BadCharTable);

	// 착한 접미부 이동 테이블 구축
	BuildGST(Pattern, PatternSize, PosOfBorder, GoodSuffTable);

	// 본문의 문자열 순회
	while (i <= TextSize - PatternSize)
	{
		j = PatternSize - 1;

		/*
			패턴의 문자열 순회 
			
			보이어 무어 알고리즘은 오른쪽 -> 왼쪽 순으로 순회함. 
			이 때, 순회하며 본문과 패턴의 각 문자를 비교
		*/
		while (j >= 0 && Pattern[j] == Text[i + j])
		{
			j--;
		}

		// while 문 탈출
		if (j < 0)
		{
			// 패턴을 모두 무사히 순회하며 while 문을 탈출한 경우

			// 패턴과 일치하는 본문 상의 시작 위치 저장 후 루프 탈출
			Position = i;
			break;
		}
		else
		{
			// 패턴을 순회하다가 중간에 불일치가 발생하여 while 문을 탈출한 경우

			/*
				착한 접미부 이동 테이블과
				나쁜 문자 이동 테이블로부터

				각각 이동거리를 계산한 뒤,
				더 멀리 이동하는 거리를 선택하여
				본문 탐색 위치 i 에 누산함.

				참고로, 
				GoodSuffTable[j + 1] 는
				패턴 상에서 불일치가 발생한 위치의 오른쪽,
				그러니까 착한 접미부 x 의 시작 위치를 의미함.

				이 착한 접미부 시작 위치에 저장된
				착한 접미부 이동 테이블 상의 이동거리를 가져오려는 것임.

				또한, Text[i + j] 는
				불일치가 발생한 본문 위치의 문자를 뜻하고,

				BadCharTable[Text[i + j]] 는
				해당 문자의 아스키 코드 위치에 저장된
				패턴 상에서 가장 오른쪽에 있는 불일치 문자의 위치값을
				나쁜 문자 이동 테이블에서 가져오려는 것임!

				현재 패턴 위치인 j 에 이 위치값을 빼주면,
				나쁜 문자 이동의 이동거리가 나오겠지!
			*/
			i += Max(GoodSuffTable[j + 1], j - BadCharTable[Text[i + j]]);
		}
	}

	// 문자열 탐색 종료 후, calloc() 으로 동적 할당했던 테이블 메모리 반납
	free(PosOfBorder);
	free(GoodSuffTable);

	// 패턴과 일치하는 본문 상의 하위 문자열 시작 위치 반환
	return Position;
}

// 나쁜 문자 이동 테이블 구축
void BuildBCT(char* Pattern, int PatternSize, int* BadCharTable)
{
	int i;
	int j;

	for (i = 0; i < 128; i++)
	{
		/*
			모든 아스키 문자(총 128개)를 입력할 수 있는
			정적 배열인 int BadCharTable[128] 을
			모두 -1 로 초기화
		*/
		BadCharTable[i] = -1;
	}

	for ( j = 0; j < PatternSize; j++)
	{
		/*
			패턴 내의 각 문자의 아스키 코드 자리에
			패턴 상의 해당 문자의 위치값을 기록함.

			이때, 동일한 아스키 코드의 문자라면,
			이전의 위치값을 덮어씀으로써,

			패턴 상에서 가장 오른쪽에 위치하는 문자의 위치값이
			최종적으로 테이블에 기록되도록 함.
		*/
		BadCharTable[Pattern[j]] = j;
	}
}

// 착한 접미부 이동 테이블 구축
void BuildGST(char* Pattern, int PatternSize, int* PosOfBorder, int* GoodSuffTable)
{

}

// 더 큰 이동거리 비교 함수
int Max(int A, int B)
{

}
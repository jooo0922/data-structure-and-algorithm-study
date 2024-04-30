#include "MakingChange.h"

// 거스름돈 계산 함수 (해 선택)
/*
	매개변수 정리

	- int Price : 가격 
	- int Pay : 지불 금액
	- int CoinUnits[] : 입력된 동전의 단위들 (정적 배열) -> qsort() 내장함수에 의해 내림차순 정렬됨.
	- int Change[] : 입력된 각 동전 단위별 갯수. 즉, 거스름돈 총액이 담긴 배열 -> '부분해 집합(Solution Set)'. p.574 참고
	- int Size : 입력된 동전 단위들의 가짓수
*/
void GetChange(int Price, int Pay, int CoinUnits[], int Change[], int Size)
{
	// 입력된 동전 단위 배열을 순회할 인덱스
	int i = 0;

	// 지불해야 할 거스름돈 총액
	int ChangeAmount = Pay - Price;

	/*
		입력된 동전 단위 배열(CoinUnits)을 순회하면서 
		거스름돈 총액을 지불하기 위해 필요한 
		각 동전 단위들의 갯수 계산 
	*/
	for (i = 0; i < Size; i++)
	{
		/*
			내림차순으로 정렬된 동전 단위 배열을 순회하므로,
			거스름돈을 구성하는 데 필요한 동전들 중, 더 큰 단위의 동전의 갯수를 먼저 계산함.

			따라서, 매 순회마다 앞에 남아있는(순회할) 동전 단위들이 
			뭐가 있는지는 살펴 볼 생각도 안하고,
			
			일단 '현재 상태에서 가장 큰 동전 단위를 먼저 선택해서' 
			갯수를 계산하게 됨.

			-> 즉, 앞으로 남아있는 선택지들은 생각하지 않고, 
			'현재 상태에서 가장 좋은 해'만 먼저 선택해서 거스름돈에 추가함.
			이러한 방식으로 부분 문제의 해를 '근시안적'으로 고르는 것을 
			'탐욕 알고리즘' 이라고 함!

			또한, 선택한 가장 큰 동전 단위의 갯수를 반환받았으면,
			부분해 집합인 Change[] 정적 배열에 현재 선택한 동전 갯수(부분해)를 추가함.
		*/
		Change[i] = CountCoins(ChangeAmount, CoinUnits[i]);
	
		// 부분해 집합에 추가한 만큼의 금액(동전 단위 * 개수)만큼 거스름돈 총액에서 차감함
		ChangeAmount = ChangeAmount - (CoinUnits[i] * Change[i]);
	}
}

// 거스름돈 계산 시, 각 동전 단위별 갯수 반환 함수 (실행 가능성 검사 및 해 검사)
/*
	매개변수 정리

	- int Amount : 거스름돈 총액에서 현재까지 차감되고 남은 거스름돈 액수
	- int CoinUnit : 현재 순회에서 선택한 가장 큰 동전 단위 -> 근시안적으로 고른 부분 문제의 최적해
*/
int CountCoins(int Amount, int CoinUnit)
{
	// 동전 갯수
	int CoinCount = 0;

	// 반복문을 돌며 차감하기 위해 남은 거스름돈 액수를 복사함
	int CurrentAmount = Amount;

	/*
		현재 순회에서 선택한 가장 큰 동전 단위보다 
		남은 거스름돈 액수가 더 작아질 때까지 
		(-> p.574 2번 과정에서 말한 '문제의 제약조건'을 검사한 것.
		즉, '거스름돈 총액을 넘기지 않을 때까지만' 동전 갯수를 카운팅하는 것.) 

		반복문을 순회하며 
		현재 순회에서 선택한 동전 단위의 갯수를 계속 늘려나감
	*/
	while (CurrentAmount >= CoinUnit)
	{
		// 동전 갯수 카운딩
		CoinCount++;

		// 반복문을 돌며 복사된 남은 거스름돈 액수를 차감해나감.
		CurrentAmount = CurrentAmount - CoinUnit;
	}

	// 반복문 종료 후, 지금까지 카운팅된 동전 갯수 반환
	return CoinCount;
}

// 거스름돈 출력 함수
void PrintChange(int CoinUnits[], int Change[], int Size)
{

}

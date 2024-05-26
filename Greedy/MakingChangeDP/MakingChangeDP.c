#include "MakingChangeDP.h"
#include <string.h>

// 거스름돈 계산 함수 (해 선택)
/*
	매개변수 정리

	- int Price : 가격
	- int Pay : 지불 금액
	- int CoinUnits[] : 입력된 동전의 단위들 (정적 배열) -> qsort() 내장함수에 의해 내림차순 정렬됨.
	- int Change[] : 입력된 각 동전 단위별 갯수. 즉, 거스름돈 총액이 담긴 배열
	- int Size : 입력된 동전 단위들의 가짓수
*/
void GetChangeDP(int Price, int Pay, int CoinUnits[], int Change[], int Size)
{
	// 지불해야 할 거스름돈 총액
	int ChangeAmount = Pay - Price;

	// 1원부터 ChangeAmount원 까지의 최소 동전 개수(부분해)를 담는 DPTable 메모리 할당
	int* MinCoins = (int*)malloc(sizeof(int) * (ChangeAmount + 1));

	// DPTable 초기화
	for (int i = 0; i <= ChangeAmount; i++) {
		MinCoins[i] = INT_MAX;
	}

	// 거스름돈이 0원이면 최소 동전 개수는 0개로 초기화
	MinCoins[0] = 0;

	// 동적 계획법으로 각 거스름돈(i)의 최소 동전 개수(MinCoins[i])를 계산
	for (int i = 1; i <= ChangeAmount; i++)
	{
		/*
			각 거스름돈 부분해(i)마다 각 동전 단위들(CoinUnits[j])을 뺀 기준의 최소 동전 개수 계산한 후,

			동전 개수가 가장 작은 케이스를
			DPTable 에 저장!

			즉, 거스름돈 M 원에 대한 최소 동전 개수 S(M) 에 대한 점화식인
			S(M) = Min(S(M-C1)+1, S(M-C2)+1, ..., S(M-Cn)+1)
			를 코드로 구현한 것!
			
			위 점화식에서 C1, C2, ..., Cn 은 각 동전 단위들(CoinUnits[j])에 해당!

			이렇게 가장 작은 거스름돈 i의 최소 동전 개수(부분해)부터 계산하여 테이블에 저장하고, 
			
			저장된 부분해를 꺼내서 거스름돈 총액 ChangeAmount 의 최소 동전 개수(전체해)까지 계산하는 것!

			거스름돈 계산 문제를 동적 계획법으로 해결하는 방법 관련
			https://alnova2.tistory.com/1048 참고!
		*/
		for (int j = 0; j < Size; j++)
		{
			if (i >= CoinUnits[j] && MinCoins[i - CoinUnits[j]] != INT_MAX)
			{
				/*
					MinCoins[i - CoinUnits[j]] + 1 은
					위 점화식의 S(M - Cn) + 1 을 코드로 구현한 것이고,

					각 동전 단위들 Cn 에 대한 현재 거스름돈 M 의  
					최소 동전 개수 S(M - Cn) + 1의 최솟값(위 점화식에서 Min(...) 에 해당)
					을 구하는 과정이 안쪽 for 문을 돌면서
					MinCoins[i]의 최솟값을 업데이트하는 방식으로 구현된 것임!
				*/
				if (MinCoins[i] > MinCoins[i - CoinUnits[j]] + 1)
				{
					MinCoins[i] = MinCoins[i - CoinUnits[j]] + 1;
				}
			}
		}
	}

	// Change 배열 초기화
	for (int i = 0; i < Size; i++)
	{
		Change[i] = 0;
	}

	/*
		동적 계획법으로 구축한 MinCoins 테이블에 저장된 부분해를 사용하여
		거스름돈 총액(ChangeAmount)을 지불하기 위한
		각 동전들의 최소 개수를 Change 배열에 계산
	*/
	int amount = ChangeAmount;
	while (amount > 0)
	{
		for (int i = 0; i < Size; i++)
		{
			if (amount >= CoinUnits[i] && MinCoins[amount] == MinCoins[amount - CoinUnits[i]] + 1)
			{
				Change[i]++;
				amount -= CoinUnits[i];
				break;
			}
		}
	}

	free(MinCoins);
}

// 거스름돈 출력 함수
/*
	매개변수 정리

	- int CoinUnits[] : 입력받은 동전 단위들의 배열
	- int Change[] : 거스름돈 총액. 즉, 각 동전 단위별 갯수 -> 부분해 집합
	- int Size : 입력받은 동전 단위 가짓수
*/
void PrintChange(int CoinUnits[], int Change[], int Size)
{
	int i = 0;

	/*
		입력받은 동전 단위들을 순회하며
		거스름돈 총액을 구성하는 각 동전들의 갯수를 출력함
	*/
	for (i = 0; i < Size; i++)
	{
		printf("%8d won : %d\n", CoinUnits[i], Change[i]);
	}
}

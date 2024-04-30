#include "MakingChange.h"


// 입력받은 동전 단위들을 내림차순으로 정렬할 때 사용할 비교함수
int Compare(const void* a, const void* b)
{
	// 매개변수 a, b 를 각각 int* 타입의 포인터 변수로 형변환한 후, de-referencing 하여 int 값을 복사
	int _a = *(int*)a;
	int _b = *(int*)b;

	if (_a < _b)
	{
		return 1;
	}
	else
	{
		return -1;
	}
}

int main()
{
	int i = 0;
	int Pay = 0;
	int Price = 0;
	int UnitCount = 0;
	int* CoinUnits = NULL;
	int* Change = NULL;

	// 동전 단위의 가짓수를 입력받음
	printf("Enter Unit Count :");
	scanf_s("%d", &UnitCount);

	// 동전 단위들을 입력받을 동적 배열 메모리 할당
	CoinUnits = (int*)malloc(sizeof(int) * UnitCount);
	
	// 각 동전 단위들의 갯수를 계산하여 저장할 동적 배열 메모리 할당 -> 즉, 부분해 집합의 메모리 할당
	Change = (int*)malloc(sizeof(int) * UnitCount);

	// 입력받은 동전 단위 가짓수 만큼 반복문을 순회하며 각 동전 단위를 입력받음
	for (i = 0; i < UnitCount; i++)
	{
		printf("Enter [%d] th Coin Unit : ", i);
		scanf_s("%d", &CoinUnits[i]);
	}

	// 입력받은 동전 단위 배열을 내림차순으로 퀵 정렬 (p.227 참고)
	qsort(CoinUnits, UnitCount, sizeof(int), Compare);

	// 물건 가격을 입력받음
	printf("Enter Price : ");
	scanf_s("%d", &Price);

	// 지불 금액을 입력받음
	printf("Enter Pay : ");
	scanf_s("%d", &Pay);

	// 거스름돈 총액을 구성한 부분해 집합(Change[])를 채움
	GetChange(Price, Pay, CoinUnits, Change, UnitCount);

	// 거스름돈 총액 (-> 부분해 집합) 출력
	PrintChange(CoinUnits, Change, UnitCount);

	return 0;
}
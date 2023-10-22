#include <stdio.h>

// 배열 순차탐색 함수
int SequentialSearch(int DataSet[], int Length, int Target)
{
	int Current = NULL; // 순차탐색 시 순회할 값 초기화
	int Match = NULL; // 찾고자 하는 값을 임시로 저장해 둘 변수 초기화

	// 정적 배열 길이만큼 순회하며 순차탐색
	for (int i = 0; i < Length; i++)
	{
		Current = DataSet[i];
		if (Current == Target)
		{
			// 찾고자 하는 값을 발견했다면, 해당 요소를 Match 에 저장
			Match = Current;
			break;
		}
	}

	// 찾고자 하는 값이 저장된 변수를 반환함.
	return Match;
}

int main()
{
	int DataSet[] = { 6, 4, 2, 3, 1, 5 }; // 순차탐색할 정적 배열 선언 및 초기화
	int Length = sizeof DataSet / sizeof DataSet[0]; // 정적 배열 길이 계산하여 저장

	// 순차탐색으로 정적 배열에서 3을 탐색한다는 메시지 출력
	printf("Search Node which has value of 3 by Sequential Search...\n");

	// 배열 순차탐색 수행
	int MatchValue = SequentialSearch(DataSet, Length, 3);
	if (MatchValue == NULL)
	{
		// 순차탐색 결과 해당 요소가 없을 경우, 탐색에 실패했다는 메시지 출력
		printf("Node Not Found!\n");
	}
	else
	{
		// 순차탐색 결과 해당 요소를 발견했다면, 요소의 값을 출력
		printf("Match Value : %d\n", MatchValue);
	}

	return 0;
}
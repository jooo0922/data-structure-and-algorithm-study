#include <stdio.h>
#include <string.h> // memmove() 사용을 위해 포함

// 배열 순차탐색 함수
int ARR_SequentialSearch(int DataSet[], int Length, int Target)
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

// 배열 전진이동법 순차탐색 함수
int ARR_MoveToFront(int DataSet[], int Length, int Target)
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

			// 0번 요소부터 찾고자 하는 값을 발견한 i번 요소까지 한 칸 씩 뒤로 이동 (전진 이동법)
			/*
				memmove()

				배열처럼 연속된 데이터를 메모리 상에서 단번에 이동시킬 때 쓰기 좋음.

				첫 번째 매개변수 : 연속된 원본 데이터를 옮길 메모리 공간의 시작 지점 주소
				두 번째 매개변수 : 연속된 원본 데이터의 시작 지점 주소
				세 번째 매개변수 : 이동하는 연속된 원본 데이터의 메모리 크기 (= 옮길 원본 데이터의 시작 지점 요소와 정렬범위 마지막 요소 사이의 메모리 간격)
			*/
			memmove(&DataSet[1], &DataSet[0], sizeof(DataSet[0]) * i);

			// 찾고자 하는 요소의 값을 정적 배열에서 맨앞으로 이동
			DataSet[0] = Match;

			// 원하는 요소를 찾았으니 순차 탐색 종료
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

	// 탐색할 정적 배열 출력
	printf("Printing DataSet...\n");
	for (unsigned int i = 0; i < Length; i++)
	{
		printf("%d ", DataSet[i]);
	}
	printf("\n");

	// 순차탐색으로 정적 배열에서 3을 탐색한다는 메시지 출력
	//printf("Search Node which has value of 3 by Sequential Search...\n");

	// 배열 순차탐색 수행
	//int MatchValue = ARR_SequentialSearch(DataSet, Length, 3);

	// 전진이동법 순차탐색으로 정적 배열에서 3을 탐색한다는 메시지 출력
	printf("\nSearch Node which has value of 3 by Sequential Search with MoveToFront...\n");

	// 배열 순차탐색 수행
	int MatchValue = ARR_MoveToFront(DataSet, Length, 3);
	if (MatchValue == NULL)
	{
		// 순차탐색 결과 해당 요소가 없을 경우, 탐색에 실패했다는 메시지 출력
		printf("Node Not Found!\n");
	}
	else
	{
		// 순차탐색 결과 해당 요소를 발견했다면, 요소의 값을 출력
		printf("Match Value : %d\n", MatchValue);

		// 전진이동법으로 정렬된 배열 출력
		printf("\nPrinting DataSet...\n");
		for (unsigned int i = 0; i < Length; i++)
		{
			printf("%d ", DataSet[i]);
		}
		printf("\n");
	}

	return 0;
}
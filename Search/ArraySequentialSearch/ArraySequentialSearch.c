#include <stdio.h>
#include <string.h> // memmove() 사용을 위해 포함
#include <stdlib.h> // qsort() 퀵 정렬 함수를 사용하기 위해 포함

#include "Node.h"

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
	int Current = NULL; // 순차탐색 시 순회할 변수 초기화
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

// 배열 전위법 순차탐색 함수
int ARR_Transpose(int DataSet[], int Length, int Target)
{
	int Current = NULL; // 순차탐색 시 순회할 변수 초기화
	int Previous = NULL; // 현재 요소의 이전 요소를 저장해 둘 변수 초기화
	int Match = NULL; // 찾고자 하는 값을 임시로 저장해 둘 변수 초기화

	// 정적 배열 길이만큼 순회하며 순차탐색
	for (int i = 0; i < Length; i++)
	{
		Current = DataSet[i];
		Previous = DataSet[i - 1];
		if (Current == Target)
		{
			// 찾고자 하는 값을 발견했다면, 해당 요소를 Match 에 저장
			Match = Current;

			// 현재 요소와 이전 요소를 교환 > 현재 요소가 1칸 앞으로 이동 (전위법)
			DataSet[i - 1] = Current;
			DataSet[i] = Previous;

			// 원하는 요소를 찾았으니 순차 탐색 종료
			break;
		}
	}

	// 찾고자 하는 값이 저장된 변수를 반환함.
	return Match;

}

// 내림차순으로 정렬하는 비교함수 선언 및 구현
int CompareNodeDescend(const void* _elem1, const void* _elem2)
{
	// 두 void* 타입의 주소값을 Node* 타입으로 형변환하여 Node* 타입 포인터 변수에 복사
	Node* elem1 = (Node*)_elem1;
	Node* elem2 = (Node*)_elem2;

	// 두 포인터 변수를 de-referencing 하여 두 Node 구조체의 FrequencyCount 멤버의 값 크기를 비교함
	if (elem1->FrequencyCount > elem2->FrequencyCount)
	{
		// 첫 번째 요소가 두 번째 요소보다 크면 오름차순과 반대로 -1 반환
		return -1;
	}
	else if (elem1->FrequencyCount < elem2->FrequencyCount)
	{
		// 첫 번째 요소가 두 번째 요소보다 작다면 오름차순과 반대로 1 반환
		return 1;
	}
	else
	{
		// 첫 번째 요소와 두 번째 요소가 같다면 0을 반환
		return 0;
	}
}

// 배열 계수법 순차탐색 함수
Node* ARR_FrequencyCount(Node NodeSet[], int Length, int Target)
{
	Node* Current; // 순차탐색 시 순회할 변수 초기화

	// 정적 배열 길이만큼 순회하며 순차탐색
	for (int i = 0; i < Length; i++)
	{
		Current = &NodeSet[i];
		if (Current->Data == Target)
		{
			// 찾고자 하는 노드를 발견했을 때, 노드의 탐색 횟수 증가
			Current->FrequencyCount += 1;

			// 원하는 노드를 찾았으니 순차 탐색 종료
			break;
		}
	}

	// 탐색 횟수를 기준으로 내림차순 퀵 정렬 수행
	qsort((void*)NodeSet, Length, sizeof(Node), CompareNodeDescend);

	// 찾고자 하는 값이 저장된 변수를 반환함.
	return &NodeSet[0];
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
	//printf("\nSearch Node which has value of 3 by Sequential Search with MoveToFront...\n");

	// 배열 순차탐색 수행
	//int MatchValue = ARR_MoveToFront(DataSet, Length, 3);

	// 전위법 순차탐색으로 정적 배열에서 3을 탐색한다는 메시지 출력
	printf("\nSearch Node which has value of 3 by Sequential Search with Transpose...\n");

	// 배열 순차탐색 수행
	int MatchValue = ARR_Transpose(DataSet, Length, 3);

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


	/* 배열 기반 계수법 순차탐색 테스트 코드 */
	int NodeSetLength = sizeof NodeSet / sizeof NodeSet[0]; // 정적 배열 길이 계산하여 저장

	// 탐색할 정적 배열 출력
	printf("\nPrinting NodeSet...\n");
	for (int i = 0; i < NodeSetLength; i++)
	{
		printf("%d ", NodeSet[i].Data);
	}
	printf("\n");

	// 계수법 순차탐색으로 정적 배열에서 3을 탐색한다는 메시지 출력
	printf("\nSearch Node which has value of 3 by Sequential Search with FrequencyCount...\n");

	// 배열 순차탐색 수행
	Node* MatchNode = ARR_FrequencyCount(NodeSet, NodeSetLength, 3);
	MatchNode = ARR_FrequencyCount(NodeSet, NodeSetLength, 6);
	MatchNode = ARR_FrequencyCount(NodeSet, NodeSetLength, 2);
	MatchNode = ARR_FrequencyCount(NodeSet, NodeSetLength, 2);
	MatchNode = ARR_FrequencyCount(NodeSet, NodeSetLength, 3);
	MatchNode = ARR_FrequencyCount(NodeSet, NodeSetLength, 6);
	MatchNode = ARR_FrequencyCount(NodeSet, NodeSetLength, 6);
	MatchNode = ARR_FrequencyCount(NodeSet, NodeSetLength, 3);
	MatchNode = ARR_FrequencyCount(NodeSet, NodeSetLength, 3);

	if (MatchNode == NULL)
	{
		// 순차탐색 결과 해당 요소가 없을 경우, 탐색에 실패했다는 메시지 출력
		printf("Node Not Found!\n");
	}
	else
	{
		// 순차탐색 결과 해당 요소를 발견했다면, 요소의 값을 출력
		printf("Match Node : %d\n", MatchNode->Data);

		// 전진이동법으로 정렬된 배열 출력 (가장 많이 탐색된 순으로 정렬)
		printf("\nPrinting NodeSet...\n");
		for (int i = 0; i < NodeSetLength; i++)
		{
			printf("%d ", NodeSet[i].Data);
		}
		printf("\n");
	}

	return 0;
}
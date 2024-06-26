#include <stdio.h> // printf(), scanf() 같은 입출력 함수 선언이 포함된 헤더파일
#include <stdlib.h> // malloc(), free() 같은 함수 선언이 포함된 헤더파일

// 병합정렬 함수
void MergeSort(int DataSet[], int StartIndex, int EndIndex);

// 분할된 두 하위 데이터를 '정렬하며 합치기' (본문 p.527 ~ p.529 과정을 코드로 구현)
void Merge(int DataSet[], int StartIndex, int MiddleIndex, int EndIndex);

// 병합정렬 함수
/*
	매개변수 목록

	- int DataSet[] : 정렬할 원본 데이터
	- int StartIndex : 현재 하위 데이터의 시작 지점
	- int EndIndex : 현재 하위 데이터의 끝 지점
*/
void MergeSort(int DataSet[], int StartIndex, int EndIndex)
{
	// 현재 하위 데이터의 분할 기준점 위치를 저장할 변수 선언
	int MiddleIndex;

	// 하위 데이터 크기가 1보다 작으면, 하위 데이터가 비어있다는 뜻이므로, 함수를 종료.
	if (EndIndex - StartIndex < 1)
	{
		return;
	}

	// 현재 하위 데이터의 반으로 나눌 기준점 계산
	MiddleIndex = (StartIndex + EndIndex) / 2;

	// 반으로 나눠진 두 하위 데이터의 각각의 시작 지점과 끝 지점을 매개변수로 전달하여 재귀 호출
	MergeSort(DataSet, StartIndex, MiddleIndex);
	MergeSort(DataSet, MiddleIndex + 1, EndIndex);

	// 나눠진 두 하위 데이터를 '정렬하며 합치기' (p.527 ~ 529 과정에 해당)
	Merge(DataSet, StartIndex, MiddleIndex, EndIndex);
}

// 최솟값 반환 util 함수
int getMin(int x, int y) { return (x < y) ? x : y; }

// 반복 병합정렬(재귀 x) 함수
// https://www.geeksforgeeks.org/iterative-merge-sort 참고
void IterativeMergeSort(int DataSet[], int Length)
{
	// 분할된 하위 데이터 크기
	int subDataSetSize; 

	// 병합정렬할 현재 하위 데이터의 시작 인덱스
	int startIndex; 

	/*
		이미 subDataSet 이 1개로 분할(= subDataSetSize)되어 있다고 가정하고,
		bottom -> top 방향으로 iterative 하게 병합정렬 진행
	*/
	// 바깥 쪽 for 문에서는 분할된 하위 데이터(subDataSetSize) 크기를 2배씩 늘려나감
	for (subDataSetSize = 1; subDataSetSize < Length - 1; subDataSetSize *= 2)
	{
		// 안쪽 for 문에서는 현재 분할된 하위 데이터 크기를 기준으로 병합 정렬할 하위 데이터의 시작, 중간, 끝 지점 인덱스 계산
		for (startIndex = 0; startIndex < Length - 1; startIndex += 2 * subDataSetSize)
		{
			// 병합정렬할 현재 하위 데이터의 중간 지점 인덱스 계산
			int middleIndex = getMin(startIndex + subDataSetSize - 1, Length - 1);

			// 병합정렬할 현재 하위 데이터의 끝 지점 인덱스 계산
			int endIndex = getMin(startIndex + 2 * subDataSetSize - 1, Length - 1);

			Merge(DataSet, startIndex, middleIndex, endIndex);
		}
	}
}

// 분할된 두 하위 데이터를 '정렬하며 합치기' (본문 p.527 ~ p.529 과정을 코드로 구현)
/*
	매개변수 목록

	- int DataSet[] : 정렬할 원본 데이터
	- int StartIndex : 왼쪽 하위 데이터(본문의 A)의 시작 지점
	- int MiddleIndex : 왼쪽 하위 데이터(본문의 A)의 끝 지점
	- int MiddleIndex + 1 : 오른쪽 하위 데이터(본문의 B)의 시작 지점
	- int EndIndex : 오른쪽 하위 데이터(본문의 B)의 끝 지점
*/
void Merge(int DataSet[], int StartIndex, int MiddleIndex, int EndIndex)
{
	int i;

	// 왼쪽 하위 데이터(A)의 현재 인덱스 초기화
	int LeftIndex = StartIndex;

	// 오른쪽 하위 데이터(B)의 현재 인덱스 초기화
	int RightIndex = MiddleIndex + 1;

	// 새롭게 메모리를 할당할 빈 데이터(본문의 C)의 현재 인덱스 초기화
	int DestIndex = 0;

	// 두 하위 데이터 A, B 의 크기를 합친 만큼의 새로운 빈 데이터 C 메모리 동적 할당
	int* Destination = (int*)malloc(sizeof(int) * (EndIndex - StartIndex + 1));

	// 두 하위 데이터 A, B 중 하나라도 순회 완료된 게 있을 때까지 하위 데이터끼리 요소 비교 반복 (p.528 과정 반복)
	while (LeftIndex <= MiddleIndex && RightIndex <= EndIndex)
	{
		// 두 하위 데이터 A, B 의 첫 번째 요소끼리 크기 비교
		if (DataSet[LeftIndex] < DataSet[RightIndex])
		{
			// 더 작은 쪽의 요소를 빈 데이터 C 에 추가
			Destination[DestIndex] = DataSet[LeftIndex];

			// 빈 데이터 C 에 요소가 추가되었다면, 해당 하위 데이터의 현재 인덱스를 증가시킴
			// (= 추가된 요소를 원본 하위 데이터에서 삭제하는 것에 해당!)
			LeftIndex++;
		}
		else
		{
			// 더 작은 쪽의 요소를 빈 데이터 C 에 추가
			Destination[DestIndex] = DataSet[RightIndex];

			// 빈 데이터 C 에 요소가 추가되었다면, 해당 하위 데이터의 현재 인덱스를 증가시킴
			// (= 추가된 요소를 원본 하위 데이터에서 삭제하는 것에 해당!)
			RightIndex++;
		}

		// 빈 데이터 C 에 요소를 추가한 뒤, 현재 인덱스를 증가시킴
		DestIndex++;
	}

	// 하위 데이터 A 에 아직 비교를 수행하지 못한 요소가 남아있다면, 전부 데이터 C 로 이동시킴 (p.529 참고)
	while (LeftIndex <= MiddleIndex)
	{
		Destination[DestIndex++] = DataSet[LeftIndex++];
	}

	// 하위 데이터 B 에 아직 비교를 수행하지 못한 요소가 남아있다면, 전부 데이터 C 로 이동시킴 (p.529 참고)
	while (RightIndex <= EndIndex)
	{
		Destination[DestIndex++] = DataSet[RightIndex++];
	}

	// '정렬하며 합쳐진' 데이터 C 의 요소들을 원본 데이터에 순차적으로 덮어쓰기
	DestIndex = 0;
	for (i = StartIndex; i <= EndIndex; i++)
	{
		DataSet[i] = Destination[DestIndex++];
	}

	// 정렬하며 합치기가 끝난 뒤, 데이터 C 의 메모리 반납
	free(Destination);
}

int main()
{
	// 병합정렬할 원본 데이터를 정적 배열로 선언
	int DataSet[] = { 334, 6, 4, 2, 3, 1, 5, 117, 12, 34 };

	// 원본 데이터 길이를 저장
	int Length = sizeof DataSet / sizeof DataSet[0];

	// 원본 데이터를 순회할 인덱스 초기화
	int i = 0;

	// 원본 데이터 병합정렬
	//MergeSort(DataSet, 0, Length - 1);

	// 원본 데이터를 재귀 없이 병합정렬
	IterativeMergeSort(DataSet, Length);

	// 병합정렬된 원본 데이터를 순회하며 출력
	for (i = 0; i < Length; i++)
	{
		printf("%d ", DataSet[i]);
	}

	printf("\n");

	return 0;
}
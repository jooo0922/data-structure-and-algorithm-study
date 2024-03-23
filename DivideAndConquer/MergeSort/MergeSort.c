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

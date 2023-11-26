#include "Heap.h"

// 힙 구조체 생성
Heap* HEAP_Create(int InitialSize)
{
	// Heap 구조체 크기 만큼의 힙 메모리 할당
	// malloc() 이 할당한 힙 메모리 주소값 반환 시, Heap* 타입의 포인터 주소로 형변환하여 반환.
	Heap* NewHeap = (Heap*)malloc(sizeof(Heap));

	// Heap 구조체 각 멤버변수 초기화
	NewHeap->Capacity = InitialSize;
	NewHeap->UsedSize = 0;

	// 힙 노드 배열은 "HeapNode 구조체 크기 * 힙의 최대 용량" 만큼 배열 메모리 동적 할당
	NewHeap->Nodes = (HeapNode*)malloc(sizeof(HeapNode) * NewHeap->Capacity);

	// HeapNode 구조체 메모리 크기 출력
	printf("size : %d\n", sizeof(HeapNode));

	// 생성된 힙 구조체 주소값(이 담긴 포인터 변수) 반환
	return NewHeap;
}

// 힙 구조체 메모리 해제
void HEAP_Destroy(Heap* H)
{
	// 힙 노드 배열 메모리 해제
	free(H->Nodes);

	// 힙 구조체 메모리 해제
	free(H);
}

// 힙 노드 삽입
void HEAP_Insert(Heap* H, ElementType NewData)
{

}

// 힙 최솟값 노드 삭제 (= 뿌리노드 삭제)
void HEAP_DeleteMin(Heap* H, HeapNode* Root)
{

}

// 주어진 노드의 부모노드 탐색
int HEAP_GetParent(int Index)
{
	// k번 인덱스에 위치한 노드의 부모노드 인덱스: (k - 1) / 2 의 몫 (p.313 참고)
	return (int)((Index - 1) / 2);
}

// 주어진 노드의 왼쪽 자식노드 탐색 (오른쪽 자식노드 = 왼쪽 자식노드 위치 + 1)
int HEAP_GetLeftChild(int Index)
{

}

// 힙의 두 노드 위치 교환
void HEAP_SwapNodes(Heap* H, int Index1, int Index2)
{

}

// 힙 전체 출력
void HEAP_PrintNodes(Heap* H)
{

}

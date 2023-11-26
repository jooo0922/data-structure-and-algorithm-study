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
	// 힙의 최고 깊이 가장 우측 노드 인덱스 저장
	// (정확히는 힙의 최고 깊이 가장 우측 노드 옆에 삽입할 예비 노드의 인덱스!)
	int CurrentPosition = H->UsedSize;

	// 힙의 최고 깊이 가장 우측 노드의 부모노드 인덱스 저장
	int ParentPosition = HEAP_GetParent(CurrentPosition);

	// 새로운 노드를 실제 삽입하기 전, 현재 힙의 노드 배열 개수와 최대 용량을 비교해서
	// 노드 배열이 꽉 차있으면 힙의 최대 용량(메모리)를 2배로 늘려 재할당
	if (H->UsedSize == H->Capacity)
	{
		H->Capacity *= 2;
		H->Nodes = (HeapNode*)realloc(H->Nodes, sizeof(HeapNode) * H->Capacity); // realloc() 관련 설명 하단 참고
	}

	// 힙의 최고 깊이 가장 우측에 새로운 노드 삽입
	H->Nodes[CurrentPosition].Data = NewData;

	// 힙 속성 유지를 위한 뒷처리 로직
	while (CurrentPosition > 0 
		&& H->Nodes[CurrentPosition].Data < H->Nodes[ParentPosition].Data)
	{
		// 삽입한 노드가 뿌리노드(0)가 아니고, 
		// 삽입한 노드보다 부모노드가 더 크다면, 부모노드와 위치를 교체
		HEAP_SwapNodes(H, CurrentPosition, ParentPosition);

		// 두 노드의 위치를 교체한 것에 맞춰서,
		// 삽입한 노드 인덱스와 그것의 부모노드 인덱스도 변경해 줌.
		CurrentPosition = ParentPosition;
		ParentPosition = HEAP_GetParent(CurrentPosition);
	}

	// 노드를 새로 삽입했으므로, 실제 노드 개수를 +1 증가시킴
	H->UsedSize++;
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
	// k번 인덱스에 위치한 노드의 왼쪽 자식 노드 인덱스: 2k + 1 (p.313 참고)
	return (2 * Index) + 1;
}

// 힙의 두 노드 위치 교환
void HEAP_SwapNodes(Heap* H, int Index1, int Index2)
{
	// 복사할 메모리 사이즈 (= HeapNode 단일 구조체 크기) 저장
	int CopySize = sizeof(HeapNode);

	// 첫 번째 HeapNode(= Index1)를 임시 저장할 메모리 동적 할당
	HeapNode* Temp = (HeapNode*)malloc(CopySize);

	// 첫 번째 HeapNode 데이터를 Temp 자유 메모리에 임시 복사 (memcpy() 관련 설명 하단 참고)
	memcpy(Temp, &H->Nodes[Index1], CopySize);

	// 두 번째 HeapNode 데이터를 첫 번째 HeapNode 메모리에 복사
	memcpy(&H->Nodes[Index1], &H->Nodes[Index2], CopySize);

	// Temp 에 임시로 복사해 둔 첫 번째 HeapNode 데이터를 두 번째 HeapNode 메모리에 복사
	// 이제 첫 번째 노드와 두 번째 노드의 데이터가 서로 교체됨! -> 두 노드 위치 교환 완료!
	memcpy(&H->Nodes[Index2], Temp, CopySize);

	// 두 노드 위치 교환 완료 후, 불필요한 임시 메모리 반납
	free(Temp);
}

// 힙 전체 출력
void HEAP_PrintNodes(Heap* H)
{

}

/*
	void *memcpy(void *dest, const void *src, size_t n);

	dest: 복사한 데이터가 저장될 목적지를 가리키는 포인터입니다.
	src: 복사할 데이터를 가리키는 포인터입니다.
	n: 복사할 바이트 수를 나타내는 size_t 타입의 정수입니다.
*/

/*
	realloc()

	배열을 동적으로 증가시킬 때, realloc() 사용
	
	기존의 배열 메모리 블록 확장 및 기존 데이터 복사 과정에서 
	성능에 영향을 미치므로 가급적 사용 자제...
*/

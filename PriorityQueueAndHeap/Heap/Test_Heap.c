#include "Heap.h"

int main()
{
	// 노드 배열 초기 용량을 3개로 설정하여 힙 구조체 생성
	Heap* H = HEAP_Create(3);

	// 힙에서 제거된 최솟값 노드(= 뿌리노드)가 저장될 포인터 변수 선언
	HeapNode* MinNode;

	// 힙에 노드 삽입
	HEAP_Insert(H, 12);
	HEAP_Insert(H, 87);
	HEAP_Insert(H, 111);
	HEAP_Insert(H, 34);
	HEAP_Insert(H, 16);
	HEAP_Insert(H, 75);

	// 현재까지 구축된 힙 (완전 이진 트리) 출력
	HEAP_PrintNodes(H);

	// 현재 힙에서 최솟값 노드(= 뿌리노드) 제거 후 힙 출력
	HEAP_DeleteMin(H, &MinNode);
	HEAP_PrintNodes(H);

	// 현재 힙에서 최솟값 노드(= 뿌리노드) 제거 후 힙 출력
	HEAP_DeleteMin(H, &MinNode);
	HEAP_PrintNodes(H);

	// 현재 힙에서 최솟값 노드(= 뿌리노드) 제거 후 힙 출력
	HEAP_DeleteMin(H, &MinNode);
	HEAP_PrintNodes(H);

	// 현재 힙에서 최솟값 노드(= 뿌리노드) 제거 후 힙 출력
	HEAP_DeleteMin(H, &MinNode);
	HEAP_PrintNodes(H);

	// 현재 힙에서 최솟값 노드(= 뿌리노드) 제거 후 힙 출력
	HEAP_DeleteMin(H, &MinNode);
	HEAP_PrintNodes(H);

	// 현재 힙에서 최솟값 노드(= 뿌리노드) 제거 후 힙 출력
	HEAP_DeleteMin(H, &MinNode);
	HEAP_PrintNodes(H);

	return 0;
}
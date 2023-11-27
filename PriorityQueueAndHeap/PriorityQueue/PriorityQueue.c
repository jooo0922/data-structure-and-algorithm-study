#include "PriorityQueue.h"

// 우선순위 큐 구조체 생성
PriorityQueue* PQ_Create(int InitialSize)
{
	// PriorityQueue 구조체 크기 만큼의 힙 메모리 할당
	// malloc() 이 할당한 힙 메모리 주소값 반환 시, PQNode* 타입의 포인터 주소로 형변환하여 반환.
	PriorityQueue* NewPQ = (PriorityQueue*)malloc(sizeof(PriorityQueue));

	// PriorityQueue 구조체 각 멤버변수 초기화
	NewPQ->Capacity = InitialSize;
	NewPQ->UsedSize = 0;

	// 우선순위 큐 노드 배열은 "PQNode 구조체 크기 * 우선순위 큐의 최대 용량" 만큼 배열 메모리 동적 할당
	NewPQ->Nodes = (PQNode*)malloc(sizeof(PQNode) * NewPQ->Capacity);

	// 생성된 우선순위 큐 구조체 주소값(이 담긴 포인터 변수) 반환
	return NewPQ;
}

// 우선순위 큐 구조체 메모리 해제
void PQ_Destroy(PriorityQueue* PQ)
{
	// 우선순위 큐 노드 배열 메모리 해제
	free(PQ->Nodes);

	// 우선순위 큐 구조체 메모리 해제
	free(PQ);
}

// 우선순위 큐 노드 삽입
void PQ_Enqueue(PriorityQueue* PQ, PQNode NewData)
{

}

// 우선순위 큐 최솟값 노드 삭제 (= 뿌리노드 삭제)
void PQ_Dequeue(PriorityQueue* PQ, PQNode* Root)
{

}

// 주어진 노드의 부모노드 탐색
int PQ_GetParent(int Index)
{
	// k번 인덱스에 위치한 노드의 부모노드 인덱스: (k - 1) / 2 의 몫 (p.313 참고)
	return (int)((Index - 1) / 2);
}

// 주어진 노드의 왼쪽 자식노드 탐색 (오른쪽 자식노드 = 왼쪽 자식노드 위치 + 1)
int PQ_GetLeftChild(int Index)
{
	// k번 인덱스에 위치한 노드의 왼쪽 자식 노드 인덱스: 2k + 1 (p.313 참고)
	return (2 * Index) + 1;
}

// 우선순위 큐의 두 노드 위치 교환
void PQ_SwapNodes(PriorityQueue* PQ, int Index1, int Index2)
{
	// 복사할 메모리 사이즈 (= PQNode 단일 구조체 크기) 저장
	int CopySize = sizeof(PQNode);

	// 첫 번째 PQNode(= Index1)를 임시 저장할 메모리 동적 할당
	PQNode* Temp = (PQNode*)malloc(CopySize);

	// 첫 번째 PQNode 데이터를 Temp 자유 메모리에 임시 복사 (memcpy() 관련 설명 하단 참고)
	memcpy(Temp, &PQ->Nodes[Index1], CopySize);

	// 두 번째 PQNode 데이터를 첫 번째 PQNode 메모리에 복사
	memcpy(&PQ->Nodes[Index1], &PQ->Nodes[Index2], CopySize);

	// Temp 에 임시로 복사해 둔 첫 번째 PQNode 데이터를 두 번째 PQNode 메모리에 복사
	// 이제 첫 번째 노드와 두 번째 노드의 데이터가 서로 교체됨! -> 두 노드 위치 교환 완료!
	memcpy(&PQ->Nodes[Index2], Temp, CopySize);

	// 두 노드 위치 교환 완료 후, 불필요한 임시 메모리 반납
	free(Temp);
}

// 우선순위 큐의 노드 배열이 비었는지 확인
int PQ_IsEmpty(PriorityQueue* PQ)
{
	// 우선순위 큐 노드 배열 개수가 0개인 지 확인
	return (PQ->UsedSize == 0);
}

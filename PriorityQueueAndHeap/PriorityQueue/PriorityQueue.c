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
void PQ_Enqueue(PriorityQueue* PQ, PQNode NewNode)
{
	// 우선순위 큐의 최고 깊이 가장 우측 노드 인덱스 저장
	// (정확히는 우선순위 큐의 최고 깊이 가장 우측 노드 옆에 삽입할 예비 노드의 인덱스!)
	int CurrentPosition = PQ->UsedSize;

	// 우선순위 큐의 최고 깊이 가장 우측 노드의 부모노드 인덱스 저장
	int ParentPosition = HEAP_GetParent(CurrentPosition);

	// 새로운 노드를 실제 삽입하기 전, 현재 우선순위 큐의 노드 배열 개수와 최대 용량을 비교해서
	// 노드 배열이 꽉 차있으면 우선순위 큐의 최대 용량(메모리)를 2배로 늘려 재할당
	if (PQ->UsedSize == PQ->Capacity)
	{
		if (PQ->Capacity == 0)
		{
			// 만약 최대 용량이 0개이면 2배 늘려봤자 0 * 2 = 0 으로 아무 소용 없으므로,
			// 최대 용량이 0개로 되어있을 경우를 대비해서 1로 변경함
			PQ->Capacity = 1;
		}

		PQ->Capacity *= 2;
		PQ->Nodes = (PQNode*)realloc(PQ->Nodes, sizeof(PQNode) * PQ->Capacity); // realloc() 관련 설명 하단 참고
	}

	// 우선순위 큐의 최고 깊이 가장 우측에 새로운 노드 삽입
	PQ->Nodes[CurrentPosition] = NewNode;

	// 우선순위 큐 속성 유지를 위한 뒷처리 로직
	while (CurrentPosition > 0
		&& PQ->Nodes[CurrentPosition].Priority < PQ->Nodes[ParentPosition].Priority)
	{
		// 삽입한 노드가 뿌리노드(0)가 아니고, 
		// 삽입한 노드보다 부모노드의 우선순위가 더 크다면, 부모노드와 위치를 교체
		HEAP_SwapNodes(PQ, CurrentPosition, ParentPosition);

		// 두 노드의 위치를 교체한 것에 맞춰서,
		// 삽입한 노드 인덱스와 그것의 부모노드 인덱스도 변경해 줌.
		CurrentPosition = ParentPosition;
		ParentPosition = HEAP_GetParent(CurrentPosition);
	}

	// 노드를 새로 삽입했으므로, 실제 노드 개수를 +1 증가시킴
	PQ->UsedSize++;
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

/*
	void *memcpy(void *dest, const void *src, size_t n);

	dest: 복사한 데이터가 저장될 목적지를 가리키는 포인터입니다.
	src: 복사할 데이터를 가리키는 포인터입니다.
	n: 복사할 바이트 수를 나타내는 size_t 타입의 정수입니다.
*/

/*
	void *memset(void *ptr, int value, size_t num);

	'memory set' 의 줄임말로,
	주로 배열이나 구조체와 같은 데이터 구조의 메모리 영역을
	지정해준 값으로 초기화하는 데 사용됨.

	ptr: 초기화할 메모리 영역의 시작 포인터
	value: 메모리 영역을 초기화할 값
	num: 초기화할 바이트 수

	ptr이 가리키는 메모리 영역을
	value 값으로 num 바이트만큼 채운다고 이해하면 됨.
*/

/*
	realloc()

	배열을 동적으로 증가시킬 때, realloc() 사용

	기존의 배열 메모리 블록 확장 및 기존 데이터 복사 과정에서
	성능에 영향을 미치므로 가급적 사용 자제...
*/

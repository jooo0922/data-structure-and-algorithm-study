#include "ArrayStack.h"

// 스택 생성
void AS_CreateStack(ArrayStack** Stack, int Capacity)
{
	(*Stack) = (ArrayStack*)malloc(sizeof(ArrayStack)); // ArrayStack 이 들어갈 힙 메모리 공간 할당
	
	(*Stack)->Nodes = (Node*)malloc(sizeof(Node) * Capacity); // 입력된 스택의 용량만큼 Node 배열이 들어갈 힙 메모리 공간 할당

	// 나머지 포인터 멤버변수 값 초기화
	(*Stack)->Capacity = Capacity;
	(*Stack)->Top = -1; // 첫번째 요소를 가리키는 인덱스가 0 인데, 첫번째 요소가 없는 상태라면, Top 인덱스는 -1 이어야 겠지!
}

// 스택 파괴 (메모리 해제)
void AS_DestroyStack(ArrayStack* Stack)
{
	free(Stack->Nodes); // Node 배열에 대한 힙 메모리 해제

	free(Stack); // ArrayStack 에 대한 힙 메모리 해제
}

// 스택 노드 삽입
void AS_Push(ArrayStack* Stack, ElementType Data)
{
	Stack->Top++; // 최상위 노드 인덱스 증가
	Stack->Nodes[Stack->Top].Data = Data; // 스택의 현재 최상위 노드에 데이터 저장

	if (AS_IsFull(Stack))
	{
		// 스택이 가득찼을 때, 배열의 용량을 동적으로 증가
		int IncreasedCapacity = (int)(Stack->Capacity * 1.3f); // 30% 증가된 Capacity 계산

		// 배열을 동적으로 증가시킬 때, realloc() 사용 
		// > 기존의 배열 메모리 블록 확장 및 기존 데이터 복사 과정에서 성능에 영향을 미치므로 가급적 사용 자제... 
		Stack->Nodes = (Node*)realloc(Stack->Nodes, sizeof(Node) * IncreasedCapacity);

		Stack->Capacity = IncreasedCapacity; // Capacity 포인터 멤버변수 변경
	}
}

// 스택 노드 제거
ElementType AS_Pop(ArrayStack* Stack)
{
	int Position = Stack->Top--; // 최상위 노드 인덱스 감소

	int MinSize = (int)(Stack->Capacity * 0.7); // 현재 스택 최대 용량의 70%
	if (AS_GetSize(Stack) < MinSize)
	{
		// 현재 스택 크기가 현재 스택 최대 용량의 70% 보다 낮아질 경우 처리
		Node* DecreasedNodes = (Node*)malloc(sizeof(Node) * MinSize); // 현재 스택 최대 용량의 70% 만큼의 새로운 배열 메모리 할당

		/*
			void *memcpy(void *dest, const void *src, size_t n);
			
			dest: 복사한 데이터가 저장될 목적지를 가리키는 포인터입니다.
			src: 복사할 데이터를 가리키는 포인터입니다.
			n: 복사할 바이트 수를 나타내는 size_t 타입의 정수입니다.
		*/
		memcpy(DecreasedNodes, Stack->Nodes, sizeof(Node) * MinSize); // 기존 Nodes 배열에서 최대 용량의 70% 개수의 Node 만큼 새로운 배열에 복사

		free(Stack->Nodes); // 기존 Nodes 배열 메모리 해제

		Stack->Nodes = DecreasedNodes; // Nodes 포인터 멤버변수가 새로운 배열의 메모리 공간을 가리키도록 할당
		Stack->Capacity = MinSize; // Capacity 포인터 멤버변수가 가리키는 메모리의 값을 이전 스택 최대 용량의 70% 개수로 변경
	}

	return Stack->Nodes[Position].Data; // 제거하려는 최상위 노드 데이터 반환
}

// 스택의 최상위 노드 데이터 반환
ElementType AS_Top(ArrayStack* Stack)
{
	return Stack->Nodes[Stack->Top].Data; // 최상위 노드 데이터 반환
}

// 스택의 크기 반환
int AS_GetSize(ArrayStack* Stack)
{
	return Stack->Top + 1; // 최상위 노드 인덱스 + 1 == 스택의 현재 노드 개수
}

int AS_IsEmpty(ArrayStack* Stack)
{
	// 최상위 노드 인덱스가 -1 이라는 것은, 아직 스택에 노드가 추가되지 않았다는 뜻!
	// 따라서, 조건문이 true 이므로, 1을 출력할 것임.
	// 반대로, 조건문이 false 라면, 0을 출력하겠지
	return (Stack->Top == -1);
}

// 스택의 초기 설정 용량이 가득 찼는지 체크
int AS_IsFull(ArrayStack* Stack)
{
	// 스택의 현재 노드 개수가 스택의 Capacity 보다 크거나 같다면 true(1),
	// 작다면 false(0) 를 반환할 것임.
	return (Stack->Top + 1 >= Stack->Capacity);
}
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
}

// 스택 노드 제거
ElementType AS_Pop(ArrayStack* Stack)
{
	int Position = Stack->Top--; // 최상위 노드 인덱스 감소
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
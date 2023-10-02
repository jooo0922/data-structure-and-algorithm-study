#include "BinaryTree.h"

// 이진트리 노드 생성
SBTNode* SBT_CreateNode(ElementType NewData)
{
	// SBTNode 구조체 크기 만큼의 힙 메모리 할당
	// malloc() 이 할당한 힙 메모리 주소값 반환 시, SBTNode* 타입의 포인터 주소로 형변환하여 반환.
	SBTNode* NewNode = (SBTNode*)malloc(sizeof(SBTNode));

	// 노드 구조체 각 멤버변수 초기화
	NewNode->Left = NULL;
	NewNode->Right = NULL;
	NewNode->Data = NewData;

	// 생성한 노드의 주소값(이 담긴 포인터 변수) 반환
	return NewNode;
}

// 이진트리 노드 메모리 해제
void SBT_DestroyNode(SBTNode* Node)
{
	free(Node); // 힙 메모리에 할당받은 메모리 반납
}

// 이진트리의 뿌리노드 메모리 해제 > 트리 전체의 메모리 해제
void SBT_DestroyTree(SBTNode* Node)
{
	// 이진트리 메모리 해제 시, 후위 순회로 노드를 방문하여 메모리를 반납해야 함.
	// why? 잎 노드부터 뿌리 노드 순으로 메모리를 제거해야 하는데, 
	// 이 순서에 가장 적합한 순회 방식이 '후위 순회'

	// 현재 순회중인 노드 포인터 NULL 체크
	if (Node == NULL)
	{
		return;
	}

	// 현재 노드 포인터 변수가 NULL 이 아니라면,
	// 후위 순회 순서로 (왼쪽 하위 트리 -> 오른쪽 하위 트리 -> 뿌리 노드)
	// 재귀적으로 함수를 호출하여 노드 메모리 반납

	// 왼쪽 하위 트리(노드) 메모리 반납 (재귀 호출)
	SBT_DestroyTree(Node->Left);

	// 오른쪽 하위 트리(노드) 메모리 반납 (재귀 호출)
	SBT_DestroyTree(Node->Right);

	// 뿌리 노드(현재 노드) 메모리 반납
	// 현재 노드에 대해서는 재귀 호출을 하지 않고 실제 메모리 반납 처리
	SBT_DestroyNode(Node); 
}

// 이진트리 전위순회 출력
void SBT_PreorderPrintTree(SBTNode* Node)
{
	// 현재 순회중인 노드 포인터 NULL 체크
	if (Node == NULL)
	{
		// 현재 노드 포인터 변수에 주소값이 존재하지 않으면 순회를 종료함.
		return; 
	}

	// 현재 노드 포인터 변수가 NULL 이 아니라면,
	// 전위 순회 순서로 (뿌리 노드 -> 왼쪽 하위 트리 -> 오른쪽 하위 트리)
	// 재귀적으로 함수를 호출하여 노드 데이터 출력
	// (이처럼, 트리구조를 순회할 때에는 재귀 호출이 자주 사용됨!)

	// 뿌리 노드(현재 노드) 출력
	printf(" %c", Node->Data);

	// 왼쪽 하위 트리(노드) 출력 (재귀 호출)
	SBT_PreorderPrintTree(Node->Left);

	// 오른쪽 하위 트리(노드) 출력 (재귀 호출)
	SBT_PreorderPrintTree(Node->Right);
}

// 이진트리 중위순회 출력
void SBT_InorderPrintTree(SBTNode* Node)
{
	// 현재 순회중인 노드 포인터 NULL 체크
	if (Node == NULL)
	{
		// 현재 노드 포인터 변수에 주소값이 존재하지 않으면 순회를 종료함.
		return;
	}

	// 현재 노드 포인터 변수가 NULL 이 아니라면,
	// 중위 순회 순서로 (왼쪽 하위 트리 -> 뿌리 노드 -> 오른쪽 하위 트리)
	// 재귀적으로 함수를 호출하여 노드 데이터 출력

	// 왼쪽 하위 트리(노드) 출력 (재귀 호출)
	SBT_InorderPrintTree(Node->Left);

	// 뿌리 노드(현재 노드) 출력
	printf(" %c", Node->Data);

	// 오른쪽 하위 트리(노드) 출력 (재귀 호출)
	SBT_InorderPrintTree(Node->Right);
}

// 이진트리 후위순회 출력
void SBT_PostorderPrintTree(SBTNode* Node)
{
	// 현재 순회중인 노드 포인터 NULL 체크
	if (Node == NULL)
	{
		// 현재 노드 포인터 변수에 주소값이 존재하지 않으면 순회를 종료함.
		return;
	}

	// 현재 노드 포인터 변수가 NULL 이 아니라면,
	// 후위 순회 순서로 (왼쪽 하위 트리 -> 오른쪽 하위 트리 -> 뿌리 노드)
	// 재귀적으로 함수를 호출하여 노드 데이터 출력

	// 왼쪽 하위 트리(노드) 출력 (재귀 호출)
	SBT_PostorderPrintTree(Node->Left);

	// 오른쪽 하위 트리(노드) 출력 (재귀 호출)
	SBT_PostorderPrintTree(Node->Right);

	// 뿌리 노드(현재 노드) 출력
	printf(" %c", Node->Data);
}
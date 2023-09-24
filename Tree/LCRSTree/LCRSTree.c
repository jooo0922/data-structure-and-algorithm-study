#include "LCRSTree.h"

// LCRS 트리 노드 생성
LCRSNode* LCRS_CreateNode(ElementType NewData)
{
	// 노드 구조체 크기 만큼의 힙 메모리 할당
	// malloc() 이 할당한 힙 메모리 주소값 반환 시, LCRSNode* 타입의 포인터 주소로 형변환하여 반환.
	LCRSNode* NewNode = (LCRSNode*)malloc(sizeof(LCRSNode));

	// 노드 구조체의 각 멤버변수 초기화
	NewNode->LeftChild = NULL;
	NewNode->RightSibling = NULL;
	NewNode->Data = NewData;

	// 생성한 노드의 주소값(이 담긴 포인터 변수) 반환
	return NewNode;
}

// LCRS 트리 노드 메모리 해제
void LCRS_DestroyNode(LCRSNode* Node)
{
	free(Node); // 힙 메모리에 할당받은 메모리 반납
}

// LCRS 트리의 뿌리노드 메모리 해제 > 트리 전체 노드의 메모리 해제
void LCRS_DestroyTree(LCRSNode* Root)
{
	// 뿌리 노드(또는 재귀 루프 상에서 현재 노드)의 오른쪽 형제 노드가 존재할 경우, 
	if (Root->RightSibling != NULL)
	{
		// 형제 노드에 대해 재귀를 돌려서 먼저 메모리 해제
		LCRS_DestroyTree(Root->RightSibling);
	}

	// 뿌리 노드(또는 재귀 루프 상에서 현재 노드)의 왼쪽 자식 노드가 존재할 경우, 
	if (Root->LeftChild != NULL)
	{
		// 자식 노드에 대해 재귀를 돌려서 먼저 메모리 해제
		LCRS_DestroyTree(Root->LeftChild);
	}

	// 뿌리 노드(또는 재귀 루프 상에서 현재 노드)의 메모리를 반납하기 전, 포인터 멤버 초기화
	Root->LeftChild = NULL;
	Root->RightSibling = NULL;

	// 뿌리 노드(또는 재귀 루프 상에서 현재 노드)의 메모리를 반납
	LCRS_DestroyNode(Root);
}

// LCRS 트리의 특정 노드에 자식 노드 추가
void LCRS_AddChildNode(LCRSNode* ParentNode, LCRSNode* ChildNode)
{
	if (ParentNode->LeftChild == NULL)
	{
		// 부모 노드에 자식 노드가 하나도 없는 경우,
		ParentNode->LeftChild = ChildNode; // 왼쪽 자식 포인터에 매개변수로 전달받은 자식노드를 바로 연결
	}
	else
	{
		// 부모 노드에 자식 노드가 하나 이상 존재하는 경우,
		LCRSNode* TempNode = ParentNode->LeftChild; // 가장 왼쪽 자식 노드부터 탐색 시작
		while (TempNode->RightSibling != NULL)
		{
			/*
				가장 오른쪽 자식 노드(RightSibling 포인터가 NULL 인 노드)를
				찾을 때까지 반복문 순회
			*/
			TempNode = TempNode->RightSibling;
		}

		// 반복문이 종료되면 TempNode 에는 가장 오른쪽 자식 노드 주소값이 할당되어 있음.
		// 따라서, 가장 오른쪽 자식 노드의 RightSibling 포인터에 새로운 자식노드 연결
		TempNode->RightSibling = ChildNode;
	}
}

// LCRS 트리 출력
void LCRS_PrintTree(LCRSNode* Node, int Depth)
{
	// 현재 노드의 깊이(Depth)만큼 반복문을 순회하며 들여쓰기 적용
	int i = 0;
	for (i = 0; i < Depth - 1; i++)
	{
		printf("   ");
	}

	if (Depth > 0)
	{
		// 깊이가 0인 뿌리 노드를 제외하면(Depth > 0),
		// 모든 노드는 누군가의 자식노드 이므로, 자식노드 표식(+--)를 출력
		printf("+--");
	}

	// 현재 노드의 데이터 출력
	printf("%c\n", Node->Data);

	if (Node->LeftChild != NULL)
	{
		// 현재 노드의 왼쪽 자식 노드 포인터가 존재하면,
		// 현재 노드 깊이 + 1 증가시켜서 왼쪽 자식노드에 대해 재귀를 돌려서 출력함.
		LCRS_PrintTree(Node->LeftChild, Depth + 1);
	}

	if (Node->RightSibling != NULL)
	{
		// 현재 노드의 오른쪽 형제 노드 포인터가 존재하면,
		// 현재 노드 깊이와 동일한 깊이값을 전달하여 오른쪽 형제노드에 대해 재귀를 돌려서 출력함. (형제 노드니까 깊이값은 같아야겠지!)
		LCRS_PrintTree(Node->RightSibling, Depth);
	}
}

// 특정 레벨에 해당하는 모든 노드 출력
void LCRS_PrintNodesAtLevel(LCRSNode* Node, int Depth, int Level)
{ 
	if (Depth == Level)
	{
		// 현재 노드의 깊이값과 특정 레벨이 일치하면,
		// 현재 노드의 데이터를 출력함.
		printf("%c ", Node->Data);
	}

	if (Node->LeftChild != NULL)
	{
		// 현재 노드의 왼쪽 자식 노드 포인터가 존재하면,
		// 현재 노드 깊이 + 1 증가시켜서 왼쪽 자식노드에 대해 재귀를 돌려서 출력함.
		LCRS_PrintNodesAtLevel(Node->LeftChild, Depth + 1, Level);
	}

	if (Node->RightSibling != NULL)
	{
		// 현재 노드의 오른쪽 형제 노드 포인터가 존재하면,
		// 현재 노드 깊이와 동일한 깊이값을 전달하여 오른쪽 형제노드에 대해 재귀를 돌려서 출력함. (형제 노드니까 깊이값은 같아야겠지!)
		LCRS_PrintNodesAtLevel(Node->RightSibling, Depth, Level);
	}
}

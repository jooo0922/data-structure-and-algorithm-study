#include "BinarySearchTree.h"

// 이진탐색트리 노드 생성
BSTNode* BST_CreateNode(ElementType NewData)
{
	// BSTNode 구조체 크기 만큼의 힙 메모리 할당
	// malloc() 이 할당한 힙 메모리 주소값 반환 시, BSTNode* 타입의 포인터 주소로 형변환하여 반환.
	BSTNode* NewNode = (BSTNode*)malloc(sizeof(BSTNode));

	// 노드 구조체 각 멤버변수 초기화
	NewNode->Left = NULL;
	NewNode->Right = NULL;
	NewNode->Data = NewData;

	// 생성한 노드의 주소값(이 담긴 포인터 변수) 반환
	return NewNode;
}

// 이진탐색트리 노드 메모리 해제
void BST_DestroyNode(BSTNode* Node)
{
	free(Node);
}

// 이진탐색트리 전체 메모리 해제
void BST_DestroyTree(BSTNode* Tree)
{
	// 오른쪽 하위트리가 존재한다면, 재귀적으로 순회하여 하위 노드(잎 노드) 먼저 메모리 해제
	if (Tree->Right != NULL)
	{
		BST_DestroyTree(Tree->Right);
	}

	// 왼쪽 하위트리가 존재한다면, 재귀적으로 순회하여 하위 노드(잎 노드) 먼저 메모리 해제
	if (Tree->Left != NULL)
	{
		BST_DestroyTree(Tree->Left);
	}

	// 위에서 자식노드 메모리를 모두 해제했다면, 자식 노드 포인터를 NULL 초기화
	Tree->Left = NULL;
	Tree->Right = NULL;

	// 현재 노드 메모리 해제
	BST_DestroyNode(Tree);
}

// 이진탐색트리 노드 탐색
BSTNode* BST_SearchNode(BSTNode* Tree, ElementType Target)
{
	if (Tree == NULL)
	{
		// 현재 노드 NULL 체크
		return NULL;
	}

	if (Tree->Data == Target)
	{
		// 현재 순회중인 노드가 목표 노드와 같은 경우,
		// 현재 노드 주소값을 그대로 반환
		return Tree;
	}
	else if (Tree->Data > Target)
	{
		// 현재 순회중인 노드보다 목표 노드가 더 작을 경우,
		// 현재 노드의 왼쪽 하위 트리를 재귀적으로 다시 탐색함
		return BST_SearchNode(Tree->Left, Target);
	}
	else
	{
		// 현재 순회중인 노드보다 목표 노드가 더 클 경우,
		// 현재 노드의 오른쪽 하위 트리를 재귀적으로 다시 탐색함
		return BST_SearchNode(Tree->Right, Target);

	}
}

// 주어진 하위트리 내의 최솟값 노드 탐색
BSTNode* BST_SearchMinNode(BSTNode* Tree)
{
	if (Tree == NULL)
	{
		// 현재 노드 NULL 체크
		return NULL;
	}

	/* 
		이진탐색트리 상에서는 
		현재 노드보다 작은 노드를 
		항상 왼쪽 하위 트리에 둔다는 것을 명심!
	*/

	if (Tree->Left == NULL)
	{
		// 현재 노드의 왼쪽 하위트리가 존재하지 않을 경우,
		// 현재 하위트리(=현재 노드)상에서 더 작은 노드는 존재하지 않는다는 의미이므로,
		// 현재 노드를 최솟값 노드로 반환함
		return Tree;
	}
	else
	{
		// 현재 노드의 왼쪽 하위트리가 존재할 경우,
		// 현재 하위트리 상에서 더 작은 노드가 존재한다는 의미이므로,
		// 현재 노드의 왼쪽 자식노드를 전달해서 재귀적으로 최솟값 노드를 재탐색함.
		return BST_SearchMinNode(Tree->Left);
	}
}

// 이진탐색트리 노드 삽입
void BST_InsertNode(BSTNode* Tree, BSTNode* Child)
{
	if (Tree->Data < Child->Data)
	{
		// 현재 노드보다 삽입할 노드가 더 클 경우, 오른쪽 하위트리에서 삽입 위치 탐색

		if (Tree->Right == NULL)
		{
			// 현재 노드의 오른쪽 하위트리가 비어있을 경우, 삽입할 노드를 오른쪽 하위트리에 추가함
			Tree->Right = Child;
		}
		else
		{
			// 현재 노드의 오른쪽 하위트리가 존재할 경우, 재귀적으로 오른쪽 하위트리 재탐색
			BST_InsertNode(Tree->Right, Child);
		}
	}
	else if (Tree->Data > Child->Data)
	{
		// 현재 노드보다 삽입할 노드가 더 작은 경우, 왼쪽 하위트리에서 삽입 위치 탐색

		if (Tree->Left == NULL)
		{
			// 현재 노드의 왼쪽 하위트리가 비어있을 경우, 삽입할 노드를 왼쪽 하위트리에 추가함
			Tree->Left = Child;
		}
		else
		{
			// 현재 노드의 왼쪽 하위트리가 존재할 경우, 재귀적으로 왼쪽 하위트리 재탐색
			BST_InsertNode(Tree->Left, Child);
		}
	}
}

// 이진탐색트리 노드 제거
BSTNode* BST_RemoveNode(BSTNode* Tree, BSTNode* Parent, ElementType Target)
{

}

// 이진탐색트리 중위순회 충력
void BST_InorderPrintTree(BSTNode* Node)
{

}

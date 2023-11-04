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

}

// 이진탐색트리 노드 탐색
BSTNode* BST_SearchNode(BSTNode* Tree, ElementType Target)
{

}

// 주어진 하위트리 내의 최솟값 노드 탐색
BSTNode* BST_SearchMinNode(BSTNode* Tree)
{

}

// 이진탐색트리 노드 삽입
void BST_InsertNode(BSTNode* Tree, BSTNode* Child)
{

}

// 이진탐색트리 노드 제거
BSTNode* BST_RemoveNode(BSTNode* Tree, BSTNode* Parent, ElementType Target)
{

}

// 이진탐색트리 중위순회 충력
void BST_InorderPrintTree(BSTNode* Node)
{

}
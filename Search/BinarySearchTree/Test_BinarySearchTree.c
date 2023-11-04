#include "BinarySearchTree.h"

// 노드 탐색 결과 출력 함수
void PrintSearchResult(int SearchTarget, BSTNode* Result)
{
	if (Result != NULL)
	{
		// 탐색된 노드가 존재할 경우, 해당 노드의 Data 출력
		printf("Found : %d \n", Result->Data);
	}
	else
	{
		// 탐색된 노드가 존재하지 않을 경우,
		// 탐색하려고 했던 목표값만 출력
		printf("Not Found: %d\n", SearchTarget);
	}
}

int main()
{
	// 이진탐색트리 뿌리노드 생성 및 초기화
	BSTNode* Tree = BST_CreateNode(123);

	// 이진탐색트리 연산 결과 노드의 주소값을 저장할 포인터 변수 초기화
	BSTNode* Node = NULL;

	// 이진탐색트리에 노드 생성하여 삽입
	BST_InsertNode(Tree, BST_CreateNode(22));
	BST_InsertNode(Tree, BST_CreateNode(9918));
	BST_InsertNode(Tree, BST_CreateNode(424));
	BST_InsertNode(Tree, BST_CreateNode(17));
	BST_InsertNode(Tree, BST_CreateNode(3));
	
	BST_InsertNode(Tree, BST_CreateNode(98));
	BST_InsertNode(Tree, BST_CreateNode(34));

	BST_InsertNode(Tree, BST_CreateNode(760));
	BST_InsertNode(Tree, BST_CreateNode(317));
	BST_InsertNode(Tree, BST_CreateNode(1));

	// 노드 17 이진탐색
	int SearchTarget = 17;
	Node = BST_SearchNode(Tree, SearchTarget);
	PrintSearchResult(SearchTarget, Node);

	// 노드 117 이진탐색
	SearchTarget = 117;
	Node = BST_SearchNode(Tree, SearchTarget);
	PrintSearchResult(SearchTarget, Node);

	// 이진탐색트리 중위순회 출력
	BST_InorderPrintTree(Tree);
	printf("\n");

	// 노드 98 제거 및 메모리 반납
	printf("Removing 98...\n");

	Node = BST_RemoveNode(Tree, NULL, 98);
	BST_DestroyNode(Node);

	// 특정 노드 제거 후 다시 중위순회 출력
	BST_InorderPrintTree(Tree);
	printf("\n");

	// 노드 111 새로 삽입
	printf("Inserting 111...\n");

	BST_InsertNode(Tree, BST_CreateNode(111));

	// 특정 노드 삽입 후 다시 중위순회 출력
	BST_InorderPrintTree(Tree);
	printf("\n");

	// 이진탐색트리 전체 메모리 반납
	BST_DestroyTree(Tree);

	return 0;
}
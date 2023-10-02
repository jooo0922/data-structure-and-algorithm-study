#include "BinaryTree.h"

int main()
{
	// 이진트리 노드 생성
	SBTNode* A = SBT_CreateNode('A');
	SBTNode* B = SBT_CreateNode('B');
	SBTNode* C = SBT_CreateNode('C');
	SBTNode* D = SBT_CreateNode('D');
	SBTNode* E = SBT_CreateNode('E');
	SBTNode* F = SBT_CreateNode('F');
	SBTNode* G = SBT_CreateNode('G');

	// 이진트리 각 노드에 자식노드 추가
	// 본문 p.170 에 그려진 이진 트리(포화 이진 트리이자 완전 높이 균형 이진 트리) 와
	// 동일한 형태로 트리 구축
	A->Left = B;
	B->Left = C;
	B->Right = D;

	A->Right = E;
	E->Left = F;
	E->Right = G;

	// 이진트리 전위 순회 출력
	printf("Preorder ...\n");
	SBT_PreorderPrintTree(A);
	printf("\n\n");

	// 이진트리 중위 순회 출력
	printf("Inorder ...\n");
	SBT_InorderPrintTree(A);
	printf("\n\n");

	// 이진트리 후위 순회 출력
	printf("Postorder ...\n");
	SBT_PostorderPrintTree(A);
	printf("\n");

	// 트리 출력이 끝나면 이진트리를 후위순회하며 
	// 재귀적으로 전체 노드 메모리 반납
	SBT_DestroyTree(A);

	return 0;
}
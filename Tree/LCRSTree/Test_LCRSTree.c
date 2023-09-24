#include "LCRSTree.h"

int main()
{
	// LCRS 트리 노드 생성
	LCRSNode* Root = LCRS_CreateNode('A');
	LCRSNode* B = LCRS_CreateNode('B');
	LCRSNode* C = LCRS_CreateNode('C');
	LCRSNode* D = LCRS_CreateNode('D');
	LCRSNode* E = LCRS_CreateNode('E');
	LCRSNode* F = LCRS_CreateNode('F');
	LCRSNode* G = LCRS_CreateNode('G');
	LCRSNode* H = LCRS_CreateNode('H');
	LCRSNode* I = LCRS_CreateNode('I');
	LCRSNode* J = LCRS_CreateNode('J');
	LCRSNode* K = LCRS_CreateNode('K');

	// LCRS 트리의 각 노드에 자식노드 추가
	// 트리구조가 잘 보이도록, LCRS_AddChildNode() 함수 호출 코드에 들여쓰기 적용
	LCRS_AddChildNode(Root, B);
		LCRS_AddChildNode(B, C);
		LCRS_AddChildNode(B, D);
			LCRS_AddChildNode(D, E);
			LCRS_AddChildNode(D, F);
		
	LCRS_AddChildNode(Root, G);
		LCRS_AddChildNode(G, H);
	
	LCRS_AddChildNode(Root, I);
		LCRS_AddChildNode(I, J);
			LCRS_AddChildNode(J, K);

	// LCRS 트리 출력
	// 뿌리노드부터 재귀적으로 자식 및 형제 노드들을 모두 출력
	LCRS_PrintTree(Root, 0); // 뿌리노드의 깊이값은 0

	// 특정 레벨에 해당하는 모든 노드를 출력
	// 출력하고자 하는 노드들이 속한 레벨 출력
	int Level = 3;
	printf("Nodes at Level %d : ", Level); 
	
	// 해당 레벨에 속한 노드들을 재귀적으로 출력
	LCRS_PrintNodesAtLevel(Root, 0, Level); 

	// LCRS 트리 메모리 해제
	// 뿌리노드부터 재귀적으로 자식 및 형제 노드들을 모두 메모리 해제
	LCRS_DestroyTree(Root);

	return 0;
}
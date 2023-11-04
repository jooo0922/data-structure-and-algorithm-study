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
	return 0;
}
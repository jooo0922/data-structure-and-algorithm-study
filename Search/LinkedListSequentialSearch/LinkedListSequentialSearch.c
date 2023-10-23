#include "LinkedList.h"

int main()
{
	int i = 0; // 링크드리스트 노드에 들어갈 데이터 초기값
	int Count = 0; // 링크드리스트 개수 초기화
	Node* List = NULL; // 링크드리스트 포인터 변수 초기화
	Node* Current = NULL; // 링크드리스트 상의 현재 노드 포인터 변수 초기화
	Node* NewNode = NULL; // 새로운 노드 포인터 변수 초기화

	// 6개의 Node 를 생성해서 링크드리스트에 계속 추가
	SLL_AppendNode(&List, SLL_CreateNode(6));
	SLL_AppendNode(&List, SLL_CreateNode(4));
	SLL_AppendNode(&List, SLL_CreateNode(2));
	SLL_AppendNode(&List, SLL_CreateNode(3));
	SLL_AppendNode(&List, SLL_CreateNode(1));
	SLL_AppendNode(&List, SLL_CreateNode(5));

	// 링크드리스트 출력
	Count = SLL_GetNodeCount(List); // 링크드리스트 개수 반환
	for (i = 0; i < Count; i++)
	{
		Current = SLL_GetNodeAt(List, i); // 링크드리스트의 각 노드 주소를 찾아서 반환
		printf("%d ", Current->Data); // 링크드리스트의 각 노드 데이터 출력
	}
	printf("\n");

	// 순차탐색으로 3을 데이터로 갖는 노드를 탐색한다는 메시지 출력
	//printf("\nSearch Node which has value of 3 by Sequential Search...\n");

	// 링크드리스트 순차탐색 수행
	//Node* MatchNode = SLL_SequentialSearch(List, 3);

	// 전진이동법 순차탐색으로 3을 데이터로 갖는 노드를 탐색한다는 메시지 출력
	printf("\nSearch Node which has value of 3 by Sequential Search with MoveToFront...\n");

	// 전진이동법 순차탐색 수행
	Node* MatchNode = SLL_MoveToFront(&List, 3);

	if (MatchNode == NULL)
	{
		// 순차탐색 결과 해당 노드가 없을 경우, 탐색에 실패했다는 메시지 출력
		printf("Node Not Found!\n");
	}
	else
	{
		// 순차탐색 결과 해당 노드를 발견했을 경우, 해당 노드의 데이터와 다음 노드 데이터 출력
		printf("Match Node : %d\n", MatchNode->Data);
		printf("Next Node : %d\n", MatchNode->NextNode->Data);

		// 전진이동법으로 정렬된 링크드리스트 출력
		for (i = 0; i < Count; i++)
		{
			Current = SLL_GetNodeAt(List, i); // 링크드리스트의 각 노드 주소를 찾아서 반환
			printf("%d ", Current->Data); // 링크드리스트의 각 노드 데이터 출력
		}
		printf("\n");
	}

	// 링크드리스트 상의 모든 노드 메모리 해제한다는 메시지 출력
	printf("\nDestroying List...\n");

	// 모든 노드 제거
	SLL_DestroyAllNodes(&List);

	// 다시 링크드리스트 출력
	Count = SLL_GetNodeCount(List); // 현재까지 링크드리스트 개수 반환
	printf("List Counts : %d\n", Count); // %d 는 정수값을 입력받은 형식지정자 > 문자열 뒤에 전달한 정수값으로 치환함

	return 0;
}
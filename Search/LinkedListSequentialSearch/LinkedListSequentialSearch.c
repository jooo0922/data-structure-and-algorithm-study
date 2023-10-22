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

		// 링크드리스트의 각 노드 인덱스와 데이터 출력
		// printf() 입출력 표준함수를 사용할 수 있는 이유는, LinkedList.h 헤더파일에 stdio.h 헤더파일을 포함시켜놓은 덕분!
		printf("List[%d] : %d\n", i, Current->Data); // %d 는 정수값을 입력받은 형식지정자 > 문자열 뒤에 전달한 정수값으로 치환함
	}

	printf("\nSearch Node which has value of 3 by Sequential Search...\n");
	Node* MatchNode = SLL_SequentialSearch(List, 3);
	if (MatchNode == NULL)
	{
		printf("Node Not Found!\n");
	}
	else
	{
		printf("Match Node : %d\n", MatchNode->Data);
		printf("Next Node : %d\n", MatchNode->NextNode->Data);
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
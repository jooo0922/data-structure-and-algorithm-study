#include "CircularDoubleLinkedList.h"

int main()
{
	int i = 0; // 환형 더블 링크드리스트 노드에 들어갈 데이터 초기값
	int Count = 0; // 환형 더블 링크드리스트 개수 초기화
	Node* List = NULL; // 환형 더블 링크드리스트 포인터 변수 초기화
	Node* NewNode = NULL; // 새로운 노드 포인터 변수 초기화
	Node* Current = NULL; // 환형 더블 링크드리스트 상의 현재 노드 포인터 변수 초기화

	// 5개의 Node 를 생성해서 환형 더블 링크드리스트에 계속 추가
	for (i = 0; i < 5; i++)
	{
		NewNode = CDLL_CreateNode(i);
		CDLL_AppendNode(&List, NewNode); // List 외부 포인터 변수의 주소값을 인자로 넣어줌.
	}

	// 환형 더블 링크드리스트 출력
	Count = CDLL_GetNodeCount(List); // 환형 더블 링크드리스트 개수 반환
	for (i = 0; i < Count; i++)
	{
		Current = CDLL_GetNodeAt(List, i); // 환형 더블 링크드리스트 각 노드 레퍼런스를 찾아서 반환

		// 환형 더블 링크드리스트의 각 노드 인덱스와 데이터 출력
		// printf() 입출력 표준함수를 사용할 수 있는 이유는, CircularDoubleLinkedList.h 헤더파일에 stdio.h 헤더파일을 포함시켜놓은 덕분!
		printf("List[%d] : %d\n", i, Current->Data); // %d 는 정수값을 입력받은 형식지정자 > 문자열 뒤에 전달한 정수값으로 치환함
	}

	// 새로운 노드 삽입한다는 메세지 출력
	printf("\nInserting 3000 After [2]...\n");

	// 환형 더블 링크드리스트의 세 번째 노드 뒤에 새로운 노드 삽입
	Current = CDLL_GetNodeAt(List, 2); // 세 번째 노드 가져오기
	NewNode = CDLL_CreateNode(3000); // 3000을 데이터로 갖는 새로운 노드 만듦.
	CDLL_InsertAfter(Current, NewNode); // 세 번째 노드(Current) 뒤에 새로운 노드(NewNode) 삽입

	// 노드를 리스트 상에서 제거한다는 메시지 출력
	printf("\nRemoving Node at 2...\n");

	// 환형 더블 링크드리스트의 세 번째 노드 제거
	Current = CDLL_GetNodeAt(List, 2); // 세 번째 노드 가져오기
	CDLL_RemoveNode(&List, Current); // 세 번째 노드를 링크드리스트 상에서 제외
	CDLL_DestroyNode(Current); // 세 번째 노드가 저장된 (힙)메모리 해제

	// 다시 환형 더블 링크드리스트 출력
	// 노드 개수의 2배 만큼 for 루프를 돌려서 '환형 구조'임을 확인
	Count = CDLL_GetNodeCount(List); // 환형 더블 링크드리스트 개수 반환
	for (i = 0; i < Count * 2; i++)
	{
		// 만약, 환형 구조가 아니라면, 인덱스가 아무리 늘어나더라도,
		// 테일의 NextNode 포인터가 NULL 이므로, 이후의 루프부터 참조 에러가 발생하겠지!
		if (i == 0)
		{
			Current = List; // 인덱스가 0이면, 즉, 첫 번째 루프에서는 현재 노드를 헤드로 할당
		}
		else
		{
			Current = Current->NextNode;
		}

		// 환형 더블 링크드리스트의 각 노드 인덱스와 데이터 출력
		// printf() 입출력 표준함수를 사용할 수 있는 이유는, CircularDoubleLinkedList.h 헤더파일에 stdio.h 헤더파일을 포함시켜놓은 덕분!
		printf("List[%d] : %d\n", i, Current->Data); // %d 는 정수값을 입력받은 형식지정자 > 문자열 뒤에 전달한 정수값으로 치환함
	}

	// 환형 더블 링크드리스트 상의 모든 노드 메모리 해제한다는 메시지 출력
	printf("\nDestroying List...\n");

	Count = CDLL_GetNodeCount(List); // 환형 더블 링크드리스트 개수 반환

	// 모든 노드를 메모리 상에서 제거(Destroy)
	// for문으로 환형 더블 링크드리스트 상의 모든 노드 순회
	for (i = 0; i < Count; i++)
	{
		// 0번째 노드, 즉 환형 더블 링크드리스트의 헤드를 현재 노드 포인터 변수가 가리키도록 초기화
		Current = CDLL_GetNodeAt(List, 0);

		if (Current != NULL)
		{
			CDLL_RemoveNode(&List, Current); // 우선 환형 더블 링크드리스트 상에서 현재노드 제거
			CDLL_DestroyNode(Current); // 환형 더블 링크드리스트를 메모리 상에서 제거(free(), 힙 메모리 영역에서 해제)
		}
	}
}
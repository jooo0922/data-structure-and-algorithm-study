#include "LinkedList.h"

int main()
{
	int i = 0; // 링크드리스트 노드에 들어갈 데이터 초기값
	int Count = 0; // 링크드리스트 개수 초기화
	Node* List = NULL; // 링크드리스트 포인터 변수 초기화
	Node* Current = NULL; // 링크드리스트 상의 현재 노드 포인터 변수 초기화
	Node* NewNode = NULL; // 새로운 노드 포인터 변수 초기화

	// 5개의 Node 를 생성해서 링크드리스트에 계속 추가
	for (i = 0; i < 5; i++)
	{
		NewNode = SLL_CreateNode(i);
		SLL_AppendNode(&List, NewNode); // List 외부 포인터 변수의 주소값을 인자로 넣어줌.
	}

	// -1을 데이터로 갖는 새로운 노드를 만든 뒤, 링크드리스트의 헤드노드로 삽입
	NewNode = SLL_CreateNode(-1);
	SLL_InsertNewHead(&List, NewNode); // List 외부 포인터 변수(이제는 링크드리스트의 헤드노드를 가리킴)의 주소값을 인자로 넣어줌.

	// -2을 데이터로 갖는 새로운 노드를 만든 뒤, 링크드리스트의 헤드노드로 또 삽입
	NewNode = SLL_CreateNode(-2);
	SLL_InsertNewHead(&List, NewNode);

	// 링크드리스트 출력
	Count = SLL_GetNodeCount(List); // 링크드리스트 개수 반환
	for (i = 0; i < Count; i++)
	{
		Current = SLL_GetNodeAt(List, i); // 링크드리스트의 각 노드 주소를 찾아서 반환

		// 링크드리스트의 각 노드 인덱스와 데이터 출력
		// printf() 입출력 표준함수를 사용할 수 있는 이유는, LinkedList.h 헤더파일에 stdio.h 헤더파일을 포함시켜놓은 덕분!
		printf("List[%d] : %d\n", i, Current->Data); // %d 는 정수값을 입력받은 형식지정자 > 문자열 뒤에 전달한 정수값으로 치환함
	}

	// 새로운 노드 삽입한다는 메세지 출력
	printf("\nInserting 3000 After [2]...\n\n");

	// 링크드리스트의 세 번째 노드 뒤에 새로운 노드 삽입
	Current = SLL_GetNodeAt(List, 2); // 세 번째 노드 가져오기
	NewNode = SLL_CreateNode(3000); // 3000을 데이터로 갖는 새로운 노드 만듦.
	SLL_InsertAfter(Current, NewNode); // 세 번째 노드(Current) 뒤에 새로운 노드(NewNode) 삽입

	// 다시 링크드리스트 출력
	Count = SLL_GetNodeCount(List); // 현재까지 링크드리스트 개수 반환
	for (i = 0; i < Count; i++)
	{
		Current = SLL_GetNodeAt(List, i); // 링크드리스트의 각 노드 주소를 찾아서 반환

		// 링크드리스트의 각 노드 인덱스와 데이터 출력
		// printf() 입출력 표준함수를 사용할 수 있는 이유는, LinkedList.h 헤더파일에 stdio.h 헤더파일을 포함시켜놓은 덕분!
		printf("List[%d] : %d\n", i, Current->Data); // %d 는 정수값을 입력받은 형식지정자 > 문자열 뒤에 전달한 정수값으로 치환함
	}

	// 새로운 노드 삽입한다는 메세지 출력
	printf("\nInserting 2000 Before [2]...\n\n");

	// 링크드리스트의 세 번째 노드 앞에 새로운 노드 삽입
	Current = SLL_GetNodeAt(List, 2);
	NewNode = SLL_CreateNode(2000);
	SLL_InsertBefore(&List, Current, NewNode);

	// 다시 링크드리스트 출력
	Count = SLL_GetNodeCount(List); // 현재까지 링크드리스트 개수 반환
	for (i = 0; i < Count; i++)
	{
		Current = SLL_GetNodeAt(List, i); // 링크드리스트의 각 노드 주소를 찾아서 반환

		// 링크드리스트의 각 노드 인덱스와 데이터 출력
		// printf() 입출력 표준함수를 사용할 수 있는 이유는, LinkedList.h 헤더파일에 stdio.h 헤더파일을 포함시켜놓은 덕분!
		printf("List[%d] : %d\n", i, Current->Data); // %d 는 정수값을 입력받은 형식지정자 > 문자열 뒤에 전달한 정수값으로 치환함
	}

	// 링크드리스트 상의 모든 노드 메모리 해제한다는 메시지 출력
	printf("\nDestroying List...\n");

	// 모든 노드를 메모리 상에서 제거(Destroy)
	// for문으로 링크드리스트 상의 모든 노드 순회
	//for (i = 0; i < Count; i++)
	//{
	//	Current = SLL_GetNodeAt(List, 0); // 0번째 노드, 즉 링크드리스트의 헤드노드를 현재 노드 포인터 변수가 가리키도록 초기화

	//	if (Current != NULL)
	//	{
	//		SLL_RemoveNode(&List, Current); // 우선 링크드리스트 상에서 현재노드 제거
	//		SLL_DestroyNode(Current); // 링크드리스트를 메모리 상에서 제거
	//	}
	//}

	// 모든 노드 제거
	SLL_DestroyAllNodes(&List);

	// 다시 링크드리스트 출력
	Count = SLL_GetNodeCount(List); // 현재까지 링크드리스트 개수 반환
	printf("List Counts : %d\n", Count); // %d 는 정수값을 입력받은 형식지정자 > 문자열 뒤에 전달한 정수값으로 치환함

	return 0;
}
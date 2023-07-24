#include "CircularDoubleLinkedList.h" // 헤더파일 포함

// 노드 생성
Node* CDLL_CreateNode(ElementType NewData)
{
	Node* NewNode = (Node*)malloc(sizeof(Node)); // 힙 메모리에 Node 포인터 타입에 해당하는 메모리 공간 할당

	NewNode->Data = NewData; // 포인터 멤버변수 참조로 데이터 저장
	NewNode->PrevNode = NULL; // 포인터 멤버변수 참조로 이전 노드에 대한 포인터는 NULL 로 초기화
	NewNode->NextNode = NULL; // 포인터 멤버변수 참조로 다음 노드에 대한 포인터는 NULL 로 초기화

	return NewNode;
}

// 노드 소멸(메모리에서 아예 제거)
void CDLL_DestroyNode(Node* Node)
{
	free(Node); // 힙 메모리에서 전달받은 Node 포인터가 가리키는 메모리 해제
}

// 노드 추가 (테일 노드에 추가)
void CDLL_AppendNode(Node** Head, Node* NewNode)
{
	// 헤드 노드가 NULL 이면 인자로 전달받은 새로운 노드가 헤드 노드가 되도록 주소값을 할당
	// *Head 는 "포인터 변수 Head 가 가리키는 메모리 공간에 저장된 값, 가리키는 대상"을 의미! 이를 "역참조 연산자" 라고 함.
	// 즉, Head 포인터 변수는 Node 포인터 변수(Node*)를 가리키는 이중 포인터 변수이므로,
	// *Head 는 Node* 포인터 변수(외부 포인터 변수)를 가리킨다고 보면 됨!
	if ((*Head) == NULL)
	{
		*Head = NewNode;

		// 헤드노드의 모든 포인터가 헤드노드 자신을 가리키도록 함.
		// 환형 더블 링크드리스트의 노드가 헤드노드 1개밖에 없을 때의 특징 (p.58 참고)
		(*Head)->NextNode = *Head;
		(*Head)->PrevNode = *Head;
	}
	else
	{
		// 리스트가 비어있지 않은 경우
		// 테일과 헤드 사이에 NewNode 삽입
		Node* Tail = (*Head)->PrevNode; // 일단, 헤드노드의 이전노드 포인터로 테일 레퍼런스 가져옴.

		Tail->NextNode->PrevNode = NewNode; // 헤드노드의 이전노드 포인터가 새로운 (테일)노드를 가리키도록 함.
		Tail->NextNode = NewNode; // 현재 테일의 다음노드 포인터가 새로운 (테일)노드를 가리키도록 함.
	
		NewNode->NextNode = (*Head); // 새로운 (테일)노드의 다음노드 포인터가 헤드를 가리키도록 함.
		NewNode->PrevNode = Tail; // 새로운 (테일)노드의 이전노드 포인터가 현재 테일을 가리키도록 함.
	}
}

// 노드 삽입
void CDLL_InsertAfter(Node* Current, Node* NewNode)
{
	NewNode->NextNode = Current->NextNode; // 새 노드의 NextNode 가 현재 노드의 NextNode 를 가리키게 함.
	NewNode->PrevNode = Current; // 새 노드의 PrevNode 는 현재 노드(이전노드)를 가리키도록 함.

	// 현재 노드의 다음 노드가 존재하는지 체크 (why? 마지막 노드 뒤에 '삽입'하는 걸수도 있잖아!)
	if (Current->NextNode != NULL)
	{
		Current->NextNode->PrevNode = NewNode; // 다음 노드의 PreNode 포인터가 새로운 노드를 가리키도록 함.
		Current->NextNode = NewNode; // 현재 노드(이전노드)의 NextNode 포인터도 새로운 노드를 가리키도록 함.
	}
}

// 노드 제거(링크드리스트 내에서만 제거) 
void CDLL_RemoveNode(Node** Head, Node* Remove)
{
	if (*Head == Remove)
	{
		// 제거할 노드가 헤드노드인 경우
		(*Head)->PrevNode->NextNode = Remove->NextNode; // 테일(헤드의 이전노드)의 다음노드 포인터가 제거할 노드(헤드)의 다음노드를 가리키도록 함.
		(*Head)->NextNode->PrevNode = Remove->PrevNode; // 새로운 헤드(헤드의 다음노드)의 이전노드 포인터가 제거할 노드(헤드)의 이전노드를 가리키도록 함.

		*Head = Remove->NextNode; // 헤드노드를 새로운 헤드(제거할 헤드노드의 다음노드)로 교체

		// 리스트에서 삭제할 노드의 포인터 멤버변수들은 항상 NULL 초기화를 해줘야 함!
		Remove->PrevNode = NULL;
		Remove->NextNode = NULL;
	}
	else
	{
		// 제거할 노드가 헤드노드가 아닌 경우
		// 제거할 노드가 헤드노드인 경우와 거의 비슷한데, 헤드노드를 교체하는 로직만 빠짐.
		Remove->PrevNode->NextNode = Remove->NextNode; // 제거할 노드 이전 노드의 다음노드 포인터가 제거할 노드의 다음노드를 가리키도록 함.
		Remove->NextNode->PrevNode = Remove->PrevNode; // 제거할 노드 다음 노드의 이전노드 포인터가 제거할 노드의 이전노드를 가리키도록 함.

		// 리스트에서 삭제할 노드의 포인터 멤버변수들은 항상 NULL 초기화를 해줘야 함!
		Remove->PrevNode = NULL;
		Remove->NextNode = NULL;
	}
}

// 노드 탐색
Node* CDLL_GetNodeAt(Node* Head, int Location)
{
	Node* Current = Head; // 반복순회할 현재 노드가 헤드노드를 가리키도록 포인터 변수 초기화
	
	while (Current != NULL && (--Location) >= 0)
	{
		// 사용자가 전달한 인덱스(Location) 을 1씩 차감하며 원하는 노드까지 순서대로 접근 
		Current = Current->NextNode;
	}

	return Current;
}

// 노드 개수 세기
int CDLL_GetNodeCount(Node* Head)
{
	unsigned int Count = 0; // 개수는 양수이므로, 부호가 없는 정수형 타입 변수로 초기화해도 충분하겠지? -> 메모리 공간 절약!
	Node* Current = Head; // 현재 노드가 헤드노드를 가리키도록 포인터 변수 주소값 초기화

	while (Current != NULL)
	{
		Current = Current->NextNode; // 현재 노드를 다음 노드로 덮어쓰면서 테일 노드까지 계속 순회
		Count++; // 순회하면서 개수 변수를 1씩 증가

		// 환형 더블 링크드리스트에서는 마지막 노드(테일)의 NextNode 포인터가 항상 헤드를 가리키므로,
		// 결국 위 반복문이 무한반복 루프에 빠지게 된다.
		// 이를 방지하기 위해, 현재노드가 헤드이면 테일까지 한바퀴 루프를 돌았다는 뜻이므로,
		// 반복문을 빠져나오도록 해서 무한 루프를 방지한다.
		if (Current == Head)
			break;
	}

	return Count;
}

// 노드 데이터 출력
void PrintNode(Node* _Node)
{
	if (_Node->PrevNode == NULL)
	{
		// PrevNode 포인터가 가리키는 노드가 없는 경우 > 환형 더블 링크드리스트에는 이런 노드가 없겠지.
		printf("Prev: NULL");
	}
	else
	{
		// 현재 노드의 PrevNode 가 가리키는 노드의 데이터 출력
		printf("Prev: %d", _Node->PrevNode->Data);
	}

	// 현재 노드의 데이터 출력
	printf("Current: %d", _Node->Data);

	if (_Node->NextNode == NULL)
	{
		// NextNode 포인터가 가리키는 노드가 없는 경우 > 환형 더블 링크드리스트에는 이런 노드가 없겠지.
		printf("Next: NULL\n");
	}
	else
	{
		// 현재 노드의 NextNode 가 가리키는 노드의 데이터 출력
		printf("Next: %d", _Node->NextNode->Data);
	}
}
#include "DoubleLinkedList.h" // 헤더파일 포함

// 노드 생성
Node* DLL_CreateNode(ElementType NewData)
{
	Node* NewNode = (Node*)malloc(sizeof(Node)); // 힙 메모리에 Node 포인터 타입에 해당하는 메모리 공간 할당

	NewNode->Data = NewData; // 포인터 멤버변수 참조로 데이터 저장
	NewNode->PrevNode = NULL; // 포인터 멤버변수 참조로 이전 노드에 대한 포인터는 NULL 로 초기화
	NewNode->NextNode = NULL; // 포인터 멤버변수 참조로 다음 노드에 대한 포인터는 NULL 로 초기화

	return NewNode; // 생성한 노드 포인터(주소값) 반환
}

// 노드 소멸(메모리에서 아예 제거)
void DLL_DestroyNode(Node* Node)
{
	free(Node); // 힙 메모리에서 전달받은 Node 포인터가 가리키는 메모리 해제
}

// 노드 추가 (테일 노드에 추가)
void DLL_AppendNode(Node** Head, Node* NewNode)
{
	// 헤드 노드가 NULL 이면 인자로 전달받은 새로운 노드가 헤드 노드가 되도록 주소값을 할당
	// *Head 는 "포인터 변수 Head 가 가리키는 메모리 공간에 저장된 값, 가리키는 대상"을 의미! 이를 "역참조 연산자" 라고 함.
	// 즉, Head 포인터 변수는 Node 포인터 변수(Node*)를 가리키는 이중 포인터 변수이므로,
	// *Head 는 Node* 포인터 변수(외부 포인터 변수)를 가리킨다고 보면 됨!
	if ((*Head) == NULL)
	{
		*Head = NewNode; // Head 포인터가 가리키는 대상인 또 다른 (외부) 포인터 변수 Node* 에 NewNode 주소값 할당
	}
	else
	{
		// 테일 노드를 찾는다
		Node* Tail = (*Head); // 반복 순회의 첫 번째 노드를 헤드노드로 지정
		while (Tail->NextNode != NULL)
		{
			// NextNode 포인터 멤버변수가 아무것도 가리키지 않는 노드가 테일 노드이니,
			// 테일 노드를 찾을 때까지 계속 덮어씀
			Tail = Tail->NextNode;
		}

		Tail->NextNode = NewNode; // 최종적으로 찾은 테일노드의 NextNode 포인터가 NewNode 를 가리키도록 주소값 할당
		NewNode->PrevNode = Tail; // NewNode 의 PrevNode 포인터는 기존 테일노드를 가리키도록 함. 
	}
}

// 노드 삽입
void DLL_InsertAfter(Node* Current, Node* NewNode)
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
void DLL_RemoveNode(Node** Head, Node* Remove)
{
	if (*Head == Remove)
	{
		// 헤드노드를 가리키는 포인터 변수와 제거할 노드를 가리키는 포인터 변수가 동일하다면,
		// 제거할 노드가 현재의 헤드노드 그 자체이기 때문에,
		// 그냥 헤드노드를 가리키는 포인터 변수가, 현재 헤드노드의 다음 노드를 가리키도록 바꿔주기만 하면 됨!
		*Head = Remove->NextNode;

		// 헤드노드가 방금 변경되었기 때문에, 
		// 기본적으로 더블 링크드리스트에서 모든 헤드노드는 PrevNode 포인터가 아무것도 가리키지 않도록 NULL 초기화를 해줘야 함.
		if ((*Head) != NULL)
		{
			(*Head)->PrevNode = NULL; // 교체된 헤드노드의 PrevNode 포인터는 NULL 로 초기화!
		}

		// 리스트에서 삭제할 노드의 포인터 멤버변수들은 항상 NULL 초기화를 해줘야 함!
		Remove->PrevNode = NULL;
		Remove->NextNode = NULL;
	}
	else
	{
		// 헤드노드와 제거할 노드가 서로 다를 경우!

		// 제거할 노드의 참조를 다른 포인터 변수에도 저장해두기
		Node* Temp = Remove;

		if (Remove->PrevNode != NULL)
		{
			// 제거할 노드의 이전 노드의 NextNode 포인터가 제거할 노드(Temp)의 다음 노드를 가리키도록!
			Remove->PrevNode->NextNode = Temp->NextNode;
		}

		if (Remove->NextNode != NULL)
		{
			// 제거할 노드의 다음 노드의 PrevNode 포인터가 제거할 노드(Temp)의 이전 노드를 가리키도록!
			Remove->NextNode->PrevNode = Temp->PrevNode;
		}

		// 리스트에서 삭제할 노드의 포인터 멤버변수들은 항상 NULL 초기화를 해줘야 함!
		Remove->PrevNode = NULL;
		Remove->NextNode = NULL;
	}
}

// 노드 탐색
Node* DLL_GetNodeAt(Node* Head, int Location)
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
int DLL_GetNodeCount(Node* Head)
{
	unsigned int Count = 0; // 개수는 양수이므로, 부호가 없는 정수형 타입 변수로 초기화해도 충분하겠지? -> 메모리 공간 절약!
	Node* Current = Head; // 현재 노드가 헤드노드를 가리키도록 포인터 변수 주소값 초기화

	while (Current != NULL)
	{
		Current = Current->NextNode; // 현재 노드를 다음 노드로 덮어쓰면서 테일 노드까지 계속 순회
		Count++; // 순회하면서 개수 변수를 1씩 증가
	}

	return Count;
}

void PrintNode(Node* _Node)
{
	if (_Node->PrevNode == NULL)
	{
		// PrevNode 포인터가 가리키는 노드가 없는 경우 (즉, 헤드노드인 경우)
		printf("Prev: NULL");
	}
	else
	{
		printf("Prev: %d", _Node->PrevNode->Data); // 현재 노드의 PrevNode 가 가리키는 노드의 데이터 출력
		printf("Current: %d", _Node->Data); // 현재 노드의 데이터 출력
	}

	if (_Node->NextNode == NULL)
	{
		// NextNode 포인터가 가리키는 노드가 없는 경우 (즉, 테일노드인 경우)
		printf("Next: NULL\n");
	}
	else
	{
		printf("Next: %d\n", _Node->NextNode->Data);
	}
}
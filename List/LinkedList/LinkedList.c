#include "LinkedList.h" // 헤더파일 포함

// 노드 생성
Node* SLL_CreateNode(ElementType NewData)
{
	Node* NewNode = (Node*)malloc(sizeof(Node)); // 힙 메모리에 Node 포인터 타입에 해당하는 메모리 공간 할당

	NewNode->Data = NewData; // 포인터 멤버변수 참조로 데이터 저장
	NewNode->NextNode = NULL; // 포인터 멤버변수 참조로 다음 노드에 대한 포인터는 NULL 로 초기화

	return NewNode; // 생성한 노드 포인터(주소값) 반환
}

// 노드 소멸(메모리에서 아예 제거)
void SLL_DestroyNode(Node* Node)
{
	free(Node); // 힙 메모리에서 전달받은 Node 포인터가 가리키는 메모리 해제
}

// 전체 노드 소멸
void SLL_DestroyAllNodes(Node** List)
{
	Node* Current = *List; // 현재 노드가 헤드노드를 가리키도록 포인터 변수 주소값 초기화

	while (Current != NULL)
	{
		Node* Head = Current; // 현재 Current 노드는 링크드리스트 상의 맨앞 노드이므로, 이것을 Head 포인터 변수가 가리키도록 초기화
		*List = Current->NextNode; // 링크드리스트 상에서 헤드노드를 Remove
		Current = *List; // 현재 노드를 링크드리스트 상에서 업데이트된 다음 노드로 덮어쓰기

		free(Head); // Current 는 주소값이 다음 노드로 변경된 상태이므로, Head 포인터가 가리키는 헤드노드의 메모리 해제
	}
}

// 노드 추가 (테일 노드에 추가)
void SLL_AppendNode(Node** Head, Node* NewNode)
{
	/*
		Head 노드가 매개변수로 선언되어 스택 메모리에 할당되면,
		Head 에 담긴 주소값이 NULL 이어서 NewNode 주소값을 다시 할당하더라도,
		함수가 종료되면 스택 메모리에서 자동으로 해제되어 새로 할당된 주소값을 잃어버리게 됨.

		그런데, 해당 함수 호출부에 있는,
		즉, 외부 포인터 변수에 NewNode 주소값을 저장해놓으면
		함수가 종료되어도 새로 할당한 NewNode 의 주소값이 날라가지 않음.

		따라서, 인자로 전달받은 포인터 변수의 주소를 의미하는 
		"이중 포인터(**)" 로 매개변수를 선언함으로써, 외부 포인터 변수에
		새로 할당한 NewNode 주소값을 저장할 수 있도록 한 것!
	*/
	// 헤드 노드가 NULL 이면 인자로 전달받은 새로운 노드가 헤드 노드가 되도록 주소값을 할당
	// *Head 는 "포인터 변수 Head 가 가리키는 메모리 공간에 저장된 값, 가리키는 대상"을 의미! 이를 "역참조 연산자" 라고 함.
	// 즉, Head 포인터 변수는 Node 포인터 변수(Node*)를 가리키는 이중 포인터 변수이므로,
	// *Head 는 Node* 포인터 변수를 가리킨다고 보면 됨!
	// 역참조 연산자는 주소로 지정된 메모리에 저장된 값을 가져오거나 수정할 때 사용한다고 함!
	if ((*Head) == NULL)
	{
		*Head = NewNode; // Head 포인터가 가리키는 대상인 또 다른 포인터 변수 Node* 에 NewNode 주소값 할당
	}
	else
	{
		// 테일 노드를 찾고, 그것의 NextNode 포인터가 NewNode 를 가리키도록 연결
		Node* Tail = (*Head); // 반복 순회의 첫 번째 노드를 헤드노드로 지정
		while (Tail->NextNode != NULL)
		{
			// NextNode 포인터 멤버변수가 아무것도 가리키지 않는 노드가 테일 노드이니,
			// 테일 노드를 찾을 때까지 계속 덮어씀
			Tail = Tail->NextNode;
		}

		Tail->NextNode = NewNode; // 최종적으로 찾은 테일노드의 NextNode 포인터가 NewNode 를 가리키도록 주소값 할당
	}
}

// 노드 삽입
void SLL_InsertAfter(Node* Current, Node* NewNode)
{
	NewNode->NextNode = Current->NextNode; // 새 노드의 NextNode 가 현재 노드의 NextNode 를 가리키게 함.
	Current->NextNode = NewNode; // 현재 노드의 NextNode 가 NewNode 를 가리키게 함.
}

// 노드 삽입 (특정 노드 앞에)
void SLL_InsertBefore(Node** Head, Node* Current, Node* NewNode)
{
	if (*Head == Current)
	{
		// 헤드노드와 특정 노드가 같으면, 헤드노드 삽입과 동일하게 처리
		if (Head == NULL)
		{
			// 헤드노드가 NULL 일 경우를 대비해서 이중 포인터로 외부 포인터 변수를 가리키도록 함.
			// 헤드노드가 NULL 이면, 역참조 연산자 *Head 로 외부 포인터 변수에 NewNode 주소값 할당  
			(*Head) = NewNode;
		}
		else
		{
			// 헤드노드가 존재할 경우, 일단 NewNode 노드의 NextNode 가 현재의 Head 노드를 가리키는 주소값을 할당하고,
			NewNode->NextNode = (*Head);
			// 실제 Head 노드를 가리키는 포인터 변수에는 NewNode 노드의 주소값을 할당해서 바꿔치기 함.
			(*Head) = NewNode;
		}
	}
	else
	{
		// 반복 순회할 이전노드를 가리키는 포인터 변수를 헤드노드를 가리키는 포인터 변수로 초기화함. 
		Node* PrevNode = *Head;

		while (PrevNode != NULL && PrevNode->NextNode != Current)
		{
			// NextNode 가 Current 인 노드를 찾을 때까지 PrevNode 를 순차적으로 덮어씀
			PrevNode = PrevNode->NextNode;
		}

		if (PrevNode != NULL)
		{
			PrevNode->NextNode = NewNode; // 이전 노드의 NextNode 는 NewNode 를 가리키도록 함.
			NewNode->NextNode = Current; // NewNode 의 NextNode 는 Current 노드를 가리키도록 함.
		}
	}
}

// 헤드노드 삽입
void SLL_InsertNewHead(Node** Head, Node* NewHead)
{
	if (Head == NULL)
	{
		// 헤드노드가 NULL 일 경우를 대비해서 이중 포인터로 외부 포인터 변수를 가리키도록 함.
		// 헤드노드가 NULL 이면, 역참조 연산자 *Head 로 외부 포인터 변수에 NewHead 주소값 할당  
		(*Head) = NewHead;
	}
	else
	{
		// 헤드노드가 존재할 경우, 일단 NewHead 노드의 NextNode 가 현재의 Head 노드를 가리키는 주소값을 할당하고,
		NewHead->NextNode = (*Head);
		// 실제 Head 노드를 가리키는 포인터 변수에는 NewHead 노드의 주소값을 할당해서 바꿔치기 함.
		(*Head) = NewHead;
	}
}

// 노드 제거(링크드리스트 내에서만 제거)
void SLL_RemoveNode(Node** Head, Node* Remove)
{
	if (*Head == Remove)
	{
		// 헤드노드를 가리키는 포인터 변수와 제거할 노드를 가리키는 포인터 변수가 동일하다면,
		// 제거할 노드가 현재의 헤드노드 그 자체이기 때문에,
		// 그냥 헤드노드를 가리키는 포인터 변수가, 현재 헤드노드의 다음 노드를 가리키도록 바꿔주기만 하면 됨!
		*Head = Remove->NextNode;
	}
	else
	{
		// 반복 순회할 현재노드를 가리키는 포인터 변수를 헤드노드를 가리키는 포인터 변수로 초기화함. 
		Node* Current = *Head;

		while (Current != NULL && Current->NextNode != Remove)
		{
			// NextNode 가 제거할 노드와 일치하는 노드를 찾을 때까지 Current 노드를 순차적으로 덮어씀
			Current = Current->NextNode;
		}

		if (Current != NULL)
		{
			// 위 while 문에 의해 Current 노드는 NextNode 가 제거할 노드를 가리키게 되고,
			// Current 노드의 NextNode 가 제거할 노드의 NextNode 를 가리키게 함으로써,
			// 제거할 노드만 링크드 리스트에서 제외시키도록 함!
			Current->NextNode = Remove->NextNode;
		}
	}
}

// 노드 탐색
Node* SLL_GetNodeAt(Node* Head, int Location)
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
int SLL_GetNodeCount(Node* Head)
{
	int Count = 0; // 개수 초기화
	Node* Current = Head; // 현재 노드가 헤드노드를 가리키도록 포인터 변수 주소값 초기화

	while (Current != NULL)
	{
		Current = Current->NextNode; // 현재 노드를 다음 노드로 덮어쓰면서 테일 노드까지 계속 순회
		Count++; // 순회하면서 개수 변수를 1씩 증가
	}

	return Count;
}
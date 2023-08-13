#include "LinkedListStack.h"

// 스택 생성
void LLS_CreateStack(LinkedListStack** Stack)
{
	// 역참조 연산자를 통해 가리키는 *Stack 은, 결국
	// 이 함수를 호출하는 외부의 LinkedListStack* 타입의 포인터 변수를 의미함.
	// 그래야 이 변수에 저장된 메모리 주소값이 함수 스코프가 종료되어도 날라가지 않음.
	// 이 변수는 함수 실행 시점에 선언되서 잠깐 사용되는 '매개변수'가 아니라, 
	// '외부 포인터 변수'니까!
	(*Stack) = (LinkedListStack*)malloc(sizeof(LinkedListStack)); // LinkedListStack 구조체가 들어갈 사이즈 만큼의 힙 메모리 공간 할당
	
	// LLS 구조체의 각 포인터 멤버변수 NULL 초기화
	// why? 스택 초기 생성 시에는 아무런 노드도 없으니까!
	(*Stack)->List = NULL;
	(*Stack)->Top = NULL;
}

// 스택 파괴 (메모리 해제)
void LLS_DestroyStack(LinkedListStack* Stack)
{
	// 링크드리스트 스택이 빌 때까지 노드 제거 및 메모리 해제를 반복함.
	while (!LLS_IsEmpty(Stack))
	{
		Node* Popped = LLS_Pop(Stack); // 노드 제거
		LLS_DestroyNode(Popped); // 제거된 노드 메모리 해제
	}

	// 위 반복문을 통해 스택의 노드들을 비우고 난 뒤, LLS 구조체를 자유 메모리에서 해제
	free(Stack);
}

// 스택에 삽입할 노드 생성
Node* LLS_CreateNode(char* NewData)
{
	// Node 구조체를 저장할 공간과 문자열 데이터를 저장할 공간을 모두 malloc() 으로 생성
	/*
		참고로 (Node*) 는 '포인터 타입 형변환'

		즉, malloc() 이 힙 메모리에 할당한 공간을 가리키는
		포인터 변수를 반환할 때, 기본값을 void* 즉, 
		void 타입 데이터가 담긴 메모리를 가리키는 포인터 변수를 반환함.

		그런데, 우리가 void 저장하려고 힙 메모리를 할당한 게 아니잖아?
		우리는 Node 구조체를 저장하고 싶었던 거잖아?

		그러니까, 이 malloc() 으로 생성한 메모리 공간을 가리키는
		포인터 변수를 반환할 때, 해당 포인터 변수는 
		Node 구조체 데이터를 가리키는 포인터 변수인
		Node* 타입의 포인터 변수로 형변환(캐스팅)해서 반환받는 것임!
	*/
	Node* NewNode = (Node*)malloc(sizeof(Node)); // Node 구조체 크기 만큼의 자유 메모리 할당
	
	// NewData 문자열 길이 (strlen()) + 1 만큼의 자유 메모리 할당
	// 왜 +1 하냐면, NULL 종료문자('\o') 도 저장하기 위함!
	NewNode->Data = (char*)malloc(strlen(NewData) + 1);

	// strcpy(대상 버퍼(메모리), 원본 문자열) -> 대상 버퍼에 원본 문자열을 복사해서 저장함
	strcpy(NewNode->Data, NewData); // 생성한 Node의 Data 포인터 멤버변수에 문자열 데이터 저장

	// 스택에 새로 추가할 노드는, 한 마디로 스택의 최상위 노드로 추가할 노드라는 뜻이지!
	// 따라서, 최상위 노드 위에 노드는 당연히 없어야 하는게 맞으니 NextNode 포인터 멤버변수는
	// NULL 로 초기화해줘야 함.
	NewNode->NextNode = NULL;

	return NewNode; // 생성한 노드의 포인터 변수(주소값) 반환
}

// 스택의 노드 파괴 (메모리 해제)
void LLS_DestroyNode(Node* _Node)
{
	// 노드를 생성할 때, malloc() 을 두 번 호출했으므로,
	// 노드의 메모리를 해제할 때에서 free() 를 두번 사용함.
	free(_Node->Data); // 노드의 문자열 데이터 메모리 해제
	free(_Node); // 노드 구조체 메모리 해제
}

// 스택 노드 삽입
void LLS_Push(LinkedListStack* Stack, Node* NewNode)
{
	if (Stack->List == NULL)
	{
		// 스택에 노드가 비어있을 경우

		Stack->List = NewNode; // 새 노드를 스택의 첫 번째 노드로 지정
	}
	else
	{
		// 스택에 노드가 비어있지 않을 경우
		 
		// 새 노드를 스택의 현재 최상위 노드의 NextNode 포인터 멤버변수에서 가리키도록 지정
		// 즉, 현재 최상위 노드의 윗 노드로 지정
		Stack->Top->NextNode = NewNode;
	}

	Stack->Top = NewNode; // 스택의 최상위 노드 멤버변수가 새 노드를 가리키도록 등록
}

// 스택 노드 제거
void LLS_Pop(LinkedListStack* Stack)
{
	Node* TopNode = Stack->Top; // 예전 최상위 노드를 다른 노드 포인터 변수가 가리키도록 보관해 둠.

	if (Stack->List == Stack->Top)
	{
		// 스택의 헤드와 테일이 같을 경우, 즉,
		// 스택에 노드가 하나밖에 없는 경우

		// 스택의 두 노드 포인터 멤버변수를 NULL 초기화하면 끝.
		Stack->List = NULL;
		Stack->Top = NULL;
	}
	else
	{
		// 스택에 노드가 2개 이상인 경우

		// 스택의 새로운 최상위 노드를 저장할 포인터 변수를 선언하고,
		// 그것이 일단 스택의 헤드노드를 가리키도록 초기화함.
		Node* CurrentTop = Stack->List;

		while (CurrentTop != NULL && CurrentTop->NextNode != Stack->Top)
		{
			// 예전 최상위 노드(TopNode) 의 바로 아래 노드(새로운 최상위 노드)가
			// 나올 때까지 while 문을 반복해서 CurrentTop 덮어쓰기
			CurrentTop = CurrentTop->NextNode;
		}

		Stack->Top = CurrentTop; // 스택의 Top 멤버변수가 새로운 최상위 노드를 가리키도록 덮어씀.
		
		// 새로운 최상위 노드는 말 그대로 '최상위 노드'가 되었으므로, 
		// 윗노드를 가리키는 포인터 멤버변수(NextNode)는 아무것도 가리키면 안되겠지!
		Stack->Top->NextNode; 
	}
}

// 스택의 최상위 노드 반환
Node* LLS_Top(LinkedListStack* Stack)
{
	return Stack->Top;
}

// 스택의 크기 반환
int LLS_GetSize(LinkedListStack* Stack)
{
	int Count = 0; // 스택의 노드 개수 변수 선언 및 0으로 초기화
	Node* Current = Stack->List; // 반복순회하면서 덮어쓸 현재 노드 포인터 변수가 스택의 헤드노드를 가리키도록 초기화

	while (Current != NULL)
	{
		// 현재 노드 포인터 변수가 NULL 이 되기 전까지 계속 덮어쓰면서
		// 스택의 노드 개수 변수를 1씩 증가시킴
		Current = Current->NextNode;
		Count++;
	}

	return Count; // 노드 개수 반환
}

// 스택이 비어있는지 여부 반환
int LLS_IsEmpty(LinkedListStack* Stack)
{
	// 스택의 첫번째 노드인 헤드노드 포인터 멤버변수가 비어있는지 확인하면,
	// 스택 자체가 비어있는지 여부를 알 수 있겠지!
	return (Stack->List == NULL);
}
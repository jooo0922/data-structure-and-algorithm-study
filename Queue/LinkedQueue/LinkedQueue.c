#include "LinkedQueue.h"

// 링크드 큐 생성
void LQ_CreateQueue(LinkedQueue** Queue)
{
	// 링크드 큐 구조체를 힙 메모리에 할당
	// de-referencing 을 사용해서, 외부에 선언된 링크드 큐 포인터 변수에 할당된 메모리 공간 주소값 할당
	(*Queue) = (LinkedQueue*)malloc(sizeof(LinkedQueue));

	// 링크드 큐 구조체 각 멤버변수 초기화
	(*Queue)->Front = NULL;
	(*Queue)->Rear = NULL;
	(*Queue)->Count = 0;
}

// 링크드 큐 메모리 반납
void LQ_DestroyQueue(LinkedQueue* Queue)
{
	// 링크드 큐 노드가 비워지기 전까지 반복문 순회
	while (!LQ_IsEmpty(Queue))
	{
		Node* Popped = LQ_Dequeue(Queue); // 노드 제거 및 제거된 노드의 주소값 반환
		LQ_DestroyNode(Popped); // 제거된 노드의 메모리 반납
	}

	free(Queue); // 링크드 큐 구조체 메모리 반납
}

// 링크드 큐에 삽입할 노드 생성
Node* LQ_CreateNode(char* NewData)
{
	Node* NewNode = (Node*)malloc(sizeof(Node)); // 새로운 Node 구조체 힙 메모리 공간 할당

	// NewData 문자열 길이 (strlen(NewData)) + 1 만큼의 힙 메모리 공간 할당
	// 왜 +1 하냐면, NULL 종료문자('\o') 도 저장하기 위함!
	NewNode->Data = (char*)malloc(strlen(NewData) + 1);

	// strcpy_s(대상 버퍼(메모리 공간 주소), 복사할 문자열 크기, 원본 문자열)
	// -> 대상 버퍼에 원본 문자열을 복사해서 저장함
	// 생성한 Node의 Data 포인터가 가리키는 메모리 공간에 문자열 데이터 복사해서 저장
	strcpy_s(NewNode->Data, strlen(NewData) + 1, NewData); 

	// 큐에 새로 삽입할 노드를 삽입한 것이므로,
	// 새로 삽입된 노드는 가리킬 다음 노드가 없겠지!
	// 따라서, 다음 노드 포인터를 NULL 초기화한 것
	NewNode->NextNode = NULL;

	// 생성한 노드 반환
	return NewNode;
}

// 링크드 큐의 노드 메모리 해제
void LQ_DestroyNode(Node* _Node)
{
	// 노드를 생성할 때, malloc() 을 두 번 호출했으므로,
	// 노드의 메모리를 해제할 때에서 free() 를 두번 사용함.
	free(_Node->Data); // 노드의 문자열 데이터 메모리 반납
	free(_Node); // 노드 구조체 메모리 반납
}

// 링크드 큐 노드 삽입
void LQ_Enqueue(LinkedQueue* Queue, Node* NewNode)
{
	if (Queue->Front == NULL)
	{
		// 전단이 NULL 일 경우, 즉, 링크드 큐에 노드가 하나도 없는 경우
		// 새로 삽입할 유일한 노드가 곧 큐의 전단이자 후단이 됨.
		Queue->Front = NewNode;
		Queue->Rear = NewNode;
		Queue->Count++; // 노드 개수 증가
	}
	else
	{
		// 링크드 큐에 노드가 최소 하나 이상 있는 경우
		Queue->Rear->NextNode = NewNode; // 링크드 큐의 현재 후단의 다음 노드 포인터가 새로 삽입할 노드를 가리키도록 함.
		Queue->Rear = NewNode; // 링크드 큐의 현재 후단을 새로 삽입된 노드로 변경함.
		Queue->Count++; // 노드 개수 증가
	}
}

// 링크드 큐 노드 제거
Node* LQ_Dequeue(LinkedQueue* Queue)
{
	Node* Front = Queue->Front; // 현재 링크드 큐의 전단 노드 주소값을 캐싱해 둠.

	if (Queue->Front->NextNode == NULL)
	{
		// 전단 노드의 다음 노드 포인터가 NULL 일 경우, 즉, 큐에 전단 노드 하나만 남았을 경우
		// 큐에 남아있는 전단 노드 하나마저 제거해버리면,
		// 큐의 전단과 후단 포인터는 NULL 초기화를 할 수밖에!
		Queue->Front = NULL;
		Queue->Rear = NULL;
	}
	else
	{
		// 링크드 큐에 전단 노드 이외의 노드도 존재할 경우
		// 현재 링크드 큐의 전단 포인터가
		// 현재 링크드 큐의 전단 노드의 다음 노드를 가리키도록 변경 
		Queue->Front = Queue->Front->NextNode;
	}

	Queue->Count--; // 노드 개수 차감

	// 방금 제거된 전단 노드의 포인터(주소값) 반환
	// -> 큐에서 제거된 노드의 메모리 해제 시 사용될 것임.
	return Front;
}

int LQ_IsEmpty(LinkedQueue* Queue)
{
	// 링크드 큐의 전단 존재 여부는 링크드 큐의 공백 여부와 같음.
	// why? 링크드 큐의 전단 노드는 큐에 있는 모든 노드들의 시작 노드인데, 
	// 이런 전단 노드가 없다면, 큐에 노드가 하나도 존재하지 않는다는 뜻이니까!
	return (Queue->Front == NULL);
}
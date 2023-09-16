#include "CircularQueue.h"

// 큐 생성
void CQ_CreateQueue(CircularQueue** Queue, int Capacity)
{
	// 큐를 힙 메모리에 할당
	// 역참조 연산자를 사용해서, 외부에 선언된 순환 큐 포인터 변수에 할당된 메모리 공간 주소값 대입
	(*Queue) = (CircularQueue*)malloc(sizeof(CircularQueue));

	// 입력된 Capacity + 1 만큼의 Node 구조체를 힙 메모리에 할당 (공백 노드 추가 생성)
	(*Queue)->Nodes = (Node*)malloc(sizeof(Node) * (Capacity + 1)); // Node 배열의 첫 번째 요소가 저장된 메모리 주소를 할당

	// 기타 포인터 멤버변수 초기화
	(*Queue)->Capacity = Capacity;
	(*Queue)->Front = 0;
	(*Queue)->Rear = 0;
}

// 큐 메모리 해제
void CQ_DestroyQueue(CircularQueue* Queue)
{
	free(Queue->Nodes); // 순환 큐 안에 Node 구조체 배열부터 메모리 해제
	free(Queue); // 큐 구조체 메모리 해제
}

// 큐 노드 삽입
void CQ_Enqueue(CircularQueue* Queue, ElementType Data)
{
	int Position = 0; // 큐 배열의 마지막 Node 를 가리킬 인덱스(후단 이전)

	if (Queue->Rear == Queue->Capacity)
	{
		// 후단이 큐 배열 끝에 도달했다면,
		// 후단을 배열의 맨 첫번째 요소(0번 인덱스)를 가리키도록 되돌리고,
		Position = Queue->Rear;
		Queue->Rear = 0;
	}
	else
	{
		// 후단이 아직 큐 배열 끝에 도달하지 않았다면,
		// 후단이 +1 만큼 뒷쪽에 있는 요소를 가리키도록 함.
		/*
			아래 코드를 풀어쓰면,
			Position = Queue->Rear;
			Queue->Rear++;
		*/
		Position = Queue->Rear++;
	}

	Queue->Nodes[Position].Data = Data; // 마지막 Node 요소 인덱스(후단 이전)에 입력받은 데이터 할당
}

// 큐 노드 제거
ElementType CQ_Dequeue(CircularQueue* Queue)
{
	int Position = Queue->Front; // 현재 전단이 가리키는 Node(제거하고자 하는 노드)의 인덱스 저장 

	if (Queue->Front == Queue->Capacity)
	{
		// 전단이 큐 배열의 끝에 도달한 경우, CQ_Enqueue() 에서와 마찬가지로,
		// 전단을 배열의 맨 첫번째 요소를 가리키도록 되돌림.
		Queue->Front = 0;
	}
	else
	{
		// 전단이 아직 큐 배열 끝에 도달하지 않았다면,
		// 전단이 +1 만큼 뒷쪽에 있는 요소를 가리키도록 함.
		// 이제 전단이 가리키는 곳부터 큐 배열의 시작점이므로, 
		// Position 에 저장되어 있던 이전 전단이 가리키던 Node 는 큐 배열에 속하지 않음.
		Queue->Front++;
	}

	return Queue->Nodes[Position].Data; // 제거된 노드의 데이터 반환
}

// 큐 배열 크기 계산
int CQ_GetSize(CircularQueue* Queue)
{
	if (Queue->Front <= Queue->Rear)
	{
		// 전단이 후단 앞에 있거나 같을 경우, 큐 배열 크기 계산 방법 (p.119 하단 그림 첫 번째 과정인 상황)
		return Queue->Rear - Queue->Front; // 후단 - 전단으로 간단하게 계산 (p.119 그림 보면서 직접 계산해보면 이해됨.)
	}
	else
	{
		// 전단이 후단 뒤에 있을 경우, 큐 배열 크기 계산 방법 (p.119 하단 그림 두, 세 번째 과정인 상황)
		return Queue->Rear + (Queue->Capacity - Queue->Front) + 1; // 후단 + (큐의 용량 - 전단) + 1 로 계산 (p.119 그림 보면서 직접 계산해보면 이해됨.)
	}
}

// 큐 배열 공백 상태 확인
int CQ_IsEmpty(CircularQueue* Queue)
{
	// p.120 에서 공백 노드에 의해, 
	// 전단과 후단이 가리키는 위치가 같으면 공백 상태로 판별할 수 있댔지?
	return (Queue->Front == Queue->Rear);
}

// 큐 배열 포화 상태 확인
int CQ_IsFull(CircularQueue* Queue)
{
	if (Queue->Front < Queue->Rear)
	{
		// 전단이 후단 앞에 있을 경우, 포화 상태 확인 방법 (p.119 하단 그림 첫 번째 과정인 상황)
		// 전단과 후단의 차이가 큐 배열의 용량과 동일할 때 -> 포화상태!
		return (Queue->Rear - Queue->Front == Queue->Capacity);
	}
	else
	{
		// 전단이 후단과 같은 위치이거나 뒤에 있을 경우, 포화 상태 확인 방법 (p.119 하단 그림 두, 세 번째 과정인 상황)
		// 전단 + 1 이 후단과 동일할 때 -> 포화상태!
		return (Queue->Rear + 1 == Queue->Front);
	}

}
#include "CircularQueue.h"

int main()
{
	int i; // 반복문 순회에 사용될 인덱스 변수
	CircularQueue* Queue; // 순환 큐 구조체가 담긴 메모리 공간 주소값을 저장할 포인터 변수

	// <순환 큐 구조체가 담긴 메모리 공간의 주소값> 이 담긴 메모리 공간의 주소값을 첫 번째 인자로 넘겨줌.
	// 마지막으로, 노드 배열 용량을 10개로 두 번째 인자로 넘겨줘서 순환 큐 생성
	CQ_CreateQueue(&Queue, 10); 

	CQ_Enqueue(Queue, 1); // 큐 노드 삽입
	CQ_Enqueue(Queue, 2); // 큐 노드 삽입
	CQ_Enqueue(Queue, 3); // 큐 노드 삽입
	CQ_Enqueue(Queue, 4); // 큐 노드 삽입

	// 인덱스 변수 i 를 0으로 초기화한 후, 3번만 반복문 순회
	for (i = 0; i < 3; i++)
	{
		printf("Dequeue: %d, ", CQ_Dequeue(Queue)); // 방금 삽입했던 큐 노드 제거 및 제거된 노드의 데이터 출력
		printf("Front:%d, Rear:%d\n", Queue->Front, Queue->Rear); // 현재 큐의 전단과 후단 출력
	}

	i = 100; // 반복문 순회 인덱스 변수를 100으로 초기화
	// 순환 큐가 포화상태가 아닐 때까지(즉, 아직 배열에 노드들이 꽉 차기 전까지!) 반복문을 계속 순회
	while (CQ_IsFull(Queue) == 0)
	{
		// 포화상태가 아닌 순환 큐에 노드들을 계속 삽입함.
		// 이때, 노드에 할당할 데이터는 100부터 시작해서 101, 102, 103, ... 이렇게 1씩 추가해서 전달함.
		CQ_Enqueue(Queue, i++);
	}

	// 순환 큐가 포화상태가 되기 전까지 큐 노드 삽입 반복을 마치고 나면,
	// 현재 순환 큐의 최대 용량과 노드 배열 크기를 출력함.
	printf("Capacity: % d, Size : % d\n\n", Queue->Capacity, CQ_GetSize(Queue));

	// 이번엔 반대로, 순환 큐가 공백상태가 아닐 때까지(즉, 아직 배열에 노드가 없어지기 전까지) 반복문을 계속 순회 
	while (CQ_IsEmpty(Queue) == 0)
	{
		printf("Dequeue: %d, ", CQ_Dequeue(Queue)); // 큐 노드 제거 및 제거된 노드 데이터 출력
		printf("Front:%d, Rear:%d\n", Queue->Front, Queue->Rear); // 현재 큐의 전단과 후단 출력
	}

	CQ_DestroyQueue(Queue); // 큐 안의 노드배열과 순환 큐 구조체 메모리 해제

	return 0;
}
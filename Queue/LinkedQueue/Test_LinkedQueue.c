#include "LinkedQueue.h"

int main()
{
	Node* Popped; // 링크드 큐에서 제거된 노드의 주소값을 저장할 포인터 변수
	LinkedQueue* Queue; // 순환 큐 구조체의 주소값을 저장할 포인터 변수

	// <링크드 큐 구조체가 담긴 메모리 공간의 주소값> 이 담긴 메모리 공간의 주소값을 인자로 넘겨줌.
	LQ_CreateQueue(&Queue);

	LQ_Enqueue(Queue, LQ_CreateNode("abc")); // 큐 노드 삽입
	LQ_Enqueue(Queue, LQ_CreateNode("def")); // 큐 노드 삽입
	LQ_Enqueue(Queue, LQ_CreateNode("efg")); // 큐 노드 삽입
	LQ_Enqueue(Queue, LQ_CreateNode("hij")); // 큐 노드 삽입

	printf("Queue Size : %d\n", Queue->Count); // 현재까지 링크드 큐에 삽입된 노드 개수 출력

	// 링크드 큐가 공백상태가 되기 전까지 반복문을 계속 순회
	while (LQ_IsEmpty(Queue) == 0)
	{
		Popped = LQ_Dequeue(Queue); // 삽입된 순서대로 큐의 노드 제거 및 제거된 노드 주소값 반환

		printf("Dequeue: %s \n", Popped->Data); // 제거된 노드의 데이터 출력

		LQ_DestroyNode(Popped); // 제거된 노드 메모리 반환
	}

	// 반복문 순회를 마치면, 링크드 큐에 노드의 메모리를 모두 반환한 상태이므로,
	// 링크드 큐 구조체의 메모리도 반환한다.
	LQ_DestroyQueue(Queue);

	return 0;
}
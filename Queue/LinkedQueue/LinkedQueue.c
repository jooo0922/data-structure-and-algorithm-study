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
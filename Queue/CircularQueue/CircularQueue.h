#ifndef CIRCULAR_QUEUE_H
#define CIRCULAR_QUEUE_H
/*
	여기서 사용된 #ifndef ~ #endif 전처리기는
	헤더파일인 ArrayStack.h 의 헤더가드를 처리해주는 방법 중 하나였지?

	cpp-study > TBCppStudy > Chapter1_12 > add.h 필기 참고!
*/

#include <stdio.h> // printf(), scanf() 같은 입출력 함수 선언이 포함된 헤더파일
#include <stdlib.h> // malloc(), free() 같은 메모리 할당 함수 선언이 포함된 헤더파일
// -> 헤더파일에 포함되어 있어야, 이를 가져다 쓰는 .c 파일들에서 사용할 때 에러가 안남.

// 노드에 들어갈 정수형 데이터 타입을 별칭으로 선언
typedef int ElementType;

// 순환 큐에 추가될 단일 노드 구조체 별칭으로 선언
typedef struct tagNode
{
	ElementType Data; // 노드에 들어갈 데이터
} Node;

// 순환 큐 구조체 선언
typedef struct tagCircularQueue
{
	int Capacity; // 순환 큐 초기 생성 시 부여되는 전체 노드 용량 (실제 용량은 공백노드로 인해 Capacity + 1)
	int Front; // 전단 위치
	int Rear; // 후단 위치

	Node* Nodes; // 순환 큐 배열 포인터 (정확히는 배열의 첫 번째 요소의 주소값이 담긴 포인터)
} CircularQueue;

// 함수 원형 선언
void CQ_CreateQueue(CircularQueue** Queue, int Capacity); // 순환 큐 생성
void CQ_DestroyQueue(CircularQueue* Queue); // 순환 큐 메모리 해제
void CQ_Enqueue(CircularQueue* Queue, ElementType Data); // 순환 큐에 노드 삽입
ElementType CQ_Dequeue(CircularQueue* Queue); // 순환 큐에서 노드 제거
int CQ_GetSize(CircularQueue* Queue); // 순환 큐의 현재 크기 반환
int CQ_IsEmpty(CircularQueue* Queue); // 순환 큐 공백 상태 확인
int CQ_IsFull(CircularQueue* Queue); // 순환 큐 포화 상태 확인

#endif // !CIRCULAR_QUEUE_H


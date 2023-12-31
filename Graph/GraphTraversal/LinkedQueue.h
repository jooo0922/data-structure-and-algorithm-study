#ifndef LINKED_QUEUE_H
#define LINKED_QUEUE_H
/*
	여기서 사용된 #ifndef ~ #endif 전처리기는
	헤더파일인 LinkedQueue.h 의 헤더가드를 처리해주는 방법 중 하나였지?

	cpp-study > TBCppStudy > Chapter1_12 > add.h 필기 참고!
*/

#include <stdio.h> // printf(), scanf() 같은 입출력 함수 선언이 포함된 헤더파일
#include <stdint.h> // printf(), scanf() 같은 입출력 함수 선언이 포함된 헤더파일
#include <string.h> // strlen(), strcpy() 같은 문자열 처리 함수 선언이 포함된 헤더파일
#include <stdlib.h> // malloc(), free() 같은 메모리 할당 함수 선언이 포함된 헤더파일
#include "Graph.h"

// 링크드 큐에 추가될 단일 노드의 데이터를 Vertex(그래프 정점 구조체) 타입 포인터 주소로 선언
typedef Vertex* ElementType;

// 링크드 큐에 추가될 단일 노드 구조체 별칭으로 선언
typedef struct tagNode
{
	ElementType Data; // 노드에 들어갈 문자열 데이터
	struct tagNode* NextNode; // 다음 노드를 가리키는 포인터 변수 필드
} Node;

// 링크드 큐 구조체 선언
typedef struct tagLinkedQueue
{
	Node* Front; // 큐의 전단
	Node* Rear; // 큐의 후단
	int Count; // 큐에 삽입된 노드 개수(= 링크드리스트 노드 개수)
} LinkedQueue;

// 함수 원형 선언
void LQ_CreateQueue(LinkedQueue** Queue); // 링크드 큐 생성
void LQ_DestroyQueue(LinkedQueue* Queue); // 링크드 큐 메모리 해제

Node* LQ_CreateNode(ElementType Data); // 링크드 큐에 삽입할 노드 생성 (메모리 할당)
void LQ_DestroyNode(Node* _Node); // 링크드 큐의 노드 메모리 해제

void LQ_Enqueue(LinkedQueue* Queue, Node* NewNode); // 링크드 큐 노드 삽입
Node* LQ_Dequeue(LinkedQueue* Queue); // 링크드 큐 노드 제거

int LQ_IsEmpty(LinkedQueue* Queue); // 링크드 큐 공백 여부 확인

#endif // !LINKED_QUEUE_H
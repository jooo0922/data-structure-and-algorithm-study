#ifndef PRIORITYQUEUE_H
#define PRIORITYQUEUE_H
/*
	여기서 사용된 #ifndef ~ #endif 전처리기는
	헤더파일의 헤더가드를 처리해주는 방법 중 하나였지?

	cpp-study > TBCppStudy > Chapter1_12 > add.h 필기 참고!
*/

#include <stdio.h> // printf(), scanf() 같은 입출력 함수 선언이 포함된 헤더파일
#include <memory.h> // memcpy(), memset() 같은 메모리 복사 및 초기화 함수 선언이 포함된 헤더파일 
#include <stdlib.h> // malloc(), free() 같은 메모리 할당 함수 선언이 포함된 헤더파일
// -> 헤더파일에 포함되어 있어야, 이를 가져다 쓰는 .c 파일들에서 사용할 때 에러가 안남.

// 노드에 들어갈 우선순위 필드 타입을 별칭으로 선언
typedef int PriorityType;

// 우선순위 큐에 추가될 단일 노드 구조체 타입을 별칭으로 선언
typedef struct tagPQNode
{
	PriorityType Priority; // 우선순위
	void* Data; // 추후 다른 알고리즘에서 우선순위 큐 활용을 위해 데이터 필드를 특정 자료형으로 제한하지 않도록 함! 
} PQNode;

// 우선순위 큐 구조체 타입을 별칭으로 선언
typedef struct tagPriorityQueue
{
	PQNode* Nodes; // 우선순위 큐 노드 배열
	int Capacity; // 우선순위 큐 노드 배열 최대 용량 (할당된 메모리 사이즈에 기반)
	int UsedSize; // 우선순위 큐 노드 배열 실제 노드 개수
} PriorityQueue;

PriorityQueue* PQ_Create(int InitialSize); // 우선순위 큐 구조체 생성
void PQ_Destroy(PriorityQueue* PQ); // 우선순위 큐 구조체 메모리 해제
void PQ_Enqueue(PriorityQueue* PQ, PQNode NewNode); // 우선순위 큐 노드 삽입
void PQ_Dequeue(PriorityQueue* PQ, PQNode* Root); // 우선순위 큐 최솟값 노드 삭제 (= 뿌리노드 삭제)
int PQ_GetParent(int Index); // 주어진 노드의 부모노드 탐색
int PQ_GetLeftChild(int Index); // 주어진 노드의 왼쪽 자식노드 탐색 (오른쪽 자식노드 = 왼쪽 자식노드 위치 + 1)
void PQ_SwapNodes(PriorityQueue* PQ, int Index1, int Index2); // 우선순위 큐의 두 노드 위치 교환
int PQ_IsEmpty(PriorityQueue* PQ); // 우선순위 큐의 노드 배열이 비었는지 확인

#endif // !PRIORITYQUEUE_H

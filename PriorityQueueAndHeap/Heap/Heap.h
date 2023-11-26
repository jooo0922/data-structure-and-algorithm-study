#ifndef HEAP_H
#define	HEAP_H 
/*
	여기서 사용된 #ifndef ~ #endif 전처리기는
	헤더파일의 헤더가드를 처리해주는 방법 중 하나였지?

	cpp-study > TBCppStudy > Chapter1_12 > add.h 필기 참고!
*/

#include <stdio.h> // printf(), scanf() 같은 입출력 함수 선언이 포함된 헤더파일
#include <memory.h> // memcpy(), memset() 같은 메모리 복사 및 초기화 함수 선언이 포함된 헤더파일 
#include <stdlib.h> // malloc(), free() 같은 메모리 할당 함수 선언이 포함된 헤더파일
// -> 헤더파일에 포함되어 있어야, 이를 가져다 쓰는 .c 파일들에서 사용할 때 에러가 안남.

// 노드에 들어갈 정수형 데이터 타입을 별칭으로 선언
typedef int ElementType;

// 힙에 추가될 단일 노드 구조체 타입을 별칭으로 선언
typedef struct tagHeapNode
{
	ElementType Data;
} HeapNode;

// 힙 구조체 타입을 별칭으로 선언
typedef struct tagHeap
{
	HeapNode* Nodes; // 힙 노드 배열
	int Capacity; // 힙 노드 배열 최대 용량 (할당된 메모리 사이즈에 기반)
	int UsedSize; // 힙 노드 배열 실제 노드 개수
} Heap;

#endif // !HEAP_H

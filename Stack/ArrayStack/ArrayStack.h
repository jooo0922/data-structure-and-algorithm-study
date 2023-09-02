#ifndef ARRAYSTACK_H
#define ARRAYSTACK_H
/*
	여기서 사용된 #ifndef ~ #endif 전처리기는
	헤더파일인 ArrayStack.h 의 헤더가드를 처리해주는 방법 중 하나였지?

	cpp-study > TBCppStudy > Chapter1_12 > add.h 필기 참고!
*/

#include <stdio.h> // printf(), scanf() 같은 입출력 함수 선언이 포함된 헤더파일
#include <stdlib.h> // malloc(), free() 같은 메모리 할당 함수 선언이 포함된 헤더파일
#include <string.h> // 배열 크기를 동적으로 줄일 때, memcpy() 같은 메모리 내 데이터 복사 함수를 사용하기 위해 포함된 라이브러리
// -> 헤더파일에 포함되어 있어야, 이를 가져다 쓰는 .c 파일들에서 사용할 때 에러가 안남.

// 노드에 들어갈 데이터 타입. 여기서는 정수형으로 임의로 정함.
typedef int ElementType;

// 스택에 추가될 단일 노드 구조체 선언
typedef struct tagNode
{
	ElementType Data; // 노드에 들어갈 데이터
} Node;

// 배열 기반 스택 구조체 선언
typedef struct tagArrayStack
{
	int Capacity; // 스택 초기 생성 시 부여되는 전체 노드 용량
	int Top; // 최상위 노드 인덱스
	Node* Nodes; // Node 구조체 배열
} ArrayStack;

// 함수 원형 선언
void AS_CreateStack(ArrayStack** Stack, int Capacity); // 배열 기반 스택 생성
void AS_DestroyStack(ArrayStack* Stack); // 스택 파괴 (메모리 해제)
void AS_Push(ArrayStack* Stack, ElementType Data); // 스택 노드 삽입
ElementType AS_Pop(ArrayStack* Stack); // 스택 노드 제거
ElementType AS_Top(ArrayStack* Stack); // 스택의 현재 최상위 노드 데이터 반환
int AS_GetSize(ArrayStack* Stack); // 스택의 크기 반환
int AS_IsEmpty(ArrayStack* Stack); // 스택이 비어있는지 여부 반환
int AS_IsFull(ArrayStack* Stack); // 스택의 설정 용량이 가득 찼는지 체크

#endif // !ARRAYSTACK_H

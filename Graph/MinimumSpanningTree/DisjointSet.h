#ifndef DISJOINTSET_H
#define DISJOINTSET_H
/*
	여기서 사용된 #ifndef ~ #endif 전처리기는
	헤더파일인 DisjointSet.h 의 헤더가드를 처리해주는 방법 중 하나였지?

	cpp-study > TBCppStudy > Chapter1_12 > add.h 필기 참고!
*/

#include <stdio.h> // printf(), scanf() 같은 입출력 함수 선언이 포함된 헤더파일
#include <stdlib.h> // malloc(), free() 같은 함수 선언이 포함된 헤더파일
// -> 헤더파일에 포함되어 있어야, 이를 가져다 쓰는 .c 파일들에서 사용할 때 에러가 안남.

// 분리집합에 추가될 단일 노드 구조체 타입을 별칭으로 선언
typedef struct tagDisjointSet
{
	struct tagDisjointSet* Parent; // 부모 노드 포인터 멤버
	void* Data; // 노드 데이터 포인터 멤버 (어떤 자료형의 포인터 주소값이든 할당될 수 있도록, void* 타입으로 포인터 멤버변수 타입 선언)
} DisjointSet;

// 함수 원형 선언
void DS_UnionSet(DisjointSet* Set1, DisjointSet* Set2); // 합집합 연산
DisjointSet* DS_FindSet(DisjointSet* Set); // 원소가 속한 집합 탐색
DisjointSet* DS_MakeSet(void* NewData); // 분리집합 생성
void DS_DestroySet(DisjointSet* Set); // 분리집합 메모리 반납

#endif // !DISJOINTSET_H

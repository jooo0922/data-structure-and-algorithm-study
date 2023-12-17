#ifndef HASH_TABLE_DISJOINT_SET_H
#define HASH_TABLE_DISJOINT_SET_H
/*
	여기서 사용된 #ifndef ~ #endif 전처리기는
	헤더파일의 헤더가드를 처리해주는 방법 중 하나였지?

	cpp-study > TBCppStudy > Chapter1_12 > add.h 필기 참고!
*/

#include <stdio.h> // printf(), scanf() 같은 입출력 함수 선언이 포함된 헤더파일
#include <stdlib.h> // malloc(), free() 같은 메모리 할당 함수 선언이 포함된 헤더파일
#include <string.h> // strcmp() 같은 문자열 비교 함수 선언이 포함된 헤더파일
// -> 헤더파일에 포함되어 있어야, 이를 가져다 쓰는 .c 파일들에서 사용할 때 에러가 안남.

// 해시 테이블 노드 구조체의 Key(주소로 사용할 데이터) 타입을 별칭으로 선언 
typedef char* KeyType;

// 해시 테이블 노드 구조체의 Value(Key로 얻어낸 주소에 저장할 데이터) 타입을 별칭으로 선언
typedef char* ValueType;

// 해시 테이블 요소의 상태를 나타낼 enum 을 선언 -> 해시값 충돌 여부 확인 목적
enum ElementStatus
{
	EMPTY = 0, // 탐색한 해시 테이블 요소가 비어있을 때
	OCCUPIED = 1 // 탐색한 해시 테이블 요소가 점유되어 있을 때
};

// 해시 테이블에 추가될 각 요소의 타입(Key - Value 쌍)을 별칭으로 선언
typedef struct tagElementType
{
	KeyType Key; // 해시하여 주소값을 얻어낼 원본 데이터
	ValueType Value; // 해시하여 얻어낸 주소값에 저장할 데이터

	enum ElementStatus Status; // 해시 테이블 요소의 상태

	struct tagElementType* Root; // 각 요소의 분리집합 뿌리노드
} ElementType;

// 개방 주소법 기반 해시 테이블 구조체 타입을 별칭으로 선언
typedef struct tagHasTable
{
	int OccupiedCount; // 해시 테이블에서 점유된 요소의 개수
	int TableSize; // 해시 테이블 크기(= 요소 개수)

	ElementType* Table; // 해시 테이블 각 요소 타입(ElementType)의 동적 배열(의 첫 번째 요소 주소값)
} HashTable;

HashTable* HTDS_CreateHashTable(int TableSize); // 해시 테이블 구조체 생성
void HTDS_DestroyHashTable(HashTable* HT); // 해시 테이블 구조체 메모리 해제
void HTDS_ClearElement(ElementType* Element); // 해시 테이블 요소 메모리 해제

void HTDS_Set(HashTable** HT, KeyType Key, ValueType Value); // 해시 테이블 요소 삽입
ValueType HTDS_Get(HashTable* HT, KeyType Key); // 해시 테이블 요소 탐색
int HTDS_Hash(KeyType Key, int KeyLength, int TableSize); // 해시 함수 (해시 주소값 계산용)
int HTDS_Hash2(KeyType Key, int KeyLength, int TableSize); // 해시 함수 (탐사 이동폭 계산용 -> 이중 해싱)

void HTDS_Rehash(HashTable** HT); // 해시 테이블 재해싱

void HTDS_UnionSet(ElementType Set1, ElementType Set2); // 두 분리집합 합집합 연산
ValueType HTDS_FindSet(ElementType Element); // 특정 요소가 포함된 집합 탐색

#endif // !HASH_TABLE_DISJOINT_SET_H

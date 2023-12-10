#ifndef CHAINING_H
#define CHAINING_H
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

// 해시 테이블(의 링크드리스트)에 추가될 단일 노드 구조체 타입을 별칭으로 선언
typedef struct tagNode
{
	KeyType Key; // 해시하여 주소값을 얻어낼 원본 데이터
	ValueType Value; // 해시하여 얻어낸 주소값에 저장할 데이터

	struct tagNode* Next; // 링크드리스트 상에서 다음 노드에 대한 포인터 주소값
} Node;

// 체이닝 기반 해시 테이블의 각 해시값이 가리킬 링크드리스트 타입을 별칭으로 선언
typedef Node* List;

// 체이닝 기반 해시 테이블 구조체 타입을 별칭으로 선언
typedef struct tagHashTable
{
	int TableSize; // 해시 테이블 크기(= 노드 개수)
	List* Table; // 해시 테이블의 각 해시값이 가리킬 링크드리스트 주소값 (정확히는 링크드리스트 첫 번째 요소, 즉, 헤드노드의 주소값!)
} HashTable;

HashTable* CHT_CreateHashTable(int TableSize); // 해시 테이블 구조체 생성
void CHT_DestroyHashTable(HashTable* HT); // 해시 테이블 구조체 메모리 해제

Node* CHT_CreateNode(KeyType Key, ValueType Value); // 해시 테이블(의 링크드리스트) 노드 생성
void CHT_DestroyNode(Node* TheNode); // 해시 테이블(의 링크드리스트) 노드 메모리 해제

void CHT_Set(HashTable* HT, KeyType Key, ValueType Value); // 해시 테이블 노드 삽입
ValueType CHT_Get(HashTable* HT, KeyType Key); // 해시 테이블 노드 탐색
int CHT_Hash(KeyType Key, int KeyLength, int TableSize); // 해시 함수 (자릿수 접기 + 나눗셈법)

#endif // !CHAINING_H

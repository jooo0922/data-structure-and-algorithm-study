#ifndef SIMPLE_HASHTABLE_H
#define SIMPLE_HASHTABLE_H
/*
	여기서 사용된 #ifndef ~ #endif 전처리기는
	헤더파일의 헤더가드를 처리해주는 방법 중 하나였지?

	cpp-study > TBCppStudy > Chapter1_12 > add.h 필기 참고!
*/

#include <stdio.h> // printf(), scanf() 같은 입출력 함수 선언이 포함된 헤더파일
#include <stdlib.h> // malloc(), free() 같은 메모리 할당 함수 선언이 포함된 헤더파일
// -> 헤더파일에 포함되어 있어야, 이를 가져다 쓰는 .c 파일들에서 사용할 때 에러가 안남.

// 해시 테이블 노드 구조체의 Key(주소로 사용할 데이터) 타입을 별칭으로 선언 
typedef int KeyType; 

// 해시 테이블 노드 구조체의 Value(Key로 얻어낸 주소에 저장할 데이터) 타입을 별칭으로 선언
typedef int ValueType;

// 해시 테이블에 추가될 단일 노드 구조체 타입을 별칭으로 선언
typedef struct tagNode
{
	KeyType Key; // 해시하여 주소값을 얻어낼 원본 데이터
	ValueType Value; // 해시하여 얻어낸 주소값에 저장할 데이터
} Node;

// 해시 테이블 구조체 타입을 별칭으로 선언
typedef struct tagHashTable
{
	int TableSize; // 해시 테이블 크기(= 노드 개수)
	Node* Table; // 해시 테이블 노드 배열
} HashTable;


#endif // !SIMPLE_HASHTABLE_H

#ifndef HUFFMAN_H
#define HUFFMAN_H
/*
	여기서 사용된 #ifndef ~ #endif 전처리기는
	헤더파일의 헤더가드를 처리해주는 방법 중 하나였지?

	cpp-study > TBCppStudy > Chapter1_12 > add.h 필기 참고!
*/

#include <stdio.h> // printf(), scanf() 같은 입출력 함수 선언이 포함된 헤더파일
#include <stdlib.h> // malloc(), free() 같은 메모리 할당 함수 선언이 포함된 헤더파일
#include "PriorityQueue.h" // 허프만 트리 구축에 사용할 우선순위 큐 자료구조가 포함된 헤더파일
// -> 헤더파일에 포함되어 있어야, 이를 가져다 쓰는 .c 파일들에서 사용할 때 에러가 안남.

// 허프만 코딩으로 압축할 문자열의 최대 길이를 매크로 전처리기로 선언
#define MAX_CHAR 256

// 허프만 코딩으로 압축할 각 문자의 접두어 코드 최대 크기를 bits 단위로 선언
#define MAX_BITS 8

// 허프만 코딩에 사용할 각 사용자 정의 자료형을 별칭으로 선언
typedef unsigned int UINT;
typedef unsigned char UCHAR;

// 허프만 코딩으로 압축할 각 기호 정보에 대한 사용자 정의 자료형을 별칭으로 선언
typedef struct TagSymbolInfo
{
	UCHAR Symbol; // 기호 자체를 저장할 멤버변수
	int Frequency; // 전체 문자열에서 기호가 차지하는 개수(p.587 의 '기호의 빈도')
} SymbolInfo;

// 허프만 트리에 추가될 단일 노드 구조체 타입을 별칭으로 선언
typedef struct TagHuffmanNode
{
	SymbolInfo Data; // 허프만 트리 노드에 저장된 기호 정보(허프만 트리에서는 '잎 노드'에만 기호가 저장됨. p.588 참고)
	struct TagHuffmanNode* Left; // 허프만 트리 노드의 왼쪽 자식 노드를 가리키는 포인터 멤버
	struct TagHuffmanNode* Right; // 허프만 트리 노드의 오른쪽 자식 노드를 가리키는 포인터 멤버
} HuffmanNode;

// 문자열을 허프만 코딩을 통해 접두어 코드로 압축하여 담아두는 버퍼를 표현한 자료형을 별칭으로 선언 (p.592 의 '압축 데이터' 테이블)
typedef struct TagBitBuffer
{
	UCHAR* Buffer; // 압축 데이터 테이블을 표현하는 배열
	UINT Size; // 압축 데이터 테이블의 크기
} BitBuffer;

// 각 기호에 대한 접두어 코드 탐색을 쉽게 하도록 만든 '접두어 코드 테이블'을 표현한 자료형을 별칭으로 선언 (p.591 의 '접두어 코드 테이블')
typedef struct TagHuffmanCode
{
	UCHAR Code[MAX_BITS]; // 각 기호에 대한 접두어 코드를 최대 8 bits(MAX_CHAR)까지 저장한 정적 배열
	int Size; // 각 기호에 대한 접두어 코드의 크기
};

#endif // !HUFFMAN_H

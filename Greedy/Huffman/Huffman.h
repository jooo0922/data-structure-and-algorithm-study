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
#define MAX_BIT 8

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
	UINT Size; // 압축 데이터 테이블의 크기 (단위는 bit)
	/*
		주!

		여기서 UINT Size 값은 
		realloc() 된 전체 Buffer 의 메모리 크기가 아닌, 
		
		Huffman_AddBit() 함수 내부에서
		비트 마스킹 연산에 의해 UCHAR* Buffer 메모리 블록에 '실제로 쓰여진 데이터(접두어 코드)의 크기'
		만을 기록 및 추적하기 위해 선언해 둔 멤버변수!
	*/
} BitBuffer;

// 각 기호에 대한 접두어 코드 탐색을 쉽게 하도록 만든 '접두어 코드 테이블'을 표현한 자료형을 별칭으로 선언 (p.591 의 '접두어 코드 테이블')
typedef struct TagHuffmanCode
{
	UCHAR Code[MAX_BIT]; // 각 기호에 대한 접두어 코드를 최대 8 bits(MAX_CHAR)까지 저장한 정적 배열
	int Size; // 각 기호에 대한 접두어 코드의 크기
} HuffmanCode;

HuffmanNode* Huffman_CreateNode(SymbolInfo NewData); // 허프만 트리 노드 생성
void Huffman_DestroyNode(HuffmanNode* Node); // 허프만 트리 노드 메모리 해제
void Huffman_DestroyTree(HuffmanNode* Node); // 허프만 트리 메모리 해제
void Huffman_AddBit(BitBuffer* Buffer, char Bit); // 압축 데이터 테이블(Buffer)에 변환된 접두어 코드(Bits) 기록
void Huffman_Encode(HuffmanNode** Tree, UCHAR* Source, BitBuffer* Encoded, HuffmanCode CodeTable[MAX_CHAR]); // 주어진 문자열(Source)을 허프만 코딩으로 데이터 압축 (압축된 데이터는 Encoded 에 기록)
void Huffman_Decode(HuffmanNode* Tree, BitBuffer* Encoded, UCHAR* Decoded); // 압축 데이터 테이블(Encoded)을 허프만 코딩으로 데이터 압축 해제 (압축 해제된 문자열은 Decoded 에 기록)
void Huffman_BuildPrefixTree(HuffmanNode** Tree, SymbolInfo SymbolInfoTable[MAX_CHAR]); // 허프만 트리 구축
void Huffman_BuildCodeTable(HuffmanNode* Tree, HuffmanCode CodeTable[MAX_CHAR], UCHAR Code[MAX_BIT], int Size); // 각 기호에 대한 접두어 코드 테이블 구축
void Huffman_PrintBinary(BitBuffer* Buffer); // 압축 데이터 테이블 출력

#endif // !HUFFMAN_H

/*
	허프만 트리 구축에 우선순위 큐를 사용하는 이유


	우선, 허프만 트리 자체를 우선순위 큐(즉, Priority 값을 기준 힙 자료구조)로 
	구현하려는 것은 절대 아님!

	다만, p.589 에서
	허프만 트리를 구축하는 알고리즘에서
	'탐욕 알고리즘'이 사용된다고 했었지?

	허프만 트리를 구축하는 과정에서
	'현재 상태에서 가장 좋은 해', 
	
	즉, '근시안적인 해'는 '빈도가 낮은 기호'를 
	먼저 선택하여 상위에 더 많은 부모 노드를 추가하여
	빈도가 낮은 기호를 갖는 노드의 경로를 길게 가져가는 것이라고 했지?

	그래야 허프만 트리의 압축률이 높아진다고 했으니까!

	이때, 노드집합에서 '빈도가 낮은 노드들을 우선적으로' 뽑으려면,
	허프만 트리 노드의 빈도(Frequency) 값을 우선순위(Priority) 삼는
	우선순위 큐에 허프만 트리의 각 노드들을 임시로 보관해두면 딱 좋겠지!

	왜냐? 우선순위 큐에서 Dequeue 할 때에는,
	항상 현재 상태에서 우선순위가 가장 낮은 노드들부터,
	즉, '현재 상태에서 빈도가 가장 낮은 노드들부터' Dequeue 되니까!

	그래서 허프만 트리의 각 노드들을 보관해두는 노드 집합(일종의 Node Pool)을
	우선순위 큐로 관리하면, 
	
	해당 우선순위 큐로부터 Dequeue 하는 행위 자체가
	탐욕 알고리즘의 근시안적인 해를 선택하는 행위에 해당하기 때문에
	탐욕 알고리즘이 사용된 허프만 트리 구축 과정에서 써먹기 아주 좋은 자료구조임!
*/

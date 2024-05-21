#include "Huffman.h"

// 허프만 트리 노드 생성
HuffmanNode* Huffman_CreateNode(SymbolInfo NewData)
{
	// HuffmanNode 구조체 크기 만큼의 힙 메모리 할당
	// malloc() 이 할당한 힙 메모리 주소값 반환 시, HuffmanNode* 타입의 포인터 주소로 형변환하여 반환.
	HuffmanNode* NewNode = (HuffmanNode*)malloc(sizeof(HuffmanNode));

	// HuffmanNode 구조체 각 멤버변수 초기화
	NewNode->Left = NULL;
	NewNode->Right = NULL;
	NewNode->Data = NewData;

	// 생성된 허프만 트리 노드 구조체 주소값(이 담긴 포인터 변수) 반환
	return NewNode;
}

// 허프만 트리 노드 메모리 해제
void Huffman_DestroyNode(HuffmanNode* Node)
{
	free(Node);
}

// 허프만 트리 메모리 해제
void Huffman_DestroyTree(HuffmanNode* Node)
{

}

// 압축 데이터 테이블(Buffer)에 변환된 접두어 코드(Bits) 기록
void Huffman_AddBit(BitBuffer* Buffer, char Bit)
{

}

// 주어진 문자열(Source)을 허프만 코딩으로 데이터 압축 (압축된 데이터는 Encoded 에 기록)
void Huffman_Encode(HuffmanNode** Tree, UCHAR* Source, BitBuffer* Encoded, HuffmanCode CodeTable[MAX_CHAR])
{

}

// 압축 데이터 테이블(Encoded)을 허프만 코딩으로 데이터 압축 해제 (압축 해제된 문자열은 Decoded 에 기록)
void Huffman_Decode(HuffmanNode* Tree, BitBuffer* Encoded, UCHAR* Decoded)
{

}

// 허프만 트리 구축
void Huffman_BuildPrefixTree(HuffmanNode** Tree, SymbolInfo SymbolInfoTable[MAX_CHAR])
{

}

// 각 기호에 대한 접두어 코드 테이블 구축
void Huffman_BuildCodeTable(HuffmanNode* Tree, HuffmanCode CodeTable[MAX_CHAR], UCHAR Code[MAX_BIT], int Size)
{

}

// 압축 데이터 테이블 출력
void Huffman_PrintBinary(BitBuffer* Buffer)
{

}

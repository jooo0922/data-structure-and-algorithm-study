#include "Huffman.h"
#include <string.h> // memset() 같은 연속된 메모리 블록 조작 함수 사용을 위해 포함

int main()
{
	// 압축할 원본 문자열 초기화
	char* Source = "This Is Algorithms.";

	// 허프만 압축 데이터를 해제한 압축 해제 버퍼를 담는 문자열 초기화
	char* Decoded = "";

	// 허프만 트리를 구축할 뿌리노드의 포인터 변수 초기화
	HuffmanNode* Tree = NULL;

	// 허프만 알고리즘으로 압축한 접두어 코드들을 담는 압축 데이터 테이블 초기화
	BitBuffer Encoded = { NULL, 0 };

	// 허프만 압축 시 참고할 256 개의 각 ASCII 기호별 접두어 코드 테이블 초기화
	HuffmanCode CodeTable[MAX_CHAR];

	// ASCII 접두어 코드 테이블에 할당된 메모리 블록의 값들을 모두 0으로 초기화
	memset(&CodeTable, 0, sizeof(HuffmanCode) * MAX_CHAR);

	// 허프만 압축 실행 -> 허프만 트리 구축 및 압축 데이터 테이블에 원본 문자열이 압축된 접두어 코드 기록 
	Huffman_Encode(&Tree, (UCHAR*)Source, &Encoded, CodeTable);

	// 원본 문자열과 압축 데이터 테이블의 크기를 각각 비트 단위로 출력
	printf("Original Size:%d Encoded Size:%d\n", (strlen(Source) + 1) * sizeof(char) * 8, Encoded.Size);

	// 압축 해제 버퍼에 원본 문자열 크기만큼 메모리 동적 할당
	Decoded = (char*)malloc(sizeof(char) * (strlen(Source) + 1));

	// 압축 데이터 테이블을 허프만 압축 해제하여 결과물을 압축 해제 버퍼에 저장
	Huffman_Decode(Tree, &Encoded, (UCHAR*)Decoded);

	// 원본 문자열 출력
	printf("Original : %s\n", Source);

	// 압축 데이터 테이블을 비트 단위로 출력
	printf("Encoded  : ");
	Huffman_PrintBinary(&Encoded);

	printf("\n");

	// 압축 해제 버퍼에 저장된 문자열 출력
	printf("Decoded  : %s\n", Decoded);

	// 허프만 압축 시 구축했던 허프만 트리 메모리 반납
	Huffman_DestroyTree(Tree);

	// malloc() 으로 동적 할당했던 압축 해제 버퍼 메모리 반납
	free(Decoded);

	return 0;
}
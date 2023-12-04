#include "SimpleHashTable.h"

// 해시 테이블 구조체 생성
HashTable* SHT_CreateHashTable(int TableSize)
{
	// HashTable 구조체 크기 만큼의 힙 메모리 할당
	// malloc() 이 할당한 힙 메모리 주소값 반환 시, HashTable* 타입의 포인터 주소로 형변환하여 반환.
	HashTable* HT = (HashTable*)malloc(sizeof(HashTable));

	// 해시 테이블 노드 배열은 "Node 구조체 크기 * 해시 테이블의 크기" 만큼 배열 메모리 동적 할당
	HT->Table = (Node*)malloc(sizeof(Node) * TableSize);

	// 해시 테이블 크기 멤버변수 초기화
	HT->TableSize = TableSize;

	// 생성된 해시 테이블 구조체 주소값(이 담긴 포인터 변수) 반환
	return HT;
}

// 해시 테이블 노드 추가
void SHT_Set(HashTable* HT, KeyType Key, ValueType Value)
{

}

// 해시 테이블 노드 데이터 읽기
ValueType SHT_Get(HashTable* HT, KeyType Key)
{

}

// 해시 테이블 구조체 메모리 해제
void SHT_DestroyHashTable(HashTable* HT)
{

}

// 해시 함수 (나눗셈법)
int SHT_Hash(KeyType Key, int TableSize)
{

}
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
	// 나눗셈법으로 해싱한 테이블의 주소값 반환
	int Address = SHT_Hash(Key, HT->TableSize);

	// 해싱한 주소값을 노드 배열의 인덱스로 삼아, 해당 노드의 멤버 값 초기화
	HT->Table[Address].Key = Key;
	HT->Table[Address].Value = Value;
}

// 해시 테이블 노드 데이터 읽기
ValueType SHT_Get(HashTable* HT, KeyType Key)
{
	// 두 번째 매개변수로 입력받은 Key 값으로 재해싱하여 주소값 반환
	// (참고로, 나눗셈법 알고리즘은 동일한 Key 값이 입력되면 항상 동일한 주소값을 반환해 줌!)
	int Address = SHT_Hash(Key, HT->TableSize);
	
	// 입력받은 Key 값에 대응되는 해시 테이블 노드의 Value 를 반환
	return HT->Table[Address].Value;
}

// 해시 테이블 구조체 메모리 해제
void SHT_DestroyHashTable(HashTable* HT)
{
	// 해시 테이블 노드 배열 메모리 해제
	free(HT->Table);

	// 해시 테이블 구조체 메모리 해제
	free(HT);
}

// 해시 함수 (나눗셈법)
int SHT_Hash(KeyType Key, int TableSize)
{
	// 해시 함수를 나눗셈법 알고리즘으로 구현
	// 입력값(Key)을 해시 테이블 크기(TableSize)로 나눈 나머지값을 테이블의 주소값으로 반환함.
	// 이때, 나눗셈법으로 해싱한 주소값은 0 ~ (테이블 크기 - 1) 사이의 주소 반환을 보장함! (p.337 참고)
	return Key % TableSize;
}
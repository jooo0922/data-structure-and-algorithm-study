#include "OpenAddressing.h"

// 해시 테이블 구조체 생성
HashTable* OAHT_CreateHashTable(int TableSize)
{
	// HashTable 구조체 크기 만큼의 힙 메모리 할당
	// malloc() 이 할당한 힙 메모리 주소값 반환 시, HashTable* 타입의 포인터 주소로 형변환하여 반환.
	HashTable* HT = (HashTable*)malloc(sizeof(HashTable));

	// HashTable 각 요소(ElementType) 구조체 크기 * HashTable 크기 만큼 힙 메모리 동적 할당
	HT->Table = (ElementType*)malloc(sizeof(ElementType) * TableSize);

	// Table 멤버에 동적 할당된 메모리 블록의 값을 모두 0으로 초기화
	/*
		이처럼, 동적할당된 메모리 블록을 
		0 또는 예측 가능한 안정적인 상수값으로 초기화하는 작업이 매우 중요함.

		특히, 해시테이블처럼 Key, Value 자리에
		예측할 수 없는 쓰레기값(garbage value)이 들어있으면
		예상치 못한 버그나 오작동을 일으킬 수 있기 때문에,

		동적할당된 해시테이블 요소의 모든 메모리 블록을
		0으로 초기화해준 것임!
	*/
	memset(HT->Table, 0, sizeof(ElementType) * TableSize);

	// 해시 테이블의 나머지 멤버변수 초기화
	HT->TableSize = TableSize;
	HT->OccupiedCount = 0;

	// 생성된 해시 테이블 구조체 주소값(이 담긴 포인터 변수) 반환
	return HT;
}

// 해시 테이블 구조체 메모리 해제
void OAHT_DestroyHashTable(HashTable* HT)
{

}

// 해시 테이블 요소 메모리 해제
void OAHT_ClearElement(ElementType* Element)
{

}

// 해시 테이블 요소 삽입
void OAHT_Set(HashTable** HT, KeyType Key, ValueType Value)
{

}

// 해시 테이블 요소 탐색
ValueType OAHT_Get(HashTable* HT, KeyType Key)
{

}

// 해시 함수 (해시 주소값 계산용)
int OAHT_Hash(KeyType Key, int KeyLength, int TableSize)
{

}

// 해시 함수 (탐사 이동폭 계산용 -> 이중 해싱)
int OAHT_Hash2(KeyType Key, int KeyLength, int TableSize)
{

}

// 해시 테이블 재해싱
void OAHT_Rehash(HashTable** HT)
{

}
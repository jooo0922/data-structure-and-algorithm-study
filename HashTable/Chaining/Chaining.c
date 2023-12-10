#include "Chaining.h"

// 해시 테이블 구조체 생성
HashTable* CHT_CreateHashTable(int TableSize)
{
	// HashTable 구조체 크기 만큼의 힙 메모리 할당
	// malloc() 이 할당한 힙 메모리 주소값 반환 시, HashTable* 타입의 포인터 주소로 형변환하여 반환.
	HashTable* HT = (HashTable*)malloc(sizeof(HashTable));

	// 해시 테이블 링크드리스트는 "링크드리스트의 단일 Node 구조체 크기 * 해시 테이블의 크기" 만큼 메모리를 미리 동적 할당해 둠.
	// 다만, 체이닝 기반 해시 테이블의 Table 멤버는 링크드리스트 타입으로 선언되어 있으므로, 주소값 할당 시, List* 구조체 포인터 타입으로 형변환해줄 것!
	HT->Table = (List*)malloc(sizeof(Node) * TableSize);

	// Table 멤버에 동적 할당된 메모리 블록의 값을 모두 0으로 초기화
	// 이때, 동적 할당 시, List* 타입으로 주소값을 캐스팅 했으므로, sizeof(List) 로 초기화할 메모리 블록의 크기를 계산하는 것은 가능함.
	// 그러나, 가급적 이렇게 메모리 동적 할당 시 캐스팅하는 기법은 권장하지 않는다고 함.
	memset(HT->Table, 0, sizeof(List) * TableSize);

	// 해시 테이블 크기 멤버변수 초기화
	HT->TableSize = TableSize;

	// 생성된 해시 테이블 구조체 주소값(이 담긴 포인터 변수) 반환
	return HT;
}

// 해시 테이블 구조체 메모리 해제
void CHT_DestroyHashTable(HashTable* HT)
{

}

// 해시 테이블(의 링크드리스트) 노드 생성
Node* CHT_CreateNode(KeyType Key, ValueType Value)
{

}

// 해시 테이블(의 링크드리스트) 노드 메모리 해제
void CHT_DestroyNode(Node* TheNode)
{

}

// 해시 테이블 노드 삽입
void CHT_Set(HashTable* HT, KeyType Key, ValueType Value)
{

}

// 해시 테이블 노드 탐색
ValueType CHT_Get(HashTable* HT, KeyType Key)
{

}

// 해시 함수 (자릿수 접기 + 나눗셈법)
int CHT_Hash(KeyType Key, int KeyLength, int TableSize)
{

}
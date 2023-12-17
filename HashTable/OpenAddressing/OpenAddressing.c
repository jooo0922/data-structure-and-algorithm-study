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
	// 해시 테이블 각 요소의 메모리 해제(== Key, Value 초기화)
	int i = 0;
	for (int i = 0; i < HT->TableSize; i++)
	{
		OAHT_ClearElement(&(HT->Table[i]));
	}

	// 해시 테이블 구조체 메모리 해제
	free(HT->Table);
	free(HT);
}

// 해시 테이블 요소 메모리 해제 -> 정확히는, 해당 요소의 Key, Value 초기화
void OAHT_ClearElement(ElementType* Element)
{
	// 해당 요소 점유 상태가 EMPTY 라면,
	// 아직 해당 요소의 Key, Value 메모리 블록이 0으로 초기화되어 있는 상태이므로,
	// 메모리 초기화를 생략함.
	if (Element->Status == EMPTY)
	{
		return;
	}

	// 만약 점유 상태가 OCCUPIED 라면, 해당 요소의 Key, Value 블록 메모리 해제
	free(Element->Key);
	free(Element->Value);
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
	int i = 0;
	int HashValue = 0; // 자릿수 접기로 누산할 해시값 변수 초기화

	// 문자열 개수만큼 순회하며 해시값 누산
	for (i = 0; i < KeyLength; i++)
	{
		// P.344 ~ 346 예제처럼, 최대 문자열 길이가 10개이고,
		// 테이블 크기가 12289로 설정되어 14자리 bits 로 표현 가능하다는 전제 하에,
		// 해시값을 누산할 때마다 누산값을 이진수 상에서 3칸식 Left Shift 해주면,
		// 주어진 14 자리의 bits 를 모두 활용해서 표현함으로써,
		// 10개의 문자열 길이로 0 ~ 12288 사이의 주소값을 모두 계산 가능함!
		// (자세한 설명은 p.345 ~ 346 참고)
		HashValue = (HashValue << 3) + Key[i];

		/*
			참고로, char 타입은 + 같은 산술연산자의 피연산자로 사용될 시,
			ASCII 코드로 자동 변환되어 처리됨!
		*/
	}

	// 자릿수 접기로 누산한 해시값을 나눗셈법으로 나머지 연산함
	HashValue = HashValue % TableSize;

	// 최종 계산된 해시값 반환
	return HashValue;
}

// 해시 함수 (탐사 이동폭 계산용 -> 이중 해싱)
int OAHT_Hash2(KeyType Key, int KeyLength, int TableSize)
{
	int i = 0;
	int HashValue = 0; // 자릿수 접기로 누산할 해시값 변수 초기화

	// 문자열 개수만큼 순회하며 해시값 누산
	for (i = 0; i < KeyLength; i++)
	{
		HashValue = (HashValue << 2) + Key[i];
	}

	// 자릿수 접기로 누산한 해시값을 나눗셈법으로 나머지 연산함
	HashValue = HashValue % (TableSize - 3);

	// 최종 계산된 해시값 반환
	return HashValue + 1;
}

// 해시 테이블 재해싱
void OAHT_Rehash(HashTable** HT)
{
	int i = 0;

	// 현재 해시테이블 요소들의 동적 배열(의 주소값) 임시 저장
	ElementType* OldTable = (*HT)->Table;

	// 현재 해시테이블보다 2배 더 큰 새로운 해시테이블 생성
	HashTable* NewHT = OAHT_CreateHashTable((*HT)->TableSize * 2);

	// 재해싱 알림 출력
	printf("\nRehashed. New table size is : %d\n\n", NewHT->TableSize);

	// 현재 해시테이블 요소들 중, 점유 상태인 요소들의 [Key, Value] 를 가지고서
	// 새로운 해시테이블 요소로 추가
	for (i = 0; i < (*HT)->TableSize; i++)
	{
		if (OldTable[i].Status == OCCUPIED)
		{
			OAHT_Set(&NewHT, OldTable[i].Key, OldTable[i].Value);
		}
	}

	// 기존 해시테이블 메모리 해제
	OAHT_DestroyHashTable((*HT));

	// 이중 포인터로 선언된 매개변수를 de-referencing 하여,
	// 기존 해시테이블 주소값이 저장된 외부 포인터 변수에 접근한 뒤,
	// 새로운 해시테이블 주소값을 할당
	(*HT) = NewHT;
}
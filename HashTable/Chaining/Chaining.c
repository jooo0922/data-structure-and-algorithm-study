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

// 해시 테이블(의 링크드리스트) 노드 생성
Node* CHT_CreateNode(KeyType Key, ValueType Value)
{
	// Node 구조체 크기 만큼의 힙 메모리 할당
	Node* NewNode = (Node*)malloc(sizeof(Node));

	// Node 구조체의 Key 멤버에 (매개변수 Key 문자열 길이 + 1) 만큼의 동적 배열 할당 후, strcpy() 로 문자열 복사
	// 길이에 + 1 더한 이유는, 종료문자('\0')를 포함하기 위함.
	NewNode->Key = (char*)malloc(sizeof(char) * (strlen(Key) + 1));
	strcpy_s(NewNode->Key, sizeof(char) * (strlen(Key) + 1), Key);

	// Node 구조체의 Value 멤버에 (매개변수 Value 문자열 길이 + 1) 만큼의 동적 배열 할당 후, strcpy() 로 문자열 복사
	// 길이에 + 1 더한 이유는, 종료문자('\0')를 포함하기 위함.
	NewNode->Value = (char*)malloc(sizeof(char) * (strlen(Value) + 1));
	strcpy_s(NewNode->Value, sizeof(char) * (strlen(Value) + 1), Value);

	// Node 구조체의 다음 노드 포인터를 NULL 초기화
	NewNode->Next = NULL;

	// 생성된 Node 구조체 주소값 반환
	return NewNode;
}

// 해시 테이블(의 링크드리스트) 노드 메모리 해제
void CHT_DestroyNode(Node* TheNode)
{
	// 노드의 각 문자열 멤버변수에 할당된 메모리 반납
	free(TheNode->Key);
	free(TheNode->Value);

	// 노드 메모리 반납
	free(TheNode);
}

// 해시 테이블의 링크드리스트 메모리 해제
void CHT_DestroyList(List L)
{
	// 링크드리스트 NULL 체크
	if (L == NULL)
	{
		return;
	}

	// 링크드리스트의 현재 노드를 기준으로, 다음 노드가 존재할 경우,
	// 재귀적으로 함수를 호출하여 다음 노드 메모리 해제
	if (L->Next != NULL)
	{
		CHT_DestroyList(L->Next);
	}

	// 링크드리스트의 현재 노드 메모리 해제
	CHT_DestroyNode(L);
}

// 해시 테이블 구조체 메모리 해제
void CHT_DestroyHashTable(HashTable* HT)
{
	int i = 0;
	for (i = 0; i < HT->TableSize; i++)
	{
		// 해시테이블의 각 주소값(= 해시값. i)을 순회하며
		// 그 주소값으로 저장된 링크드리스트 메모리를 순차적으로 해제
		List L = HT->Table[i];
		CHT_DestroyList(L);
	}

	// 링크드리스트 배열(여러 개의 링크드리스트로 이루어진 동적 배열) 멤버변수 Table 의 메모리 해제
	free(HT->Table);

	// HashTable 구조체 메모리 해제
	free(HT);
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
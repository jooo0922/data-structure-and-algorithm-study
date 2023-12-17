#include "HashTableDisjointSet.h"

// 해시 테이블 구조체 생성
HashTable* HTDS_CreateHashTable(int TableSize)
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
void HTDS_DestroyHashTable(HashTable* HT)
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
void HTDS_ClearElement(ElementType* Element)
{
	// 해당 요소 점유 상태가 EMPTY 라면,
	// 아직 해당 요소의 Key, Value 메모리 블록이 0으로 초기화되어 있는 상태이므로,
	// 메모리 초기화를 생략함.
	if (Element->Status == EMPTY)
	{
		return;
	}

	// 해당 요소의 뿌리노드 초기화
	Element->Root = NULL;

	// 만약 점유 상태가 OCCUPIED 라면, 해당 요소의 Key, Value 블록 메모리 해제
	free(Element->Key);
	free(Element->Value);
}

// 해시 테이블 요소 삽입
void HTDS_Set(HashTable** HT, ElementType* Root, KeyType Key, ValueType Value)
{
	// Key 길이, 해시값, 탐사 이동폭 변수 선언
	int KeyLen, Address, StepSize;

	// 해시테이블 점유율 변수 선언
	double Usage;

	// 현재 해시테이블 점유율 계산 (int 타입 결과값을 double 타입으로 형변환)
	Usage = (double)(*HT)->OccupiedCount / (*HT)->TableSize;

	// 현재 해시테이블 점유율이 50%(== 0.5) 초과 시, 재해싱
	if (Usage > 0.5)
	{
		OAHT_Rehash(HT);
	}

	// 해시테이블에 삽입할 요소의 Key 길이, 해시값, 탐사 이동폭 계산
	KeyLen = strlen(Key);
	Address = OAHT_Hash(Key, KeyLen, (*HT)->TableSize);
	StepSize = OAHT_Hash2(Key, KeyLen, (*HT)->TableSize);

	// 해싱된 주소값에 이미 어떤 요소가 점유되어 있고,
	// 점유된 요소의 Key 값과 삽입할 요소의 Key 값이 다를 때, 
	// (strcmp() 는 두 문자열 비교 결과가 같을 때에만 0을 반환)
	// 즉, '해시값 충돌'이 발생했을 때의 처리
	while ((*HT)->Table[Address].Status != EMPTY &&
		strcmp((*HT)->Table[Address].Key, Key) != 0)
	{
		// 해시값 충돌이 발생했음을 출력
		printf("Collision occured! : Key(%s), Address(%d), StepSize(%d)\n", Key, Address, StepSize);

		// 해시값 충돌이 발생되지 않을 때까지
		// 기존 해시값(Address)에 이중 해시함수로 계산된 탐사 이동폭(StepSize)을
		// 계속 더하면서 삽입할 요소가 자리잡을 수 있는 새로운 주소값을 계속 탐사해나감.
		// 이때, '% TableSize' 로 나머지 연산을 해주는 것은,
		// p.365 에서 테이블의 끝을 넘어가는 경우, 첫 주소 칸으로 돌아가서 마저 탐사하는 동작을 구현한 코드!
		Address = (Address + StepSize) % (*HT)->TableSize;
	}

	// 여기까지 무사히 넘어왔다면, 충돌이 발생하지 않는 해시값을 찾은 상태이므로,
	// 해당 해시값(주소값) 자리에 새로운 요소의 [Key, Value] 쌍을 삽입

	// 새로운 요소의 Key 삽입
	// (참고로, 문자열 메모리 동적할당 시, KeyLen + 1 해준 것은, 종료문자('\0') 포함 목적!)
	(*HT)->Table[Address].Key = (char*)malloc(sizeof(char) * (KeyLen + 1));
	strcpy_s((*HT)->Table[Address].Key, sizeof(char) * (KeyLen + 1), Key);

	// 새로운 요소의 Value 삽입
	(*HT)->Table[Address].Value = (char*)malloc(sizeof(char) * (strlen(Value) + 1));
	strcpy_s((*HT)->Table[Address].Value, sizeof(char) * (strlen(Value) + 1), Value);

	// 삽입된 새로운 요소의 상태를 OCCUPIED 로 변경
	(*HT)->Table[Address].Status = OCCUPIED;

	// 삽입된 새로운 요소의 뿌리노드 초기화
	(*HT)->Table[Address].Root = Root;

	// 해시테이블의 점유 요소 개수를 +1 증가
	(*HT)->OccupiedCount++;

	// 새로운 해시값 주소에 요소가 삽입되었음을 출력
	printf("Key(%s) entered at address(%d)\n", Key, Address);
}

// 해시 테이블 요소 탐색
ValueType HTDS_Get(HashTable* HT, KeyType Key)
{
	// Key 문자열 길이 저장
	int KeyLen = strlen(Key);

	// 탐색할 요소의 해시값, 탐사 이동폭 계산
	int Address = OAHT_Hash(Key, KeyLen, HT->TableSize);
	int StepSize = OAHT_Hash2(Key, KeyLen, HT->TableSize);

	// 해시값 충돌이 발생하지 않을 때까지 탐색할 요소가 저장된 해시값을 계속 탐사해나감. 
	while (HT->Table[Address].Status != EMPTY &&
		strcmp(HT->Table[Address].Key, Key) != 0)
	{
		// 해시값 충돌이 발생되지 않을 때까지
		// 기존 해시값(Address)에 이중 해시함수로 계산된 탐사 이동폭(StepSize)을
		// 계속 더하면서 탐색할 요소가 저장된 새로운 주소값을 계속 탐사해나감.
		Address = (Address + StepSize) % HT->TableSize;
	}

	// 해시값 충돌이 발생하지 않는 주소값을 찾은 후, 해당 요소의 Value 반환
	return HT->Table[Address].Value;
}

// 해시 함수 (해시 주소값 계산용)
int HTDS_Hash(KeyType Key, int KeyLength, int TableSize)
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
int HTDS_Hash2(KeyType Key, int KeyLength, int TableSize)
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
void HTDS_Rehash(HashTable** HT)
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
			OAHT_Set(&NewHT, OldTable[i].Root, OldTable[i].Key, OldTable[i].Value);
		}
	}

	// 기존 해시테이블 메모리 해제
	OAHT_DestroyHashTable((*HT));

	// 이중 포인터로 선언된 매개변수를 de-referencing 하여,
	// 기존 해시테이블 주소값이 저장된 외부 포인터 변수에 접근한 뒤,
	// 새로운 해시테이블 주소값을 할당
	(*HT) = NewHT;
}
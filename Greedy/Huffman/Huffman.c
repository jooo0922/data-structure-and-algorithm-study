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
	if (Node == NULL)
	{
		// 허프만 트리를 재귀적으로 순회하면서 매개변수로 전달받은 자식노드가 NULL 이면 함수 종료
		return;
	}

	// 현재 순회중인 허프만 트리 노드의 왼쪽과 오른쪽 자식노드에 대해 각각 재귀 호출
	Huffman_DestroyTree(Node->Left);
	Huffman_DestroyTree(Node->Right);

	// 현재 순회중인 허프만 트리 노드 메모리 해제
	Huffman_DestroyNode(Node);
}

// 압축 데이터 테이블(Buffer)에 변환된 접두어 코드(Bits) 기록
void Huffman_AddBit(BitBuffer* Buffer, char Bit)
{
	// 압축 데이터 테이블(Buffer)에 비트 마스킹으로 접두어 코드를 기록할 때 사용할 비트마스크 변수
	// 비트 마스킹 관련 https://github.com/jooo0922/cpp-study/blob/main/TBCppStudy/Chapter3_9/Chapter3_9.cpp 참고
	UCHAR Mask = 0x80; // 1000 0000

	/*
		비트 마스킹 연산에 의해 UCHAR* Buffer 메모리 블록에 
		'실제로 쓰여진 데이터(접두어 코드)의 크기(비트 수)'가 8배수를 넘었다면,
		
		기존에 realloc() 된 메모리 블록에 데이터를 모두 기록했다는 뜻이므로,
		(-> why? Huffman_AddBit() 내에서 realloc() 할 때, 
		1 byte(= 8 bits) 씩 추가하기 때문!)

		다시 realloc() 을 호출하여
		1 byte(= 8 bits) 만큼의 메모리를 재할당함.
	*/
	if (Buffer->Size % 8 == 0)
	{
		// 기존 UCHAR* Buffer 메모리 블록에 1 byte(= 8 bits) 만큼 추가 (realloc() 관련 설명 하단 참고)
		Buffer->Buffer = realloc(Buffer->Buffer, sizeof(UCHAR) * ((Buffer->Size / 8) + 1));

		// 기존 Buffer 메모리 블록에 추가된 8 bits 들을 모두 0으로 초기화 (관련 필기 하단 참고)
		Buffer->Buffer[Buffer->Size / 8] = 0x00;
	}

	// right shift 로 비트마스킹을 수행할 자릿수 결정 (관련 필기 하단 참고)
	Mask >>= Buffer->Size % 8;

	if (Bit == 1)
	{
		// 매개변수로 입력받은 비트 값이 1이면, Buffer 메모리 블록에 1 로 덮어쓰도록 bitwise OR 비트마스킹 수행
		Buffer->Buffer[Buffer->Size / 8] |= Mask;
	}
	else
	{
		// 매개변수로 입력받은 비트 값이 0이면, Buffer 메모리 블록에 0 으로 덮어쓰도록 보수를 취해 bitwise AND 비트마스킹 수행
		// https://github.com/jooo0922/cpp-study/blob/main/TBCppStudy/Chapter3_9/Chapter3_9.cpp 참고
		Buffer->Buffer[Buffer->Size / 8] &= ~Mask;
	}

	// 실제 UCHAR* Buffer 메모리 블록에 쓰여진 데이터(접두어 코드)의 크기 증가
	Buffer->Size++;
}

// 주어진 문자열(Source)을 허프만 코딩으로 데이터 압축 (압축된 데이터는 Encoded 에 기록)
void Huffman_Encode(HuffmanNode** Tree, UCHAR* Source, BitBuffer* Encoded, HuffmanCode CodeTable[MAX_CHAR])
{

}

// 압축 데이터 테이블(Encoded)을 허프만 코딩으로 데이터 압축 해제 (압축 해제된 문자열은 Decoded 에 기록)
void Huffman_Decode(HuffmanNode* Tree, BitBuffer* Encoded, UCHAR* Decoded)
{

}

// 허프만 트리 구축 (p.589 ~ p.590 과정 코드로 구현)
/*
	매개변수 정리

	- HuffmanNode** Tree : 해당 함수에서 구축하려는 허프만 트리의 최상위 노드
	- SymbolInfo SymbolInfoTable[MAX_CHAR] : 압축할 문자열에 등장하는 각 기호와 빈도 수를 기록한 테이블
*/
void Huffman_BuildPrefixTree(HuffmanNode** Tree, SymbolInfo SymbolInfoTable[MAX_CHAR])
{
	// 반복문을 순회할 인덱스 변수 초기화
	int i = 0;

	// 노드집합(우선순위 큐)에 마지막으로 남게 될 노드를 Dequeue 하여 저장할 변수 선언 (p.590 하단 참고)
	PQNode Result;

	// 노드집합으로 사용할 우선순위 큐 생성 (우선순위 큐 사용 이유 관련 하단 필기 참고)
	PriorityQueue* PQ = PQ_Create(0);

	// 압축할 문자열의 최대 길이만큼 반복문 순회
	for (i = 0; i < MAX_CHAR; i++)
	{
		// 압축할 문자열에 등장하는 각 기호와 그것의 빈도 수를 기록한 테이블을 순회함
		if (SymbolInfoTable[i].Frequency > 0)
		{
			// 각 기호와 빈도 수 데이터를 갖는 허프만 트리 노드(즉, 기호를 갖는 잎 노드) 생성
			// -> 허프만 트리에서 기호는 잎 노드에만 저장된다고 했었지? p.589 참고!
			HuffmanNode* BitNode = Huffman_CreateNode(SymbolInfoTable[i]);

			// 해당 허프만 트리 노드의 '빈도 수'를 '우선순위'로 삼는 우선순위 큐 노드 생성
			PQNode NewNode;
			NewNode.Priority = SymbolInfoTable[i].Frequency;
			NewNode.Data = BitNode; // PriorityQueue.h 에서 다른 예제들에서의 재사용성을 위해, PQNode.Data 타입은 void* 로 지정해놨었지?

			// 기호와 빈도 수를 갖는 각각의 잎 노드를 노드집합(우선순위 큐)에 추가 (p.589)
			PQ_Enqueue(PQ, NewNode);
		}
	}

	// 노드집합(우선순위 큐)에 단 하나의 노드만 남을 때까지 탐욕 알고리즘 반복 수행 (p.590 하단)
	while (PQ->UsedSize > 1)
	{
		// 해 선택 단계에서 고른 노드 2개의 부모노드로 추가할 허프만 트리 노드 생성
		SymbolInfo NewData = { 0, 0 };
		HuffmanNode* BitNode = Huffman_CreateNode(NewData);
		HuffmanNode* Left;
		HuffmanNode* Right;

		// 새로 만든 허프만 트리 부모노드에 대응되는, 노드집합(우선순위 큐)에 추가할 우선순위 큐 노드 생성
		PQNode QLeft;
		PQNode QRight;
		PQNode NewNode;

		// 해 선택 -> 현 시점에서 빈도가 가장 작은 노드 2개를 노드집합(우선순위 큐)에서 선택 (근시안적인 해)
		PQ_Dequeue(PQ, &QLeft);
		PQ_Dequeue(PQ, &QRight);

		// 노드집합에서 선택한 2개의 우선순위 큐 노드에 대응되는 허프만 트리 노드 주소값 복사
		Left = (HuffmanNode*)QLeft.Data;
		Right = (HuffmanNode*)QRight.Data;

		// 선택한 2개의 노드에 대한 허프만 트리 부모노드의 멤버변수 값 초기화
		// 이때, 부모노드의 빈도 수는 선택한 2개의 노드의 빈도 수의 합으로 지정 (p.589 상단)
		BitNode->Data.Symbol = 0;
		BitNode->Data.Frequency = Left->Data.Frequency + Right->Data.Frequency;

		// 부모노드의 왼쪽, 오른쪽 자식 노드 포인터 멤버에 각각 선택한 2개의 허프만 트리 노드 주소값 할당
		BitNode->Left = Left;
		BitNode->Right = Right;

		// 허프만 트리 부모노드에 대응되는 우선순위 큐 부모노드의 멤버변수 값 초기화
		// 마찬가지로, 부모노드의 '빈도 수'를 '우선순위'로 지정 
		NewNode.Priority = BitNode->Data.Frequency;
		NewNode.Data = BitNode;

		// 생성한 부모노드를 노드집합(우선순위 큐)에 추가 (p.590)
		PQ_Enqueue(PQ, NewNode);
	}

	/*
		노드집합(우선순위 큐)에 단 하나의 노드만 남게 되어 while 문을 탈출한 뒤,
		최종적으로 남아있는 노드(= 허프만 트리 자체)를 Dequeue 하여 꺼내오기. (p.590 하단)
	*/
	PQ_Dequeue(PQ, &Result);

	/*
		꺼내온 우선순위 큐(노드집합) 노드에 대응되는 허프만 트리 노드의 주소값을
		매개변수로 전달받은 허프만 트리 이중 포인터를 de-referencing 하여 저장
		
		-> 이렇게 하면, 외부에서 전달한 HuffmanNode* 타입의 포인터 변수에
		완성된 허프만 트리 노드의 주소값이 저장될 것임!
	*/
	*Tree = (HuffmanNode*)Result.Data;
}

// 각 기호에 대한 접두어 코드 테이블 구축
void Huffman_BuildCodeTable(HuffmanNode* Tree, HuffmanCode CodeTable[MAX_CHAR], UCHAR Code[MAX_BIT], int Size)
{

}

// 압축 데이터 테이블 출력
void Huffman_PrintBinary(BitBuffer* Buffer)
{

}

/*
	void* realloc(void* ptr, size_t size);

	realloc() 는 메모리 블록의 크기를 조정할 수 있음. 
	기존의 메모리 블록을 확대 또는 축소할 수 있음.

	멤버변수 설명
	- ptr : 현재 할당된 메모리 블록을 가리키는 포인터.
	- size : 새로운 메모리 블록의 크기를 바이트 단위로 지정.

	위 예제에서
	새로운 현재 메모리 블록 Buffer->Buffer 의
	새로운 메모리 블록의 크기를 sizeof(UCHAR) * ((Buffer->Size / 8) + 1)
	로 계산하고 있는데,

	일단, sizeof(UCHAR) 는 unsigned char 자료형의 메모리 크기인 1 byte 를 반환하고,

	(Buffer->Size / 8) 는 현재 메모리 블록 Buffer->Buffer 에 비트 마스킹에 의해
	'실제 쓰여진 데이터(접두어 코드)'의 비트 수를 byte 단위로 변환하는 것이라고 보면 됨!
	전체 쓰여진 데이터의 비트 수를 8 bits 로 나누고 있으니까!

	여기에 + 1 하는 건 뭐겠어 그러면?
	현재 메모리 블록 Buffer->Buffer 의 크기(byte)에 1 byte(= 8 bits) 만큼을
	더 늘려서 재할당하라는 뜻이겠지!
*/

/*
	realloc() 으로 추가된 메모리 블록 0으로 초기화


	Buffer->Buffer[Buffer->Size / 8]

	먼저, 새로 추가된 메모리 블록 위치의 인덱스를 위와 같이 계산함.
	이렇게 계산하면 새로 추가된 메모리 블록 위치에 접근할 수 있는 이유는,

	Buffer->Buffer 자체가 1byte 짜리 UCHAR* 타입의 배열이므로,
	해당 배열의 인덱싱도 결국 1byte 단위로 할 수 있음.

	따라서, Buffer->Buffer[n] 는 n * 16 bits 번째 이후에
	새로 추가된 1 byte (= 8 bits) 짜리 메모리 블록 영역을 가리키게 됨.

	어쨋든, 새로 추가된 8 bits 짜리 메모리 블록을
	0x00, 즉, '0000 0000' 로 초기화함.
*/

/*
	right shift 로 비트마스킹을 수행할 자릿수 결정


	Buffer->Buffer 메모리 블록에 새롭게 추가된 8 bits 내에서
	몇 번째 비트에 비트마스킹을 수행할 것인지 결정하기 위해
	비트마스크 변수를 right shift 처리함.

	ex> 기존 Buffer->Size 가 16 bits 였는데,
	Huffman_AddBit() 호출에 의해,
	realloc() 으로 Buffer->Buffer 의 최종 크기가 24 bits(16 + 8)까지 늘어나고,
	새로 늘어난 8 bits 중 첫 번째 비트가 비트마스킹된 후, Buffer->Size++ 로 증가되고 함수 종료된 상태라고 치자.

	이후 Huffman_AddBit() 추가 호출되면,
	Buffer->Size 가 17 bits 일 것이고,

	이 말은 곧,
	이전 Huffman_AddBit() 호출에서 realloc() 으로 재할당된 24 bits 중에서,
	비트마스킹에 의해 17 bits 까지 데이터(접두어 코드)가 기록되어 있는 상태라는 뜻임.

	그렇다면, realloc() 으로 추가된 8 bits 중에서
	두 번째 비트를 비트마스킹 해줘야 할 것임!

	그러려면, 비트마스크 변수 Mask 를
	right shift 연산을 통해 '0100 0000' 으로 만들어줘야 함.

	따라서, Buffer->Size * 8 = 17 % 8 = 1 이므로,
	'1000 0000' >> 1 = '0100 0000' 이 되겠지!

	참고로, >>= 는
	좌변의 비트마스크 변수 Mask 를 right shift 한 뒤,
	그 결과값을 Mask 에 대입시키는 연산자!
*/

/*
	허프만 트리 구축 함수인 Huffman_BuildPrefixTree() 에서 
	우선순위 큐를 사용하는 이유


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
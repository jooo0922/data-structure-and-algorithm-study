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
	int i = 0,
		j = 0;

	// 8 bits ASCII 코드의 개수(2^8 = 256개)만큼 SymbolInfo 정적 배열 테이블 선언
	SymbolInfo SymbolInfoTable[MAX_CHAR];

	// Huffman_BuildCodeTable() 함수로 접두어 코드 테이블 구축 시, 접두어 코드를 담는 임시 배열 선언
	UCHAR Temporary[MAX_BIT];

	// ASCII 코드 개수인 256 회만큼 반복 순회하며 ASCII 기호 및 빈도 초기화
	for (i = 0; i < MAX_CHAR; i++)
	{
		// SymbolInfo.Symbol 은 UCHAR 타입이므로, 정수형 i 를 할당하면 ASCII 문자로 자동 변환되어 저장
		SymbolInfoTable[i].Symbol = i;

		// 각 기호의 빈도를 우선 0으로 초기화
		SymbolInfoTable[i].Frequency = 0;
	}

	i = 0;

	// 종료문자 null('\0')을 만날 때까지 압축할 원본 문자열 순회
	while (Source[i] != '\0')
	{
		/*
			현재 순회중인 원본 문자열 상의 ASCII 기호(Source[i++])를
			SymbolInfo 테이블 상의 '인덱스'로 자동 변환하여,

			그것에 대응되는 기호 정보(SymbolInfoTable[Source[i++]])를 찾고,
			원본 문자열에서 같은 기호를 찾을 때마다, 빈도 수를 늘려나감.

			-> 이로써, SymbolInfoTable 는
			256 개의 8 bits ASCII 코드들의 목록과,
			각 ASCII 코드들이 원본 문자열 Source 에서 등장하는
			기호의 빈도를 저장한 테이블이 되었음!
		*/
		SymbolInfoTable[Source[i++]].Frequency++;
	}

	// SymbolInfoTable 넘겨줘서 허프만 트리 구축
	Huffman_BuildPrefixTree(Tree, SymbolInfoTable);

	// 원본 문자열을 접두어 코드로 압축 시, 각 기호의 접두어 코드를 참조하기 위한 접두어 코드 테이블 구축
	// (p.591 참고)
	Huffman_BuildCodeTable(*Tree, CodeTable, Temporary, 0);

	i = 0;

	// 종료문자 null('\0')을 만날 때까지 압축할 원본 문자열 다시 순회
	while (Source[i] != '\0')
	{
		// 현재 순회중인 문자(CodeTable[Source[i]])의 접두어 코드 길이를 저장
		int BitCount = CodeTable[Source[i]].Size;

		/*
			현재 순회중인 문자(CodeTable[Source[i]])의 접두어 코드 길이만큼 순회하며 
			압축 데이터 테이블(Encoded)에 비트 단위로 접두어 코드(.Code[j]) 기록 
		*/
		for (j = 0; j < BitCount; j++)
		{
			Huffman_AddBit(Encoded, CodeTable[Source[i]].Code[j]);
		}

		i++;
	}
}

// 압축 데이터 테이블(Encoded)을 허프만 코딩으로 데이터 압축 해제 (압축 해제된 문자열은 Decoded 에 기록)
void Huffman_Decode(HuffmanNode* Tree, BitBuffer* Encoded, UCHAR* Decoded)
{
	int i = 0;

	// 압축 해제 버퍼 테이블(= Decoded. p.592 빈 테이블 참고)을 순회할 인덱스값 초기화
	int Index = 0;

	// 구축된 허프만 트리의 최상위 노드 주소값을 현재 노드에 저장
	HuffmanNode* Current = Tree;

	// 압축 데이터 테이블(Encoded)를 순회 -> p.592 ~ 594 과정을 코드로 구현한 것!
	for (i = 0; i <= Encoded->Size; i++)
	{
		// 압축 데이터 테이블(Encoded)에서 비트 마스킹으로 접두어 코드를 읽을 때 사용할 비트마스크 변수
		// 비트 마스킹 관련 https://github.com/jooo0922/cpp-study/blob/main/TBCppStudy/Chapter3_9/Chapter3_9.cpp 참고
		UCHAR Mask = 0x80; // 1000 0000

		// 압축 데이터 테이블(Encoded)에서 접두어 코드를 읽으며 허프만 트리를 순회 시, '잎 노드'를 만났을 때의 처리
		if (Current->Left == NULL && Current->Right == NULL)
		{
			// 압축 해제 버퍼 테이블(Decoded)에 '잎 노드'에 저장된 기호를 저장함
			Decoded[Index++] = Current->Data.Symbol;

			// p.592 ~ 594 과정처럼, 압축 해제 버퍼에 기호를 추가하고 나면 뿌리 노드로 돌아감.
			Current = Tree;
		}

		// right shift 로 8 bits 접두어 코드 내에서 비트마스킹을 수행할 자릿수 결정 (관련 필기 하단 참고)
		Mask >>= i % 8;

		if ((Encoded->Buffer[i / 8] & Mask) != Mask)
		{
			/*
				압축 데이터 테이블(Encoded->Buffer) 상에서
				현재 순회 중인 8 bits 접두어 코드(Encoded->Buffer[i/8]) 와
				비트마스킹 변수 간의 Bitwise AND 연산을 수행했을 때,

				결과값이 현재 비트마스킹 변수와 불일치(!= Mask)한다면,
				현재 순회 중인 접두어 코드 상에서
				현재 비트마스킹 하고 있는 자릿 수에 0이 기록되어 있다는 뜻.

				즉, 압축 데이터 테이블(Encoded)에서 읽은 비트가 0이므로,
				왼쪽 자식 노드(Current->Left)로 이동함.
			*/
			/*
				참고로, Encoded->Buffer[i/8] 로 읽으면,
				
				i 가 0 ~ 7 일 때까지는 
				압축 데이터 테이블(Encoded->Buffer) 상에서 첫 8 bits 의 인덱스인 0으로 읽어서
				Encoded->Buffer[0] 으로 읽음.

				Encoded->Buffer 가 UCHAR* 타입의 정적 배열이므로,
				unsigned char 타입의 크기인 1byte(= 8bits) 단위로 비트들을 읽어올 것임!

				같은 원리로,
				i 가 8 ~ 15 일 때까지는
				압축 데이터 테이블 상에서 두 번째 8 bits 를 읽어오겠지!
			*/
			Current = Current->Left;
		}
		else
		{
			/*
				반대로, 결과값이 현재 비트마스킹 변수와 일치(== Mask)한다면,
				현재 순회 중인 접두어 코드 상에서
				현재 비트마스킹 하고 있는 자릿 수에 1이 기록되어 있다는 뜻.

				즉, 압축 데이터 테이블(Encoded)에서 읽은 비트가 1이므로,
				오른쪽 자식 노드(Current->Right)로 이동함.
			*/
			Current = Current->Right;
		}
	}

	/*
		압축 데이터 테이블(Encoded)를 모두 읽고 나서 반복문을 탈출하면, 
		압축 해제 버퍼 테이블(Decoded)의 마지막에 종료 문자를 추가하고 함수를 종료함.
	*/
	Decoded[Index] = '\0';
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
/*
	매개변수 정리

	- HuffmanNode** Tree : 구축된 허프만 트리
	- HuffmanCode CodeTable[MAX_CHAR] : 해당 함수에서 구축하려는 각 기호에 대한 접두어 코드 테이블
		-> 8 bits ASCII 코드 갯수(2^8 = 256개)만큼 테이블 정적 배열을 매개변수로 선언
	- UCHAR Code[MAX_BIT] : 허프만 트리를 순회하면서 누산해 갈 8 bits 까지 저장 가능한 접두어 코드 배열
	- int Size : 허프만 트리를 순회하면서 누산해 갈 접두어 코드의 길이
*/
void Huffman_BuildCodeTable(HuffmanNode* Tree, HuffmanCode CodeTable[MAX_CHAR], UCHAR Code[MAX_BIT], int Size)
{
	if (Tree == NULL)
	{
		// 비어있는 허프만 트리 노드를 마주쳤을 경우 함수 종료
		return;
	}

	if (Tree->Left != NULL)
	{
		// 현재 순회중인 노드에 왼쪽 자식노드가 존재한다면, 접두어 코드 배열에 0으로 저장
		// (p. 588 > 왼쪽 자식노드는 접두어 코드를 0으로 읽는댔지?)
		Code[Size] = 0;

		// 왼쪽 자식노드에 대해 재귀호출
		/*
			접두어 코드 배열인 Code 를 재귀호출 시 넘겨줄 경우,
			
			다른 재귀 호출에서 저장한 접두어 코드들까지 모두 담겨있는 
			접두어 코드 배열이 넘어가는 것으로 착각할 수 있음.
			(= 즉, 각 잎 노드까지 도달했을 때, 
			그 잎 노드에 저장된 기호와 무관한 접두어 코드들까지 
			Code 배열에 저장되어 있는 것으로 착각할 수 있다는 뜻!)

			그러나, 지금 접두어 코드 배열 Code 의 '주소값'을 넘겨주는 게 아니라,
			접두어 코드 배열 Code '자체'를 '매개변수에 복사해서' 넘겨주고 있음.

			이 말은 즉, 다른 재귀 호출에서 접두어 코드 배열 Code 에 값을 넣더라도,
			현재 재귀 호출에서 매개변수로 전달받은 Code 에는 아무런 영향을 주지 않는다는 뜻!

			-> 결국, Code 배열에는 각 재귀 호출이 '잎 노드를 만날 때 까지의 접두어 코드만'
			저장되어 있으니 걱정 안해도 됨!
		*/
		Huffman_BuildCodeTable(Tree->Left, CodeTable, Code, Size + 1);
	}

	if (Tree->Right != NULL)
	{
		// 현재 순회중인 노드에 오른쪽 자식노드가 존재한다면, 접두어 코드 배열에 1로 저장
		// (p. 588 > 오른쪽 자식노드는 접두어 코드를 0으로 읽는댔지?)
		Code[Size] = 1;

		// 오른쪽 자식노드에 대해 재귀호출
		Huffman_BuildCodeTable(Tree->Right, CodeTable, Code, Size + 1);
	}

	if (Tree->Left == NULL && Tree->Right == NULL)
	{
		/*
			현재 노드가 NULL 은 아니여서 이 if block 까지 도달했으나,
			두 자식노드가 모두 존재하지 않는다면? -> '잎 노드'라고 봐야겠지!

			허프만 트리를 순회하다가, 기호가 저장된 잎 노드를 발견하면,

			접두어 코드 테이블(CodeTable)에 
			해당 기호에 대한 접두어 코드(Code[MAX_BIT])와
			접두어 코드의 길이(Size)를 저장함.
		*/
		int i;

		for (i = 0; i < Size; i++)
		{
			/*
				현재까지 누산된 접두어 코드의 길이(Size)만큼
				현재까지 저장된 접두어 코드 배열인 Code 를 순회하며 CodeTable 에 저장함

				이때, 현재 잎 노드에 저장된 ASCII 코드(Tree->Data.Symbol)를
				정수형으로 자동변환하여 테이블의 index 로 삼을 수 있음!
			*/
			CodeTable[Tree->Data.Symbol].Code[i] = Code[i];
		}

		// 접두어 코드 테이블(CodeTable)에 저장된 접두어 코드의 '길이' 도 같이 저장함.
		CodeTable[Tree->Data.Symbol].Size = Size;
	}
}

// 압축 데이터 테이블 출력
void Huffman_PrintBinary(BitBuffer* Buffer)
{
	int i;

	// 압축 데이터 테이블(Buffer)를 순회
	for (i = 0; i < Buffer->Size; i++)
	{
		// 압축 데이터 테이블(Buffer)에서 비트 마스킹으로 접두어 코드를 읽을 때 사용할 비트마스크 변수
		UCHAR Mask = 0x80; // 1000 0000

		// right shift 로 8 bits 접두어 코드 내에서 비트마스킹을 수행할 자릿수 결정 (관련 필기 하단 참고)
		Mask >>= i % 8;

		/*
			압축 데이터 테이블(Buffer->Buffer) 상에서
			현재 순회 중인 8 bits 접두어 코드(Buffer->Buffer[i/8]) 와
			비트마스킹 변수 간의 Bitwise AND 연산을 수행했을 때,

			결과값이 현재 비트마스킹 변수와 일치(== Mask)한다면,
			현재 순회 중인 접두어 코드 상에서
			현재 비트마스킹 하고 있는 자릿 수에 1이 기록되어 있다는 뜻.

			즉, 압축 데이터 테이블(Encoded)에서 읽은 비트가 1 이면 1을 출력하고,
			0 이면 0을 출력하라는 뜻!
		*/
		printf("%d", (Buffer->Buffer[i / 8] & Mask) == Mask);
	}
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
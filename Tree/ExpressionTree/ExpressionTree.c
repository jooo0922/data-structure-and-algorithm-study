#include "ExpressionTree.h"

// 수식트리 노드 생성
ETNode* ET_CreateNode(ElementType NewData)
{
	// ETNode 구조체 크기 만큼의 힙 메모리 할당
	// malloc() 이 할당한 힙 메모리 주소값 반환 시, ETNode* 타입의 포인터 주소로 형변환하여 반환.
	ETNode* NewNode = (ETNode*)malloc(sizeof(ETNode));

	// 노드 구조체 각 멤버변수 초기화
	NewNode->Left = NULL;
	NewNode->Right = NULL;
	NewNode->Data = NewData;

	// 생성한 노드의 주소값(이 담긴 포인터 변수) 반환
	return NewNode;
}

// 수식트리 노드 메모리 해제
void ET_DestroyNode(ETNode* Node)
{
	free(Node); // 힙 메모리에 할당받은 메모리 반납
}

// 수식트리 뿌리노드 메모리 해제 > 수식트리 전체 메모리 해제
void ET_DestroyTree(ETNode* Node)
{
	// 수식트리 메모리 해제 시, 후위 순회로 노드를 방문하여 메모리를 반납해야 함.
	// why? 잎 노드부터 뿌리 노드 순으로 메모리를 제거해야 하는데, 
	// 이 순서에 가장 적합한 순회 방식이 '후위 순회'

	// 현재 순회중인 노드 포인터 NULL 체크
	if (Node == NULL)
	{
		return;
	}

	// 현재 노드 포인터 변수가 NULL 이 아니라면,
	// 후위 순회 순서로 (왼쪽 하위 트리 -> 오른쪽 하위 트리 -> 뿌리 노드)
	// 재귀적으로 함수를 호출하여 노드 메모리 반납

	// 왼쪽 하위 트리(노드) 메모리 반납 (재귀 호출)
	ET_DestroyTree(Node->Left);

	// 오른쪽 하위 트리(노드) 메모리 반납 (재귀 호출)
	ET_DestroyTree(Node->Right);

	// 뿌리 노드(현재 노드) 메모리 반납
	// 현재 노드에 대해서는 재귀 호출을 하지 않고 실제 메모리 반납 처리
	ET_DestroyNode(Node);
}

// 수식트리 전위순회 출력 > 전위표기식 출력
void ET_PreorderPrintTree(ETNode* Node)
{
	// 현재 순회중인 노드 포인터 NULL 체크
	if (Node == NULL)
	{
		// 현재 노드 포인터 변수에 주소값이 존재하지 않으면 순회를 종료함.
		return;
	}

	// 현재 노드 포인터 변수가 NULL 이 아니라면,
	// 전위 순회 순서로 (뿌리 노드 -> 왼쪽 하위 트리 -> 오른쪽 하위 트리)
	// 재귀적으로 함수를 호출하여 노드 데이터 출력
	// (이처럼, 트리구조를 순회할 때에는 재귀 호출이 자주 사용됨!)

	// 뿌리 노드(현재 노드) 출력
	printf(" %c", Node->Data);

	// 왼쪽 하위 트리(노드) 출력 (재귀 호출)
	ET_PreorderPrintTree(Node->Left);

	// 오른쪽 하위 트리(노드) 출력 (재귀 호출)
	ET_PreorderPrintTree(Node->Right);

}

// 수식트리 중위순회 출력 > 중위표기식 출력
void ET_InorderPrintTree(ETNode* Node)
{
	// 현재 순회중인 노드 포인터 NULL 체크
	if (Node == NULL)
	{
		// 현재 노드 포인터 변수에 주소값이 존재하지 않으면 순회를 종료함.
		return;
	}

	// 현재 노드 포인터 변수가 NULL 이 아니라면,
	// 중위 순회 순서로 (왼쪽 하위 트리 -> 뿌리 노드 -> 오른쪽 하위 트리)
	// 재귀적으로 함수를 호출하여 노드 데이터 출력

	// 중위표기식은 하나의 트리 단위를 중괄호로 묶어서 표현하므로,
	// 트리 출력 시작 전, 여는 중괄호를 먼저 출력하고,
	// 트리 출력 종료 후, 닫는 중괄호를 마지막으로 출력함.

	// 왼쪽 하위 트리(노드) 출력 (재귀 호출)
	printf("("); 
	ET_InorderPrintTree(Node->Left);

	// 뿌리 노드(현재 노드) 출력
	printf("%c", Node->Data);

	// 오른쪽 하위 트리(노드) 출력 (재귀 호출)
	ET_InorderPrintTree(Node->Right);
	printf(")");
}

// 수식트리 후위순회 출력 > 후위표기식 출력
void ET_PostorderPrintTree(ETNode* Node)
{
	// 현재 순회중인 노드 포인터 NULL 체크
	if (Node == NULL)
	{
		// 현재 노드 포인터 변수에 주소값이 존재하지 않으면 순회를 종료함.
		return;
	}

	// 현재 노드 포인터 변수가 NULL 이 아니라면,
	// 후위 순회 순서로 (왼쪽 하위 트리 -> 오른쪽 하위 트리 -> 뿌리 노드)
	// 재귀적으로 함수를 호출하여 노드 데이터 출력

	// 왼쪽 하위 트리(노드) 출력 (재귀 호출)
	ET_PostorderPrintTree(Node->Left);

	// 오른쪽 하위 트리(노드) 출력 (재귀 호출)
	ET_PostorderPrintTree(Node->Right);

	// 뿌리 노드(현재 노드) 출력
	printf(" %c", Node->Data);
}

// 수식트리 구축
/*
	매개변수 Node 는 
	외부에서 전달된 포인터 변수가 저장된 
	메모리 공간의 주소값 (= 이중 포인터)을 인자로 받도록 함으로써,

	외부 포인터 변수의 주소값을 수정하는 등,
	외부에서 전달된 변수의 값을 직접 수정할 수 있도록 함!
*/
void ET_BuildExpressionTree(char* PostfixExpression, ETNode** Node)
{
	int len = strlen(PostfixExpression); // 현재 후위표기식 문자열 길이 반환
	char Token = PostfixExpression[len - 1]; // 현재 후위표기식의 맨 마지막 토큰 읽어오기
	
	/*
		현재 후위표기식의 맨 마지막 문자를 '종료문자' 로 교체

		-> 후위표기식 문자열을 -1씩 줄여나가면서
		재귀 호출 시 전달함!

		-> 이는 피연산자가 한 자릿수로만 구성된 토큰(ex> '1', '2', '3')
		인 경우에만 유효한 방식!

		만약에 두 자릿수 피연산자 토큰(ex> '11', '22')인 경우에는
		이 방식으로는 피연산자 토큰을 제대로 읽어오지 못할 것임.
	*/
	PostfixExpression[len - 1] = '\0';

	switch (Token)
	{
		// 토큰이 연산자인 경우
		case '+': case '-': case '*': case '/':
			(*Node) = ET_CreateNode(Token); // 읽어들인 토큰으로 노드 생성
			
			// 연산자 노드는 자식노드로 2개의 피연산자 노드를 필요로 하므로,
			// 왼쪽과 오른쪽 자식 포인터 각각에 대해 재귀 호출하여 자식노드 생성 
			ET_BuildExpressionTree(PostfixExpression, &(*Node)->Right);
			ET_BuildExpressionTree(PostfixExpression, &(*Node)->Left);
			break;

		// 토큰이 피연산자인 경우
		default:
			// 수식트리에서 피연산자는 잎 노드이므로, 자식노드를 재귀호출하여 생성할 필요 x
			(*Node) = ET_CreateNode(Token); // 읽어들인 토큰으로 노드 생성
			break;
	}
}

// 수식트리 계산
double ET_Evaluate(ETNode* Tree)
{
	// 피연산지 토큰을 임시로 저장해 둘 문자열 배열 선언
	// (한 자릿수 피연산자 토큰 + 종료문자 '\0' = 2개 길이의 문자열)
	char Temp[2]; 

	// 왼쪽 하위트리와 오른쪽 하위트리 계산 결과 저장할 변수 초기화
	double Left = 0;
	double Right = 0;

	// 양쪽 하위트리 계산결과 합산 또는 문자열에서 실수형으로 변환된 피연산자 토큰 저장할 변수 초기화
	double Result = 0;

	// 매개변수로 들어온 노드 NULL 체크
	if (Tree == NULL)
	{
		return 0;
	}

	switch (Tree->Data)
	{
		// 토큰이 연산자인 경우
		case '+': case '-': case '*': case '/':
			// 연산자 노드의 각 하위 트리 계산결과를 얻기 위해 양쪽 하위 노드에 대해 재귀호출
			Left = ET_Evaluate(Tree->Left);
			Right = ET_Evaluate(Tree->Right);

			// 양쪽 하위트리 계산 결과를 연산자 토큰 타입에 따라 합산
			if (Tree->Data == '+') Result = Left + Right;
			else if (Tree->Data == '-') Result = Left - Right;
			else if (Tree->Data == '*') Result = Left * Right;
			else if (Tree->Data == '/') Result = Left / Right;

			break;

		// 토큰이 피연산자인 경우
		default:
			// 피연산자 토큰을 임시로 저장할 문자열 메모리 공간 Temp 를 종료문자 '\0'로 초기화
			memset(Temp, 0, sizeof(Temp));

			// 문자열의 첫번째 메모리 공간을 피연산자 토큰 문자로 덮어씀
			Temp[0] = Tree->Data;

			// atof() : 'ascii to float' 의 줄임말. 문자열을 부동 소수점 실수형으로 변환.
			Result = atof(Temp);
			break;
	}

	// 양쪽 하위트리 계산결과 합산 또는 문자열에서 실수형으로 변환된 피연산자 토큰 반환
	return Result;
}
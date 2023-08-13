#include "LinkedListStack.h"

int main()
{
	int i = 0; // for 문 돌릴 때 사용할 인덱스 변수 초기화
	int Count = 0; // for 문 반복 순회 횟수 (스택의 노드 개수) 변수 선언 및 초기화

	Node* Popped; // 제거된 노드를 반환받아 저장할 변수 초기화

	LinkedListStack* Stack; // 링크드리스트 기반 스택 포인터 변수 선언

	// 스택 생성
	LLS_CreateStack(&Stack); // 외부 포인터 변수 LinkedListStack 에 저장되도록 포인터 변수의 주소값 전달

	// 스택에 노드 4개 순서대로 생성 및 삽입
	LLS_Push(Stack, LLS_CreateNode("abc"));
	LLS_Push(Stack, LLS_CreateNode("def"));
	LLS_Push(Stack, LLS_CreateNode("efg"));
	LLS_Push(Stack, LLS_CreateNode("hij"));

	Count = LLS_GetSize(Stack); // 스택 노드 개수 반환

	// 스택의 노드 개수 및 최상위 노드 데이터에 저장된 문자열 출력
	// 참고로, %s 변환문자는 char* 타입의 문자열 데이터 주소값을 받아서,
	// 해당 주소값이 가리키는 메모리에서 종료문자 '\o'가 나올때까지 문자열을 계속 출력함!
	printf("Size: %d, Top: %s\n\n",
		Count, LLS_Top(Stack)->Data);

	// 스택의 노드 개수만큼 반복 순회
	for (i = 0; i < Count; i++)
	{
		if (LLS_IsEmpty(Stack))
		{
			break; // 스택이 비게 되면 반복문 종료
		}

		Popped = LLS_Pop(Stack); // 스택의 최상위 노드 제거 후 반환

		printf("Popped: %s, ", Popped->Data); // 제거된 최상위 노드의 문자열 데이터 출력

		LLS_DestroyNode(Popped); // 제거된 최상위 노드 메모리 해제

		if (!LLS_IsEmpty(Stack))
		{
			// 아직 스택이 비어있지 않다면, 스택의 현재 최상위 노드의 문자열 데이터 출력
			printf("Current Top: %s\n", LLS_Top(Stack)->Data);
		}
		else
		{
			// 스택이 비어있다면 비었다고 출력
			printf("Stack is Empty.\n");
		}
	}

	// 반복문을 돌고 나면 스택이 비게 되므로,
	// 반복문 종료 후, 비어있는 스택의 메모리 해제
	LLS_DestroyStack(Stack);

	return 0;
}
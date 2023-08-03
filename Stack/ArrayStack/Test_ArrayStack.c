#include "ArrayStack.h"

int main()
{
	int i = 0; // for 문 돌릴 때 사용할 인덱스 변수 초기화
	ArrayStack* Stack = NULL; // 배열 기반 스택 포인터 변수 초기화

	// 스택 생성 (초기 생성 시, 최대 용량 10개로 지정)
	AS_CreateStack(&Stack, 10); // 외부 포인터 변수에 생성된 ArrayStack 이 저장되도록 포인터 변수의 주소값 전달

	// 스택에 노드 4개 순서대로 삽입
	AS_Push(Stack, 3);
	AS_Push(Stack, 37);
	AS_Push(Stack, 11);
	AS_Push(Stack, 12);

	// 스택 초기 생성 시 지정된 최대 용량, 현재 스택 크기, 최상위 스택 출력 
	printf("Capacity: %d, Size: %d, Top: %d\n\n",
		Stack->Capacity, AS_GetSize(Stack), AS_Top(Stack));

	// 스택에 초기에 삽입된 노드 개수만큼 반복 순회
	for ( i = 0; i < 4; i++)
	{
		// 스택이 비어있다면 반복문 중단
		if (AS_IsEmpty(Stack))
			break;

		// 스택 최상위 노드부터 하나씩 제거 (후입선출) 및 제거된 노드 데이터 출력
		printf("Popped: %d, ", AS_Pop(Stack));

		if (!AS_IsEmpty(Stack))
		{
			// 스택이 비어있지 않다면, 현재 최상위 노드 출력
			printf("Current Top: %d\n", AS_Top(Stack));
		}
		else
		{
			printf("Stack Is Empty.\n");
		}
	}

	// 스택 및 노드 메모리 해제
	AS_DestroyStack(Stack);

	return 0;
}

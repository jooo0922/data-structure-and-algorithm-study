#ifndef LINKEDLISTSTACK_H
#define LINKEDLISTSTACK_H
/*
	여기서 사용된 #ifndef ~ #endif 전처리기는
	헤더파일인 ArrayStack.h 의 헤더가드를 처리해주는 방법 중 하나였지?

	cpp-study > TBCppStudy > Chapter1_12 > add.h 필기 참고!
*/

#include <stdio.h> // printf(), scanf() 같은 입출력 함수 선언이 포함된 헤더파일
#include <string.h> // strlen(), strcpy() 같은 문자열을 다루는 함수 선언이 포함된 헤더파일
#include <stdlib.h> // malloc(), free() 같은 메모리 할당 함수 선언이 포함된 헤더파일
// -> 헤더파일에 포함되어 있어야, 이를 가져다 쓰는 .c 파일들에서 사용할 때 에러가 안남.

// 링크드리스트 스택에 추가될 단일 노드 구조체 선언
typedef struct tagNode
{
	// 노드에 들어갈 데이터 
	// 이번에는 문자'열' 데이터를 사용할 것이므로, 
	// 기본 자료형 리터럴을 바로 멤버변수의 값으로 할당할 수 없음! 
	// 즉, char 타입을 배열 형태로 저장해야 되므로, 
	// 해당 문자열이 저장된 자유 저장소의 주소값을 관리하는, 
	// 즉, 포인터 멤버변수로 관리해야 함!
	char* Data; 
	struct tagNode* NextNode; // 다음 노드(자신의 '위'에 쌓인 노드)를 가리키는 포인터 멤버변수
} Node;

// 링크드리스트 기반 스택 구조체 선언
typedef struct tagLinkedListStack
{
	Node* List; // 리스트 헤드 (스택의 맨 첫 번째 노드)
	Node* Top; // 리스트 테일 (스택의 최상위 노드(맨 마지막 노드))
} LinkedListStack;

// 함수 원형 선언
void LLS_CreateStack(LinkedListStack** Stack); // 링크드리스트 기반 스택 생성
void LLS_DestroyStack(LinkedListStack* Stack); // 스택 파괴 (메모리 해제)

Node* LLS_CreateNode(char* Data); // 스택의 노드 생성
void LLS_DestroyNode(Node* _Node); // 스택의 노드 파괴 (메모리 해제)

void LLS_Push(LinkedListStack* Stack, Node* NewNode); // 스택에 노드 삽입 (최상위 노드 추가)
Node* LLS_Pop(LinkedListStack* Stack); // 스택에서 노드 제거 (최상위 노드 제거)

Node* LLS_Top(LinkedListStack* Stack); // 스택의 현재 최상위 노드 데이터 반환
int LLS_GetSize(LinkedListStack* Stack); // 스택의 크기 반환
int LLS_IsEmpty(LinkedListStack* Stack); // 스택이 비어있는지 여부 반환

#endif // !LINKEDLISTSTACK_H

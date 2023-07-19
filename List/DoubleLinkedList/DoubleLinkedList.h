#ifndef  DOUBLE_LINKEDLIST_H
#define DOUBLE_LINKEDLIST_H

/*
	헤더파일 중복 include 에 대한 헤더가드를 처리해주는 방법 중 하나였지?
	cpp-study > TBCppStudy > Chapter1_12 > add.h 필기 참고!
*/

#include <stdio.h> // printf(), scanf() 같은 입출력 함수 선언이 포함된 헤더파일
#include <stdlib.h> // malloc(), free() 같은 메모리 할당 함수 선언이 포함된 헤더파일
// -> 헤더파일에 포함되어 있어야, 이를 가져다 쓰는 .c 파일에서 malloc() 등 사용할 때 에러가 안남.

// 노드에 들어갈 데이터 타입. 여기서는 정수형으로 임의로 정함.
typedef int ElementType;

// 노드 구조체 선언 (struct 키워드 생략하고 사용하기 위해 typedef 로 구조체 별칭 선언)
typedef struct tagNode
{
	ElementType Data; // 노드에 들어갈 데이터
	struct tagNode* PrevNode; // 링크드리스트 상에서 이전 노드 구조체를 가리키는 포인터 멤버변수
	struct tagNode* NextNode; // 링크드리스트 상에서 다음 노드 구조체를 가리키는 포인터 멤버변수
} Node;

// 함수 원형 선언
Node* DLL_CreateNode(ElementType NewData); // 최초 노드(헤드노드) 생성
void DLL_DestroyNode(Node* Node); // 노드 파괴(메모리 해제)
void DLL_AppendNode(Node** Head, Node* NewNode); // 노드 추가 (테일노드에 추가)
void DLL_InsertAfter(Node* Current, Node* NewNode); // 노드 삽입
void DLL_RemoveNode(Node** Head, Node* Remove); // 링크드리스트에서 노드 제거
Node* DLL_GetNodeAt(Node* Head, int Location); // 노드 탐색
int DLL_GetNodeCount(Node* Head); // 노드 개수 세기

#endif // ! DOUBLE_LINKEDLIST_H

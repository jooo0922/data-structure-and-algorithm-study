#ifndef LINKEDLIST_H
#define LINKEDLIST_H

/*
	여기서 사용된 #ifndef ~ #endif 전처리기는
	헤더파일인 LinkedList.h 의 헤더가드를 처리해주는 방법 중 하나였지?

	cpp-study > TBCppStudy > Chapter1_12 > add.h 필기 참고!
*/

#include <stdio.h> // printf(), scanf() 같은 입출력 함수 선언이 포함된 헤더파일
#include <stdlib.h> // malloc(), free() 같은 메모리 할당 함수 선언이 포함된 헤더파일
// -> LinkedList.h 헤더파일에 포함되어 있어야, 이를 가져다 쓰는 LinkedList.c 파일에서 malloc() 등 사용할 때 에러가 안남.

#include "Graph.h"

// 노드에 들어갈 데이터 타입. 여기서는 정수형으로 임의로 정함.
typedef Vertex* ElementType;

// 노드 구조체 선언 (struct 키워드 생략하고 사용하기 위해 typedef 로 구조체 별칭 선언)
typedef struct tagNode
{
	ElementType Data; // 노드에 들어갈 데이터
	struct tagNode* NextNode; // 링크드리스트 상에서 다음 노드 구조체를 가리키는 포인터 멤버변수
} Node;

// 함수 원형 선언
Node* SLL_CreateNode(ElementType NewData); // 최초 노드(헤드노드) 생성
void SLL_DestroyNode(Node* Node); // 노드 파괴(메모리 해제)
void SLL_DestroyAllNodes(Node** List); // 전체 노드 파괴
void SLL_AppendNode(Node** Head, Node* NewNode); // 노드 추가 (테일노드에 추가)
void SLL_InsertAfter(Node* Current, Node* NewNode); // 노드 삽입
void SLL_InsertBefore(Node** Head, Node* Current, Node* NewNode); // 노드 삽입 (특정 노드 앞에 삽입)
void SLL_InsertNewHead(Node** Head, Node* NewHead); // 새로운 헤드노드 삽입
void SLL_RemoveNode(Node** Head, Node* Remove); // 링크드리스트에서 노드 제거
Node* SLL_GetNodeAt(Node* Head, int Location); // 노드 탐색
int SLL_GetNodeCount(Node* Head); // 노드 개수 세기

#endif // !LINKEDLIST_H

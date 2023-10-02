#ifndef BINARY_TREE_H
#define BINARY_TREE_H
/*
	여기서 사용된 #ifndef ~ #endif 전처리기는
	헤더파일인 BinaryTree.h 의 헤더가드를 처리해주는 방법 중 하나였지?

	cpp-study > TBCppStudy > Chapter1_12 > add.h 필기 참고!
*/

#include <stdio.h> // printf(), scanf() 같은 입출력 함수 선언이 포함된 헤더파일
#include <stdlib.h> // malloc(), free() 같은 메모리 할당 함수 선언이 포함된 헤더파일
// -> 헤더파일에 포함되어 있어야, 이를 가져다 쓰는 .c 파일들에서 사용할 때 에러가 안남.

// 노드에 들어갈 char(문자) 데이터 타입을 별칭으로 선언 > 알파벳 데이터만 담을 예정
typedef char ElementType;

// 이진트리에 추가될 단일 노드 구조체 타입을 별칭으로 선언
typedef struct tagSBTNode
{
	struct tagSBTNode* Left; // 왼쪽 자식 노드 포인터 멤버
	struct tagSBTNode* Right; // 오른쪽 자식 노드 포인터 멤버

	ElementType Data; // 노드 데이터 멤버
} SBTNode;

// 함수 원형 선언
SBTNode* SBT_CreateNode(ElementType NewData); // 이진트리 노드 생성
void SBT_DestroyNode(SBTNode* Node); // 이진트리 노드 메모리 해제
void SBT_DestroyTree(SBTNode* Root); // 이진트리 뿌리노드 메모리 해제 > 이진트리 전체 메모리 해제

void SBT_PreorderPrintTree(SBTNode* Node); // 이진트리 전위순회 출력
void SBT_InorderPrintTree(SBTNode* Node); // 이진트리 중위순회 출력
void SBT_PostorderPrintTree(SBTNode* Node); // 이진트리 후위순회 출력

#endif // !BINARY_TREE_H

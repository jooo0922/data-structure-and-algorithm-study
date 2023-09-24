#ifndef LCRS_TREE_H
#define LCRS_TREE_H
/*
	여기서 사용된 #ifndef ~ #endif 전처리기는
	헤더파일인 LCTSTree.h 의 헤더가드를 처리해주는 방법 중 하나였지?

	cpp-study > TBCppStudy > Chapter1_12 > add.h 필기 참고!
*/

#include <stdio.h> // printf(), scanf() 같은 입출력 함수 선언이 포함된 헤더파일
#include <stdlib.h> // malloc(), free() 같은 메모리 할당 함수 선언이 포함된 헤더파일
// -> 헤더파일에 포함되어 있어야, 이를 가져다 쓰는 .c 파일들에서 사용할 때 에러가 안남.

// 노드에 들어갈 char(문자) 데이터 타입을 별칭으로 선언
typedef char ElementType;

// LCTS 트리에 추가될 단일 노드 구조체 타입을 별칭으로 선언
typedef struct tagLCRSNode
{
	struct tagLCRSNode* LeftChild; // 왼쪽 자식 노드 포인터 멤버
	struct tagLCRSNode* RightSibling; // 오른쪽 형제 노드 포인터 멤버

	ElementType Data; // 노드 데이터 멤버
} LCRSNode;

// 함수 원형 선언
LCRSNode* LCRS_CreateNode(ElementType NewData); // LCRS 트리 노드 생성
void LCRS_DestroyNode(LCRSNode* Node); // LCRS 트리 노드 메모리 해제
void LCRS_DestroyTree(LCRSNode* Root); // LCRS 트리의 뿌리노드 메모리 해제 > 전체 트리 노드 메모리 해제와 같음

void LCRS_AddChildNode(LCRSNode* ParentNode, LCRSNode* ChildNode); // LCRS 트리의 특정 노드에 자식 노드 추가
void LCRS_PrintTree(LCRSNode* Node, int Depth); // LCRS 트리 출력

#endif // !LCRS_TREE_H

#ifndef REDBLACKTREE_H
#define REDBLACKTREE_H
/*
	여기서 사용된 #ifndef ~ #endif 전처리기는
	헤더파일의 헤더가드를 처리해주는 방법 중 하나였지?

	cpp-study > TBCppStudy > Chapter1_12 > add.h 필기 참고!
*/

#include <stdio.h> // printf(), scanf() 같은 입출력 함수 선언이 포함된 헤더파일
#include <stdlib.h> // malloc(), free() 같은 메모리 할당 함수 선언이 포함된 헤더파일
// -> 헤더파일에 포함되어 있어야, 이를 가져다 쓰는 .c 파일들에서 사용할 때 에러가 안남.

// 노드에 들어갈 정수형 데이터 타입을 별칭으로 선언
typedef int ElementType;

// 레드블랙트리에 추가될 단일 노드 구조체 타입을 별칭으로 선언
typedef struct tagRBTNode
{
	struct tagRBTNode* Parent; // 부모 노드 포인터 멤버
	struct tagRBTNode* Left; // 왼쪽 자식 노드 포인터 멤버 (현재 노드보다 더 작음)
	struct tagRBTNode* Right; // 오른쪽 자식 노드 포인터 멤버 (현재 노드보다 더 큼)

	enum { RED, BLACK } Color; // 노드 색상 멤버 (빨간색 / 검은색 여부)

	ElementType Data; // 노드 데이터 멤버
} RBTNode;

#endif // !REDBLACKTREE_H

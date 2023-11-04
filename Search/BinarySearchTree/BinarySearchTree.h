#ifndef BINARY_SEARCH_TREE_H
#define BINARY_SEARCH_TREE_H
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

// 이진탐색트리에 추가될 단일 노드 구조체 타입을 별칭으로 선언
typedef struct tagBSTNode
{
	struct tagBSTNode* Left; // 왼쪽 자식 노드 포인터 멤버 (현재 노드보다 더 작음)
	struct tagBSTNode* Right; // 오른쪽 자식 노드 포인터 멤버 (현재 노드보다 더 큼)

	ElementType Data; // 노드 데이터 멤버
} BSTNode;

BSTNode* BST_CreateNode(ElementType NewData); // 이진탐색트리 노드 생성
void BST_DestroyNode(BSTNode* Node); // 이진탐색트리 노드 메모리 해제
void BST_DestroyTree(BSTNode* Tree); // 이진탐색트리 전체 메모리 해제

BSTNode* BST_SearchNode(BSTNode* Tree, ElementType Target); // 이진탐색트리 노드 탐색
BSTNode* BST_SearchMinNode(BSTNode* Tree); // 주어진 하위트리 내의 최솟값 노드 탐색
void BST_InsertNode(BSTNode* Tree, BSTNode* Child); // 이진탐색트리 노드 삽입
BSTNode* BST_RemoveNode(BSTNode* Tree, BSTNode* Parent, ElementType Target); // 이진탐색트리 노드 제거
void BST_InorderPrintTree(BSTNode* Node); // 이진탐색트리 중위순회 출력

#endif // !BINARY_SEARCH_TREE_H


#ifndef EXPRESSION_TREE_H
#define EXPRESSION_TREE_H
/*
	여기서 사용된 #ifndef ~ #endif 전처리기는
	헤더파일인 ExpressionTree.h 의 헤더가드를 처리해주는 방법 중 하나였지?

	cpp-study > TBCppStudy > Chapter1_12 > add.h 필기 참고!
*/

#include <stdio.h> // printf(), scanf() 같은 입출력 함수 선언이 포함된 헤더파일
#include <stdlib.h> // malloc(), free(). atof() 같은 함수 선언이 포함된 헤더파일
#include <string.h> // memset() 같은 연속된 메모리 블록 조작 함수 사용을 위해 포함
// -> 헤더파일에 포함되어 있어야, 이를 가져다 쓰는 .c 파일들에서 사용할 때 에러가 안남.

// 노드에 들어갈 char(문자) 데이터 타입을 별칭으로 선언 > 알파벳 데이터만 담을 예정
typedef char ElementType;

// 수식트리에 추가될 단일 노드 구조체 타입을 별칭으로 선언 (이진트리 노드 구조체와 동일)
typedef struct tagETNode
{
	struct tagETNode* Left; // 왼쪽 자식 노드 포인터 멤버
	struct tagETNode* Right; // 오른쪽 자식 노드 포인터 멤버

	ElementType Data; // 노드 데이터 멤버
} ETNode;

// 함수 원형 선언 (이진트리 함수 원형과 거의 동일)
ETNode* ET_CreateNode(ElementType NewData); // 수식트리 노드 생성
void ET_DestroyNode(ETNode* Node); // 수식트리 노드 메모리 해제
void ET_DestroyTree(ETNode* Root); // 수식트리 뿌리노드 메모리 해제 > 수식트리 전체 메모리 해제

void ET_PreorderPrintTree(ETNode* Node); // 수식트리 전위순회 출력 > 전위표기식 출력
void ET_InorderPrintTree(ETNode* Node); // 수식트리 중위순회 출력 > 중위표기식 출력
void ET_PostorderPrintTree(ETNode* Node); // 수식트리 후위순회 출력 > 후위표기식 출력
void ET_BuildExpressionTree(char* PostfixExpression, ETNode** Node); // 수식트리 구축
double ET_Evaluate(ETNode* Tree); // 수식트리 계산

#endif // !EXPRESSION_TREE_H

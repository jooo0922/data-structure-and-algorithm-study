#include "RedBlackTree.h"
#include <string.h> // 문자열 관련 함수 사용을 위해 포함

// 테스트 파일에 선언된 동일한 전역 Nil 노드 사용을 위해 extern 키워드로 선언
/*
	extern

	c언어에서 extern 키워드는
	변수나 함수가 다른 소스 파일에서 선언되었음을 나타냄. 
	
	이 키워드를 선언하면 컴파일러에게 해당 변수나 함수가 
	이미 다른 곳에서 정의되었으며, 
	
	링크 단계에서는 
	이를 찾아서 연결해야 한다는 것을 알려줌.
*/
extern RBTNode* Nil;

// 레드블랙트리 노드 생성
RBTNode* RBT_CreateNode(ElementType NewData)
{
	// RBTNode 구조체 크기 만큼의 힙 메모리 할당
	// malloc() 이 할당한 힙 메모리 주소값 반환 시, RBTNode* 타입의 포인터 주소로 형변환하여 반환.
	RBTNode* NewNode = (RBTNode*)malloc(sizeof(RBTNode));

	// 노드 구조체 각 멤버변수 초기화
	NewNode->Parent = NULL;
	NewNode->Left = NULL;
	NewNode->Right = NULL;
	NewNode->Data = NewData;

	// 기본값은 검은색 노드로 초기화
	NewNode->Color = BLACK;

	// 생성한 노드의 주소값(이 담긴 포인터 변수) 반환
	return NewNode;
}


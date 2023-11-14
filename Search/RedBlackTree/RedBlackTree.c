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

// 레드블랙트리 노드 메모리 해제
void RBT_DestroyNode(RBTNode* Node)
{
	free(Node);
}

// 레드블랙트리 전체 메모리 해제
void RBT_DestroyTree(RBTNode* Tree)
{
	if (Tree->Right != Nil)
	{
		// 오른쪽 하위트리가 전역 더미노드가 아니라면, 재귀적으로 순회하여 하위 노드(잎 노드) 먼저 메모리 해제
		RBT_DestroyTree(Tree->Right);
	}

	if (Tree->Left != Nil)
	{
		// 왼쪽 하위트리가 전역 더미노드가 아니라면, 재귀적으로 순회하여 하위 노드(잎 노드) 먼저 메모리 해제
		RBT_DestroyTree(Tree->Left);
	}

	// 위에서 자식노드 메모리를 모두 해제했다면, 자식 노드 포인터들이 전역 더미노드를 가리키도록 초기화
	// 왜냐하면, 자식노드 모두 메모리 반납했다면, 현재 Tree 노드가 '(사실상) 잎 노드'에 해당하므로,
	// 레드블랙트리의 '(사실상) 잎 노드' 하위에는 양쪽에 더미노드를 연결해서 3번 규칙을 지키기 위함!
	Tree->Left = Nil;
	Tree->Right = Nil;

	// 현재 노드 메모리 해제
	RBT_DestroyNode(Tree);
}

// 레드블랙트리 노드 탐색
RBTNode* RBT_SearchNode(RBTNode* Tree, ElementType Target)
{
	if (Tree == Nil)
	{
		// 현재 노드가 전역 더미노드일 경우, NULL 반환
		// (전역 더미노드는 3번 규칙을 유지하기 위한 형식적인 노드에 불과)
		return NULL;
	}

	if (Tree->Data > Target)
	{
		// 현재 순회중인 노드보다 목표 노드가 더 작을 경우,
		// 현재 노드의 왼쪽 하위 트리를 재귀적으로 다시 탐색함
		return RBT_SearchNode(Tree->Left, Target);
	}
	else if (Tree->Data < Target)
	{
		// 현재 순회중인 노드보다 목표 노드가 더 클 경우,
		// 현재 노드의 오른쪽 하위 트리를 재귀적으로 다시 탐색함
		return RBT_SearchNode(Tree->Right, Target);
	} 
	else
	{
		// 현재 순회중인 노드가 목표 노드와 같은 경우,
		// 현재 노드 주소값을 그대로 반환
		return Tree;
	}
}

// 주어진 하위트리 내의 최솟값 노드 탐색
RBTNode* RBT_SearchMinNode(RBTNode* Tree)
{
	if (Tree == Nil)
	{
		// 현재 노드가 전역 더미노드일 경우, 더미노드 주소값 반환
		return Nil;
	}

	/*
		레드블랙트리(= 이진탐색트리) 상에서는
		현재 노드보다 작은 노드를
		항상 왼쪽 하위 트리에 둔다는 것을 명심!
	*/

	if (Tree->Left == Nil)
	{
		// 현재 노드의 왼쪽 하위트리가 더미노드 뿐이라면,
		// 현재 하위트리(=현재 노드)상에서 더 작은 노드는 존재하지 않는다는 의미이므로,
		// 현재 노드를 최솟값 노드로 반환함
		return Tree;
	}
	else
	{
		// 현재 노드의 왼쪽 하위트리가 존재할 경우,
		// 현재 하위트리 상에서 더 작은 노드가 존재한다는 의미이므로,
		// 현재 노드의 왼쪽 자식노드를 전달해서 재귀적으로 최솟값 노드를 재탐색함.
		return RBT_SearchMinNode(Tree->Left);
	}
}

// 레드블랙트리 노드 삽입
void RBT_InsertNode(RBTNode** Tree, RBTNode* NewNode)
{
	// 이진탐색트리 노드 삽입 수행
	RBT_InsertNodeHelper(Tree, NewNode);

	// 삽입할 새 노드를 빨간색으로 칠하고, 양쪽 자식에 더미노드 연결
	NewNode->Color = RED;
	NewNode->Left = Nil;
	NewNode->Right = Nil;

	// 레드블랙트리 노드 삽입 후 뒷처리
	RBT_RebuildAfterInsert(Tree, NewNode);
}

// 이진탐색트리 노드 삽입과 거의 유사한 코드를 별도 함수로 추출
void RBT_InsertNodeHelper(RBTNode** Tree, RBTNode* NewNode)
{
	if ((*Tree) == NULL)
	{
		// 트리 이중 포인터를 de-referencing 했을 때,  
		// 뿌리노드 주소값(RBTNode*)이 비어있을 경우, 삽입할 노드의 주소값을 뿌리노드 주소값으로 할당.
		// -> 비어있는 트리의 뿌리노드로 삽입할 노드를 추가한 것!
		(*Tree) = NewNode;
	}

	if ((*Tree)->Data < NewNode->Data)
	{
		// 현재 노드보다 삽입할 노드가 더 클 경우, 오른쪽 하위트리에서 삽입 위치 탐색

		if ((*Tree)->Right == Nil)
		{
			// 현재 노드의 오른쪽 하위트리에 더미노드 뿐이라면, 삽입할 노드를 오른쪽 하위트리에 추가함
			(*Tree)->Right = NewNode;

			// 레드블랙트리 노드(RBTNode)는 부모노드 포인터도 존재하므로, 현재 노드의 주소값으로 채워줄 것.
			NewNode->Parent = (*Tree);
		}
		else
		{
			// 현재 노드의 오른쪽 하위트리가 존재할 경우, 재귀적으로 오른쪽 하위트리 재탐색
			/*
				참고로, &(*Tree)->Right 는

				현재노드(*Tree) 의 오른쪽 자식노드(Right)가 저장된 메모리의 주소값이
				담긴 또 다른 메모리의 주소값(&)을 앰퍼샌드 연산자로 전달하려는 것임.

				즉, &((*Tree)->Right) 이렇게 표현하면 더 이해가 쉬울 것임!

				RBT_InsertNodeHelper() 함수가 첫 번째 인자를 이중 포인터로 받기 때문에,
				재귀함수를 호출할 때에도 항상 이중 포인터로 전달해줘야 함!
			*/
			RBT_InsertNodeHelper(&(*Tree)->Right, NewNode);
		}
	}
	else if ((*Tree)->Data > NewNode->Data)
	{
		// 현재 노드보다 삽입할 노드가 더 작은 경우, 왼쪽 하위트리에서 삽입 위치 탐색

		if ((*Tree)->Left == Nil)
		{
			// 현재 노드의 왼쪽 하위트리가 더미노드 뿐이라면, 삽입할 노드를 왼쪽 하위트리에 추가함
			(*Tree)->Left = NewNode;

			// 레드블랙트리 노드(RBTNode)는 부모노드 포인터도 존재하므로, 현재 노드의 주소값으로 채워줄 것.
			NewNode->Parent = (*Tree);
		}
		else
		{
			// 현재 노드의 왼쪽 하위트리가 존재할 경우, 재귀적으로 왼쪽 하위트리 재탐색
			RBT_InsertNodeHelper(&(*Tree)->Left, NewNode);
		}
	}
}

// 레드블랙트리 노드 삽입 후 뒷처리 (레드블랙트리 규칙이 무너지지 않도록)
void RBT_RebuildAfterInsert(RBTNode** Tree, RBTNode* NewNode)
{

}




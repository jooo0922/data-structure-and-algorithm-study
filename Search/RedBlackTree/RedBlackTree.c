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

// 레드블랙트리 상에서 노드 우회전 (= '왼쪽 자식노드' <-> '부모' 간 위치 교환)
void RBT_RotateRight(RBTNode** Root, RBTNode* Parent)
{
	// '왼쪽 자식노드' 가져오기
	RBTNode* LeftChild = Parent->Left;


	/* 이진탐색트리의 조건을 유지하기 위한 전처리 */

	// '왼쪽 자식노드'의 오른쪽 자식을 '부모노드'의 왼쪽 자식으로 등록
	Parent->Left = LeftChild->Right;

	// 그에 따라, '왼쪽 자식노드'의 오른쪽 자식의 부모도 변경해 줌.
	if (LeftChild->Right != Nil)
	{
		LeftChild->Right->Parent = Parent;
	}

	
	/* '왼쪽 자식노드' <-> '부모' 간 위치 교환 */

	// '왼쪽 자식노드'의 부모 먼저 변경
	LeftChild->Parent = Parent->Parent;

	if (Parent->Parent == NULL)
	{
		// '부모'가 뿌리노드였던 경우, '왼쪽 자식노드'를 뿌리노드로 교체함.
		(*Root) = LeftChild;
	}
	else
	{
		// '부모'가 뿌리노드가 아니였던 경우

		if (Parent == Parent->Parent->Left)
		{
			// '부모'가 할아버지 노드의 왼쪽 자식이었던 경우,
			// 할아버지 노드의 왼쪽 자식을 '왼쪽 자식노드'로 교체함
			Parent->Parent->Left = LeftChild;
		}
		else
		{
			// '부모'가 할아버지 노드의 오른쪽 자식이었던 경우,
			// 할아버지 노드의 오른쪽 자식을 '왼쪽 자식노드'로 교체함
			Parent->Parent->Right = LeftChild;
		}
	}

	// '왼쪽 자식노드'의 오른쪽 자식을 '부모'로 등록
	LeftChild->Right = Parent;

	// '부모'의 부모노드를 '왼쪽 자식노드'로 등록
	Parent->Parent = LeftChild;
}

// 레드블랙트리 상에서 노드 좌회전 (= '오른쪽 자식노드' <-> '부모' 간 위치 교환)
// 노드 우회전 코드에서 '왼쪽 자식노드' -> '오른쪽 자식노드' 로만 바꾸면 됨!
void RBT_RotateLeft(RBTNode** Root, RBTNode* Parent)
{
	// '오른쪽 자식노드' 가져오기
	RBTNode* RightChild = Parent->Right;


	/* 이진탐색트리의 조건을 유지하기 위한 전처리 */

	// '오른쪽 자식노드'의 왼쪽 자식을 '부모노드'의 오른쪽 자식으로 등록
	Parent->Right = RightChild->Left;

	// 그에 따라, '오른쪽 자식노드'의 왼쪽 자식의 부모도 변경해 줌.
	if (RightChild->Left != Nil)
	{
		RightChild->Left->Parent = Parent;
	}


	/* '오른쪽 자식노드' <-> '부모' 간 위치 교환 */

	// '오른쪽 자식노드'의 부모 먼저 변경
	RightChild->Parent = Parent->Parent;

	if (Parent->Parent == NULL)
	{
		// '부모'가 뿌리노드였던 경우, '오른쪽 자식노드'를 뿌리노드로 교체함.
		(*Root) = RightChild;
	}
	else
	{
		// '부모'가 뿌리노드가 아니였던 경우

		if (Parent == Parent->Parent->Left)
		{
			// '부모'가 할아버지 노드의 왼쪽 자식이었던 경우,
			// 할아버지 노드의 왼쪽 자식을 '오른쪽 자식노드'로 교체함
			Parent->Parent->Left = RightChild;
		}
		else
		{
			// '부모'가 할아버지 노드의 오른쪽 자식이었던 경우,
			// 할아버지 노드의 오른쪽 자식을 '오른쪽 자식노드'로 교체함
			Parent->Parent->Right = RightChild;
		}
	}

	// '오른쪽 자식노드'의 왼쪽 자식을 '부모'로 등록
	RightChild->Left = Parent;

	// '부모'의 부모노드를 '오른쪽 자식노드'로 등록
	Parent->Parent = RightChild;
}

// 레드블랙트리 노드 삽입 후 뒷처리 (레드블랙트리 규칙이 무너지지 않도록)
void RBT_RebuildAfterInsert(RBTNode** Root, RBTNode* NewNode)
{
	// 새로 삽입한 노드가 뿌리노드가 아니고(뿌리노드면 검은색으로 칠하면 금방 해결됨..),
	// 새로 삽입한 노드의 부모노드가 빨간색 노드일 때에는 반복문을 계속 돌리며 3개의 뒷처리 케이스 반복
	while (NewNode !=  (*Root) && NewNode->Parent->Color == RED)
	{
		if (NewNode->Parent == NewNode->Parent->Parent->Left)
		{
			/* 부모노드가 할아버지 노드의 왼쪽 자식일 때 기준으로 뒷처리 */

			// 삼촌노드(= 부모노드의 유일한 형제 노드) 가져오기
			RBTNode* Uncle = NewNode->Parent->Parent->Right;

			if (Uncle->Color == RED)
			{
				/* 1. 삼촌노드가 빨간색인 경우 뒷처리 */

				// 부모노드와 삼촌노드를 검은색으로 칠함
				NewNode->Parent->Color = BLACK;
				Uncle->Color = BLACK;

				// 할아버지 노드를 빨간색으로 칠함
				NewNode->Parent->Parent->Color = RED;

				// 위에서 할아버지 노드를 빨간색으로 칠함에 따라, 
				// 레드블랙트리 4번 규칙 (= 빨간색 노드의 자식은 모두 검은색이다) 이 위배될 가능성이 생김.

				// 따라서, 할아버지 노드를 새로 삽입한 노드로 간주하여 
				// 다음 반복문에서 할아버지를 타고 올라가며 4번 규칙을 위배하는지 계속 검사하며 뒷처리 반복!
				NewNode = NewNode->Parent->Parent;
			}
			else
			{
				if (NewNode == NewNode->Parent->Right)
				{
					/* 2. 삼촌노드가 검은색이고, 새로 삽입한 노드가 부모노드의 오른쪽 자식인 경우 뒷처리 */

					// 새로 삽입한 노드와 부모노드를 좌회전으로 위치 교환할 것이므로,
					// 그전에 부모노드를 새로 삽입한 노드로 간주시킴
					NewNode = NewNode->Parent;

					// 부모노드를 기준으로 좌회전
					// (참고로, 부모노드는 새로 삽입한 노드로 간주되었으니, 현재 NewNode 에는 부모노드 주소값이 들어있는 상태!)
					RBT_RotateLeft(Root, NewNode);

					// 부모노드를 좌회전함으로써, 3번 뒷처리 케이스와 동일한 꼴이 됨 -> 3번 케이스로 뒷처리를 넘긴 셈!
				}

				/* 3. 삼촌노드가 검은색이고, 새로 삽입한 노드가 부모노드의 왼쪽 자식인 경우 뒷처리 */

				// 부모노드를 검은색으로 칠함
				NewNode->Parent->Color = BLACK;

				// 할아버지 노드를 빨간색으로 칠함
				NewNode->Parent->Parent->Color = RED;

				// 할아버지 노드를 기준으로 우회전 -> 부모노드와 할아버지 노드 간 위치 교환
				// -> 드디어 4번 규칙에 위배되지 않게 됨!
				RBT_RotateRight(Root, NewNode->Parent->Parent);
			}
		}
		else
		{
			/* 부모노드가 할아버지 노드의 오른쪽 자식일 때 기준으로 뒷처리 */
			// 부모노드가 왼쪽 자식일 때 기준 코드에서 왼쪽 <-> 오른쪽 만 바꿔주면 됨!

			// 삼촌노드(= 부모노드의 유일한 형제 노드) 가져오기
			RBTNode* Uncle = NewNode->Parent->Parent->Left;

			if (Uncle->Color == RED)
			{
				/* 1. 삼촌노드가 빨간색인 경우 뒷처리 */

				// 부모노드와 삼촌노드를 검은색으로 칠함
				NewNode->Parent->Color = BLACK;
				Uncle->Color = BLACK;

				// 할아버지 노드를 빨간색으로 칠함
				NewNode->Parent->Parent->Color = RED;

				// 위에서 할아버지 노드를 빨간색으로 칠함에 따라, 
				// 레드블랙트리 4번 규칙 (= 빨간색 노드의 자식은 모두 검은색이다) 이 위배될 가능성이 생김.

				// 따라서, 할아버지 노드를 새로 삽입한 노드로 간주하여 
				// 다음 반복문에서 할아버지를 타고 올라가며 4번 규칙을 위배하는지 계속 검사하며 뒷처리 반복!
				NewNode = NewNode->Parent->Parent;
			}
			else
			{
				if (NewNode == NewNode->Parent->Left)
				{
					/* 2. 삼촌노드가 검은색이고, 새로 삽입한 노드가 부모노드의 왼쪽 자식인 경우 뒷처리 */

					// 새로 삽입한 노드와 부모노드를 우회전으로 위치 교환할 것이므로,
					// 그전에 부모노드를 새로 삽입한 노드로 간주시킴
					NewNode = NewNode->Parent;

					// 부모노드를 기준으로 우회전
					// (참고로, 부모노드는 새로 삽입한 노드로 간주되었으니, 현재 NewNode 에는 부모노드 주소값이 들어있는 상태!)
					RBT_RotateRight(Root, NewNode);

					// 부모노드를 우회전함으로써, 3번 뒷처리 케이스와 동일한 꼴이 됨 -> 3번 케이스로 뒷처리를 넘긴 셈!
				}

				/* 3. 삼촌노드가 검은색이고, 새로 삽입한 노드가 부모노드의 오른쪽 자식인 경우 뒷처리 */

				// 부모노드를 검은색으로 칠함
				NewNode->Parent->Color = BLACK;

				// 할아버지 노드를 빨간색으로 칠함
				NewNode->Parent->Parent->Color = RED;

				// 할아버지 노드를 기준으로 좌회전 -> 부모노드와 할아버지 노드 간 위치 교환
				// -> 드디어 4번 규칙에 위배되지 않게 됨!
				RBT_RotateLeft(Root, NewNode->Parent->Parent);
			}
		}
	}

	// 2번 규칙(= 뿌리노드는 검은색이다)을 위반하지 않기 위해,
	// 마지막에는 뿌리노드를 항상 검은색으로 칠해줌.
	(*Root)->Color = BLACK;
}

// 레드블랙트리 노드 제거
RBTNode* RBT_RemoveNode(RBTNode** Root, ElementType Data)
{
	/* 노드 제거에 필요한 포인터 변수 초기화 */

	// 제거할 노드의 주소값을 저장 및 반환할 포인터 변수 초기화
	RBTNode* Removed = NULL;

	// 제거할 노드를 대체할 노드 주소값을 저장할 포인터 변수 초기화 
	// (= 제거할 노드의 자식노드 or RBT_RebuildAfterRemove() 에서는 '이중흑백노드')
	RBTNode* Successor = NULL;

	// 제거할 노드를 탐색하여 주소값 저장 (BST_RemoveNode() 와 달리 탐색할 때 재귀 호출 미사용!)
	RBTNode* Target = RBT_SearchNode((*Root), Data);


	// 제거할 노드를 못찾았으면 NULL 을 반환하고 함수 종료
	if (Target == NULL)
	{
		return NULL;
	}


	/* 제거할 노드의 자식 존재 여부에 따른 처리 (p.256 ~ 257) */

	if (Target->Left == Nil || Target->Right == Nil)
	{
		// 제거할 노드의 자식이 둘 중 하나라도 더미노드(Nil)인 경우,
		// 즉, 제거할 노드의 자식이 존재하지 않거나, 제거할 노드의 자식이 1개인 경우 처리
		
		// 제거할 노드의 주소값을 곧바로 저장
		Removed = Target; 
	}
	else
	{
		// 제거할 노드의 자식이 둘 다 더미노드(Nil)가 아닌 경우,
		// 즉, 제거할 노드가 양쪽 자식을 모두 갖고 있는 경우 처리

		// 제거할 노드의 오른쪽 하위 트리에서 최솟값 노드를 탐색 (p.257 참고)
		Removed = RBT_SearchMinNode(Target->Right);

		// 최솟값 노드로 제거할 노드 자리를 교체함 (p.257 참고)
		Target->Data = Removed->Data;
	}


	/* 제거할 노드의 자식노드 (= 대체노드)의 주소값 저장 */

	if (Removed->Left != Nil)
	{
		// 제거할 노드가 '왼쪽 자식만' 존재할 경우, 왼쪽 자식을 대체노드로 지정
		Successor = Removed->Left;
	}
	else
	{
		// 제거할 노드가 '오른쪽 자식만' 존재하거나,
		// 제거할 노드가 위에서 '최솟값 노드로 덮어쓰여서' 오른쪽 자식만 존재하거나(p.257 하단 설명 참고), -> 원래는 제거할 노드의 자식이 양쪽에 모두 있던 케이스!
		// 제거할 노드의 자식이 모두 더미노드여서 '자식이 존재하지 않는' 경우, -> 이 경우 오른쪽 자식이라고 해봤자 더미노드(Nil)이 대체노드로 지정되겠지!
		// 오른쪽 자식을 대체노드로 지정
		Successor = Removed->Right;
	}


	// 제거할 노드의 부모를 대체노드의 부모로 삼음 
	Successor->Parent = Removed->Parent;

	
	/* 제거할 노드의 부모에 대체노드를 자식으로 추가 */

	if (Removed->Parent == NULL)
	{
		// 제거할 노드가 뿌리노드 였을 경우 처리

		// 대체노드를 뿌리노드로 지정
		(*Root) = Successor;
	}
	else
	{
		// 제거할 노드가 뿌리노드가 아니였을 경우 처리

		// 제거할 노드가 부모의 왼쪽 자식이였다면 왼쪽에,
		// 오른쪽 자식이였다면 오른쪽에 대체노드를 추가함
		if (Removed == Removed->Parent->Left)
		{
			Removed->Parent->Left = Successor;
		}
		else
		{
			Removed->Parent->Right = Successor;
		}
	}

	// 제거할 노드가 검은색 노드일 경우, 레드블랙트리의 규칙이 무너지므로, 뒷처리 함수 실행
	if (Removed->Color == BLACK)
	{
		RBT_RebuildAfterRemove(Root, Successor);
	}

	// 제거할 노드의 주소값 반환
	return Removed;
}

// 레드블랙트리 노드 제거 후 뒷처리 (레드블랙트리 규칙이 무너지지 않도록)
void RBT_RebuildAfterRemove(RBTNode** Root, RBTNode* Successor)
{
	// 이중 흑색 노드(= 대체노드)의 형제노드 주소값을 저장할 포인터 변수 초기화
	RBTNode* Sibling = NULL;

	// 대체노드가 뿌리노드가 되거나, 빨간색 노드가 되기 전까지는 루프를 계속 순회
	while (Successor->Parent != NULL && Successor->Color == BLACK)
	{
		if (Successor == Successor->Parent->Left)
		{
			/* 이중 흑색 노드(= 대체노드)가 어떤 노드의 왼쪽 자식일 경우 처리 */
			// 참고로, 오른쪽 자식일 경우 동일한 코드에서 왼쪽 <-> 오른쪽만 바꿔주면 됨 (p.279)

			// 이중 흑색 노드의 형제노드 저장
			Sibling = Successor->Parent->Right;

			if (Sibling->Color == RED)
			{
				/* 1. 이중 흑색 노드의 형제노드가 빨간색일 경우 뒷처리 (p.280 과정 코드로 구현) */

				// 형제노드를 검은색으로 칠한다
				Sibling->Color = BLACK;

				// 이중 흑색 노드의 부모노드를 빨간색으로 칠한다
				Successor->Parent->Color = RED;

				// 이중 흑색 노드의 부모노드를 좌회전한다
				RBT_RotateLeft(Root, Successor->Parent);

				// 1번 케이스가 2번대 케이스가 될 때까지(= 형제노드가 검은색이 될 때까지) 이 과정을 반복함!
			}
			else
			{
				/* 2. 이중 흑색 노드의 형제노드가 검은색일 경우 뒷처리 */

				if (Sibling->Left->Color == BLACK && Sibling->Right->Color == BLACK)
				{
					/* 2-A. 이중 흑색 노드의 형제노드가 검은색이고, 형제의 양쪽 자식이 모두 검은색일 경우 뒷처리 (p.281 과정 코드로 구현) */

					// 형제노드를 빨간색으로 칠한다
					Sibling->Color = RED;

					// 이중 흑색 노드(= 대체노드)가 갖고있던 검은색을 부모노드에게 넘겨준다
					// 즉, 부모노드를 새로운 대체노드로 지정한다
					Successor = Successor->Parent;

					// 이렇게 새로운 대체노드를 계속 부모노드로 올리기를 반복하면서
					// 새로운 대체노드가 빨간색이 되거나 뿌리노드가 될 때까지 4가지 뒷처리 케이스를 반복함!
				}
				else
				{
					if (Sibling->Left->Color = RED)
					{
						/* 2-B. 이중 흑색 노드의 형제노드가 검은색이고, 형제의 왼쪽 자식만 빨간색일 경우 뒷처리 (p.282 과정 코드로 구현) */

						// 형제의 왼쪽 자식을 검은색으로 칠한다
						Sibling->Left->Color = BLACK;

						// 형제노드를 빨간색으로 칠한다
						Sibling->Color = RED;

						// 형제노드를 우회전한다
						RBT_RotateRight(Root, Sibling);

						// 우회전 후, 새로 올라온 노드를 형제노드로 업데이트한다
						Sibling = Successor->Parent->Right;

						// 이렇게 하면 형제노드의 오른쪽 자식이 빨간색으로 바뀜에 따라,
						// 2-C 케이스로 변경된다 (= 문제 해결을 2-C 로 떠넘김)
					}


					/* 2-C. 이중 흑색 노드의 형제노드가 검은색이고, 형제의 오른쪽 자식이 빨간색일 경우 뒷처리 (p.283 과정 코드로 구현) */
					
					// 형제노드를 이중 흑색 노드의 부모가 갖고 있는 색상으로 칠한다
					Sibling->Color = Successor->Parent->Color;

					// 이중 흑색 노드의 부모노드를 검은색으로 칠한다
					Successor->Parent->Color = BLACK;

					// 형제노드의 오른쪽 자식을 검은색으로 칠한다
					Sibling->Right->Color = BLACK;

					// 이중 흑색 노드의 부모노드를 좌회전한다
					RBT_RotateLeft(Root, Successor->Parent);

					// 이중 흑색 노드(= 대체노드)가 갖고있던 검은색을 뿌리노드에게 넘겨준다
					// 즉, 뿌리노드를 새로운 대체노드(= Successor)로 지정한다
					Successor = (*Root);
				}
			}
		}
		else
		{
			/* 이중 흑색 노드(= 대체노드)가 어떤 노드의 오른쪽 자식일 경우 처리 */

			// 이중 흑색 노드의 형제노드 저장
			Sibling = Successor->Parent->Left;

			if (Sibling->Color == RED)
			{
				/* 1. 이중 흑색 노드의 형제노드가 빨간색일 경우 뒷처리 (p.280 과정 코드로 구현) */

				// 형제노드를 검은색으로 칠한다
				Sibling->Color = BLACK;

				// 이중 흑색 노드의 부모노드를 빨간색으로 칠한다
				Successor->Parent->Color = RED;

				// 이중 흑색 노드의 부모노드를 우회전한다
				RBT_RotateRight(Root, Successor->Parent);

				// 1번 케이스가 2번대 케이스가 될 때까지(= 형제노드가 검은색이 될 때까지) 이 과정을 반복함!
			}
			else
			{
				/* 2. 이중 흑색 노드의 형제노드가 검은색일 경우 뒷처리 */

				if (Sibling->Right->Color == BLACK && Sibling->Left->Color == BLACK)
				{
					/* 2-A. 이중 흑색 노드의 형제노드가 검은색이고, 형제의 양쪽 자식이 모두 검은색일 경우 뒷처리 (p.281 과정 코드로 구현) */

					// 형제노드를 빨간색으로 칠한다
					Sibling->Color = RED;

					// 이중 흑색 노드(= 대체노드)가 갖고있던 검은색을 부모노드에게 넘겨준다
					// 즉, 부모노드를 새로운 대체노드로 지정한다
					Successor = Successor->Parent;

					// 이렇게 새로운 대체노드를 계속 부모노드로 올리기를 반복하면서
					// 새로운 대체노드가 빨간색이 되거나 뿌리노드가 될 때까지 4가지 뒷처리 케이스를 반복함!
				}
				else
				{
					if (Sibling->Right->Color = RED)
					{
						/* 2-B. 이중 흑색 노드의 형제노드가 검은색이고, 형제의 오른쪽 자식만 빨간색일 경우 뒷처리 (p.282 과정 코드로 구현) */

						// 형제의 오른쪽 자식을 검은색으로 칠한다
						Sibling->Right->Color = BLACK;

						// 형제노드를 빨간색으로 칠한다
						Sibling->Color = RED;

						// 형제노드를 좌회전한다
						RBT_RotateLeft(Root, Sibling);

						// 좌회전 후, 새로 올라온 노드를 형제노드로 업데이트한다
						Sibling = Successor->Parent->Left;

						// 이렇게 하면 형제노드의 왼쪽 자식이 빨간색으로 바뀜에 따라,
						// 2-C 케이스로 변경된다 (= 문제 해결을 2-C 로 떠넘김)
					}


					/* 2-C. 이중 흑색 노드의 형제노드가 검은색이고, 형제의 왼쪽 자식이 빨간색일 경우 뒷처리 (p.283 과정 코드로 구현) */

					// 형제노드를 이중 흑색 노드의 부모가 갖고 있는 색상으로 칠한다
					Sibling->Color = Successor->Parent->Color;

					// 이중 흑색 노드의 부모노드를 검은색으로 칠한다
					Successor->Parent->Color = BLACK;

					// 형제노드의 왼쪽 자식을 검은색으로 칠한다
					Sibling->Left->Color = BLACK;

					// 이중 흑색 노드의 부모노드를 우회전한다
					RBT_RotateRight(Root, Successor->Parent);

					// 이중 흑색 노드(= 대체노드)가 갖고있던 검은색을 뿌리노드에게 넘겨준다
					// 즉, 뿌리노드를 새로운 대체노드(= Successor)로 지정한다
					Successor = (*Root);
				}
			}
		}
	}

	// 대체노드는 어떤 케이스로 처리하던지 간에, 마지막에는 항상 검은색으로 칠해줘야 함!
	Successor->Color = BLACK;
}

// 레드블랙트리 출력
void RBT_PrintTree(RBTNode* Node, int Depth, int BlackCount)
{
	// 반복문을 순회하며 현재 노드의 Depth 에 따라 들여쓰기를 추가할 때 사용할 index 값 초기화
	int i = 0;

	// 부모의 왼쪽 / 오른쪽 자식인지 여부를 저장할 변수 초기화 ('L' | 'R' | 'X') -> X 는 뿌리노드에만!
	char c = 'X';

	// 부모노드의 데이터를 저장할 변수 초기화
	int v = -1;

	// 현재 노드가 잎 노드인 경우, 
	// 뿌리노드와 현재 노드 사이의 검은색 노드 개수를 출력할 때 사용할 문자열 배열 변수 초기화
	char cnt[100];

	if (Node == NULL || Node == Nil)
	{
		// 현재 노드가 NULL 이거나 더미노드(Nil)일 경우 함수 종료
		return;
	}

	if (Node->Color == BLACK)
	{
		/* 현재 노드가 검은색일 경우 처리 */

		// 뿌리노드와 잎 노드 사이의 검은색 노드 수가 누산된 BlackGount 를 +1 증가시킴
		BlackCount++;
	}

	if (Node->Parent != NULL)
	{
		/* 현재 노드가 뿌리노드가 아닐 경우 처리 */

		// 부모노드 데이터 저장
		v = Node->Parent->Data;

		// 현재 노드가 부모의 왼쪽 / 오른쪽 자식 여부를 저장
		if (Node->Parent->Left == Node)
		{
			c = 'L';
		}
		else
		{
			c = 'R';
		}
	}

	if (Node->Left == Nil && Node->Right == Nil)
	{
		// 현재 노드의 양쪽 자식이 모두 더미노드인 경우, 즉, 잎 노드인 경우,
		// 문자열 배열 cnt 에 뿌리노드와 잎 노드 사이의 검은색 노드 수를 문자열로 저장함
		
		// sprintf() 를 사용하여 형식 지정자 %d 가 포함된 문자열을 배열에 저장하도록 함. (관련 필기 하단 참고)
		sprintf_s(cnt, sizeof(cnt), "--------- %d", BlackCount);
	}
	else
	{
		// 현재 노드에 자식이 하나라도 존재하면, 잎 노드가 아니므로,
		// 문자열 배열 cnt 에 empty string 을 저장함

		// strncpy() 를 사용하여 문자열 배열 cnt 에 원본 문자열 ""를 복사함 (관련 필기 하단 참고)
		strncpy_s(cnt, sizeof(cnt), "", sizeof(cnt));
	}

	// 현재 노드의 깊이값(Depth)만큼 반복문을 순회하며 들여쓰기 추가
	for (i = 0; i < Depth; i++)
	{
		printf("	");
	}

	// 현재 노드의 모든 정보를 최종 출력함 (p.286 하단 출력 형식 참고)
	printf("%d %s [%c, %d] %s\n", Node->Data, (Node->Color == RED) ? "RED" : "BLACK", c, v, cnt);

	// 현재 노드의 양쪽 자식노드를 재귀를 돌려서 출력을 반복함
	RBT_PrintTree(Node->Left, Depth + 1, BlackCount);
	RBT_PrintTree(Node->Right, Depth + 1, BlackCount);
}


/*
	int sprintf(char *str, const char *format, ...);


	sprintf() 함수는 형식 지정자가 포함된 문자열을 값으로 채워넣고 싶을 때 사용함.

	예를 들어, 정수를 나타내는 %d, 
	부동 소수점 숫자를 나타내는 %f 등의 형식 지정자가 포함된 문자열을
	printf() 에서 사용하는 것처럼 문자열에 값을 저장할 때에도 사용할 수 있다는 것!

	선언된 매개변수는 아래와 같음.

	str: 형식화된 데이터가 저장될 문자열의 포인터입니다.
	format: 형식 지정자를 포함하는 형식 문자열입니다.
	나머지 매개변수: 형식 문자열에 지정된 형식 지정자에 따라 값을 전달합니다.
*/

/*
	char *strncpy(char *dest, const char *src, size_t n);


	strncpy() 함수는 C 언어에서 문자열을 복사하는 함수. 
	일정한 크기의 문자열을 다른 문자열로 복사할 때 사용하기 좋음.

	strncpy() 함수는 원본 문자열 (src)에서 최대 n개의 문자를 목적지 문자열 (dest)로 복사한다! 
	
	만약 src의 길이가 n보다 작다면, 
	나머지 공간은 널 문자('\0')으로 채워짐.

	그러나 만약 src의 길이가 n보다 크다면, 
	dest는 널 문자로 종료되지 않을 수 있음!

	선언된 매개변수는 아래와 같음

	dest: 복사된 문자열이 저장될 목적지의 문자열 포인터입니다.
	src: 복사할 대상이 되는 원본 문자열의 포인터입니다.
	n: 복사할 최대 문자의 수를 나타내는 크기_t 형 매개변수입니다.

	그러나, 위에서 복사할 최대 문자의 수를
	sizeof(cnt) 로 계산한 이유는,

	char 타입 크기 자체가 어차피 1 byte 이므로,
	char 타입은 데이터 크기와 데이터 길이(= 개수)가 같아
	sizeof(char[])로 계산한 데이터 크기는 문자열 개수로도 활용 가능함!
*/
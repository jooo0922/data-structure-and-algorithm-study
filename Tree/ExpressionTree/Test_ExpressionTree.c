#include "ExpressionTree.h"

int main()
{
	// 수식트리의 루트노드 주소값을 저장할 포인터 변수 초기화
	ETNode* Root = NULL;

	// 후위표기식 문자열 배열 선언
	char PostfixExpression[20] = "71*52-/";

	// 후위표기식과 루트노드 포인터 변수의 주소값(=이중 포인터)을 전달하여 수식트리 구축
	ET_BuildExpressionTree(PostfixExpression, &Root);

	// 생성된 수식트리를 전위순회하여 출력 > 전위표기식
	printf("Preorder ...\n");
	ET_PreorderPrintTree(Root);
	printf("\n\n");

	// 생성된 수식트리를 중위순회하여 출력 > 중위표기식
	printf("Inorder ...\n");
	ET_InorderPrintTree(Root);
	printf("\n\n");

	// 생성된 수식트리를 중위순회하여 출력 > 중위표기식
	printf("Postorder ...\n");
	ET_PostorderPrintTree(Root);
	printf("\n");

	// 수식트리를 재귀적으로 순회하여 계산한 결과 출력
	printf("Evaluation Result : %f \n", ET_Evaluate(Root));

	// 수식트리 전체 메모리 반납
	ET_DestroyTree(Root);

	return 0;
}
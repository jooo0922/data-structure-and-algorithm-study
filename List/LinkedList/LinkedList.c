#include "LinkedList.h";

// 노드 생성
Node* SLL_CreateNode(ElementType NewData)
{
	Node* NewNode = (Node*)malloc(sizeof(Node)); // 힙 메모리에 Node 포인터 타입에 해당하는 메모리 공간 할당

	NewNode->Data = NewData; // 포인터 멤버변수 참조로 데이터 저장
	//NewNode->NextNode = ; 
}
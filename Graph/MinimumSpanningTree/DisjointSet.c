#include "DisjointSet.h"

// 합집합 연산
void DS_UnionSet(DisjointSet* Set1, DisjointSet* Set2)
{
	// 오른쪽 분리집합의 뿌리 노드 탐색
	Set2 = DS_FindSet(Set2); 

	// 오른쪽 분리집합의 뿌리 노드의 부모를 왼쪽 분리집합의 노드로 설정
	// 이제 오른쪽 분리집합이 왼쪽 분리집합에 포함됨에 따라, 두 집합이 하나로 합쳐짐.
	Set2->Parent = Set1;
}

// 원소가 속한 집합 탐색
DisjointSet* DS_FindSet(DisjointSet* Set)
{
	// 부모노드 포인터가 NULL 인 원소(= 뿌리노드)가 나올 때까지 반복 순회
	while (Set->Parent != NULL)
	{
		Set = Set->Parent;
	}

	// 반복문 종료 후, 부모 포인터가 NULL 인 뿌리노드가 Set 에 저장되어 있음.
	// 이 뿌리노드 반환 자체가 임의의 원소 Set 이 속한 분리집합을 반환하는 것!
	return Set;
}

// 분리집합 생성
// void* 타입의 주소값을 받는다는 건, 어느 자료형의 주소값이든 다 받도록 하겠다는 뜻!
// why? DisjointSet 노드의 데이터 멤버는 어느 자료형이든 다 허용하기 때문!
DisjointSet* DS_MakeSet(void* NewData)
{
	// 하나의 독립된 분리집합 트리를 생성한다는 것은, 뿌리노드를 생성하는 것과 같음!
	
	// 분리집합 원소 구조체 DisjointSet 크기 만큼의 힙 메모리 할당하여 주소값을 포인터 변수에 저장 
	// -> 뿌리노드 생성 == 분리집합 생성
	DisjointSet* NewNode = (DisjointSet*)malloc(sizeof(DisjointSet));

	// 노드 포인터 멤버 초기화
	NewNode->Data = NewData;
	NewNode->Parent = NULL; // 뿌리노드는 부모노드가 NULL

	return NewNode;
}

// 분리집합 메모리 반납
void DS_DestroySet(DisjointSet* Set)
{
	// 인자로 전달받은 분리집합 노드의 메모리 반납
	free(Set);
}
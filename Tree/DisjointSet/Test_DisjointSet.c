#include "DisjointSet.h"

int main()
{
	// DisjointSet 노드에 할당할 정수형 데이터 변수 선언 및 초기화
	int a = 1, b = 2, c = 3, d = 4;

	// 각각 독립적인 4개의 DisjointSet 생성 == 4개의 분리집합(= 뿌리노드) 생성
	// DisjointSet 노드에 데이터 할당 시, 데이터의 주소값을 포인터 멤버에 저장하므로, 정수형 데이터 변수들의 주소값을 넘겨줘야 함.
	DisjointSet* Set1 = DS_MakeSet(&a);
	DisjointSet* Set2 = DS_MakeSet(&b);
	DisjointSet* Set3 = DS_MakeSet(&c);
	DisjointSet* Set4 = DS_MakeSet(&d);

	// 분리집합 Set1 과 Set2 가 동일한 집합에 속하는 지 검사
	// (두 분리집합이 동일한 집합에 속하면 1, 아니면 0 을 출력할 것임.)
	printf("Set1 == Set2 : %d \n", DS_FindSet(Set1) == DS_FindSet(Set2));

	// 분리집합 Set1 과 Set3 을 합집합 연산 > 두 노드는 같은 분리집합에 속하게 됨.
	DS_UnionSet(Set1, Set3);

	// 분리집합 Set1 과 Set3 가 동일한 집합에 속하는 지 검사
	printf("Set1 == Set3 : %d \n", DS_FindSet(Set1) == DS_FindSet(Set3));

	// 분리집합 Set3 과 Set4 을 합집합 연산 > 두 노드는 같은 분리집합에 속하게 됨.
	DS_UnionSet(Set3, Set4);

	// 분리집합 Set3 과 Set4 가 동일한 집합에 속하는 지 검사
	printf("Set3 == Set4 : %d \n", DS_FindSet(Set3) == DS_FindSet(Set4));

	return 0;
}
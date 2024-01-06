#include "TopologicalSort.h"

// DGA(Directed Acycle Graph) 위상정렬
void TopologicalSort(Vertex* V, Node** List)
{
	// 더 이상 미방문 정점이 존재하지 않을 때까지 반복문 순회
	while (V != NULL && V->Visited == NotVisited)
	{
		// 더 이상 미방문 정점이 존재하지 않을 때까지 깊이 우선 탐색 반복
		TS_DFS(V, List);
		
		// 다음 순회에서 깊이 우선 탐색을 수행할 시작 정점 업데이트
		V = V->Next;
	}
}

// 깊이 우선 탐색 및 리스트에 헤드노드 추가
void TS_DFS(Vertex* V, Node** List)
{
	// 깊이 우선 탐색 결과 리스트에 헤드노드로 추가할 정점 노드의 포인터 변수 초기화 
	Node* NewHead = NULL;

	// 간선 구조체를 캐싱할 포인터 변수 초기화
	Edge* E = NULL;

	// 현재 방문한 정점을 '방문했음' 표시
	V->Visited = Visited;

	// 현재 방문한 정점의 인접 정점들의 리스트 (정확히는, 간선들의 리스트) 캐싱
	E = V->AdjacencyList;

	// 현재 방문한 정점의 인접 정점들(간선들)을 순회함
	while (E != NULL)
	{
		// 인접 정점(== 간선의 끝점(E->Target))을 아직 방문하지 않은 경우, 깊이 우선 탐색을 재귀 호출함
		if (E->Target != NULL && E->Target->Visited == NotVisited)
		{
			TS_DFS(E->Target, List);
		}

		// 다음 인접 정점을 순회하기 위해 캐싱된 간선을 업데이트함.
		E = E->Next;
	}

	/*
		while 문 이후의 코드들은
		E != NULL 인 조건을 먼저 만족하는 순으로,

		즉, 더 이상 방문할 인접 정점이 (정확히는 진출 간선) 존재하지 않는
		정점들부터 먼저 실행될 것임.

		따라서, p.411 예제 삽화로 따지면,
		가장 먼저 찾아낸 '더 이상 방문할 인접 정점이 없는 정점' 인 H 부터
		while 문 이후의 코드들이 실행된다는 뜻!
	*/

	// 깊이 우선 탐색 결과, '더 이상 방문할 인접 정점이 없는 정점' 의 데이터 출력
	printf("%c\n", V->Data);

	// '더 이상 방문할 인접 정점이 없는 정점' 을 링크드리스트의 노드로 만듦.
	NewHead = SLL_CreateNode(V);

	// 해당 노드를 링크드리스트의 헤드노드로 삽입
	SLL_InsertNewHead(List, NewHead);
}

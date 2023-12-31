#include "GraphTraversal.h"

// 깊이 우선 탐색
void DFS(Vertex* V)
{
	// 간선 구조체를 캐싱할 포인터 변수 초기화
	Edge* E = NULL; 

	// 현재 방문한 정점 데이터 출력
	printf("%d ", V->Data);

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
			DFS(E->Target);
		}

		// 다음 인접 정점을 순회하기 위해 캐싱된 간선을 업데이트함.
		E = E->Next;
	}
}

// 너비 우선 탐색
void BFS(Vertex* V, LinkedQueue* Queue)
{

}
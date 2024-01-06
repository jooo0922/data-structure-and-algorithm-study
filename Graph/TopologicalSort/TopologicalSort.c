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

}

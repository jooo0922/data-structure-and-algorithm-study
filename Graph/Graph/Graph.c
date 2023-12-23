#include "Graph.h"

// 그래프 구조체 생성
Graph* CreateGraph()
{
	// Graph 구조체 크기 만큼의 힙 메모리 할당
	// malloc() 이 할당한 힙 메모리 주소값 반환 시, Graph* 타입의 포인터 주소로 형변환하여 반환.
	Graph* graph = (Graph*)malloc(sizeof(Graph));

	// 그래프의 정점 리스트 포인터는 NULL 초기화
	graph->Vertices = NULL;

	// 그래프의 전체 개수 멤버변수 초기화
	graph->VertexCount = 0;

	// 생성된 그래프 구조체 주소값 반환
	return graph;
}

// 그래프 구조체 메모리 해제
void DestroyGraph(Graph* G)
{
	// 그래프의 정점 리스트가 NULL 이 될때까지 정점 메모리 반납을 반복
	while (G->Vertices != NULL)
	{
		// 그래프의 첫 번째 정점(리스트의 헤드노드)의 다음 정점을 임시로 캐싱
		Vertex* vertices = G->Vertices->Next; 

		// 그래프의 첫 번째 정점 메모리 반납
		DestroyVertex(G->Vertices);

		// 캐싱해 둔 다음 정점을 그래프의 새로운 첫 번째 정점으로 업데이트
		G->Vertices = vertices;
	}

	// 그래프의 정점 리스트 메모리 반납 완료 후, 그래프 구조체 메모리 반납
	free(G);
}

// 정점 구조체 생성
Vertex* CreateVertex(VElementType Data)
{

}

// 정점 구조체 메모리 해제
void DestroyVertex(Vertex* V)
{

}

// 간선 구조체 생성
Edge* CreateEdge(Vertex* From, Vertex* Target, int Weight)
{

}

// 간선 구조체 메모리 해제
void DestroyEdge(Edge* E)
{

}

// 그래프 구조체의 정점 리스트에 새로운 정점 삽입
void AddVertex(Graph* G, Vertex* V)
{

}

// 정점 구조체의 간선 리스트(== 인접 정점 리스트)에 새로운 간선 삽입
void AddEdge(Vertex* V, Edge* E)
{

}

// 그래프 출력
void PrintGraph(Graph* G)
{

}
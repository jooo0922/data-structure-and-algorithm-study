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
	// 그래프의 정점 리스트가 NULL 이 될때까지 정점(Vertex) 메모리 반납을 반복
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
	// Vertex 구조체 크기 만큼의 힙 메모리 할당
	// malloc() 이 할당한 힙 메모리 주소값 반환 시, Vertex* 타입의 포인터 주소로 형변환하여 반환.
	Vertex* V = (Vertex*)malloc(sizeof(Vertex));

	// Vertex 구조체 멤버변수 초기화
	V->Data = Data;
	V->Next = NULL;
	V->AdjacencyList = NULL;
	V->Visited = NotVisited;
	V->Index = -1;

	// 생성된 정점 구조체 주소값 반환
	return V;
}

// 정점 구조체 메모리 해제
void DestroyVertex(Vertex* V)
{
	// 정점의 간선 리스트가 NULL 이 될때까지 간선(Edge) 메모리 반납을 반복
	while (V->AdjacencyList != NULL)
	{
		// 정점의 첫 번째 간선(리스트의 헤드노드)의 다음 간선을 임시로 캐싱
		Edge* Edge = V->AdjacencyList->Next;

		// 정점의 첫 번째 간선 메모리 반납
		DestroyEdge(V->AdjacencyList);

		// 캐싱해 둔 다음 간선을 그래프의 새로운 첫 번째 간선으로 업데이트
		V->AdjacencyList = Edge;
	}

	// 정점의 간선 리스트 메모리 반납 완료 후, 정점 구조체 메모리 반납
	free(V);
}

// 간선 구조체 생성
Edge* CreateEdge(Vertex* From, Vertex* Target, int Weight)
{
	// Edge 구조체 크기 만큼의 힙 메모리 할당
	// malloc() 이 할당한 힙 메모리 주소값 반환 시, Edge* 타입의 포인터 주소로 형변환하여 반환.
	Edge* E = (Edge*)malloc(sizeof(Edge));

	// Edge 구조체 멤버변수 초기화
	E->From = From;
	E->Target = Target;
	E->Next = NULL;
	E->Weight = Weight;

	// 생성된 간선 구조체 주소값 반환
	return E;
}

// 간선 구조체 메모리 해제
void DestroyEdge(Edge* E)
{
	// 간선 구조체 메모리 반납
	free(E);
}

// 그래프 구조체의 정점 리스트에 새로운 정점 삽입
void AddVertex(Graph* G, Vertex* V)
{
	// 그래프의 정점 리스트를 임시 캐싱
	Vertex* VertexList = G->Vertices;

	if (VertexList == NULL)
	{
		// 그래프의 정점 리스트의 헤드노드가 NULL 인 경우, (== 추가된 정점이 없음)
		// 입력받은 정점 V 를 바로 추가
		G->Vertices = V;
	}
	else
	{
		// 그래프의 정점 리스트가 NULL 이 아닌 경우, (== 이미 추가된 정점이 존재)
		
		// 정점 리스트를 순차탐색하여 테일노드(리스트의 마지막 정점)을 찾아 캐싱
		while (VertexList->Next != NULL)
		{
			VertexList = VertexList->Next;
		}

		// 리스트의 마지막 정점의 Next 포인터가 
		// 입력받은 정점 V 를 가리키도록 주소값 할당
		VertexList->Next = V;
	}

	// 정점의 인덱스는 항상 그래프에 추가된 순서대로 할당.
	// 또한, 그래프의 전체 정점 개수를 +1 증가시킴.
	V->Index = G->VertexCount++;
}

// 정점 구조체의 간선 리스트(== 인접 정점 리스트)에 새로운 간선 삽입
void AddEdge(Vertex* V, Edge* E)
{

}

// 그래프 출력
void PrintGraph(Graph* G)
{

}
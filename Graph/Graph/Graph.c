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
	if (V->AdjacencyList == NULL)
	{
		// 정점의 간선 리스트의 헤드노드가 NULL 인 경우, (== 추가된 간선이 없음)
		// 입력받은 간선 E 를 바로 추가
		V->AdjacencyList = E;
	}
	else
	{
		// 정점의 간선 리스트가 NULL 이 아닌 경우, (== 이미 추가된 간선이 존재)

		// 간선 리스트의 헤드노드 (== 첫 번째 간선) 임시로 캐싱
		Edge* AdjacencyList = V->AdjacencyList;

		// 간선 리스트를 순차탐색하여 테일노드(리스트의 마지막 간선)을 찾아 캐싱
		while (AdjacencyList->Next != NULL)
		{
			AdjacencyList = AdjacencyList->Next;
		}

		// 리스트의 마지막 간선의 Next 포인터가 
		// 입력받은 간선 E 를 가리키도록 주소값 할당
		AdjacencyList->Next = E;
	}
}

// 그래프 출력
void PrintGraph(Graph* G)
{
	// 순회할 현재 정점 포인터 변수 초기화
	Vertex* V = NULL;

	// 순회할 현재 간선 포인터 변수 초기화
	Edge* E = NULL;

	// 그래프의 정점 리스트의 헤드노드가 NULL 이라면, (== 추가된 정점이 없다면)
	// 출력할 정점이 없다는 뜻이므로, 함수 실행을 종료함. 
	if ((V = G->Vertices) == NULL)
	{
		return;
	}

	// 순회할 현재 정점이 NULL 이 될때까지 출력을 반복함
	while (V != NULL)
	{
		// 현재 정점의 데이터 출력
		printf("%c : ", V->Data);

		// 정점의 간선 리스트의 헤드노드가 NULL 이라면, (== 현재 정점에 추가된 간선이 없다면,)
		// 출력할 간선이 없다는 뜻이므로, 
		// 순회할 현재 정점을 업데이트하고 다음 루프로 넘어감!
		if ((E = V->AdjacencyList) == NULL)
		{
			// 순회할 현재 정점 업데이트
			V = V->Next;

			// 줄 띄우기. -> 한 줄 단위로 정점과 그 정점의 간선 정보들이 출력되겠군!
			printf("\n");
			
			// 다음 루프로 넘어감
			continue;
		}

		// 순회할 현재 간선이 NULL 이 될때까지 출력을 반복함
		while (E != NULL)
		{
			// 현재 간선의 끝 정점 데이터와 현재 간선의 가중치를 출력
			// 현재 간선의 시작 정점은 이미 V 에 저장되서 바깥쪽 while 문에서 출력되었고, 
			// 이는 V 에 속한 간선이라면 모두 동일할 것이니 현재 간선의 끝 정점을 출력하는 것!
			printf("%c[%d] ", E->Target->Data, E->Weight);

			// 순회할 현재 간선 업데이트
			E = E->Next;
		}

		// 줄 띄우기
		printf("\n");

		// 순회할 현재 정점 업데이트
		V = V->Next;
	}

	// 모든 정점과 간선을 출력한 뒤, 마지막으로 줄 띄우기
	printf("\n");
}
#include "Graph.h"
#include "GraphTraversal.h"

int main()
{
	// 그래프 순회 모드(DFS / BFS)를 구분하는 입력변수 초기화
	int Mode = 0;

	// 그래프 생성
	Graph* G = CreateGraph();

	// 정점 생성
	Vertex* V1 = CreateVertex(1);
	Vertex* V2 = CreateVertex(2);
	Vertex* V3 = CreateVertex(3);
	Vertex* V4 = CreateVertex(4);
	Vertex* V5 = CreateVertex(5);
	Vertex* V6 = CreateVertex(6);
	Vertex* V7 = CreateVertex(7);

	// 그래프에 정점 추가
	AddVertex(G, V1);
	AddVertex(G, V2);
	AddVertex(G, V3);
	AddVertex(G, V4);
	AddVertex(G, V5);
	AddVertex(G, V6);
	AddVertex(G, V7);

	/* 정점과 정점을 간선으로 연결 (p.394 방향성 그래프 형태로 연결) */
	// 간선의 가중치는 0으로 통일

	// 1번 정점에 간선 추가
	AddEdge(V1, CreateEdge(V1, V2, 0));
	AddEdge(V1, CreateEdge(V1, V3, 0));

	// 2번 정점에 간선 추가
	AddEdge(V2, CreateEdge(V2, V4, 0));
	AddEdge(V2, CreateEdge(V2, V5, 0));

	// 3번 정점에 간선 추가
	AddEdge(V3, CreateEdge(V3, V4, 0));
	AddEdge(V3, CreateEdge(V3, V6, 0));

	// 4번 정점에 간선 추가
	AddEdge(V4, CreateEdge(V4, V5, 0));
	AddEdge(V4, CreateEdge(V4, V7, 0));

	// 5번 정점에 간선 추가
	AddEdge(V5, CreateEdge(V5, V7, 0));

	// 6번 정점에 간선 추가
	AddEdge(V5, CreateEdge(V6, V7, 0));

	// 그래프 순회 모드 입력 -> Mode 변수에 값 할당
	printf("Enter Traversal Mode (0:DFS, 1:BFS) : ");
	scanf_s("%d", &Mode);

	if (Mode == 0)
	{
		// 0번 단축키 입력 시, 깊이 우선 탐색으로 그래프 순회 출력
		DFS(G->Vertices);
	}
	else
	{
		// 1번 단축키 입력 시, 너비 우선 탐색으로 그래프 순회 출력

		// 너비 우선 탐색(BFS) 에 사용할 큐 생성
		LinkedQueue* Queue = NULL;
		LQ_CreateQueue(&Queue);

		// 너비 우선 탐색 실행
		BFS(V1, Queue);

		// 너비 우선 탐색 종료 후, 큐 메모리 반납
		LQ_DestroyQueue(Queue);
	}

	// 그래프 순회 종료 후, 그래프 메모리 반납
	DestroyGraph(G);

	return 0;
}
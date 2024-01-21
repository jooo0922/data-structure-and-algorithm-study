#include "Graph.h"
#include "ShortestPath.h"

int main()
{
	// 원본 그래프 생성
	Graph* graph = CreateGraph();

	// 데이크스트라 알고리즘으로 구축할 최단 경로 그래프 생성
	Graph* MST = CreateGraph();

	// 정점 생성
	Vertex* A = CreateVertex('A');
	Vertex* B = CreateVertex('B');
	Vertex* C = CreateVertex('C');
	Vertex* D = CreateVertex('D');
	Vertex* E = CreateVertex('E');
	Vertex* F = CreateVertex('F');
	Vertex* G = CreateVertex('G');
	Vertex* H = CreateVertex('H');
	Vertex* I = CreateVertex('I');

	// 그래프에 정점 추가
	AddVertex(graph, A);
	AddVertex(graph, B);
	AddVertex(graph, C);
	AddVertex(graph, D);
	AddVertex(graph, E);
	AddVertex(graph, F);
	AddVertex(graph, G);
	AddVertex(graph, H);
	AddVertex(graph, I);

	/* 정점과 정점을 간선으로 연결 (p.421 방향성 그래프 형태로 연결) */

	// A 정점에 간선 추가
	AddEdge(A, CreateEdge(A, E, 247));

	// B 정점에 간선 추가
	AddEdge(B, CreateEdge(B, A, 35));
	AddEdge(B, CreateEdge(B, C, 126));
	AddEdge(B, CreateEdge(B, F, 150));

	// C 정점에 간선 추가
	AddEdge(C, CreateEdge(C, D, 117));
	AddEdge(C, CreateEdge(C, F, 162));
	AddEdge(C, CreateEdge(C, G, 220));

	// E 정점에 간선 추가
	AddEdge(E, CreateEdge(E, H, 98));

	// F 정점에 간선 추가
	AddEdge(F, CreateEdge(F, E, 82));
	AddEdge(F, CreateEdge(F, G, 154));
	AddEdge(F, CreateEdge(F, H, 120));

	// G 정점에 간선 추가
	AddEdge(G, CreateEdge(G, I, 106));


	// 정점 B 를 시작 정점으로 하는 최단 경로 그래프 구축
	Dijkstra(graph, B, MST);
	PrintGraph(MST);

	// 그래프 메모리 반납
	DestroyGraph(MST);
	DestroyGraph(graph);

	return 0;
}
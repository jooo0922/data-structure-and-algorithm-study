#include "Graph.h"
#include "MST.h"

int main()
{
	// 원본 그래프 생성
	Graph* graph = CreateGraph();

	// 프림 알고리즘으로 구현한 최소 신장 트리를 구축할 그래프
	Graph* PrimMST = CreateGraph();

	// 크루스칼 알고리즘으로 구현한 최소 신장 트리를 구축할 그래프
	Graph* KruskalMST = CreateGraph();

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


	/* 정점과 정점을 간선으로 연결 (p.421 무방향성 그래프 형태로 연결) */

	// A 정점에 간선 추가
	AddEdge(A, CreateEdge(A, B, 35));
	AddEdge(A, CreateEdge(A, E, 247));

	// B 정점에 간선 추가
	AddEdge(B, CreateEdge(B, A, 35));
	AddEdge(B, CreateEdge(B, C, 126));
	AddEdge(B, CreateEdge(B, F, 150));

	// C 정점에 간선 추가
	AddEdge(C, CreateEdge(C, B, 126));
	AddEdge(C, CreateEdge(C, D, 117));
	AddEdge(C, CreateEdge(C, F, 162));
	AddEdge(C, CreateEdge(C, G, 220));

	// D 정점에 간선 추가
	AddEdge(D, CreateEdge(D, C, 117));

	// E 정점에 간선 추가
	AddEdge(E, CreateEdge(E, A, 247));
	AddEdge(E, CreateEdge(E, F, 82));
	AddEdge(E, CreateEdge(E, H, 98));

	// F 정점에 간선 추가
	AddEdge(F, CreateEdge(F, B, 150));
	AddEdge(F, CreateEdge(F, C, 162));
	AddEdge(F, CreateEdge(F, E, 82));
	AddEdge(F, CreateEdge(F, G, 154));
	AddEdge(F, CreateEdge(F, H, 120));

	// G 정점에 간선 추가
	AddEdge(G, CreateEdge(G, C, 220));
	AddEdge(G, CreateEdge(G, F, 154));
	AddEdge(G, CreateEdge(G, I, 106));

	// H 정점에 간선 추가
	AddEdge(H, CreateEdge(H, E, 98));
	AddEdge(H, CreateEdge(H, F, 120));

	// I 정점에 간선 추가
	AddEdge(I, CreateEdge(I, G, 106));


	// 프림 알고리즘으로 최소 신장 트리 구축 및 출력
	printf("Prim's Algorithm\n");
	Prim(graph, B, PrimMST);
	PrintGraph(PrimMST);

	return 0;
}
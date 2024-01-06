#include "Graph.h"
#include "TopologicalSort.h"

int main()
{
	// 위상정렬 결과를 저장할 링크드리스트 포인터 변수 초기화
	Node* SortedList = NULL;

	// 위상정렬 반복문 순회 시, 현재 노드를 캐싱할 포인터 변수 초기화
	Node* CurrentNode = NULL;

	// 그래프 생성
	Graph* graph = CreateGraph();

	// 정점 생성
	Vertex* A = CreateVertex('A');
	Vertex* B = CreateVertex('B');
	Vertex* C = CreateVertex('C');
	Vertex* D = CreateVertex('D');
	Vertex* E = CreateVertex('E');
	Vertex* F = CreateVertex('F');
	Vertex* G = CreateVertex('G');
	Vertex* H = CreateVertex('H');

	// 그래프에 정점 추가
	AddVertex(graph, A);
	AddVertex(graph, B);
	AddVertex(graph, C);
	AddVertex(graph, D);
	AddVertex(graph, E);
	AddVertex(graph, F);
	AddVertex(graph, G);
	AddVertex(graph, H);

	/* 정점과 정점을 간선으로 연결 (p.411 방향성 그래프 형태로 연결) */
	// 간선의 가중치는 0으로 통일
	
	// A 정점에 간선 추가
	AddEdge(A, CreateEdge(A, C, 0));
	AddEdge(A, CreateEdge(A, D, 0));

	// B 정점에 간선 추가
	AddEdge(B, CreateEdge(B, C, 0));
	AddEdge(B, CreateEdge(B, E, 0));

	// C 정점에 간선 추가
	AddEdge(C, CreateEdge(C, F, 0));

	// D 정점에 간선 추가
	AddEdge(D, CreateEdge(D, F, 0));
	AddEdge(D, CreateEdge(D, G, 0));

	// E 정점에 간선 추가
	AddEdge(E, CreateEdge(E, G, 0));

	// F 정점에 간선 추가
	AddEdge(F, CreateEdge(F, H, 0));

	// G 정점에 간선 추가
	AddEdge(G, CreateEdge(G, H, 0));

	// DAG(Directed Acycle Graph) 위상정렬
	TopologicalSort(graph->Vertices, &SortedList);

	// 위상정렬된 링크드리스트 출력
	printf("Topological Sort Result : ");

	// 위상정렬된 링크드리스트의 헤드노드 주소값 할당 
	CurrentNode = SortedList;

	while (CurrentNode != NULL)
	{
		// 현재 순회중인 노드의 정점 데이터 출력
		printf("%c ", CurrentNode->Data->Data);

		// 현재 순회중인 노드 주소값 업데이트
		CurrentNode = CurrentNode->NextNode;
	}
	printf("\n");

	// 위상정렬된 링크드리스트 출력 종료 후, 그래프 메모리 반납
	DestroyGraph(graph);

	return 0;
}
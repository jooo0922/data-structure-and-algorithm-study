#include "MST.h"

// 프림 알고리즘으로 최소 신장 트리 구축
void Prim(Graph* G, Vertex* StartVertex, Graph* MST)
{
	/* 프림 알고리즘에 필요한 데이터 캐싱 */

	int i = 0;

	// 시작 정점을 우선순위 큐에 맨 처음 Enqueue 할 노드로 구현
	PQNode StartNode = { 0, StartVertex };

	// 우선순위 큐 생성
	PriorityQueue* PQ = PQ_Create(10);

	// 그래프의 정점들 순회 시 현재 정점 캐싱
	Vertex* CurrentVertex = NULL;

	// 정점의 간선들 순회 시 현재 간선 캐싱
	Edge* CurrentEdge = NULL;

	// 현재 MST(이하 최소 신장 트리) 에 추가된 정점과 
	// 이를 잇는 Fringes 내의 후보 정점들 사이의 간선들의 가중치를 캐싱하는 동적 배열
	int* Weights = (int*)malloc(sizeof(int) * G->VertexCount);

	// MST 에 추가할 정점 구조체를 새로 만들어서 캐싱해 둘 동적 배열
	Vertex** MSTVertices = (Vertex**)malloc(sizeof(Vertex*) * G->VertexCount);

	// 현재 MST 에 추가된 정점들과 연결되어 있으나, 
	// MST 에는 추가되지 않은 '후보 정점'들을 캐싱해 둘 동적 배열
	Vertex** Fringes = (Vertex**)malloc(sizeof(Vertex*) * G->VertexCount);

	// MST 에 추가될 후보 정점들의 부모 정점(= 이전 정점)들을
	// 후보 정점들의 index 위치에 각각 캐싱해 둘 동적 배열
	Vertex** Precedences = (Vertex**)malloc(sizeof(Vertex*) * G->VertexCount);

	// 그래프 정점 순회를 시작할 첫 번째 정점 주소값 할당
	CurrentVertex = G->Vertices;

	// 그래프 정점들을 순회하며 프림 알고리즘에 필요한 동적 배열들 캐싱
	while (CurrentVertex != NULL)
	{
		// 현재 순회중인 정점과 똑같은 새로운 정점을 만들어 MST 그래프에 추가
		Vertex* NewVertex = CreateVertex(CurrentVertex->Data);
		AddVertex(MST, NewVertex);

		// Fringes 동적 배열 NULL 초기화
		Fringes[i] = NULL;

		// Precedences 동적 배열 NULL 초기화
		Precedences[i] = NULL;

		// MSTVertices 동적 배열을 새로 만든 정점들의 주소값으로 초기화
		MSTVertices[i] = NewVertex;

		// Weights 동적 배열을 최대 가중치 매크로 상수값으로 초기화
		// -> MST 그래프에 추가될 모든 정점들의 가중치가 MAX_WEIGHT 를 넘지 않도록 초기값 할당
		Weights[i] = MAX_WEIGHT;

		// 다음 순회할 정점 캐시 업데이트
		CurrentVertex = CurrentVertex->Next;

		i++;
	}


	/* 우선순위 큐를 활용하여 프림 알고리즘 진행 */


	/* 프림 알고리즘 진행 결과를 바탕으로 MST(최소 신장 트리) 간선 재구축 */


	/* 캐싱에 사용되었던 메모리 반납 */
}

// 크루스칼 알고리즘으로 최소 신장 트리 구축
void Kruskal(Graph* G, Graph* MST)
{

}

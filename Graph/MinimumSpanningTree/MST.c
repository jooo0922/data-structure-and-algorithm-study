#include "MST.h"

// 프림 알고리즘으로 최소 신장 트리 구축
void Prim(Graph* G, Vertex* StartVertex, Graph* MST)
{
	/* 프림 알고리즘에 필요한 데이터 캐싱 */

	int i = 0;

	// MST 에 추가할 시작 정점을 우선순위 큐에 맨 처음 Enqueue 할 노드로 구현
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

	// MST 에 시작 정점으로 추가할 노드를 우선순위 큐에 가장 먼저 Enqueue
	PQ_Enqueue(PQ, StartNode);

	// 시작 정점은 간선이 없으므로, 가중치를 0으로 변경
	Weights[StartVertex->Index] = 0;

	// 우선순위 큐가 비게 될 때까지 프림 알고리즘 반복
	while (!PQ_IsEmpty(PQ))
	{
		// 우선순위 큐에서 Dequeue 한 최솟값 노드를 캐싱해 둘 변수 선언
		PQNode Popped;

		// 프림 알고리즘에서는 우선순위 큐로 후보 정점들을 관리하므로,
		// Dequeue 하면 최소 가중치를 갖는 후보 정점(= 최솟값 노드)을 반환받음.
		PQ_Dequeue(PQ, &Popped);
		CurrentVertex = (Vertex*)Popped.Data;

		// Dequeue 한 최소 가중치 후보 정점을 Fringes 동적 배열에 캐싱
		Fringes[CurrentVertex->Index] = CurrentVertex;

		// Dequeue 한 최소 가중치 정점에 연결된 간선들을 모두 순회
		CurrentEdge = CurrentVertex->AdjacencyList;
		while (CurrentEdge != NULL)
		{
			// 최소 가중치 정점은 이미 MST 에 추가가 확정된 정점이므로,
			// 최소 가중치 정점들의 간선에 연결된 인접 정점은 결국, '새로운 후보 정점!'
			// 따라서, 이 반복문은 '새로운 후보 정점들'에 대해서 순회하고 있는 것임!
			Vertex* TargetVertex = CurrentEdge->Target;

			/*
				새로운 후보 정점을 우선순위 큐에 Enqueue 하기 전,
				두 가지 조건을 먼저 검사해줘야 함.

				1. 해당 후보 정점이 Fringes 에 아직 캐싱되어 있지 않은지

				2. 해당 후보 정점이 이미 다른 간선의 가중치로 이전에 등록되었을 때,
				그 가중치보다 더 작은 간선의 가중치로 업데이트하려는 것인지
				(or 최대 가중치 MAX_WEIGHT 보다 작은 가중치로 업데이트 하려는 것인지)

				이 두 가지 조건을 충족해야만 우선순위 큐에 
				후보 정점을 추가하여 관리할 수 있게 됨.
			
				참고로, 2번 검사 조건이 와닿지 않는다면,
				본문 p.422 에서 B-C-F 정점 사이클 생성 방지하는 과정을 살펴보면 됨.
				이 과정을 코드로 구현한 것이 2번 검사 조건!
			*/
			if (Fringes[TargetVertex->Index] == NULL &&
				CurrentEdge->Weight < Weights[TargetVertex->Index])
			{
				// 새로운 후보 정점을 우선순위 큐에 노드로 만들어 Enqueue
				PQNode NewNode = { CurrentEdge->Weight, TargetVertex };
				PQ_Enqueue(PQ, NewNode);

				// 새로운 후보 정점의 '부모 정점'을 Precedences 동적 배열에 캐싱
				Precedences[TargetVertex->Index] = CurrentEdge->From;

				// 새로운 후보 정점의 '가중치'를 Weights 동적 배열에 캐싱
				Weights[TargetVertex->Index] = CurrentEdge->Weight;
			}

			// 다음 순회할 간선 캐시 업데이트
			CurrentEdge = CurrentEdge->Next;
		}
	}


	/* 프림 알고리즘 진행 결과를 바탕으로 MST(최소 신장 트리) 간선 재구축 */

	// 기존 그래프 정점 개수만큼 반복문 순회
	for (i = 0; i < G->VertexCount; i++)
	{
		int FromIndex, ToIndex;

		// 현재 그래프 정점이 MST 트리 상에서의 부모 정점(= 이전 정점)이 없다면 
		// 간선을 만들 수 없으므로, 다음 순회로 넘어감
		if (Precedences[i] == NULL)
		{
			continue;
		}

		// 현재 그래프 정점의 'MST 트리 상에서의' 부모 정점 인덱스 캐싱
		FromIndex = Precedences[i]->Index;

		// 현재 그래프 정점의 인덱스 캐싱
		ToIndex = i;

		// MST 트리 상의 부모 정점 -> 현재 정점 방향의 간선을 생성한 뒤,
		// MST 트리 상의 부모 정점에 간선을 등록
		AddEdge(MSTVertices[FromIndex],
			CreateEdge(MSTVertices[FromIndex], MSTVertices[ToIndex], Weights[i])
		);

		// 현재 정점 -> MST 트리 상의 부모 정점 방향의 간선을 생성한 뒤,
		// 현재 정점에 간선을 등록
		AddEdge(MSTVertices[ToIndex],
			CreateEdge(MSTVertices[ToIndex], MSTVertices[FromIndex], Weights[i])
		);

		// 위와 같이, 두 정점 사이가 '상호 연결' 되었고, 두 간선의 가중치도 동일하므로,
		// MST 를 방향성이 없는 '무방향성 그래프' 로 구축하려는 것!
	}


	/* 캐싱에 사용되었던 메모리 반납 */
	free(Fringes);
	free(Precedences);
	free(MSTVertices);
	free(Weights);

	PQ_Destroy(PQ);
}


// 크루스칼 알고리즘으로 최소 신장 트리 구축
void Kruskal(Graph* G, Graph* MST)
{
	/* 크루스칼 알고리즘에 사용할 동적 배열 할당 */

	int i;

	// 그래프 정점 순회 시, 현재 정점을 캐싱할 변수 선언
	Vertex* CurrentVertex = NULL;

	// MST 에 추가할 정점 구조체를 새로 만들어서 캐싱해 둘 동적 배열
	Vertex** MSTVertices = (Vertex**)malloc(sizeof(Vertex*) * G->VertexCount);

	// 각 정점을 뿌리노드로 하는 분리집합 구조체를 만들어 캐싱해 둘 동적 배열
	DisjointSet** VertexSet = (DisjointSet**)malloc(sizeof(DisjointSet*) * G->VertexCount);

	// 그래프의 모든 정점들을 가중치 오름차순으로 관리하기 위해 사용할 우선순위 큐 생성
	PriorityQueue* PQ = PQ_Create(10);


	/* 
		1. 그래프의 간선을 가중치 순으로 오름차순 정렬하고,
		2. 각 정점별로 분리집합 구조체를 생성하는 준비 작업 수행 (p.430 - 431)
	*/
	
	i = 0;

	// 순회할 현재 정점 초기화
	CurrentVertex = G->Vertices;

	// 그래프 상의 정점들을 모두 순회
	while (CurrentVertex != NULL)
	{
		// 현재 정점의 간선들을 순회할 때 사용할 캐싱 변수 선언
		Edge* CurrentEdge;

		// 각 정점별로 분리집합 생성 후, 동적 배열에 캐싱
		VertexSet[i] = DS_MakeSet(CurrentVertex);

		// MST(이하 '최소 신장 트리')에 추가할 정점 구조체를 
		// 새롭게 생성하여 MST 그래프에 추가
		MSTVertices[i] = CreateVertex(CurrentVertex->Data);
		AddVertex(MST, MSTVertices[i]);

		// 현재 정점의 간선들을 순회
		CurrentEdge = CurrentVertex->AdjacencyList;
		while (CurrentEdge != NULL)
		{
			// 현재 순회중인 간선을 우선순위 큐에 노드로 만들어 Enqueue
			// -> 우선순위 큐는 힙 자료구조로 구현되어 있어, 가중치 순으로 오름차순 정렬될 것임!
			PQNode NewNode = { CurrentEdge->Weight, CurrentEdge };
			PQ_Enqueue(PQ, NewNode);

			// 다음 순회할 간선 캐시 업데이트
			CurrentEdge = CurrentEdge->Next;
		}

		// 다음 순회할 정점 캐시 업데이트
		CurrentVertex = CurrentVertex->Next;

		i++;
	}


	/* 
		크루스칼 알고리즘 진행
	
		별개의 분리집합에 속하는 두 정점을 간선으로 연결하고,
		각 분리집합을 합집합 수행
	*/

	// 우선순위 큐가 비게 될 때까지 크루스칼 알고리즘 반복
	while (!PQ_IsEmpty(PQ))
	{
		Edge* CurrentEdge;
		int FromIndex;
		int ToIndex;
		PQNode Popped;

		// 가중치 오름차순으로 정렬된 우선순위 큐에서
		// 가중치가 가장 낮은 간선부터 Dequeue (p.431 참고)
		PQ_Dequeue(PQ, &Popped);
		CurrentEdge = (Edge*)Popped.Data;

		// Dequeue 된 간선의 시작 정점, 끝 정점, 가중치 출력
		printf("%c - %c : %d\n",
			CurrentEdge->From->Data,
			CurrentEdge->Target->Data,
			CurrentEdge->Weight);

		// 간선의 시작 정점 인덱스 캐싱
		FromIndex = CurrentEdge->From->Index;

		// 간선의 끝 정점 인덱스 캐싱
		ToIndex = CurrentEdge->Target->Index;

		// 간선의 양 끝 정점이 서로 다른 분리집합에 속하는 지 검사
		// (p.429 > 사이클이 생기지 않기 위한 조건을 검사하는 부분을 코드로 구현)
		if (DS_FindSet(VertexSet[FromIndex]) != DS_FindSet(VertexSet[ToIndex]))
		{
			// 별개의 분리집합에 속하는 두 정점을 간선으로 연결
			
			// 간선의 시작 정점 -> 끝 정점 방향의 간선 생성 후, 시작 정점에 추가
			AddEdge(MSTVertices[FromIndex],
				CreateEdge(MSTVertices[FromIndex], MSTVertices[ToIndex], CurrentEdge->Weight)
			);

			// 간선의 끝 정점 -> 시작 정점 방향의 간선 생성 후, 끝 정점에 추가
			AddEdge(MSTVertices[ToIndex],
				CreateEdge(MSTVertices[ToIndex], MSTVertices[FromIndex], CurrentEdge->Weight)
			);

			// 위와 같이, 두 정점 사이가 '상호 연결' 되었고, 두 간선의 가중치도 동일하므로,
			// MST 를 방향성이 없는 '무방향성 그래프' 로 구축하려는 것!

			// 간선으로 연결한 두 정점이 속한 분리집합을 항상 '합집합'으로 합치기
			DS_UnionSet(VertexSet[FromIndex], VertexSet[ToIndex]);
		}
	}
}

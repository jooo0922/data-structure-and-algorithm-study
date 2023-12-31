#include "GraphTraversal.h"

// 깊이 우선 탐색
void DFS(Vertex* V)
{
	// 간선 구조체를 캐싱할 포인터 변수 초기화
	Edge* E = NULL; 

	// 현재 방문한 정점 데이터 출력
	printf("%d ", V->Data);

	// 현재 방문한 정점을 '방문했음' 표시
	V->Visited = Visited;

	// 현재 방문한 정점의 인접 정점들의 리스트 (정확히는, 간선들의 리스트) 캐싱
	E = V->AdjacencyList;

	// 현재 방문한 정점의 인접 정점들(간선들)을 순회함
	while (E != NULL)
	{
		// 인접 정점(== 간선의 끝점(E->Target))을 아직 방문하지 않은 경우, 깊이 우선 탐색을 재귀 호출함
		if (E->Target != NULL && E->Target->Visited == NotVisited)
		{
			DFS(E->Target);
		}

		// 다음 인접 정점을 순회하기 위해 캐싱된 간선을 업데이트함.
		E = E->Next;
	}
}

// 너비 우선 탐색
void BFS(Vertex* V, LinkedQueue* Queue)
{
	// 간선 구조체를 캐싱할 포인터 변수 초기화
	Edge* E = NULL;

	// 그래프의 시작 정점 데이터 출력
	printf("%d ", V->Data);

	// 그래프의 시작 정점을 '방문했음' 표시
	V->Visited = Visited;

	// 방문한 정점(== 그래프의 시작 정점)을 큐에 삽입(Enqueue)
	LQ_Enqueue(Queue, LQ_CreateNode(V));

	// 큐가 비게 될 때까지 큐의 전단을 Dequeue 하며 순회
	while (!LQ_IsEmpty(Queue))
	{
		// 큐의 현재 전단을 Dequeue 후 임시 변수에 캐싱
		Node* Popped = LQ_Dequeue(Queue);

		// Dequeue 된 전단에 할당되어 있는 정점 구조체(Vertex) 캐싱
		V = Popped->Data;

		// Dequeue 된 전단에 할당되어 있는 정점의 간선 리스트 주소값 캐싱
		E = V->AdjacencyList;

		// Dequeue 된 전단의 간선 리스트를 순회하며 인접 정점들의 방문 여부 검사
		while (E != NULL)
		{
			// Dequeue 된 전단에 할당되어 있는 정점의 인접 정점 캐싱
			V = E->Target;

			// 인접 정점이 방문되어 있지 않은 경우 처리
			if (V != NULL && V->Visited == NotVisited)
			{
				// 미방문 인접 정점의 데이터 출력
				printf("%d ", V->Data);

				// 미방문 인접 정점을 '방문했음' 표시
				V->Visited = Visited;

				// 방문한 정점(== 인접 정점)을 큐에 삽입(Enqueue)
				LQ_Enqueue(Queue, LQ_CreateNode(V));
			}

			// 다음 인접 정점으로 순회하여 방문여부 검사를 위해,
			// 순회중인 간선 업데이트
			E = E->Next;
		}
	}
}
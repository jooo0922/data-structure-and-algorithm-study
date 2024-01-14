#ifndef GRAPH_H
#define GRAPH_H
/*
	여기서 사용된 #ifndef ~ #endif 전처리기는
	헤더파일의 헤더가드를 처리해주는 방법 중 하나였지?

	cpp-study > TBCppStudy > Chapter1_12 > add.h 필기 참고!
*/

#include <stdio.h> // printf(), scanf() 같은 입출력 함수 선언이 포함된 헤더파일
#include <stdlib.h> // malloc(), free() 같은 메모리 할당 함수 선언이 포함된 헤더파일
// -> 헤더파일에 포함되어 있어야, 이를 가져다 쓰는 .c 파일들에서 사용할 때 에러가 안남.

// 그래프의 정점 방문 여부를 enum 으로 정의
enum VisitMode
{
	Visited,
	NotVisited
};

// 그래프의 정점 데이터 타입을 별칭으로 선언
typedef int VElementType;

// 그래프의 정점 구조체 타입을 별칭으로 선언
typedef struct tagVertex
{
	VElementType Data; // 정점에 담을 데이터
	int Visited; // 정점 방문 여부 (그래프 순회 알고리즘(DFS, BFS)에서 사용)
	int Index; // 정점의 인덱스 (최단 경로 탐색 알고리즘에서 사용)
	
	struct tagVertex* Next; // 다음 정점 포인터 ('리스트 자료구조 상에서의' 다음 정점을 의미함. 실제 해당 정점에 연결된 '경로 상의 다음 정점'이 아님을 명심!)
	struct tagEdge* AdjacencyList; // 인접 정점 리스트 포인터 (정확히는, 해당 정점에 연결된 '간선(Edge)' 구조체들의 리스트들 중에서 맨 첫 번째 간선의 주소값이 담긴 포인터!)
} Vertex;

// 그래프의 간선 구조체 타입을 별칭으로 선언
typedef struct tagEdge
{
	int Weight; // 정점 사이(간선)의 거리, 비용 (최소 신장 트리, 최단 경로 탐색 알고리즘에서 사용)
	struct tagEdge* Next; // 다음 간선 포인터 ('리스트 자료구조 상에서의' 다음 간선을 의미함. 실제 그래프의 '경로 상의 다음 간선'이 아님을 명심!)
	Vertex* From; // 간선의 시작 정점 포인터
	Vertex* Target; // 간선의 끝 정점 포인터
} Edge;

// 그래프 구조체 타입을 별칭으로 선언
typedef struct tagGraph
{
	Vertex* Vertices; // 그래프 상의 전체 정점 리스트 포인터 (정확히는, 그래프 상의 전체 정점들 중 맨 첫 번째 정점의 주소값이 담긴 포인터!)
	int VertexCount; // 그래프 상의 전체 정점 개수
} Graph;

Graph* CreateGraph(); // 그래프 구조체 생성
void DestroyGraph(Graph* G); // 그래프 구조체 메모리 해제

Vertex* CreateVertex(VElementType Data); // 정점 구조체 생성
void DestroyVertex(Vertex* V); // 정점 구조체 메모리 해제

Edge* CreateEdge(Vertex* From, Vertex* Target, int Weight); // 간선 구조체 생성
void DestroyEdge(Edge* E); // 간선 구조체 메모리 해제

void AddVertex(Graph* G, Vertex* V); // 그래프 구조체의 정점 리스트에 새로운 정점 삽입
void AddEdge(Vertex* V, Edge* E); // 정점 구조체의 간선 리스트(== 인접 정점 리스트)에 새로운 간선 삽입
void PrintGraph(Graph* G); // 그래프 출력

#endif // !GRAPH_H

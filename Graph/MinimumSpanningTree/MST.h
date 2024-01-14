#ifndef MST_H
#define MST_H
/*
	여기서 사용된 #ifndef ~ #endif 전처리기는
	헤더파일의 헤더가드를 처리해주는 방법 중 하나였지?

	cpp-study > TBCppStudy > Chapter1_12 > add.h 필기 참고!
*/

#include "Graph.h" // 그래프 구조체 표현을 위해 포함
#include "PriorityQueue.h" // 우선순위 큐 사용을 위해 포함
#include "DisjointSet.h" // 분리집합 구조 사용을 위해 포함

#define MAX_WEIGHT 36267 // 매크로 전처리기로 최대 가중치값을 매크로 상수로 정의

void Prim(Graph* G, Vertex* StartVertex, Graph* MST); // 프림 알고리즘으로 최소 신장 트리 구축
void Kruskal(Graph* G, Graph* MST); // 크루스칼 알고리즘으로 최소 신장 트리 구축

#endif // !MST_H

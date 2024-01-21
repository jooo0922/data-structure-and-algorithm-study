#ifndef SHORTESTPATH_H
#define SHORTESTPATH_H
/*
	여기서 사용된 #ifndef ~ #endif 전처리기는
	헤더파일의 헤더가드를 처리해주는 방법 중 하나였지?

	cpp-study > TBCppStudy > Chapter1_12 > add.h 필기 참고!
*/

#include "Graph.h" // 그래프 구조체 표현을 위해 포함
#include "PriorityQueue.h" // 우선순위 큐 사용을 위해 포함

// 매크로 전처리기로 시작 정점에서 각 정점까지의 초기 경로 길이(무한대)를 
// 매크로 상수로 정의
#define MAX_WEIGHT 36267

// 데이크스트라 알고리즘으로 최단 경로 그래프 구축
void Dijkstra(Graph* G, Vertex* StartVertex, Graph* MST);

#endif // !SHORTESTPATH_H

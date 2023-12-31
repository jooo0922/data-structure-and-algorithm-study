#ifndef GRAPH_TRAVERSAL_H
#define GRAPH_TRAVERSAL_H
/*
	여기서 사용된 #ifndef ~ #endif 전처리기는
	헤더파일의 헤더가드를 처리해주는 방법 중 하나였지?

	cpp-study > TBCppStudy > Chapter1_12 > add.h 필기 참고!
*/

#include "Graph.h" // 그래프 자료구조 포함
#include "LinkedQueue.h" // 링크드 큐 자료구조 포함

void DFS(Vertex* V); // 깊이 우선 탐색
void BFS(Vertex* V, LinkedQueue* Queue); // 너비 우선 탐색

#endif // !GRAPH_TRAVERSAL_H

#include "Graph.h" // 그래프 구조체 표현을 위해 포함
#include "LinkedList.h" // 위상정렬한 결과를 저장할 링크드 리스트 사용을 위해 포함

#ifndef TOPOLOGICALSORT_H
#define TOPOLOGICALSORT_H
/*
	여기서 사용된 #ifndef ~ #endif 전처리기는
	헤더파일의 헤더가드를 처리해주는 방법 중 하나였지?

	cpp-study > TBCppStudy > Chapter1_12 > add.h 필기 참고!
*/

void TopologicalSort(Vertex* V, Node** List); // DGA(Directed Acycle Graph) 위상정렬
void TS_DFS(Vertex* V, Node** List); // 깊이 우선 탐색 및 리스트에 헤드노드 추가

#endif // !TOPOLOGICALSORT_H

#include "PriorityQueue.h"

// 우선순위 큐 노드 출력 함수
void PrintNode(PQNode* Node)
{
	printf("Task : %s (Priority:%d)\n", Node->Data, Node->Priority);
}

int main()
{
	// 노드 배열 초기 용량을 3개로 설정하여 우선순위 큐 구조체 생성
	PriorityQueue* PQ = PQ_Create(3);

	// 우선순위 큐에서 제거(Dequeue)된 최솟값 노드(= 뿌리노드)가 저장될 포인터 변수 선언
	PQNode Popped;

	char* str1 = "coding";
	char* str2 = "meeting";
	char* str3 = "coffee making";
	char* str4 = "paper work";
	char* str5 = "debugging";
	char* str6 = "brushing teeth";

	// PQNode 타입 노드 정적 배열 생성
	PQNode Nodes[6] = {
		{ 34, (void*)str1 },
		{ 12, (void*)str2 },
		{ 87, (void*)str3 },
		{ 45, (void*)str4 },
		{ 35, (void*)str5 },
		{ 66, (void*)str6 }
	};

	// 우선순위 큐에 정적 배열에 담긴 노드들을 순서대로 추가(Enqueue)
	PQ_Enqueue(PQ, Nodes[0]);
	PQ_Enqueue(PQ, Nodes[1]);
	PQ_Enqueue(PQ, Nodes[2]);
	PQ_Enqueue(PQ, Nodes[3]);
	PQ_Enqueue(PQ, Nodes[4]);
	PQ_Enqueue(PQ, Nodes[5]);

	// 우선순위 큐에 삽입된 노드 배열 개수 출력
	printf("Tasks Left : %d\n", PQ->UsedSize);

	while (!PQ_IsEmpty(PQ))
	{
		// 우선순위 큐가 비게 될 때까지 최솟값 노드 Dequeue 후 출력
		PQ_Dequeue(PQ, &Popped);
		PrintNode(&Popped);
	}

	return 0;
}
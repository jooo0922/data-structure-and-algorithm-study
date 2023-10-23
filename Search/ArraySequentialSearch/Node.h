// 노드에 들어갈 데이터 타입. 여기서는 정수형으로 임의로 정함.
typedef int ElementType;

// 노드 구조체 선언 (struct 키워드 생략하고 사용하기 위해 typedef 로 구조체 별칭 선언)
typedef struct tagNode
{
	ElementType Data; // 노드에 들어갈 데이터
	int FrequencyCount; // 노드 탐색 횟수
} Node;

Node NodeSet[] = {
	{6, 0},
	{4, 0},
	{2, 0},
	{3, 0},
	{1, 0},
	{5, 0},
};
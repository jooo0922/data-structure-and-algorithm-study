#include "MakingChange.h"

// 입력받은 동전 단위들을 내림차순으로 정렬할 때 사용할 비교함수
int Compare(const void* a, const void* b)
{
	// 매개변수 a, b 를 각각 int* 타입의 포인터 변수로 형변환한 후, de-referencing 하여 int 값을 복사
	int _a = *(int*)a;
	int _b = *(int*)b;

	if (_a < _b)
	{
		return 1;
	}
	else
	{
		return -1;
	}
}
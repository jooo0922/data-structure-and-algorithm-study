#include "SimpleHashTable.h"

int main()
{
	// 해시 테이블 구조체 생성
	// (참고로, 해시 테이블 크기는 2의 제곱수와 거리가 먼 소수를 사용할수록 좋은 성능을 보임. p.338 참고!)
	HashTable* HT = SHT_CreateHashTable(193);

	// 해시 테이블 구조체에 노드 추가
	SHT_Set(HT, 418, 32114);
	SHT_Set(HT, 9, 514);
	SHT_Set(HT, 27, 8917);
	SHT_Set(HT, 1031, 286);

	// Key 값으로 해시 테이블에 추가된 노드 검색 및 출력
	printf("Key:%d, Value:%d\n", 418, SHT_Get(HT, 418));
	printf("Key:%d, Value:%d\n", 9, SHT_Get(HT, 9));
	printf("Key:%d, Value:%d\n", 27, SHT_Get(HT, 27));
	printf("Key:%d, Value:%d\n", 1031, SHT_Get(HT, 1031));

	// 해시 테이블 구조체 메모리 해제
	SHT_DestroyHashTable(HT);

	return 0;
}
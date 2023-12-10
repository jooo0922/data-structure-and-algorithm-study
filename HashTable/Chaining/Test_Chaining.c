#include "Chaining.h"

int main()
{
	// 체이닝 기반 해시테이블 생성
	// 테이블 크기는 12289개로 생성 -> 해시값을 최대 14 bits 이진수로 표현 가능
	// (p. 345 참고)
	HashTable* HT = CHT_CreateHashTable(12289);

	// 체이닝 기반 해시테이블에 노드 삽입
	CHT_Set(HT, "MSFT", "Microsoft Corporation");
	CHT_Set(HT, "JAVA", "Sun Microsystems");
	CHT_Set(HT, "REDH", "Red Hat Linux");
	CHT_Set(HT, "APAC", "Apache Org");
	CHT_Set(HT, "ZYMZZ", "Unisys Ops Check"); // "APAC" Key 값과 해시값 충돌 
	CHT_Set(HT, "IBM", "IBM Ltd.");
	CHT_Set(HT, "ORCL", "Oracle Corporation");
	CHT_Set(HT, "CSCO", "Cisco Systems, Inc.");
	CHT_Set(HT, "GOOG", "Google Inc.");
	CHT_Set(HT, "YHOO", "Yahoo! Inc.");
	CHT_Set(HT, "NOVL", "Novell, Inc.");

	// 해시테이블에 추가한 노드들을 탐색하여 출력
	printf("\n");
	printf("Key:%s, Value:%s\n", "MSFT", CHT_Get(HT, "MSFT"));
	printf("Key:%s, Value:%s\n", "REDH", CHT_Get(HT, "REDH"));
	printf("Key:%s, Value:%s\n", "APAC", CHT_Get(HT, "APAC"));
	printf("Key:%s, Value:%s\n", "ZYMZZ", CHT_Get(HT, "ZYMZZ"));
	printf("Key:%s, Value:%s\n", "JAVA", CHT_Get(HT, "JAVA"));
	printf("Key:%s, Value:%s\n", "IBM", CHT_Get(HT, "IBM"));
	printf("Key:%s, Value:%s\n", "ORCL", CHT_Get(HT, "ORCL"));
	printf("Key:%s, Value:%s\n", "CSCO", CHT_Get(HT, "CSCO"));
	printf("Key:%s, Value:%s\n", "GOOG", CHT_Get(HT, "GOOG"));
	printf("Key:%s, Value:%s\n", "YHOO", CHT_Get(HT, "YHOO"));
	printf("Key:%s, Value:%s\n", "NOVL", CHT_Get(HT, "NOVL"));

	// 해시테이블 메모리 해제
	CHT_DestroyHashTable(HT);

	return 0;
}
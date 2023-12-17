#include "HashTableDisjointSet.h"

int main()
{
	// 개방 주소법 기반 해시테이블 생성. 테이블 크기는 11개로 생성
	HashTable* HT = HTDS_CreateHashTable(11);

	// 해시테이블에 요소 삽입
	// 각 분리집합의 뿌리노드 삽입
	HTDS_Set(&HT, "MSFT", "MSFT", "Microsoft Corporation");
	HTDS_Set(&HT, "JAVA", "JAVA", "Sun Microsystems");
	HTDS_Set(&HT, "REDH", "REDH", "Red Hat Linux");

	// 각 분리집합의 요소 삽입
	HTDS_Set(&HT, "MSFT", "APAC", "Apache Org");
	HTDS_Set(&HT, "MSFT", "ZYMZZ", "Unisys Ops Check"); // "APAC" Key 값과 해시값 충돌 
	HTDS_Set(&HT, "MSFT", "IBM", "IBM Ltd.");
	HTDS_Set(&HT, "JAVA", "ORCL", "Oracle Corporation");
	HTDS_Set(&HT, "JAVA", "CSCO", "Cisco Systems, Inc.");
	HTDS_Set(&HT, "JAVA", "GOOG", "Google Inc.");
	HTDS_Set(&HT, "REDH", "YHOO", "Yahoo! Inc.");
	HTDS_Set(&HT, "REDH", "NOVL", "Novell, Inc.");

	// "MSFT" 요소와 "APAC" 요소가 같은 분리집합에 속해있는지 확인
	printf("MSFT == APAC : %d \n", strcmp(HTDS_FindSet(HT, "MSFT"), HTDS_FindSet(HT, "APAC")) == 0);

	// "CSCO" 요소와 "YHOO" 요소가 같은 분리집합에 속해있는지 확인
	printf("CSCO == YHOO : %d \n", strcmp(HTDS_FindSet(HT, "CSCO"), HTDS_FindSet(HT, "YHOO")) == 0);

	// "JAVA" 분리집합과 "REDH" 분리집합 합집합
	HTDS_UnionSet(HT, "JAVA", "REDH");

	// 합집합 연산 후, "CSCO" 요소와 "YHOO" 요소가 같은 분리집합에 속해있는지 다시 확인
	printf("CSCO == YHOO : %d \n", strcmp(HTDS_FindSet(HT, "CSCO"), HTDS_FindSet(HT, "YHOO")) == 0);

	return 0;
}
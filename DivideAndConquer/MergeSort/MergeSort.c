#include <stdio.h> // printf(), scanf() 같은 입출력 함수 선언이 포함된 헤더파일
#include <stdlib.h> // malloc(), free() 같은 함수 선언이 포함된 헤더파일

// 병합정렬 함수
void MergeSort(int DataSet[], int StartIndex, int EndIndex);

// 분할된 두 하위 데이터를 '정렬하며 합치기' (본문 p.527 ~ p.529 과정을 코드로 구현)
void Merge(int DataSet[], int StartIndex, int MiddleIndex, int EndIndex);
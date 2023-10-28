#include <stdlib.h> // qsort() 퀵 정렬 함수를 사용하기 위해 포함
#include <stdio.h>

#include "Point.h"

// 구매포인트 데이터를 오름차순으로 정렬하는 비교함수 선언 및 구현
int ComparePoint(const void* _elem1, const void* _elem2)
{
    // 두 void* 타입의 주소값을 Point* 타입으로 형변환하여 Point* 타입 포인터 변수에 복사
    Point* elem1 = (Point*)_elem1;
    Point* elem2 = (Point*)_elem2;

    // 두 포인터 변수를 de-referencing 하여 두 Point 구조체의 point 멤버의 값 크기를 비교함
    if (elem1->point > elem2->point)
    {
        // 첫 번째 요소가 두 번째 요소보다 크면 1 반환
        return 1;
    }
    else if (elem1->point < elem2->point)
    {
        // 첫 번째 요소가 두 번째 요소보다 작다면 -1 반환
        return -1;
    }
    else
    {
        // 첫 번째 요소와 두 번째 요소가 같다면 0을 반환
        return 0;
    }
}

int main()
{
    return 0;
}
#include <stdlib.h> // qsort() 퀵 정렬 함수를 사용하기 위해 포함
#include <stdio.h>
#include <string.h>

#include "Point.h"

// 내림차순으로 정렬하는 비교함수 선언 및 구현
int ComparePointDescend(const void* _elem1, const void* _elem2)
{
    // 두 void* 타입의 주소값을 Point* 타입으로 형변환하여 Point* 타입 포인터 변수에 복사
    Point* elem1 = (Point*)_elem1;
    Point* elem2 = (Point*)_elem2;

    // 두 포인터 변수를 de-referencing 하여 두 Point 구조체의 point 멤버의 값 크기를 비교함
    if (elem1->point > elem2->point)
    {
        // 첫 번째 요소가 두 번째 요소보다 크면 오름차순과 반대로 -1 반환
        return -1;
    }
    else if (elem1->point < elem2->point)
    {
        // 첫 번째 요소가 두 번째 요소보다 작다면 오름차순과 반대로 1 반환
        return 1;
    }
    else
    {
        // 첫 번째 요소와 두 번째 요소가 같다면 0을 반환
        return 0;
    }
}

int main()
{
    int Length = sizeof DataSet / sizeof DataSet[0]; // 정적 배열 길이 계산하여 저장
    int i = 0; // 퀵 정렬 결과를 확인할 때 for loop 에서 사용할 인덱스 변수 초기화

    // c언어 표준 라이브러리 qsort() 을 사용한 퀵 정렬 수행 (내림차순 정렬)
    qsort((void*)DataSet, Length, sizeof(Point), ComparePointDescend);

    // qsort() 를 사용한 퀵 정렬 결과 출력
    /*for (i = 0; i < Length; i++)
    {
        printf("%f\n", DataSet[i].point);
    }*/

    // 구매포인트 내림차순으로 14,142번째 고객의 ID 와 구매포인트 출력
    printf("14,142th Customer's ID : %d\n", DataSet[14142].id);
    printf("14,142th Customer's purchase points : %f\n", DataSet[14142].point);

    return 0;
}
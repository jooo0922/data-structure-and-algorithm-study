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
    int Length = sizeof DataSet / sizeof DataSet[0]; // 정적 배열 길이 계산하여 저장
    Point target; // 목표값을 저장할 Point 구조체 변수 선언
    Point* found = NULL; // 이진탐색으로 찾은 결과값의 주소를 저장할 포인터 변수

    // 구매포인트에 대해 qsort() 를 사용하여 퀵 정렬 수행 (오름차순 정렬)
    qsort((void*)DataSet, Length, sizeof(Point), ComparePoint);

    // 구매포인트가 671.78 점인 고객을 찾기 위해 목표값 초기화
    target.id = 0;
    target.point = 671.78;

    // C 표준 라이브러리의 이진탐색 함수 bsearch() 를 사용하여 이진탐색 수행
    found = bsearch(
        (void*)&target, // 목표값이 초기화된 Point 구조체 주소값을 void* 타입으로 캐스팅하여 전달
        (void*)DataSet, // 데이터 배열 주소값을 void* 타입으로 캐스팅하여 전달
        Length, // 데이터 개수
        sizeof(Point), // 데이터 하나의 크기 (바이트 단위)
        ComparePoint // 오름차순 비교함수의 함수 포인터
    );

    // 이진탐색으로 찾은 고객 데이터 출력
    printf("found... ID: %d, Point: %f \n", found->id, found->point);

    return 0;
}
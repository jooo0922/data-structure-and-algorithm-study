#include <stdlib.h> // qsort() 퀵 정렬 함수를 사용하기 위해 포함
#include <stdio.h>
#include <string.h>

// qsort() 함수에 전달할 비교함수 선언 및 구현
// 두 개의 const 포인트 변수 -> 입력 매개변수
int ComparePoint(const void* _elem1, const void* _elem2)
{
    // 두 void* 타입의 주소값을 int* 타입으로 형변환하여 int* 타입 포인터 변수에 복사
    int* elem1 = (int*)_elem1;
    int* elem2 = (int*)_elem2;
    
    // 두 포인터 변수를 de-referencing 하여 두 정수 타입의 크기를 비교함
    if (*elem1 > *elem2)
    {
        // 첫 번째 요소가 두 번째 요소보다 크면 1을 반환
        return 1;
    }
    else if (*elem1 < elem2)
    {
        // 첫 번째 요소가 두 번째 요소보다 작다면 -1을 반환
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

/*
    std::qsort() 비교함수

    참고로, qsort() 에 전달하는 비교함수 ComparePoint() 는
    JS sort() 함수와 정확히 동일한 기능을 하는 함수임!

    그래서, 위 비교함수는
    정수 타입의 배열을 '오름차순' 정렬하는 비교함수라고 보면 됨.

    자세한 내용은
    https://developer.mozilla.org/ko/docs/Web/JavaScript/Reference/Global_Objects/Array/sort 참고
*/
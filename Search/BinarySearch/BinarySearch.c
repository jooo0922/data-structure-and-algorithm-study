#include <stdlib.h> // qsort() 퀵 정렬 함수를 사용하기 위해 포함
#include <stdio.h>

#include "Point.h"

// 이진탐색 함수
Point* BinarySearch(Point PointList[], int Size, double Target)
{
    // 매 반복 순회마다 갱신할 탐색 범위 왼쪽 끝, 중앙, 오른쪽 끝 요소 인덱스
    int Left, Right, Mid;

    // 탐색 범위의 양쪽 끝 요소 인덱스 초기화
    Left = 0;
    Right = Size - 1;

    // 양쪽 끝 요소 인덱스가 같아지면 탐색 범위는 0개가 됨 -> 탐색 종료
    while (Left <= Right)
    {
        // 중앙 요소 인덱스 계산
        Mid = (Left + Right) / 2;

        if (Target == PointList[Mid].point)
        {
            // 탐색 범위의 중앙 요소와 목표값이 일치할 경우, 
            // 해당 요소의 주소값 반환하며 탐색 종료
            return &(PointList[Mid]);
        }
        else if (Target > PointList[Mid].point)
        {
            // 탐색 범위의 중앙 요소보다 목표값이 더 크다면,
            // 왼쪽 끝 요소의 인덱스를 이동시켜 다음 탐색 범위를 중앙 요소 기준 우측으로 좁힘
            Left = Mid + 1;
        }
        else
        {
            // 탐색 범위의 중앙 요소보다 목표값이 더 작다면,
            // 오른쪽 끝 요소의 인덱스를 이동시켜 다음 탐색 범위를 중앙 요소 기준 좌측으로 좁힘
            Right = Mid - 1;
        }
    }

    return NULL;
}

int main()
{
    return 0;
}
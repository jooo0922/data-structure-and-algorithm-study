#include <stdio.h>

// 배열내의 두 요소 주소값을 받아 서로의 위치를 맞교환하는 함수
void Swap(int* A, int* B)
{

}

// 주어진 그룹(DataSet)을 첫 번째 요소를 기준 요소로 삼아 왼쪽 / 오른쪽 그룹으로 분할하는 함수
// Left 는 왼쪽 정찰병 위치, Right 는 오른쪽 정찰병 위치
int Partition(int DataSet[], int Left, int Right)
{

}

// 퀵 정렬 함수 구현
void QuickSort(int DataSet[], int Left, int Right)
{

}

int main()
{
    int DataSet[] = { 6, 4, 2, 3, 1, 5 }; // 퀵 정렬할 정적 배열 선언 및 초기화
    int Length = sizeof DataSet / sizeof DataSet[0]; // 정적 배열 길이 계산하여 저장
    int i = 0; // 퀵 정렬 결과를 확인할 때 for loop 에서 사용할 인덱스 변수 초기화

    QuickSort(DataSet, 0, Length - 1);

    // 퀵 정렬 결과 출력
    for (i = 0; i < Length; i++)
    {
        printf("%d ", DataSet[i]);
    }

    printf("\n");

    return 0;
}
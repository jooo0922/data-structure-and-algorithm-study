#include <stdio.h>

// 배열내의 두 요소 주소값을 받아 서로의 위치를 맞교환하는 함수
void Swap(int* A, int* B)
{
    int Temp = *A; // de-referencing 으로 포인터 변수 A 가 가리키는 메모리 공간의 값을 임시 복사하여 저장
    *A = *B; // A가 가리키는 메모리 공간의 값을 B가 가리키는 메모리 공간의 값으로 덮어씀.
    *B = Temp; // B가 가리키는 메모리 공간의 값을 맨 처음에 복사해 둔 값으로 덮어씀.
}

int GetPivot(int DataSet[], int Left, int Right)
{
    int mid = (int)(Left + (Right - Left) / 2); // 두 정찰병 사이의 가운데 인덱스 계산

    // 왼쪽, 가운데, 오른쪽 인덱스가 가리키는 요소 저장
    int a = DataSet[Left];
    int b = DataSet[mid];
    int c = DataSet[Right];

    if ((a - b) * (c - a) >= 0)
    {
        // a, b, c 의 대소관계를 비교한 결과, c > a > b 이거나, b > a > c 라면, 
        // 즉, 가운데 요소가 가장 크거나 작다면, 두 정찰병 사이의 정렬범위는 아직 정렬되지 않은 것이므로,
        // 원래대로 맨 왼쪽 정찰병을 기준 요소로 반환함.
        return Left;
    } 
    else if ((b - a) * (c - b) >= 0)
    {
        // a, b, c 의 대소관계를 비교한 결과, c > b > a 이거나, a > b > c 라면,
        // 즉, 세 요소가 이미 정렬 또는 역순정렬 되어있을 가능성이 높으므로,
        // 가운데 인덱스를 기준요소로 반환하여 최악의 경우를 피함
    }
    else
    {
        // 위에 해당되지 않는 나머지 케이스는 맨 오른쪽 정찰병을 기준요소로 반환함. 
        return Right;
    }
}

// 주어진 그룹(DataSet)을 첫 번째 요소를 기준 요소로 삼아 왼쪽 / 오른쪽 그룹으로 분할하는 함수
// Left 는 왼쪽 정찰병 위치, Right 는 오른쪽 정찰병 위치
int Partition(int DataSet[], int Left, int Right)
{
    int First = Left; // 맨 왼쪽 정찰병의 초기 위치 = 그룹의 첫 번째 요소 위치
    int Pivot = GetPivot(DataSet, Left, Right); // 현재 정렬범위의 순서에 따라 기준요소 반환

    ++Left; // 왼쪽 정찰병의 시작 위치를 첫 번째 요소 다음 요소부터 시작하도록 지정

    // 왼쪽 정찰병(Left)와 오른쪽 정찰병(Right)이 접선할 때까지 그룹 요소를 순회
    while (Left <= Right)
    {
        // 왼쪽 정찰병이 기준요소보다 큰 요소를 발견할 때까지 왼쪽 정찰병 위치(Left) 이동
        while (DataSet[Left] <= Pivot && Left < Right)
        {
            ++Left;
        }

        // 오른쪽 정찰병이 기즌요소보다 작은 요소를 발견할 때까지 오른쪽 정찰병 위치(Right) 이동
        while (DataSet[Right] >= Pivot && Left <= Right)
        {
            --Right;
        }

        if (Left < Right)
        {
            // 두 정찰병이 아직 접선(cross)하지 않은 상태이면,
            // 두 정찰병이 찾은 기준요소보다 큰 요소와 작은 요소를 맞교환함
            Swap(&DataSet[Left], &DataSet[Right]);
        }
        else
        {
            // 두 정찰병이 접선한 상태 (Left >= Right) 이므로, 현재 그룹분할 종료
            break;
        }
    }

    // 그룹분할 종료 후, 기준요소인 첫 번째 요소와 왼쪽 그룹의 마지막 요소의 위치 맞교환
    // 참고로, 현재 Left >= Right 상태이므로, 왼쪽 그룹의 마지막 요소 위치는 Right 에 저장되어 있음! 
    Swap(&DataSet[First], &DataSet[Right]);

    // 새로운 기준이 될 요소 위치 반환
    return Right;
}

// 퀵 정렬 함수 구현
void QuickSort(int DataSet[], int Left, int Right)
{
    // 그룹의 오른쪽 정찰병 위치가 왼쪽 정찰병 위치보다 크다 == 전달받은 그룹의 크기가 1보다는 크다!
    // -> 그룹의 크기가 1보다 클 때에만 분할을 수행할 수 있댔지?
    if (Left < Right)
    {
        // 그룹을 분할하고, 분할 기준요소의 위치를 반환받아 저장해 둠.
        int Index = Partition(DataSet, Left, Right);

        /*
            분할 기준요소 위치,
            하위 그룹의 정렬범위를 결정짓는 두 정찰병 위치(Left, Right)를
            매개변수로 전달함으로써,

            현재 그룹에서 분할 기준요소 Index 를 기준으로 나눠진
            왼쪽 그룹과 오른쪽 그룹에 대해서 다시 재귀적으로 분할을 수행함.

            QuickSort() 함수를 재귀적으로 호출함으로써,
            Partition() 함수에 의해 그룹이 재귀적으로 분할됨.
        */
        QuickSort(DataSet, Left, Index - 1); // 기준요소의 왼쪽 그룹을 재귀적으로 분할
        QuickSort(DataSet, Index + 1, Right); // 기준요소의 오른쪽 그룹을 재귀적으로 분할
    }
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
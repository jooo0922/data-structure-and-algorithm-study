#include <stdio.h>

// 배열내의 두 요소 주소값을 받아 서로의 위치를 맞교환하는 함수
void Swap(int* A, int* B)
{
    int Temp = *A; // de-referencing 으로 포인터 변수 A 가 가리키는 메모리 공간의 값을 임시 복사하여 저장
    *A = *B; // A가 가리키는 메모리 공간의 값을 B가 가리키는 메모리 공간의 값으로 덮어씀.
    *B = Temp; // B가 가리키는 메모리 공간의 값을 맨 처음에 복사해 둔 값으로 덮어씀.
}

int getMedian(int Left, int Right, int Mid)
{
    // 정렬범위의 왼쪽, 오른쪽, 가운데 위치값의 대소관계를 비교해서,
    // 세 위치값 중 가운데에 있는 위치값을 반환함.
    if (Right >= Left && Left >= Mid)
    {
        // Right >= Left >= Mid
        // 위 부등식에서 Left 가 가운데에 있지? 따라서 가운데 위치값 Left 반환.
        return Left;
    }
    else if (Left >= Right && Right >= Mid)
    {
        // Left >= Right >= Mid
        // 위 부등식에서 Right 가 가운데에 있지? 따라서 가운데 위치값 Right 반환.
        return Right;
    }

    // 사실, Mid = (Left + Right) / 2 로 계산되므로, 어지간하면 Mid 값이 가운데 위치값이 됨.
    // 그러나, 위의 if - else if 블록은 Mid 가 위와 같이 계산되었음에도,
    // 실제로 Left 와 Right 위치값 사이에 존재하지 않을지 모르는 예외 케이스에 대응하기 위해 작성해 둔 코드라고 봐도 무방함.
    // 어쨋든 핵심은, 기준요소를 정렬범위의 맨 첫번째 요소가 아닌, 가운데 요소로 지정하기 위해서
    // 정렬범위 가운데에 위치한 인덱스를 반환해주는 게 이 함수의 가장 큰 목적!
    return Mid;
}

// 주어진 그룹(DataSet)을 첫 번째 요소를 기준 요소로 삼아 왼쪽 / 오른쪽 그룹으로 분할하는 함수
// Left 는 왼쪽 정찰병 위치, Right 는 오른쪽 정찰병 위치
int Partition(int DataSet[], int Left, int Right)
{
    int First = Left; // 맨 왼쪽 정찰병의 초기 위치 = 그룹의 첫 번째 요소 위치
    int Index = getMedian(Left, Right, (Left + Right) / 2); // 정렬범위의 가운데 요소 위치값 반환
    int Pivot = DataSet[Index]; // 가운데 요소를 분할 기준요소로 선택
    
    // 이제 정렬범위의 첫번째 요소와 정렬범위 가운데 요소(분할 기준요소)를 교체함.
    // 이 덕분에, 만약 정렬범위가 이미 정렬 또는 역순정렬 되어있었을 경우, 가운데 요소와 첫번째 요소를 한 번 교체함으로써,
    // 1:n-1 로 분할되는 최악의 상황을 방지할 수 있음.
    // 또한, 정렬 또는 역순정렬이 안되어있다고 할지라도, 어차피 정렬이 안되어 있는 정렬범위라면 
    // 가운데 요소와 첫번째 요소를 한 번 교체해준다고 해서 딱히 손해볼 건 없는 상황임. 어차피 정렬이 안되어 있었으니까!
    Swap(&DataSet[Index], &DataSet[Left]);            

    /* 이후부터의 정렬 과정은 이전과 동일함. 왼쪽 정찰병과 오른쪽 정찰병이 정렬범위 양쪽 끝에서부터 수색 섬멸 */

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
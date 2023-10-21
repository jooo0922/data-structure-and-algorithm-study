#include <stdio.h>
#include "LinkedListStack.h"

// 배열내의 두 요소 주소값을 받아 서로의 위치를 맞교환하는 함수
void Swap(int* A, int* B)
{
    int Temp = *A; // de-referencing 으로 포인터 변수 A 가 가리키는 메모리 공간의 값을 임시 복사하여 저장
    *A = *B; // A가 가리키는 메모리 공간의 값을 B가 가리키는 메모리 공간의 값으로 덮어씀.
    *B = Temp; // B가 가리키는 메모리 공간의 값을 맨 처음에 복사해 둔 값으로 덮어씀.
}

// 주어진 그룹(DataSet)을 첫 번째 요소를 기준 요소로 삼아 왼쪽 / 오른쪽 그룹으로 분할하는 함수
// Left 는 왼쪽 정찰병 위치, Right 는 오른쪽 정찰병 위치
int Partition(int DataSet[], int Left, int Right)
{
    int First = Left; // 맨 왼쪽 정찰병의 초기 위치 = 그룹의 첫 번째 요소 위치
    int Pivot = DataSet[First]; // 기준 요소를 그룹의 첫 번째 요소로 지정

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
    LinkedListStack* Stack; // 스택 포인터 변수 선언
    LLS_CreateStack(&Stack); // 스택 구조체 생성
    LLS_Push(Stack, LLS_CreateNode(Left, Right)); // 정렬범위 정보가 포함된 노드 생성 및 스택에 Push

    // 스택에 노드가 없어질 때까지 반복 순회
    while (!LLS_IsEmpty(Stack))
    {
        // 가장 마지막에 Push 된 정렬범위를 가져옴(Pop)
        // 참고로, 반복문을 순회할수록 점점 더 분할되어가는 정렬범위가 스택에 Push 됨!
        Node* Popped = LLS_Pop(Stack); 
        Left = Popped->Left; // Pop 으로 가져온 정렬범위의 왼쪽 정찰병 위치 저장
        Right = Popped->Right; // Pop 으로 가져온 정렬범위의 오른쪽 정찰병 위치 저장
    
        // 그룹의 오른쪽 정찰병 위치가 왼쪽 정찰병 위치보다 크다 == 전달받은 그룹의 크기가 1보다는 크다!
        // -> 그룹의 크기가 1보다 클 때에만 분할을 수행할 수 있댔지?
        if (Left < Right)
        {
            // 그룹을 분할하고, 분할 기준요소의 위치를 반환받아 저장해 둠.
            int Index = Partition(DataSet, Left, Right);

            /*
                하위 그룹의 정렬범위를 결정짓는 두 정찰병 위치(Left, Right)로
                노드를 생성하고, 이를 스택에 Push 함으로써,

                다음 순회에서
                스택으로부터 분할된 하위 정렬범위 정보를 갖는 노드를 Pop 해와서
                반복적으로 분할을 수행할 수 있도록 함!
            */

            // 기준요소의 왼쪽 하위 정렬범위를 노드로 생성 및 스택에 Push
            LLS_Push(Stack, LLS_CreateNode(Left, Index - 1)); 

            // 기준요소의 오른쪽 하위 정렬범위를 노드로 생성 및 스택에 Push
            LLS_Push(Stack, LLS_CreateNode(Index + 1, Right));
        }
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
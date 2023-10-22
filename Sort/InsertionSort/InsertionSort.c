#include <stdio.h>
#include <string.h>

// 삽입정렬 함수 구현
void InsertionSort(int DataSet[], int Length)
{
    int i = 0; // 바깥쪽 for loop 를 돌 때 사용할 인덱스 변수 초기화
    int j = 0; // 안쪽 for loop 를 돌 때 사용할 인덱스 변수 초기화
    int value = 0; // 현재 정렬범위의 마지막 요소를 임시로 저장해 둘 변수 초기화

    // 바깥쪽 for loop 는 정적 배열의 길이만큼 순회
    // p.210 1번 과정에서 첫 정렬 대상 범위는 데이터의 첫 2개 요소로 시작한다고 했으므로,
    // 바깥쪽 for loop 의 시작 인덱스는 i = 1 로 할당하여 1부터 시작함.
    for (i = 1; i < Length; i++)
    {
        if (DataSet[i - 1] <= DataSet[i])
        {
            // 정렬범위 마지막 요소가 이전 요소보다 크다면, 
            // 정렬범위 마지막 요소 이전의 요소들은 이미 이전 삽입정렬에서 정렬이 끝났으므로,
            // 더 이상 비교할 필요가 없어서 다음 삽입정렬 순회로 넘어감
            continue;
        }

        // 정렬범위 마지막 요소가 이전 요소보다 큰 게 아니라면, 어쨋거나 삽입정렬을 해줘야 하니
        // 삽입정렬의 대상이 될 마지막 요소를 임시 변수에 저장해 둠.
        value = DataSet[i];

        // 안쪽 for loop 에서는 정렬범위 마지막 요소를 정렬범위 내의 나머지 요소들과 비교함.
        // 이때, 삽입정렬이 반복될 때마다 정렬범위가 늘어난다고 했으므로,
        // 안쪽 for loop 는 바깥쪽 for loop 의 인덱스인 i 까지 돌리는 것.
        for (j = 0; j < i; j++)
        {
            // 정렬범위의 첫번째 요소부터 (j = 0) 훑어보면서 정렬범위의 마지막 요소보다 큰 요소가 있는지 검사 
            if (DataSet[j] > value)
            {
                // 정렬범위의 마지막 요소보다 큰 요소를 발견했다면, 
                // 그 지점 이후의 요소들의 메모리 공간을 모두 한 칸씩 뒤로 옮김.
                /*
                    memmove()

                    배열처럼 연속된 데이터를 메모리 상에서 단번에 이동시킬 때 쓰기 좋음.

                    첫 번째 매개변수 : 연속된 원본 데이터를 옮길 메모리 공간의 시작 지점 주소
                    두 번째 매개변수 : 연속된 원본 데이터의 시작 지점 주소
                    세 번째 매개변수 : 이동하는 연속된 원본 데이터의 메모리 크기 (= 옮길 원본 데이터의 시작 지점 요소와 정렬범위 마지막 요소 사이의 메모리 간격)
                */
                memmove(&DataSet[j + 1], &DataSet[j], sizeof(DataSet[0]) * (i - j));
                
                // 더 큰 요소 이후의 요소들이 이동하고 난 빈 자리에 
                // 정렬 범위 마지막 요소 삽입
                DataSet[j] = value;
                
                // 이후 요소들은 어차피 정렬범위 마지막 요소 value 보다 클테니, 
                // 더 비교할 필요가 없어 반복문 탈출
                break;
            }
        }
    }
}

int main()
{
    int DataSet[] = { 6, 4, 2, 3, 1, 5 }; // 삽입정렬할 정적 배열 선언 및 초기화
    int Length = sizeof DataSet / sizeof DataSet[0]; // 정적 배열 길이 계산하여 저장
    int i = 0; // 삽입정렬 결과를 확인할 때 for loop 에서 사용할 인덱스 변수 초기화

    InsertionSort(DataSet, Length);

    // 삽입정렬 결과 출력
    for (i = 0; i < Length; i++)
    {
        printf("%d ", DataSet[i]);
    }

    printf("\n");

    return 0;
}
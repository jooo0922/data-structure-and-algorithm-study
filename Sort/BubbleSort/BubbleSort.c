#include <stdio.h>
#include <stdbool.h>

// 버블정렬 함수 구현
/*
    참고로, 매개변수를 배열로 선언하면,
    외부에서 전달되는 배열의 첫 번째 요소의 주소값이 복사되는
    새로운 포인터 변수를 선언한 것으로 처리함.

    즉, 배열은 내부적으로는 포인터 변수로 처리된다는 뜻!
    물론, 저 배열 매개변수 안에 들어있는 주소값은 같겠지만,
    배열 매개변수 자체는 스택 메모리에 새롭게 선언된 변수이므로,
    배열 매개변수 자체의 주소값은 또 다른 것임!
*/
void BubbleSort(int DataSet[], int Length)
{
    int i = 0; // 바깥쪽 for loop 를 돌 때 사용할 인덱스 변수 초기화
    int j = 0; // 안쪽 for loop 를 돌 때 사용할 인덱스 변수 초기화
    int k = 0;
    int temp = 0; // 버블정렬할 정적 배열의 요소를 임시로 저장해 둘 변수 초기화

    // 바깥쪽 for loop 는 정적 배열의 길이만큼 순회
    for (i = 0; i < Length - 1; i++)
    {
        bool isSorted = true;

        // 안쪽 for loop 는 바깥쪽 for loop 가 진행될수록 반복 횟수가 줄어듦
        // 본문 p.206 에서 버블정렬이 진행될 때마다 정렬 대상 개수가 줄어드는 것을 구현한 것임.
        for (j = 0; j < Length - (i + 1); j++)
        {
            // 현재 요소를 다음 요소와 크기 비교
            if (DataSet[j] > DataSet[j + 1])
            {
                // 다음 요소보다 크다면, 오름차순 정렬 순서에 맞지 않으므로,
                // 다음 요소와 순서를 교환함.
                temp = DataSet[j + 1];
                DataSet[j + 1] = DataSet[j];
                DataSet[j] = temp;

                isSorted = false;
            }
        }

        if (isSorted)
        {
            printf("Sorting Complete!\n");
            printf("End outer loop at %d\n", i);
            break;
        }
    }
}

int main()
{
    int DataSet[] = { 6, 4, 2, 3, 1, 5 }; // 버블정렬할 정적 배열 선언 및 초기화
    int Length = sizeof DataSet / sizeof DataSet[0]; // 정적 배열 길이 계산하여 저장
    int i = 0; // 버블정렬 결과를 확인할 때 for loop 에서 사용할 인덱스 변수 초기화

    BubbleSort(DataSet, Length);

    // 버블정렬 결과 출력
    for (i = 0; i < Length; i++)
    {
        printf("%d ", DataSet[i]);
    }

    printf("\n");

    return 0;
}
#include "DoubleLinkedList.h"

// 삽입정렬 함수 구현
void DLL_InsertionSort(Node** Head)
{
    Node* Value = NULL; // 정렬범위의 마지막 노드를 저장해 둘 포인터 변수 
    Node* Temp1 = (*Head); // 바깥쪽 while 문에서 순회할 노드 포인터를 헤드노드로 초기화
    Node* Temp2 = NULL; // 안쪽 while 문에서 순회할 노드 포인터 초기화

    // 링크드리스트 헤드노드가 존재하지 않으면 함수 종료 
    if (Temp1 == NULL)
    {
        return;
    }

    // 바깥쪽 while 문에서 노드 순회 시, 2번째 노드부터 순회하도록 초기화
    // why? 삽입정렬은 첫 2개 요소를 정렬범위로 시작하는데, 이 때, Temp1 을 첫 번째 정렬범위의 마지막 요소로 저장한 것!
    // 정적 배열 삽입정렬 시, 바깥쪽 for loop 를 i = 1 로 시작한 것과 같은 원리!
    Temp1 = Temp1->NextNode;

    // 바깥쪽 while 문을 순회하는 노드가 NULL 이 되기 전까지 순회
    while (Temp1 != NULL)
    {
        if (Temp1->PrevNode->Data <= Temp1->Data)
        {
            // 정렬범위 마지막 노드가 이전 노드보다 크다면, 
            // 정렬범위 마지막 노드 이전의 노드들은 이미 이전 삽입정렬에서 정렬이 끝났으므로,
            // 더 이상 비교할 필요가 없어서 다음 삽입정렬 순회로 넘어감
            Temp1 = Temp1->NextNode; // Temp1 는 다음 정렬범위의 마지막 노드로 업데이트
            continue;
        }

        // 정렬범위 마지막 노드가 이전 노드보다 큰 게 아니라면, 어쨋거나 삽입정렬을 해줘야 하니
        // 삽입정렬의 대상이 될 마지막 노드를 임시 변수에 저장해 둠.
        Value = Temp1;

        Temp1 = Temp1->NextNode; // Temp1 는 다음 정렬범위의 마지막 요소로 업데이트
        Temp2 = (*Head); // 어떤 정렬범위든 첫 번째 요소는 항상 헤드노드이므로, 헤드노드부터 안쪽 while 문 순회 시작

        // 안쪽 while 문은 정렬범위의 첫 번째 노드부터 정렬범위 마지막 노드까지 순회
        while (Temp2 != Value)
        {
            // 정렬범위 첫 번째 요소부터 (Temp2 = (*Head)) 훑어보면서 정렬 범위 마지막 노드보다 큰 노드가 있는지 검사
            if (Temp2->Data > Value->Data)
            {
                // 정렬범위의 마지막 노드보다 큰 노드를 발견했다면,
                // 먼저 그 노드를 링크드리스트에서 제거함.
                DLL_RemoveNode(Head, Value);
                
                // 정렬범위 내에서 순회중인 현재 노드 (Temp2) 앞에 마지막 노드를 삽입함
                DLL_InsertBefore(Head, Temp2, Value);

                // 이후 노드들은 어차피 정렬범위 마지막 노드 Value 보다 클테니, 
                // 더 비교할 필요가 없어 반복문 탈출
                break;
            }
            Temp2 = Temp2->NextNode;
        }
    }
}

int main()
{
    Node* List = NULL; // 더블 링크드리스트(의 헤드노드) 주소값 초기화
    Node* Current = NULL; // 더블 링크드리스트 순회 출력 시 현재 노드 주소값을 저장해 둘 포인터 변수 초기화

    // 삽입정렬할 더블 링크드리스트 노드 생성 및 추가
    DLL_AppendNode(&List, DLL_CreateNode(6));
    DLL_AppendNode(&List, DLL_CreateNode(4));
    DLL_AppendNode(&List, DLL_CreateNode(2));
    DLL_AppendNode(&List, DLL_CreateNode(3));
    DLL_AppendNode(&List, DLL_CreateNode(1));
    DLL_AppendNode(&List, DLL_CreateNode(5));

    int Length = DLL_GetNodeCount(List); // 링크드리스트 길이 저장
    int i = 0; // 삽입정렬 결과를 확인할 때 for loop 에서 사용할 인덱스 변수 초기화

    DLL_InsertionSort(&List);

    // 삽입정렬 결과 출력
    for (i = 0; i < Length; i++)
    {
        Current = DLL_GetNodeAt(List, i);
        printf("%d ", Current->Data);
    }

    printf("\n");

    return 0;
}

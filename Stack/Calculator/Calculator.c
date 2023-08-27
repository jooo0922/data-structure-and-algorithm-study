#include "Calculator.h"

// 피연산자 토큰 생성에 사용할 십진수 문자들이 담긴 배열 선언
// 배열은 선언 및 초기화 시점에 요소를 한방에 지정할 땐, {} 로 지정해주면 됨.
// 마지막에 추가한 '.' 은 피연산자가 정수가 아닌 실수일 경우에 표현하기 위한 것이겠군.
char NUMBER[] = { '0', '1', '2', '3', '4', '5', '6', '7', '8', '9', '.' };

// 토큰이 피연산자인지 검사
int IsNumber(char Cipher)
{
    int i = 0;
    int ArrayLength = sizeof(NUMBER); // NUMBER 배열은 char 타입 배열이고, char 타입은 1 byte 이므로, 배열 개수와 배열 메모리 크기가 일치하겠군!

    for ( i = 0; i < ArrayLength; i++)
    {
        // NUMBER 배열 안에 있는 십진수 문자열 중 하나라도 일치하는 게 있다면,
        // Cipher 토큰은 '피연산자' 라는 의미이므로, 1(true)를 반환
        if (Cipher == NUMBER[i])
            return 1;
    }

    return 0; // NUMBER 안에 일치하는 문자열이 없으면 '연산자' 이므로, 0(false) 반환
}

// 다음 토큰에 대한 중위표기식 문자열 상의 인덱스를 반환(= 토큰 문자열 길이), 다음 토큰 및 토큰 타입 업데이트
// 첫 번째 매개변수인 Expression 에는, 중위표현식 문자열 상에서, 가장 최근에 검사한 토큰 이후의 문자열들이 전달됨.
unsigned int GetNextToken(char* Expression, char* Token, int* TYPE)
{
    unsigned int i = 0; // 중위표기식 문자열 상에서 토큰 문자열의 마지막 문자에 해당하는 인덱스 0으로 초기화

    // 가장 최근 토큰 이후의 중위표현식 문자열을 해당 문자열의 종료문자('\0')가 나올 때까지 순회함.
    // 종료문자의 ASCII 코드는 0이기 때문에, 0 != Expression[i] 로 표현해도 되지만,
    // 가독성을 위해서 가급적 종료문자 자체를 사용해주는 게 나음!
    for (i = 0; '\0' != Expression[i]; i++)
    {
        // 일단 다음 토큰을 업데이트해둬야 하니, 문자열들을 순회하면서
        // 각 문자열을 다음 토큰을 저장하는 문자열 포인터 변수에 저장해 둠.
        // 참고로, 토큰이 배열(문자열) 형태로 저장되는 이유가 뭐냐면,
        // 연산자는 char 타입 문자 데이터 하나만으로도 표현이 가능하지만,
        // 피연산자인 숫자는 '2013404' 이런 식으로 십진수 문자열 여러 개를 사용해야 표현할 수 있기 때문!
        Token[i] = Expression[i];

        if (IsNumber(Expression[i]) == 1)
        {   
            // 중위표현식을 순회하면서 검사하는 문자가 숫자라면, 토큰이 피연산자라는 뜻!
            // 토큰의 타입을 OPERAND(피연산자)로 업데이트 함.
            *TYPE = OPERAND;

            if (IsNumber(Expression[i + 1]) != 1)
            {
                // 만약 현재 순회중인 문자의 다음 문자는 숫자가 아니라면,
                // 숫자인 다음 토큰의 문자열까지는 순회를 마친 것이므로, 반복문 종료
                break;
            }
        }
        else
        {
            // 중위표현식을 순회하며 검사하는 문자가 숫자가 아니라면, 토큰이 연산자라는 뜻!
            // 토큰의 타입을 해당 연산자 문자로 업데이트함.
            // 우리는 토큰 타입 enum SYMBOL 의 각 타입을 단일 문자 데이터로 초기화했기 때문에,
            // 해당 연산자 문자를 할당하는 것 자체가 SYMBOL 의 연산자 타입을 할당하는 것과 동일함.
            *TYPE = Expression[i];
            break; // 연산자는 문자 1개로 이루어져 있으니 더 이상 문자열을 반복 순회할 필요 x
        }

        // 중위표현식 문자열을 순회하면서 저장해놓은 토큰의 문자열 마지막에는 종료문자를 추가함.
        // 모든 문자열은 항상 마지막에 종료문자를 추가해서 메모리에 저장해놔야 함.
        Token[i + 1] = '\0'; 

        // 중위표기식 문자열 상에서 토큰 문자열의 마지막 문자에 해당하는 인덱스 반환
        // 이때, 중위표기식 Expression 은 가장 최근에 검사한 토큰 이후부터의 중위표기식 문자열을 전달해주므로,
        // 해당 문자열의 맨 처음 문자부터 인덱스를 0 으로 초기화해놓고 누산된 값 i 를 반환해준다면,
        // i 값은 현재 업데이트된 토큰의 문자열 길이와 동일하다고 보면 되겠지!
        return i;
    }
}

// 각 연산자 우선순위를 정수형으로 반환
// 두 번째 매개변수 InStack 은 현재 연산자 토큰이 스택 안에 있는건지,
// 아니면 현재 검사중인 스택인지 구별해주는 값
int GetPriority(char Operator, int InStack)
{
    int Priority = -1; // 반환할 우선순위 변수를 -1 로 초기화

    switch (Operator)
    {
    case LEFT_PARENTHESIS:
        if (InStack)
            Priority = 3; // 스택안에 존재하는 왼쪽 괄호는 우선순위가 3 (우선순위 가장 낮음)
        else
            Priority = 0; // 현재 검사중인 왼쪽 괄호는 우선순위가 0 (우선순위 가장 높음)
        break;
    
    case MULTIPLY:
    case DIVIDE:
        Priority = 1; // 곱셈과 나눗셈은 우선순위가 1
        break;
    
    case PLUS:
    case MINUS:
        Priority = 2;
        break;
    }

    return Priority;
}

// 스택의 최상위 노드 연산자 토큰과 현재 연산자 토큰의 우선순위 비교
int IsPrior(char OperatorInStack, char OperatorInToken)
{
    return (GetPriority(OperatorInStack, 1) > GetPriority(OperatorInToken, 0));
}

// 중위표기식 > 후위표기식으로 변환
void GetPostfix(char* InfixExpression, char* PostfixExpression)
{
    LinkedListStack* Stack; // 중위표기식의 연산자 토큰을 읽어들여서 push 해놓을 스택

    char Token[32]; // 피연산자 토큰은 숫자 길이가 길어질 수 있으므로, 최대 32자까지 저장할 수 있는 문자열 배열 변수로 선언
    int Type = -1; // 토큰 타입을 SYMBOL 타입 enum 으로 저장하는 변수 초기화
    unsigned int Position = 0; // 전체 중위표기식 문자열 상에서 현재 순회중인 문자열의 인덱스
    unsigned int Length = strlen(InfixExpression); // 중위표기식 문자열 길이 저장 (<string.h> 라이브러리가 LinkedListStack.h 에 포함되어있어 사용 가능)

    LLS_CreateStack(&Stack); // 링크드리스트 스택 생성

    // 중위표기식 문자열의 모든 문자들을 순회할 때까지 반복
    while (Position < Length)
    {
        /*
            문자열 매개변수 char* InfixExpression 를
            &InfixExpression[Position] 형태로 인자로 전달한다면,
            InfixExpression 문자열 안에서, Position 번째에 해당하는 문자의 주소값을 전달하는 것임.

            즉, GetNextToken() 함수 내에서
            InfixExpression 문자열 중 Position 번째의 문자부터 시작하는 문자열을 전달하여
            다룰 수 있도록 인자를 전달하는 것이라고 보면 됨.

            이를 통해, GetNextToken() 함수 내에서는
            Position 번째부터 시작하는 문자열을 분석해서
            다음 토큰이 무엇인지 알아내서 Token 변수에 덮어쓰고,
            그 토큰의 타입도 알아내서 Type 변수에도 덮어써 줌.

            마지막으로, 다음 토큰에 해당하는 문자열을 찾을 때까지 반복순회하며 누산한
            i 값을 반환하는데, 이는 결국 다음 토큰 문자열 길이와 동일함.

            이를 반환받아 Position 에 누적한다는 뜻은,
            다음 토큰의 문자열 길이를 
            순회중인 InfixExpression 문자열의 현재 인덱스값인 Position 에 더해서
            현재 순회중인 InfixExpression 전체 문자열 상의 현재 인덱스 값을 업데이트 해준다는 뜻!
        */
        Position += GetNextToken(&InfixExpression[Position], Token, &Type);

        if (Type == OPERAND)
        {
            // 현재 토큰이 피연산자라면, 후위표기식 문자열에 바로 이어붙임. (책에서는 '후위표기식에 출력한다'고 표현됨.)
            /*
                strcat()

                두 개의 문자열 결합 함수
                strcat(dest, src) 로 실행하면,
                src 문자열을 dest 문자열 끝에 이어붙인다는 의미.

                이때, dest 문자열이 최종적으로 변경되는 것이기 때문에, 
                dest 문자열은 문자열을 추가할 수 있을 만큼 버퍼가 충분히 
                크게 할당되어 있어야 함.
            */
            strcat(PostfixExpression, Token);
            strcat(PostfixExpression, " "); // 후위표기식에 토큰 추가 후, 다음에 추가될 토큰과 구분하기 위해 띄어쓰기(공백 문자)를 추가함.
        }
        else if (Type == RIGHT_PARENTHESIS)
        {
            // 현재 토큰이 오른쪽 괄호라면, 
            // 스택 최상위 노드에 왼쪽 괄호가 나올 때까지 계속 스택 제거(LLS_Pop())를 수행하고,
            // 제거한 노드에 담긴 연산자 토큰을 후위표기식 문자열에 이어붙임. > p.99 4번 과정 코드화
            while (!LLS_IsEmpty(Stack))
            {
                Node* Popped = LLS_Pop(Stack); // 스택 최상위 노드 제거 후 보관

                if (Popped->Data[0] == LEFT_PARENTHESIS)
                {
                    // 제거한 최상위 노드의 연산자 토큰이 '왼쪽 괄호'라면,
                    // 더 이상 최상위 노드 제거 및 후위표기식에 이어붙이는 반복문을 중단함.
                    LLS_DestroyNode(Popped); // 일단 이미 제거한 최상위 노드의 메모리는 해제
                    break;
                }
                else
                {
                    // 제거한 최상위 노드의 연산자 토큰이 왼쪽괄호가 아닌 '연산자'인 경우
                    // 제거한 최상위 노드의 연산자 토큰을 후위표기식에 이어붙임
                    strcat(PostfixExpression, Popped->Data);
                    break;
                }
            }
        }
        else
        {
            // 현재 토큰이 오른쪽 괄호가 아닌 '그냥 연산자'일 경우,
            // 스택의 최상위 노드에 담긴 토큰과 현재 토큰의 우선순위를 비교하고,
            // 현재 토큰의 우선순위가 더 높을 경우, 최상위 노드 토큰을 제거(LLS_Pop())해서 후위표기식에 이어붙임.
            // 마지막으로, 현재 토큰을 스택의 최상위 노드로 삽입함(LLS_Push()) > p.99 3번 과정
            while (!LLS_IsEmpty(Stack) &&
                IsPrior(LLS_Top(Stack)->Data[0], Token[0]))
            {
                // 현재 토큰이 현재 스택 최상위 노드의 토큰보다 우선순위가 높을 경우
                Node* Popped = LLS_Pop(Stack);

                if (Popped->Data[0] != LEFT_PARENTHESIS)
                {
                    // 스택 최상위 노드에 담겨있던 연산자 토큰이 왼쪽 괄호인 경우만 제외하고,
                    // 나머지 연산자들은 후위표기식에 이어붙임
                    strcat(PostfixExpression, Popped->Data);
                }

                LLS_DestroyNode(Popped); // 항상 제거(LLS_Pop())된 최상위 노드는 메모리 해제할 것!
            }
        }
    }

    // 첫 번째 반복문이 끝나면 중위표기식을 다 읽었다는 뜻인데,
    // 중위표기식을 다 읽고 나서도 스택에 남아있는 연산자들을 마저 처리해줘야겠지!
    while (!LLS_IsEmpty(Stack))
    {
        Node* Popped = LLS_Pop(Stack); // 스택에 남아있는 최상위 노드들을 차례대로 제거해서 꺼내옴.

        if (Popped->Data[0] != LEFT_PARENTHESIS)
        {
            // 마찬가지로, 스택 최상위 노드에 담겨있던 연산자 토큰이 왼쪽 괄호인 경우만 제외하고,
            // 나머지 연산자들은 후위표기식에 이어붙임
            strcat(PostfixExpression, Popped->Data);
        }

        LLS_DestroyNode(Popped); // 항상 제거(LLS_Pop())된 최상위 노드는 메모리 해제할 것!
    }

    // 두번째 반복문으로 스택에 남아있던 모든 연산자 토큰들을 Pop 해줬다면,
    // 스택이 비어있게 될테니 메모리 해제함.
    LLS_DestroyNode(Stack);
}

// 변환된 후위표기식을 계산하여 결과값 반환
double Calculate(char* PostfixExpression)
{

}

int main()
{
    return 0;
}
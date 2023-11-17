#include "RedBlackTree.h"

// 전역에서 참조할 더미노드 선언
RBTNode* Nil;

int main()
{
	// 레드블랙트리 뿌리노드 주소값을 저장할 포인터 변수 초기화
	RBTNode* Tree = NULL;

	// 레드블랙트리 내의 특정 노드 주소값을 저장할 포인터 변수 초기화
	RBTNode* Node = NULL;

	// 더미노드 생성
	Nil = RBT_CreateNode(0);

	// 더미노드는 항상 검은색으로 지정
	Nil->Color = BLACK;

	// 사용자 입력을 받기 위해 런타임에서 무한 루프 실행
	while (1)
	{
		// 입력받은 명령어 번호를 저장할 변수 초기화
		int cmd = 0;

		// 노드 생성, 제거, 탐색 시 해당 노드의 데이터값을 입력받아 저장할 변수 초기화
		int param = 0;

		// 입력 스트림(stdin)에서 입력받은 데이터를 문자열 형태로 읽어와 저장할 변수 초기화
		char buffer[10];

		// 입력할 수 있는 명령어들을 출력하여 표시
		printf("Enter command number :\n");
		printf("(1) Create a node, (2) Remove a node, (3) Search a node\n");
		printf("(4) Display Tree (5) quit\n");
		printf("command number:");

		// 입력 스트림에서 읽어온 사용자 입력 데이터를 문자열 배열 buffer 에 저장함.
		fgets(buffer, sizeof(buffer) - 1, stdin);

		// 문자열 배열 buffer 에 저장된 문자열을 %d 형식, 즉, 정수형으로 읽어서 cmd 변수에 저장
		sscanf_s(buffer, "%d", &cmd);

		if (cmd < 1 || cmd > 5)
		{
			// 1 ~ 5 범위를 넘어서는 유효하지 않은 명령어 입력 시 입력 무시
			printf("Invalid command number.\n");
			continue;
		}
		else if (cmd == 4)
		{
			// 4번 명령어 입력 시, 트리 출력
			RBT_PrintTree(Tree, 0, 0);
			printf("\n");
			continue;
		}
		else if (cmd == 5)
		{
			// 5번 명령어 입력 시, 무한루프 탈출 > 명령어 입력 종료
			break;
		}


		/* 2번, 3번, 4번 명령어 입력 시 처리 */ 

		// 노드 데이터값 입력받기
		printf("Enter parameter (1~200) :\n");

		// 입력 스트림에서 읽어온 사용자 입력 데이터를 문자열 배열 buffer 에 저장함.
		fgets(buffer, sizeof(buffer) - 1, stdin);

		// 문자열 배열 buffer 에 저장된 문자열을 %d 형식, 즉, 정수형으로 읽어서 param 변수에 저장
		sscanf_s(buffer, "%d", &param);

		if (param < 1 || param > 200)
		{
			// 1 ~ 200 범위를 넘어서는 유효하지 않은 노드 데이터값 입력 시 입력 무시
			printf("Invalid parameter.%d\n", param);
			continue;
		}

		switch (cmd)
		{
		case 1:
			// 1번 명령어 입력 시, 노드 생성 및 삽입
			RBT_InsertNode(&Tree, RBT_CreateNode(param));
			break;
		case 2:
			// 2번 명령어 입력 시, 노드 제거

			// 제거할 노드 탐색하여 주소값 반환
			Node = RBT_RemoveNode(&Tree, param);

			if (Node == NULL)
			{
				// 제거할 노드를 찾지 못했을 경우 에러 출력
				printf("Not fount node to delete:%d\n", param);
			}
			else
			{
				// 제거할 노드의 메모리 해제
				RBT_DestroyNode(Node);
			}

			break;
		case 3:
			// 3번 명령어 입력 시, 노드 탐색

			// 노드 탐색 후 주소값 반환
			Node = RBT_SearchNode(Tree, param);

			if (Node == NULL)
			{
				// 노드를 찾지 못했을 경우 에러 출력
				printf("Not found node:%d\n", param);
			}
			else
			{
				// 찾은 노드의 데이터와 색상 출력
				printf("Found Node: %d(Color:%s)\n", Node->Data, (Node->Color == RED) ? "RED" : "BLACK");
			}

			break;
		}

		// 다음 명령어를 입력할 때 개행
		printf("\n");
	}

	// 무한루프 탈출 시, 더 이상 명령어를 입력받지 않으므로,
	// 레드블랙트리 메모리 반납 및 함수 종료
	RBT_DestroyTree(Tree);
	return 0;
}

/*
	char *fgets(char *str, int size, FILE *stream);
	

	fgets() 함수는 C 언어에서 파일이나 표준 입력 스트림에서 문자열을 읽어옴.
	주로 텍스트 파일이나 사용자의 입력을 읽어오는 데에 활용함.

	선언된 매개변수는 아래와 같음.

	str: 문자열을 저장할 배열이나 포인터입니다.
	size: 읽을 수 있는 최대 문자의 개수를 나타냅니다.
	stream: 읽기 작업을 수행할 파일 스트림입니다.

	fgets() 함수는 지정된 크기만큼의 문자를 stream으로부터 읽어서 str에 저장합니다. 
	문자열의 끝은 항상 널(null) 문자로 종료됩니다.
*/

/*
	int sscanf(const char *str, const char *format, ...);


	sscanf() 함수는 C 언어에서 문자열에서 형식화된 데이터를 읽어옴. 
	
	scanf() 함수와 비슷하지만, 
	sscanf()는 문자열에서 데이터를 읽어오고, 
	scanf()은 표준 입력 스트림에서 데이터를 읽어온다!

	선언된 매개변수는 아래와 같음.

	str: 읽어올 데이터가 들어 있는 문자열입니다.
	format: 형식 지정자를 포함하는 형식 문자열입니다.
	나머지 매개변수: 형식 문자열에 지정된 형식 지정자에 따라 값을 저장할 변수들입니다.

	참고로, sscanf() 함수는 마치 sprintf() 와 유사하게, 
	format에 지정된 형식 지정자(%d, %f 등...)를 기반으로 
	문자열에서 데이터를 읽어와서 변수들에 저장함.
*/
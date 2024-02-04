#include <stdio.h>
#include <string.h>
#include "KarpRabin.h"

// .txt 파일에서 읽어올 본문 한 줄의 크기를 매크로 전처리기로 선언
#define MAX_BUFFER 512

/*
	명령줄 인수를 선언하여
	CLI 입력으로 .txt 파일 경로와 탐색할 단어(패턴)을 전달받음.

	참고로, 터미널에서 .exe 실행 파일을 실행함과 동시에,
	.txt 파일 경로를 입력해야 하므로,
	두 파일 모두 하나의 디렉토리에 위치시키는 게 좋겠지!

	int argc : 입력받은 명령줄 인수의 개수
	char** argv : 입력받은 명령줄 인수들의 배열

	https://github.com/jooo0922/cpp-study/blob/main/TBCppChapter7/Chapter7_15/Chapter7_15.cpp 참고!
*/
int main(int argc, char** argv)
{
	// 파일 경로를 저장할 문자열 배열 변수 선언
	char* FilePath;

	// C언어에서 파일 입출력을 다룰 때 사용하는 파일 구조체 포인터 변수 선언
	FILE* fp;

	// 본문 한 줄 단위로 저장할 문자열 정적 배열 선언
	char Text[MAX_BUFFER];

	// 탐색할 단어(패턴)를 저장할 문자열 배열 변수 선언
	char* Pattern;

	// 탐색할 단어(패턴)의 크기
	int PatternSize = 0;

	// .txt 본문 줄 탐색 수 누산
	int Line = 0;

	/*
		입력받은 명령줄 인수가 3개보다 작으면
		필요한 인수들보다 적게 입력한 것이므로,

		터미널에 어떻게 입력해야 하는 지 출력해 줌.

		참고로,
		명령줄 인수의 첫번째, 즉, argv[0] 은
		항상 '실행파일 이름'이기 때문에,

		우리가 2개의 명령줄 인수를 입력받아야 한다면,
		총 3개의 명령줄 인수 갯수는 총 3개가 되어야 함.
	*/
	if (argc < 3)
	{
		printf("Usage: %s <FilePath> <Pattern>\n", argv[0]);
		return 1;
	}

	// 명령줄 인수로부터 파일 경로와 패턴 문자열을 캐싱함
	FilePath = argv[1];
	Pattern = argv[2];

	// 패턴 문자열 길이 캐싱
	PatternSize = strlen(Pattern);

	// 입력받은 파일 경로를 '읽기 모드("r"('R'ead mode))'로 열기 시도
	if (fopen_s(&fp, FilePath, "r") != 0)
	{
		/*
			파일 열기 성공 시,
			fopen_s() 함수가 0을 반환하고,
			실패하면 에러 코드를 반환하므로,

			반환값이 0이 아닐 경우의 예외 처리 적용
		*/
		printf("Cannot open file:%s\n", FilePath);
		return 1;
	}

	// 파일 포인터 fp 가 가리키는 파일에서 한 줄 크기(MAX_BUFFER)만큼 문자열을 읽어와서 Text 정적 배열에 저장
	// 더 이상 읽어올 문자열이 없을 때까지(즉, 반환값이 NULL 일 때까지) 문자열 읽기를 반복
	while (fgets(Text, MAX_BUFFER, fp) != NULL)
	{
		// .txt 본문을 한 줄 단위로 카프-라빈 알고리즘 문자열 탐색 수행
		int Position = KarpRabin(Text, strlen(Text), 0, Pattern, PatternSize);

		// 탐색한 줄 수 카운팅
		Line++;

		if (Position >= 0)
		{
			/*
				카프-라빈 알고리즘 문자열 탐색 결과가 -1만 아니면,
				본문 Text 에서 패턴을 찾았다는 뜻이므로,

				탐색이 완료된 시점의 줄 수(Line)와 열 수(Position + 1) 출력
			*/
			printf("line:%d, column:%d : %s", Line, Position + 1, Text);
		}
	}

	// 문자열 탐색 종료 후, 파일 포인터 fp 가 가리키는 파일 닫기
	fclose(fp);

	return 0;
}
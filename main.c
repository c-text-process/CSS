#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>

char* getkey();

int main() {
    printf("텍스트를 입력하세요 (종료하려면 Ctrl+s를 누르세요, Ctrl+q로 파일 불러오기):\n");
    char* inputText = getkey();
    printf("입력된 값 : %s\n", inputText);

    FILE* file = fopen("test.txt", "w");
    if (file != NULL) {
        fputs(inputText, file);
        printf("텍스트가 'test.txt' 파일로 저장되었습니다.\n");
        fclose(file);
    }
    else {
        printf("파일 저장 실패!\n");
    }

    free(inputText);

    return 0;
}

char* getkey() {
    char* String = NULL;
    int len = 0;
    char filePath[256]; // 파일 경로를 담을 변수

    while (1) {
        char c = getchar();

        if (c != EOF) {
            if (c == 19) { // Ctrl+s
                String[len] = '\0';
                break;
            }
            else if (c == 17) { // Ctrl+q
                printf("\n파일 경로와 이름을 입력하세요 (예: C:/path/to/file.txt): ");
                scanf("%s", filePath);
                getchar(); // 개행 문자 처리

                FILE* readFile = fopen(filePath, "r");
                if (readFile != NULL) {
                    fseek(readFile, 0, SEEK_END);
                    long fileSize = ftell(readFile);
                    fseek(readFile, 0, SEEK_SET);

                    String = (char*)realloc(String, sizeof(char) * (len + fileSize + 1));
                    size_t newLen = fread(String + len, sizeof(char), fileSize, readFile);
                    String[len + newLen] = '\0'; // Null-terminate the string

                    fclose(readFile);

                    len += newLen;
                    printf("파일 내용 확인:\n%s", String);
                }
                else {
                    printf("파일 열기 실패!\n");
                }
            }
            else {
                String = (char*)realloc(String, sizeof(char) * (len + 2));
                String[len] = c;
                len++;
                String[len] = '\0'; // Null-terminate the string
            }
        }
    }

    return String;
}




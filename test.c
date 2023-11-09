#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include <conio.h>
#include <string.h>

char* getkey();

int main() {
    printf("텍스트를 입력하세요 (종료하려면 Ctrl+s를 누르세요):\n");
    char * inputText = getkey();
    printf("입력된 값 : %s", inputText);
    FILE* file = fopen("test.txt", "w");
    if (file != NULL) {
        fputs(inputText, file);
        printf("텍스트가 바탕화면의 'test.txt' 파일로 저장되었습니다.\n");
    }
    else {
        printf("파일 저장 실패!\n");
    }
    free(inputText);
    return 0;
}



char* getkey() {
    char * String = NULL;
    int len = 0;
    while (1) {
        char c = getchar();
        if (c != EOF) {
            String = (char*)realloc(String, sizeof(char) * (len + 1));
            if (c == 19) {
                String[len] = '\0';
                printf("함수 안 : %s\n", String);
                break;
            }
            else {
                String[len] = c;
            }
            len++;
        }
    }
    return String;
}
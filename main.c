#include <stdio.h>
#include <stdlib.h>
#include <windows.h>

int main() {
    char* inputText = NULL;
    size_t bufferSize = 0;

    printf("텍스트를 입력하세요 (종료하려면 Ctrl+C를 누르세요, Ctrl+S로 저장):\n");

    while (1) {
        int c = fgetc(stdin);

        if (c == EOF || c == '\n') {
            if (bufferSize > 0) {
                // 텍스트를 화면에 출력
                printf("입력한 텍스트: %s\n", inputText);

                // 바탕화면 경로를 얻기 위한 버퍼
                char desktopPath[MAX_PATH];
                if (SUCCEEDED(SHGetFolderPathA(NULL, CSIDL_DESKTOPDIRECTORY, NULL, 0, desktopPath))) {
                   

                    // 파일에 저장
                char filePath[MAX_PATH];
                sprintf(filePath, "%s\\saved.txt", desktopPath);
                    FILE* file = fopen(filePath, "w");
                    if (file != NULL) {
                        fputs(inputText, file);
                        fclose(file);
                        printf("텍스트가 바탕화면의 'saved.txt' 파일로 저장되었습니다.\n");
                    }
                    else {
                        printf("파일 저장 실패!\n");
                    }
                }
                else {
                    printf("바탕화면 경로를 찾을 수 없습니다.\n");
                }

                free(inputText);
                inputText = NULL;
                bufferSize = 0;
            }
        }
        else {
            bufferSize++;
            char* newText = (char*)realloc(inputText, bufferSize);
            if (newText == NULL) {
                // 동적 메모리 할당 실패
                printf("메모리 할당 실패!\n");
                free(inputText); // 기존 메모리 해제
                return 1;
            }
            inputText = newText;
            inputText[bufferSize - 1] = (char)c;
        }
    }

    free(inputText);

    return 0;
}

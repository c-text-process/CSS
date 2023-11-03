#include <stdio.h>
#include <stdlib.h>
#include <windows.h>

int main() {
    char* inputText = NULL;
    size_t bufferSize = 0;

    printf("�ؽ�Ʈ�� �Է��ϼ��� (�����Ϸ��� Ctrl+C�� ��������, Ctrl+S�� ����):\n");

    while (1) {
        int c = fgetc(stdin);

        if (c == EOF || c == '\n') {
            if (bufferSize > 0) {
                // �ؽ�Ʈ�� ȭ�鿡 ���
                printf("�Է��� �ؽ�Ʈ: %s\n", inputText);

                // ����ȭ�� ��θ� ��� ���� ����
                char desktopPath[MAX_PATH];
                if (SUCCEEDED(SHGetFolderPathA(NULL, CSIDL_DESKTOPDIRECTORY, NULL, 0, desktopPath))) {
                   

                    // ���Ͽ� ����
                char filePath[MAX_PATH];
                sprintf(filePath, "%s\\saved.txt", desktopPath);
                    FILE* file = fopen(filePath, "w");
                    if (file != NULL) {
                        fputs(inputText, file);
                        fclose(file);
                        printf("�ؽ�Ʈ�� ����ȭ���� 'saved.txt' ���Ϸ� ����Ǿ����ϴ�.\n");
                    }
                    else {
                        printf("���� ���� ����!\n");
                    }
                }
                else {
                    printf("����ȭ�� ��θ� ã�� �� �����ϴ�.\n");
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
                // ���� �޸� �Ҵ� ����
                printf("�޸� �Ҵ� ����!\n");
                free(inputText); // ���� �޸� ����
                return 1;
            }
            inputText = newText;
            inputText[bufferSize - 1] = (char)c;
        }
    }

    free(inputText);

    return 0;
}

#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>

char* getkey();

int main() {
    printf("�ؽ�Ʈ�� �Է��ϼ��� (�����Ϸ��� Ctrl+s�� ��������, Ctrl+q�� ���� �ҷ�����):\n");
    char* inputText = getkey();
    printf("�Էµ� �� : %s\n", inputText);

    FILE* file = fopen("test.txt", "w");
    if (file != NULL) {
        fputs(inputText, file);
        printf("�ؽ�Ʈ�� ����ȭ���� 'test.txt' ���Ϸ� ����Ǿ����ϴ�.\n");
        fclose(file);
    }
    else {
        printf("���� ���� ����!\n");
    }

    free(inputText);

    return 0;
}

char* getkey() {
    char* String = NULL;
    int len = 0;
    char filePath[256]; // ���� ��θ� ���� ����

    while (1) {
        char c = getchar();

        if (c != EOF) {
            if (c == 19) { // Ctrl+s
                String[len] = '\0';
                break;
            }
            else if (c == 17) { // Ctrl+q
                printf("\n���� ��ο� �̸��� �Է��ϼ��� (��: C:/path/to/file.txt): ");
                scanf("%s", filePath);

                FILE* readFile = fopen(filePath, "r");
                if (readFile != NULL) {
                    fseek(readFile, 0, SEEK_END);
                    long fileSize = ftell(readFile);
                    fseek(readFile, 0, SEEK_SET);

                    String = (char*)realloc(String, sizeof(char) * (fileSize + 1));
                    fread(String, sizeof(char), fileSize, readFile);
                    String[fileSize] = '\0'; // Null-terminate the string

                    fclose(readFile);

                    // ���� ���� �ֿܼ� ���
                    printf("���� ���� Ȯ��:\n%s", String);
                }
                else {
                    printf("���� ���� ����!\n");
                }
            }
            else {
                String = (char*)realloc(String, sizeof(char) * (len + 2));
                String[len] = c;
                String[len + 1] = '\0'; // Null-terminate the string
                len++;
            }
        }
    }

    // ����ڰ� �ҷ��� �ؽ�Ʈ�� ������ �� �ְ� �߰� �Է��� ����
    printf("\n�ؽ�Ʈ�� �����ϼ���. (�����Ϸ��� Ctrl+s�� ��������):\n");
    while (1) {
        char c = getchar();

        if (c != EOF) {
            if (c == 19) { // Ctrl+s
                String[len] = '\0';
                break;
            }
            else {
                String = (char*)realloc(String, sizeof(char) * (len + 2));
                String[len] = c;
                String[len + 1] = '\0'; // Null-terminate the string
                len++;
            }
        }
    }

    return String;
}

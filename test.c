#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include <conio.h>
#include <string.h>

char* getkey();

int main() {
    printf("�ؽ�Ʈ�� �Է��ϼ��� (�����Ϸ��� Ctrl+s�� ��������):\n");
    char * inputText = getkey();
    printf("�Էµ� �� : %s", inputText);
    FILE* file = fopen("test.txt", "w");
    if (file != NULL) {
        fputs(inputText, file);
        printf("�ؽ�Ʈ�� ����ȭ���� 'test.txt' ���Ϸ� ����Ǿ����ϴ�.\n");
    }
    else {
        printf("���� ���� ����!\n");
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
                printf("�Լ� �� : %s\n", String);
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
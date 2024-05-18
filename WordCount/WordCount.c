#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

// ������ͳ���ļ��е��ַ���
int count_characters(FILE* file) {
    int count = 0;
    char ch;
    while ((ch = fgetc(file)) != EOF) {
        count++;
    }
    return count;
}

// ������ͳ���ļ��еĵ�����
int count_words(FILE* file) {
    int count = 0;
    char ch;
    char prev = ' ';
    while ((ch = fgetc(file)) != EOF) {
        // �����ǰ�ַ��ǿհ��ַ��򶺺�
        if (isspace(ch) || ch == ',') {
            // ���ǰһ���ַ����ǿհ��ַ��򶺺ţ����������
            if (!isspace(prev) && prev != ',') {
                count++;
            }
        }
        prev = ch;
    }
    // ������һ���ַ��Ƿ��ǵ��ʵ�һ����
    if (!isspace(prev) && prev != ',') {
        count++;
    }
    return count;
}

int main(int argc, char* argv[]) {
    // �����������Ƿ���ȷ
    if (argc != 3) {
        fprintf(stderr, "Usage: %s [-c|-w] [input_file_name]\n", argv[0]);
        return 1;
    }

    char* parameter = argv[1];
    char* file_name = argv[2];

    // ���ļ�
    FILE* file = fopen(file_name, "r");
    if (file == NULL) {
        perror("Error opening file");
        return 1;
    }

    // ���ݲ���ѡ��ͳ���ַ����򵥴���
    if (strcmp(parameter, "-c") == 0) {
        int char_count = count_characters(file);
        printf("�ַ�����%d\n", char_count);
    }
    else if (strcmp(parameter, "-w") == 0) {
        int word_count = count_words(file);
        printf("��������%d\n", word_count);
    }
    else {
        // ������Ч
        fprintf(stderr, "Invalid parameter: %s\n", parameter);
        fclose(file);
        return 1;
    }

    // �ر��ļ�
    fclose(file);
    return 0;
}

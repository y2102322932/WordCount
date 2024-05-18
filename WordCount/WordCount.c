#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

// 函数：统计文件中的字符数
int count_characters(FILE* file) {
    int count = 0;
    char ch;
    while ((ch = fgetc(file)) != EOF) {
        count++;
    }
    return count;
}

// 函数：统计文件中的单词数
int count_words(FILE* file) {
    int count = 0;
    char ch;
    char prev = ' ';
    while ((ch = fgetc(file)) != EOF) {
        // 如果当前字符是空白字符或逗号
        if (isspace(ch) || ch == ',') {
            // 如果前一个字符不是空白字符或逗号，则计数增加
            if (!isspace(prev) && prev != ',') {
                count++;
            }
        }
        prev = ch;
    }
    // 检查最后一个字符是否是单词的一部分
    if (!isspace(prev) && prev != ',') {
        count++;
    }
    return count;
}

int main(int argc, char* argv[]) {
    // 检查参数数量是否正确
    if (argc != 3) {
        fprintf(stderr, "Usage: %s [-c|-w] [input_file_name]\n", argv[0]);
        return 1;
    }

    char* parameter = argv[1];
    char* file_name = argv[2];

    // 打开文件
    FILE* file = fopen(file_name, "r");
    if (file == NULL) {
        perror("Error opening file");
        return 1;
    }

    // 根据参数选择统计字符数或单词数
    if (strcmp(parameter, "-c") == 0) {
        int char_count = count_characters(file);
        printf("字符数：%d\n", char_count);
    }
    else if (strcmp(parameter, "-w") == 0) {
        int word_count = count_words(file);
        printf("单词数：%d\n", word_count);
    }
    else {
        // 参数无效
        fprintf(stderr, "Invalid parameter: %s\n", parameter);
        fclose(file);
        return 1;
    }

    // 关闭文件
    fclose(file);
    return 0;
}

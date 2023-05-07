#define _CRT_SECURE_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#include "config.h"
#include "addpwd_config.h"

int main()
{
    // srand((unsigned int)time(NULL));
    int lines = getFileInvalidLines("./config.txt");
    struct Npc *config = NULL;
    // 解析文件
    parseFile("./config.txt", lines, &config);
    printf("id=%s\n", getValue("personID", config, lines));
    printf("name=%s\n", getValue("name", config, lines));
    printf("atk=%s\n", getValue("atk", config, lines));
    printf("def=%s\n", getValue("def", config, lines));
    printf("info=%s\n", getValue("info", config, lines));
    freeSpace(config);
    config = NULL;

    encodeFile("config.txt", "加密文件.txt");
    decodeFile("加密文件.txt", "解密文件.txt");
    return 0;
}
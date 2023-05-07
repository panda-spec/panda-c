#define _CRT_SECURE_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// 创建字典结构体
struct Npc
{
    char key[64];
    char value[64];
};

// 获取文件有效行
int getFileInvalidLines(const char *filepath);

// 判断每行字符串是否有效
int isInvalidStr(char *str);

// 对文件进行解析
void parseFile(const char *filepath, int lines, struct Npc **config);

// 通过key获取value
char *getValue(char *key, struct Npc *config, int lines);



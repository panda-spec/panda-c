#include "config.h"

// 获取文件有效行
int getFileInvalidLines(const char *filepath)
{
    // 打开文件
    FILE *file = fopen(filepath, "r");
    if ( file == NULL )
    {
        perror("open");
        return -1;
    }
    char buf[1024] = {0};
    int lines = 0;
    while ( fgets( buf, 1024, file ) != NULL )
    {
        int ret = isInvalidStr(buf);
        if ( ret )
        {
            lines++;
        }
    }
    fclose(file);
    return lines;
}

// 判断每行字符串是否有效
int isInvalidStr(char *str)
{
    if ( str[0] == '\n' || strchr(str, ':') == NULL )
    {
        return 0;
    }
    return 1;
}

// 文件解析
void parseFile(const char *filepath, int lines, struct Npc **configInfo)
{
    // 开辟空间
    struct Npc *config = malloc(sizeof(struct Npc)*lines);
    if ( config == NULL )
    {
        return;
    }
    FILE *file = fopen(filepath, "r");
    if ( file == NULL )
    {
        perror("open");
        return;
    }
    char buf[1024] = {0};
    int index = 0;
    while ( fgets( buf, 1024, file ) != NULL )
    {
        if ( isInvalidStr(buf) )
        {
            // 清空值
            memset(config[index].key, 0, 64);
            memset(config[index].value, 0, 64);
            // 切割key和value
            char *p = strchr(buf, ':');
            // 赋值
            strncpy(config[index].key, buf, p-buf);
            strncpy(config[index].value, p+1, strlen(p+1)-1); 
            index++;
        }
        memset(buf, 0, 1024);
    }
    fclose(file);
    // 建立关系
    *configInfo = config;
}

// 通过key获取value
char *getValue(char *key, struct Npc *config, int lines)
{
    for ( int i=0; i < lines; i++ )
    {
        if ( strcmp(config[i].key, key) == 0 )
        {
            return config[i].value;
        }
    }
    return NULL;
}

// 释放内存
void freeSpace(struct Npc *config)
{
    if ( config == NULL )
    {
        return;
    }
    free(config);
    config = NULL;
}
#include "addpwd_config.h"

// 加密
void encodeFile(char *source, char *encode)
{
    // 打开文件
    FILE *file1 = fopen(source, "r");
    FILE *file2 = fopen(encode, "w");
    if ( !file1 || !file2 )
    {
        perror("open");
        return;
    }
    char ch;
    while ( (ch = fgetc(file1)) != EOF )
    {
        // 将字符转成数字
        short tmp = (short)ch;
        // 左位移5位
        tmp = tmp << 5;
       
        // 统一符号位
        tmp = tmp | 0x8000;
        // printf("%d\n",tmp);
         // 加入随机数
        // tmp = tmp + rand() % 16;

        fprintf(file2, "%hd", tmp);
    }
    fclose(file1);
    fclose(file2);
}

// 解密
void decodeFile(char *pwdFile, char *decode)
{
    FILE *file1 = fopen(pwdFile, "r");
    FILE *file2 = fopen(decode, "w");
    if ( !file1 || !file2 )
    {
        perror("open");
        return;
    }
    short tmp;
    while( !feof(file1) )
    {
        fscanf(file1, "%hd", &tmp);
        tmp = tmp << 1;
        tmp = tmp >> 5;
        char ch = (char)tmp;
        fputc(ch, file2);
    }
    fclose(file1);
    fclose(file2);
}

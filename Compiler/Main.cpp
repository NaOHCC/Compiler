// Compiler.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//
#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <stdio.h>
#include "LexAnalysis.h"
using namespace std;
extern int row;
int main()
{
    FILE *fp = fopen("TestCode.txt", "r+");

    TOKEN token;
    while (!feof(fp))
    {
        token = GetToken(fp);
        if (token.name != "Error" && token.name != "")
            printf("row:%-5d<%-10s,%-10s>\n", row, token.name.c_str(), token.value.c_str());
    }

    fclose(fp);
    return 0;
}

// Compiler.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//
#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <stdio.h>
#include "LexAnalysis.h"
#include "RecursiveDescentParser.h"
#include "SLR_Parser.h"
using namespace std;
extern int row;
TOKEN token;
FILE *fp;
int main()
{
    //fp = fopen("LexTestCode.txt", "r+");
    //while (!feof(fp))
    //{
    //    token = GetToken();
    //    if (token.name != "Error" && token.name != "")
    //        printf("row:%-5d<%-10s,%-10s>\n", row, token.name.c_str(), token.value.c_str());
    //}
    

    //fp=fopen("RD_Parser_Code.txt", "r+");
    //token = GetToken();
    //program();

    fp = fopen("SLR_Code.txt", "r+");
    ReadRules("./rules.txt");
    CreateACTIONandGOTO("../Action_and_Goto_Tables.csv");
    SLR();

    fclose(fp);
    return 0;
}

//#include<stdio.h>
#include <string>
#include <stdio.h>
#include <stdlib.h>
#include <vector>
#include <string>
#include <algorithm>
#include "LexAnalysis.h"
using namespace std;
const vector<string> keywords{"if", "else", "while", "do", "main", "int", "float",
                              "double", "return", "const", "void", "continue", "break", "char", "unsigned", "enum",
                              "long", "switch", "case", "auto", "static"};
int state = 0;

TOKEN GetToken()
{
    string letter;
    TOKEN token;
    char c;
    while (1) //每次循环拿到一个字符
    {
        switch (state)
        {
        case 0:
        {
            c = getchar();
            if (isblank(c))
                state = 0;
            else if (isalpha(c) || c == '_')
            {
                ungetc(c, stdin);
                state = 1;
            }
            else if (isdigit(c))
            {
                letter.push_back(c);
                state = 50;
            }
            else if (c == '+')
                state = 5;
            else if (c == '-')
                state = 8;
            else if (c == '*')
                state = 11;
            else if (c == '/')
                state = 12;
            else if (c == '=')
                state = 13;
            else if (c == '{')
                state = 17;
            else if (c == '}')
                state = 18;
            else if (c == ';')
                state = 19;
            else if (c == '(')
                state = 20;
            else if (c == ')')
                state = 21;
            else if (c == '!')
                state = 26;
            else if (c == '&')
                state = 29;
            else if (c == '|')
                state = 32;
            else if (c == '>')
                state = 35;
            else if (c == '<')
                state = 38;
            else if (c == '\'')
                state = 41;
            else if (c == '"')
                state = 45;

            break;
        }
        case 1:
            c = getchar();
            if (isalpha(c) || isdigit(c) || c == '_')
                letter.push_back(c);
            else
            { //非字母非数字，回退一个字符，以便下次识别
                ungetc(c, stdin);
                state = 2; //跳转到2号状态
            }
            break;
        case 2: //letter识别结束
        {
            auto iter = find(keywords.begin(), keywords.end(), letter);
            if (iter != keywords.end()) //识别到保留字
            {
                token.name = *iter;
                token.value = letter;
            }
            else
            {
                token.name = "id";
                token.value = letter;
            }
            return token; //综态，无sate变化
        }
        //case 3:
        //    c = getchar();
        //    if (isdigit(c))
        //        letter.push_back(c);
        //    else
        //    { //非数字，回退一个字符，以便下次识别
        //        ungetc(c, stdin);
        //        state = 4;
        //    }
        //    break;
        //case 4:
        //{
        //    token.name = "digit";
        //    token.value = letter;
        //    return token; //综态，无sate变化
        //}
        case 5:
        {
            c = getchar();
            token.name = "symbol";
            if (c == '+')
            {
                state = 7; //识别++
            }
            else
            {
                ungetc(c, stdin); //+的下一个字符不是+
                state = 6;
            }
            break;
        }
        case 6:
        {
            token.value = "+";
            return token;
        }
        case 7:
        {
            token.value = "++";
            return token;
        }
        case 8:
        {
            c = getchar();
            token.name = "symbol";
            if (c == '-')
            {
                state = 10; //识别--
            }
            else
            {
                ungetc(c, stdin); //-的下一个字符不是-
                state = 9;
            }
            break;
        }
        case 9:
        {
            token.value = "-";
            return token;
        }
        case 10:
        {
            token.value = "--";
            return token;
        }
        case 11:
        {
            token.name = "symbol";
            token.value = "*";
            return token;
        }
        case 12:
        {
            c = getchar();
            if (c != '/' && c != '*')
            {
                ungetc(c, stdin);
                token.name = "symbol";
                token.value = "/";
                return token;
            }
            else
            {
                state = 48;
                break;
            }
        }
        case 13:
        {
            c = getchar();
            token.name = "symbol";
            if (c == '=')
            {
                state = 15; //识别==
            }
            else
            {
                ungetc(c, stdin); // =的下一个字符不是=
                state = 14;
            }
            break;
        }
        case 14:
        {
            token.value = "=";
            return token;
        }
        case 15:
        {
            token.value = "==";
            return token;
        }
        case 17:
        {
            token.name = "symbol";
            token.value = "{";
            return token;
        }
        case 18:
        {
            token.name = "symbol";
            token.value = "}";
            return token;
        }
        case 19:
        {
            token.name = "symbol";
            token.value = ";";
            return token;
        }
        case 20:
        {
            token.name = "symbol";
            token.value = "(";
            return token;
        }
        case 21:
        {
            token.name = "symbol";
            token.value = ")";
            return token;
        }
        case 22:
        {
            token.name = "symbol";
            token.value = "'";
            return token;
        }
        case 23:
        {
            token.name = "symbol";
            token.value = "'";
            return token;
        }
        case 24:
        {
            token.name = "symbol";
            token.value = "\"";
            return token;
        }
        case 25:
        {
            token.name = "symbol";
            token.value = "\"";
            return token;
        }
        case 26:
        {
            c = getchar();
            token.name = "symbol";
            if (c == '=')
            {
                state = 28; //识别!=
            }
            else
            {
                ungetc(c, stdin); // !的下一个字符不是=
                state = 27;
            }
            break;
        }
        case 27:
        {
            token.value = "!";
            return token;
        }
        case 28:
        {
            token.value = "!=";
            return token;
        }
        case 29:
        {
            c = getchar();
            token.name = "symbol";
            if (c == '&')
            {
                state = 31; //识别&&
            }
            else
            {
                ungetc(c, stdin); // &的下一个字符不是&
                state = 30;
            }
            break;
        }
        case 30:
        {
            token.value = "&";
            return token;
        }
        case 31:
        {
            token.value = "&&";
            return token;
        }
        case 32:
        {
            c = getchar();
            token.name = "symbol";
            if (c == '|')
            {
                state = 34; //识别||
            }
            else
            {
                ungetc(c, stdin); // |的下一个字符不是|
                state = 33;
            }
            break;
        }
        case 33:
        {
            token.value = "|";
            return token;
        }
        case 34:
        {
            token.value = "||";
            return token;
        }
        case 35:
        {
            c = getchar();
            token.name = "symbol";
            if (c == '=')
            {
                state = 37; //识别>=
            }
            else
            {
                ungetc(c, stdin); // >的下一个字符不是=
                state = 36;
            }
            break;
        }
        case 36:
        {
            token.value = ">";
            return token;
        }
        case 37:
        {
            token.value = ">=";
            return token;
        }

        case 38:
        {
            c = getchar();
            token.name = "symbol";
            if (c == '=')
            {
                state = 40; //识别<=
            }
            else
            {
                ungetc(c, stdin); // <的下一个字符不是=
                state = 39;
            }
            break;
        }
        case 39:
        {
            token.value = "<";
            return token;
        }
        case 40:
        {
            token.value = "<=";
            return token;
        }
        case 41:
        {
            token.name = "char"; //确定为字符常量
            c = getchar();
            if (c != '\\')
            {
                letter.push_back(c);
                state = 42;
            }
            else
            {
                letter.push_back(c);
                state = 43; //带有转义斜杠
            }
            /*增加出错处理*/
            break;
        }
        case 42:
        {
            c = getchar();
            if (c == '\'')
            {
                state = 44;
            }
            /*增加出错处理*/
            break;
        }
        case 43:
        {
            c = getchar();
            letter.push_back(c);
            state = 42;
            break;
        }
        case 44:
        {
            token.value = letter;
            return token;
        }
        case 45:
        {
            c = getchar();
            if (c != '"')
            {
                letter.push_back(c);
            }
            else
            {
                state = 46;
            }
            break;
        }
        case 46:
        {
            token.name = "string";
            token.value = letter;
            return token;
        }
        case 48:
        {
            c = getchar();
            if (c == '\n')
                state = 0;//回到初态，相当于终态
            else if (c == '*')
                state = 49;
            //都不是，则还是注释内容,state不变
            break;
        }
        case 49:
        {
            c = getchar();
            if (c == '/')
                state = 0;
            else
                state = 48;// /**/不完整
            break;
        }
        case 50:
        {
            c = getchar();
            if (isdigit(c))
                letter.push_back(c);
            else if (c == '.')
            {
                letter.push_back(c);
                state = 51;
            }
            else if (c == 'E' || c == 'e')
            {
                letter.push_back(c);
                state = 53;
            }
            else
            {
                ungetc(c, stdin);
                state = 57;
            }
            break;
        }
        case 51:
        {
            c = getchar();
            if (isdigit(c))
            {
                letter.push_back(c);
                state = 52;
            }
            break;
        }
        case 52:
        {
            c = getchar();
            if (isdigit(c))
                letter.push_back(c);
            else if (c=='E'||c=='e')
            {
                letter.push_back(c);
                state = 53;
            }
            else
            {
                ungetc(c,stdin);
                state = 58;
            }
            break;
        }
        case 53:
        {
            c = getchar();
            if (c == '+' || c == '-')
            {
                letter.push_back(c);
                state = 54;
            }
            else if (isdigit(c))
            {
                letter.push_back(c);
                state = 55;
            }
            break;
        }
        case 54:
        {
            c = getchar();
            if (isdigit(c))
            {
                letter.push_back(c);
                state = 55;
            }
            break;
        }
        case 55:
        {
            c = getchar();
            if (isdigit(c))
                letter.push_back(c);
            else
            {
                ungetc(c, stdin);
                state = 56;
            }
            break;
        }
        case 56:
        {
            token.name = "digit";
            token.value = letter;
            return token;
        }
        case 57:
        {
            token.name = "digit";
            token.value = letter;
            return token;
        }
        case 58:
        {
            token.name = "digit";
            token.value = letter;
            return token;
        }
        default:
            break;
        }
    }
}

int fail()
{
    int nextState=0;
    switch (state)
    {
    default:
        break;
    }
    return nextState;
}
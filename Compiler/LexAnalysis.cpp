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
int state;
int lexLength;
int row = 1;
extern FILE *fp;
extern TOKEN token;
TOKEN GetToken()
{
    state = 0;
    string letter;
    char c;
    lexLength = 0;
    while (!feof(fp)) //每次循环拿到一个字符
    {
        switch (state)
        {
        case 0:
        {
            c = getc(fp);
            if (c == '\n')
            {
                row++;
            }
            if (isspace(c))
            {
                state = 0;
            }
            else if (isalpha(c) || c == '_')
            {
                ungetc(c, fp);
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
            c = getc(fp);
            if (isalpha(c) || isdigit(c) || c == '_')
                letter.push_back(c);
            else
            //if (isspace(c)||c=='('||c==';')
            { //非字母非数字，回退一个字符，以便下次识别
                ungetc(c, fp);
                state = 2; //跳转到2号状态
            }
            //else
            //{
            //    ungetc(c, fp);
            //    state = fail();
            //}
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
        //    c = getc(fp);
        //    if (isdigit(c))
        //        letter.push_back(c);
        //    else
        //    { //非数字，回退一个字符，以便下次识别
        //        ungetc(c, fp);
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
            c = getc(fp);
            token.name = "operator";
            if (c == '+')
            {
                state = 7; //识别++
            }
            else
            {
                ungetc(c, fp); //+的下一个字符不是+
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
            c = getc(fp);
            token.name = "operator";
            if (c == '-')
            {
                state = 10; //识别--
            }
            else
            {
                ungetc(c, fp); //-的下一个字符不是-
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
            token.name = "operator";
            token.value = "*";
            return token;
        }
        case 12:
        {
            c = getc(fp);
            if (c != '/' && c != '*')
            {
                ungetc(c, fp);
                token.name = "operator";
                token.value = "/";
                return token;
            }
            else
            {
                state = 48; //识别到注释
                break;
            }
        }
        case 13:
        {
            c = getc(fp);
            token.name = "operator";
            if (c == '=')
            {
                state = 15; //识别==
            }
            else
            {
                ungetc(c, fp); // =的下一个字符不是=
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
            token.name = "operator";
            token.value = "{";
            return token;
        }
        case 18:
        {
            token.name = "operator";
            token.value = "}";
            return token;
        }
        case 19:
        {
            token.name = "operator";
            token.value = ";";
            return token;
        }
        case 20:
        {
            token.name = "operator";
            token.value = "(";
            return token;
        }
        case 21:
        {
            token.name = "operator";
            token.value = ")";
            return token;
        }
        case 22:
        {
            token.name = "operator";
            token.value = "'";
            return token;
        }
        case 23:
        {
            token.name = "operator";
            token.value = "'";
            return token;
        }
        case 24:
        {
            token.name = "operator";
            token.value = "\"";
            return token;
        }
        case 25:
        {
            token.name = "operator";
            token.value = "\"";
            return token;
        }
        case 26:
        {
            c = getc(fp);
            token.name = "operator";
            if (c == '=')
            {
                state = 28; //识别!=
            }
            else
            {
                ungetc(c, fp); // !的下一个字符不是=
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
            c = getc(fp);
            token.name = "operator";
            if (c == '&')
            {
                state = 31; //识别&&
            }
            else
            {
                ungetc(c, fp); // &的下一个字符不是&
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
            c = getc(fp);
            token.name = "operator";
            if (c == '|')
            {
                state = 34; //识别||
            }
            else
            {
                ungetc(c, fp); // |的下一个字符不是|
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
            c = getc(fp);
            token.name = "operator";
            if (c == '=')
            {
                state = 37; //识别>=
            }
            else
            {
                ungetc(c, fp); // >的下一个字符不是=
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
            c = getc(fp);
            token.name = "operator";
            if (c == '=')
            {
                state = 40; //识别<=
            }
            else
            {
                ungetc(c, fp); // <的下一个字符不是=
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
            c = getc(fp);
            if (c != '\\' && c != '\'')
            {
                letter.push_back(c);
                state = 42;
            }
            else if (c == '\\')
            {
                letter.push_back(c);
                state = 43; //带有转义斜杠
            }
            else // 单引号间无内容
            {
                ungetc(c, fp);
                state = fail();
            }
            break;
        }
        case 42:
        {
            c = getc(fp);
            if (c == '\'')
            {
                state = 44;
            }
            else
            {
                ungetc(c, fp);
                state = fail();
            }
            break;
        }
        case 43:
        {
            c = getc(fp);
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
            c = getc(fp);
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
            c = getc(fp);
            if (c == '\n')
            {
                ungetc(c, fp);
                state = 0; //回到初态，相当于终态
            }
            else if (c == '*')
                state = 49;
            //都不是，则还是注释内容,state不变
            break;
        }
        case 49:
        {
            c = getc(fp);
            if (c == '/')
                state = 0;
            else if (c == '\n')
                row++;
            else
            {
                state = 48; // /**/不完整
            }
            break;
        }
        case 50:
        {
            c = getc(fp);
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
            else if (c == 'L' || c == 'S')
                letter.push_back(c);
            else
            {
                ungetc(c, fp);
                state = 57;
            }
            break;
        }
        case 51:
        {
            c = getc(fp);
            if (isdigit(c))
            {
                letter.push_back(c);
                state = 52;
            }
            else
            {
                ungetc(c, fp);
                state = fail();
            }
            break;
        }
        case 52:
        {
            c = getc(fp);
            if (isdigit(c))
                letter.push_back(c);
            else if (c == 'E' || c == 'e')
            {
                letter.push_back(c);
                state = 53;
            }
            else if (c == 'L' || c == 'S')
                letter.push_back(c);
            else
            {
                ungetc(c, fp);
                state = 58;
            }
            break;
        }
        case 53:
        {
            c = getc(fp);
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
            else
            {
                ungetc(c, fp);
                state = fail();
            }
            break;
        }
        case 54:
        {
            c = getc(fp);
            if (isdigit(c))
            {
                letter.push_back(c);
                state = 55;
            }
            else
            {
                ungetc(c, fp);
                state = fail();
            }

            break;
        }
        case 55:
        {
            c = getc(fp);
            if (isdigit(c))
                letter.push_back(c);
            else if (c == 'L' || c == 'S')
                letter.push_back(c);
            else
            {
                ungetc(c, fp);
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
        case 999:
        {
            token.name = "Error";
            token.value = "";
            return token;
        }
        default:
            break;
        }
        lexLength++;
    }
    printf("---------------------lex end---------------------\n");
    return token;
}

int fail()
{
    int nextState = 0;
    switch (state)
    {
    case 1:
    {
        printf("define id error in row:%d line:%d\n", row, lexLength);
        break;
    }
    case 41:
    case 42:
    {
        printf("define const char error in row:%d line:%d\n", row, lexLength);
        break;
    }
    case 51:
    case 53:
    case 54:
    {
        printf("define number error in row:%d line:%d\n", row, lexLength);
        break;
    }
    default:
        break;
    }
    nextState = 999;
    return nextState;
}
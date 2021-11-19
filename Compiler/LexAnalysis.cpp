//#include<stdio.h>
#include<string>
#include<stdio.h>
#include<stdlib.h>
#include<vector>
#include<string>
#include<algorithm>
#include"LexAnalysis.h"
using namespace std;
const vector<string> keywords{ "if","else","while","do","main","int","float",
"double","return","const","void","continue","break","char","unsigned","enum",
"long","switch","case","auto","static" };

TOKEN GetToken()
{
	int state = 0;
	string letter;
	TOKEN token;
	char c;
	while (1)//每次循环拿到一个字符
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
				ungetc(c, stdin);
				state = 3;
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
			//else if (c == '"')
			//	state = 44;


			break; }
		case 1:
			c = getchar();
			if (isalpha(c) || isdigit(c)||c=='_')
				letter.push_back(c);
			else {//非字母非数字，回退一个字符，以便下次识别
				ungetc(c, stdin);
				state = 2;//跳转到2号状态
			}
			break;
		case 2:	//letter识别结束
		{
			auto iter = find(keywords.begin(), keywords.end(), letter);
			if (iter != keywords.end())//识别到保留字
			{
				token.name = "keyword";
				token.value = letter;
			}
			else
			{
				token.name = "id";
				token.value = letter;
			}
			return token;//综态，无sate变化
		}
		case 3:
			c = getchar();
			if (isdigit(c))
				letter.push_back(c);
			else {//非数字，回退一个字符，以便下次识别
				ungetc(c, stdin);
				state = 4;
			}
			break;
		case 4:
		{
			token.name = "digit";
			token.value = letter;
			return token;//综态，无sate变化
		}
		case 5: {
			c = getchar();
			token.name = "symbol";
			if (c == '+')
			{
				state = 7;//识别++
			}
			else
			{
				ungetc(c, stdin);//+的下一个字符不是+
				state = 6;
			}
			break;
		}
		case 6: {
			token.value = "+";
			return token;
		}
		case 7: {
			token.value = "++";
			return token;
		}
		case 8: {
			c = getchar();
			token.name = "symbol";
			if (c == '-')
			{
				state = 10;//识别--
			}
			else
			{
				ungetc(c, stdin);//-的下一个字符不是-
				state = 9;
			}
			break;
		}
		case 9: {
			token.value = "-";
			return token;
		}
		case 10: {
			token.value = "--";
			return token;
		}
		case 11: {
			token.name = "symbol";
			token.value = "*";
			return token;
		}
		case 12: {
			token.name = "symbol";
			token.value = "/";
			return token;
		}
		case 13: {
			c = getchar();
			token.name = "symbol";
			if (c == '=')
			{
				state = 15;//识别==
			}
			else
			{
				ungetc(c, stdin);// =的下一个字符不是=
				state = 14;
			}
			break;
		}
		case 14: {
			token.value = "=";
			return token;
		}
		case 15: {
			token.value = "==";
			return token;
		}
		case 17: {
			token.name = "symbol";
			token.value = "{";
			return token;
		}
		case 18: {
			token.name = "symbol";
			token.value = "}";
			return token;
		}
		case 19: {
			token.name = "symbol";
			token.value = ";";
			return token;
		}
		case 20: {
			token.name = "symbol";
			token.value = "(";
			return token;
		}
		case 21: {
			token.name = "symbol";
			token.value = ")";
			return token;
		}
		case 22: {
			token.name = "symbol";
			token.value = "'";
			return token;
		}
		case 23: {
			token.name = "symbol";
			token.value = "'";
			return token;
		}
		case 24: {
			token.name = "symbol";
			token.value = "\"";
			return token;
		}
		case 25: {
			token.name = "symbol";
			token.value = "\"";
			return token;
		}
		case 26: {
			c = getchar();
			token.name = "symbol";
			if (c == '=')
			{
				state = 28;//识别!=
			}
			else
			{
				ungetc(c, stdin);// !的下一个字符不是=
				state = 27;
			}
			break;
		}
		case 27: {
			token.value = "!";
			return token;
		}
		case 28: {
			token.value = "!=";
			return token;
		}
		case 29: {
			c = getchar();
			token.name = "symbol";
			if (c == '&')
			{
				state = 31;//识别&&
			}
			else
			{
				ungetc(c, stdin);// &的下一个字符不是&
				state = 30;
			}
			break;
		}
		case 30: {
			token.value = "&";
			return token;
		}
		case 31: {
			token.value = "&&";
			return token;
		}
		case 32: {
			c = getchar();
			token.name = "symbol";
			if (c == '|')
			{
				state = 34;//识别||
			}
			else
			{
				ungetc(c, stdin);// |的下一个字符不是|
				state = 33;
			}
			break;
		}
		case 33: {
			token.value = "|";
			return token;
		}
		case 34: {
			token.value = "||";
			return token;
		}
		case 35: {
			c = getchar();
			token.name = "symbol";
			if (c == '=')
			{
				state = 37;//识别>=
			}
			else
			{
				ungetc(c, stdin);// >的下一个字符不是=
				state = 36;
			}
			break;
		}
		case 36: {
			token.value = ">";
			return token;
		}
		case 37: {
			token.value = ">=";
			return token;
		}

		case 38: {
			c = getchar();
			token.name = "symbol";
			if (c == '=')
			{
				state = 40;//识别<=
			}
			else
			{
				ungetc(c, stdin);// <的下一个字符不是=
				state = 39;
			}
			break;
		}
		case 39: {
			token.value = "<";
			return token;
		}
		case 40: {
			token.value = "<=";
			return token;
		}
		case 41: {
			c = getchar();
			token.name = "char";
			letter.push_back(c);
			state = 42;
			break;
		}
		case 42: {
			c = getchar();
			if (c == '\'')
				state = 43;
			else
			{
				ungetc(c, stdin);
			}
		}
		case 43: {
			token.value = letter;
			return token;
		}

		default:
			break;
		}

	}
}
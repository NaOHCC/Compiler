//#include<stdio.h>
#include <string>
#include <stdio.h>
#include <stdlib.h>
#include <vector>
#include <string>
#include <algorithm>
#include "LexAnalysis.h"
using namespace std;
const vector<string> keywords{ "if", "else", "while", "do", "main", "int", "float",
							  "double", "return", "const", "void", "continue", "break", "char", "unsigned", "enum",
							  "long", "switch", "case", "auto", "static" };
int state;
int lexLength;

TOKEN GetToken(FILE* fp)
{
	state = 0;
	string letter;
	TOKEN token;
	char c;
	lexLength = 0;
	while (1) //ÿ��ѭ���õ�һ���ַ�
	{
		switch (state)
		{
		case 0:
		{
			c = getc(fp);
			if (isblank(c))
				state = 0;
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
			else if (isblank(c))
			{ //����ĸ�����֣�����һ���ַ����Ա��´�ʶ��
				ungetc(c, fp);
				state = 2; //��ת��2��״̬
			}
			else
			{
				ungetc(c, fp);
				state = fail();

			}
			break;
		case 2: //letterʶ�����
		{
			auto iter = find(keywords.begin(), keywords.end(), letter);
			if (iter != keywords.end()) //ʶ�𵽱�����
			{
				token.name = *iter;
				token.value = letter;
			}
			else
			{
				token.name = "id";
				token.value = letter;
			}
			return token; //��̬����sate�仯
		}
		//case 3:
		//    c = getc(fp);
		//    if (isdigit(c))
		//        letter.push_back(c);
		//    else
		//    { //�����֣�����һ���ַ����Ա��´�ʶ��
		//        ungetc(c, fp);
		//        state = 4;
		//    }
		//    break;
		//case 4:
		//{
		//    token.name = "digit";
		//    token.value = letter;
		//    return token; //��̬����sate�仯
		//}
		case 5:
		{
			c = getc(fp);
			token.name = "symbol";
			if (c == '+')
			{
				state = 7; //ʶ��++
			}
			else
			{
				ungetc(c, fp); //+����һ���ַ�����+
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
			token.name = "symbol";
			if (c == '-')
			{
				state = 10; //ʶ��--
			}
			else
			{
				ungetc(c, fp); //-����һ���ַ�����-
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
			c = getc(fp);
			if (c != '/' && c != '*')
			{
				ungetc(c, fp);
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
			c = getc(fp);
			token.name = "symbol";
			if (c == '=')
			{
				state = 15; //ʶ��==
			}
			else
			{
				ungetc(c, fp); // =����һ���ַ�����=
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
			c = getc(fp);
			token.name = "symbol";
			if (c == '=')
			{
				state = 28; //ʶ��!=
			}
			else
			{
				ungetc(c, fp); // !����һ���ַ�����=
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
			token.name = "symbol";
			if (c == '&')
			{
				state = 31; //ʶ��&&
			}
			else
			{
				ungetc(c, fp); // &����һ���ַ�����&
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
			token.name = "symbol";
			if (c == '|')
			{
				state = 34; //ʶ��||
			}
			else
			{
				ungetc(c, fp); // |����һ���ַ�����|
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
			token.name = "symbol";
			if (c == '=')
			{
				state = 37; //ʶ��>=
			}
			else
			{
				ungetc(c, fp); // >����һ���ַ�����=
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
			token.name = "symbol";
			if (c == '=')
			{
				state = 40; //ʶ��<=
			}
			else
			{
				ungetc(c, fp); // <����һ���ַ�����=
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
			token.name = "char"; //ȷ��Ϊ�ַ�����
			c = getc(fp);
			if (c != '\\')
			{
				letter.push_back(c);
				state = 42;
			}
			else
			{
				letter.push_back(c);
				state = 43; //����ת��б��
			}
			/*���ӳ�����*/
			break;
		}
		case 42:
		{
			c = getc(fp);
			if (c == '\'')
			{
				state = 44;
			}
			/*���ӳ�����*/
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
				state = 0;//�ص���̬���൱����̬
			else if (c == '*')
				state = 49;
			//�����ǣ�����ע������,state����
			break;
		}
		case 49:
		{
			c = getc(fp);
			if (c == '/')
				state = 0;
			else
				state = 48;// /**/������
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
			else
			{
				if (c == 'L' || c == 'S')
					letter.push_back(c);
				else
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
			else
			{
				if (c == 'L' || c == 'S')
					letter.push_back(c);
				else
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
			break;
		}
		case 55:
		{
			c = getc(fp);
			if (isdigit(c))
				letter.push_back(c);
			else
			{
				if (c == 'L' || c == 'S')
					letter.push_back(c);
				else
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
}

string numberType(string num)
{
	return "";
}

int fail()
{
	int nextState = 0;
	switch (state)
	{
	case 1:
	{
		printf("define id error in:%d\n", lexLength);
		break;
	}
	default:
		break;
	}
	nextState = 999;
	return nextState;
}
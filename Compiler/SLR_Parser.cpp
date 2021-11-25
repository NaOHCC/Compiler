#define _CRT_SECURE_NO_WARNINGS
#include <string>
#include <stack>
#include <vector>
#include <map>
#include <iostream>
#include "SLR_Parser.h"
#include "LexAnalysis.h"
using namespace std;
extern TOKEN token;

FILE *ACTION_FILE;
stack<int> slr_state;
vector<map<string, string>> ACTION;
vector<map<string, int>> GOTO;
vector<string> symbolList; //代表VT

void CreateACTIONandGOTO(const char *path)
{
    ACTION_FILE = fopen(path, "r+");
    char temp[1000];
    char *p;

    fgets(temp, 1000, ACTION_FILE);

    p = strtok(temp, ","); //得到一行的第一项

    for (int i = 0; i < VTCount + VNCount; i++)
    {
        p = strtok(NULL, ",");
        string str(p);
        size_t pos = str.find('\n'); //去除换行符
        if (pos < str.length())
            str.erase(pos, 1);
        symbolList.push_back(str);
    }

    memset(temp, 0, sizeof(temp) / sizeof(temp[0]));
    while (fgets(temp, 1000, ACTION_FILE))
    {
        map<string, string> m1;
        map<string, int> m2;
        p = strtok(temp, ",");            //得到一行的第一项
        for (int i = 0; i < VTCount; i++) //处理终结符
        {
            p = strtok(NULL, ",");
            m1.insert(make_pair(symbolList[i], string(p)));
        }
        for (int i = 0; i < VNCount; i++) //处理非终结符
        {
            p = strtok(NULL, ",");
            if (strcmp(p, "ERROR") >= 0)
                m2.insert(make_pair(symbolList[(long long)i + VTCount], -1));
            else
                m2.insert(make_pair(symbolList[(long long)i + VTCount], stoi(string(p))));
        }

        memset(temp, 0, sizeof(temp) / sizeof(temp[0]));
        ACTION.push_back(m1);
        GOTO.push_back(m2);
    }

    //for (int i = 0; i < ACTION.size(); i++)
    //{
    //	for (auto j = ACTION[i].begin(); j != ACTION[i].end(); j++)
    //	{
    //		cout << (*j).first << " " << (*j).second << " ";

    //	}
    //	cout << endl;
    //}
    //for (int i = 0; i < GOTO.size(); i++)
    //{
    //	for (auto j = GOTO[i].begin(); j != GOTO[i].end(); j++)
    //	{
    //		cout << (*j).first << " " << (*j).second << " ";

    //	}
    //	cout << endl;
    //}
}

string a;
void getNextSymbol()
{
    token = GetToken();
    if (token.name == "operator" || token.name == "ENDFLAG")
        a = token.value;
    else
        a = token.name;
}

vector<RULE> rules{RULE()};
void ReadRules(const char *path)
{
    FILE *fp = fopen(path, "r+");
    char temp[1000];

    while (fgets(temp, 1000, fp))
    {
        string s = temp;
        RULE rule;
        size_t pos = s.find("->");
        rule.no_terminal = s.substr(0, pos);
        s.erase(0, pos + 2);
        string str;
        for (int i = 0; i < s.length(); i++)
        {
            if (isspace(s[i]) || s[i] == '\n')
            {
                rule.symbol.push_back(str);
                str.clear();
            }
            else
            {
                str += s[i];
            }
        }
        rules.push_back(rule);
    }

    //for (int i = 0; i < _rules.size(); i++)
    //{
    //	cout << _rules[i].no_terminal << "->";
    //	for(int j=0;j<_rules[i].symbol.size();j++)
    //	{
    //		cout << _rules[i].symbol[j] << " ";
    //	}
    //	cout << endl;
    //}
}

void PrintRule(const int &n)
{
    printf("%2d:%s->", n, rules[n].no_terminal.c_str());
    for (int i = 0; i < rules[n].length(); i++)
    {
        cout << rules[n].symbol[i] << " ";
    }
    cout << endl;
}

void SLR()
{
    slr_state.push(0);
    getNextSymbol();
    while (1)
    {
        int top = slr_state.top();

        string cc = ACTION[top][a];
        if (ACTION[top][a][0] == 's') //移进
        {
            slr_state.push(stoi(ACTION[top][a].erase(0, 1)));
            getNextSymbol();
        }
        else if (ACTION[top][a][0] == 'r') //规约
        {
            int rule_number = stoi(ACTION[top][a].erase(0, 1));
            for (int i = 0; i < rules[rule_number].length(); i++) //符号出栈
                slr_state.pop();
            top = slr_state.top();
            slr_state.push(GOTO[top][rules[rule_number].no_terminal]); //跳转
            PrintRule(rule_number);
        }
        else if (ACTION[top][a] == "acc") //接受
        {
            printf("acc\n");
            break;
        }
        else
        {
            printf("Error\n");
        }
    }
}
#define _CRT_SECURE_NO_WARNINGS
#include"LexAnalysis.h"
#include<string>
#include<stack>
#include<vector>
#include<map>
#include<iostream>
using namespace std;
extern TOKEN token;

FILE* ACTION_FILE;
FILE* GOTO_FILE;
stack<int> s;
vector<map<string,string>> ACTION;
vector<map<string, int>> GOTO;

int count(const char* s, const char c)
{
    const char* p = s;
    int i = 0;
    while (*p != '\0')
    {
        if (c == *p)
            i++;
        p++;
    }
    return i;
}

int VTCount=15;
int VNCount=8;

void CreateACTION(const char *path)
{
    ACTION_FILE = fopen(path, "r+");
    char temp[1000];
    char* p;
    vector<string> v;//代表VT

    fgets(temp, 1000, ACTION_FILE);

    p = strtok(temp, ",");//得到一行的第一项
    string tempStr(p);

    for (int i = 0; i < VTCount; i++)
    {
        p = strtok(NULL, ",");
        tempStr = p;
        v.push_back(tempStr);
    }

    memset(temp, 0, sizeof(temp) / sizeof(temp[0]));
    while (fgets(temp, 1000, ACTION_FILE))
    {
        map<string, string> m;
        p = strtok(temp, ",");//得到一行的第一项
        for (int i = 0; i < VTCount; i++)
        {
                p = strtok(NULL, ",");
                tempStr = p;
                if (tempStr != "ERROR")
                {
                    m.insert(make_pair(v[i], tempStr));
                }
        }
        memset(temp, 0, sizeof(temp) / sizeof(temp[0]));
        ACTION.push_back(m);
    }
    for (auto i = ACTION.begin(); i != ACTION.end(); i++)
    {
        for (auto j=(*i).begin(); j!= (*i).end(); j++)
        {
            cout << (*j).first<<" " << (*j).second<<" ";
        }
        cout << endl;
    }
}

void CreateGOTO(const char* path)
{

}

void SLR()
{

}
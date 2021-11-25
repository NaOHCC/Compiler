#pragma once
#ifndef LEX_ANALYSIS_
#define LEX_ANALYSIS_
#include <string>
using namespace std;
struct TOKEN
{
    string name;  //TOKEN NAME
    string value; //TOKEN Attribute Value
};
TOKEN GetToken();

int fail();
#endif // !LEX_ANALYSIS_
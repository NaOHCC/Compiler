#pragma once
#include <string>
using namespace std;
struct TOKEN
{
	string name;//TOKEN NAME
	string value;//TOKEN Attribute Value
};
TOKEN GetToken(FILE *);

int fail();
#pragma once
#ifndef SLR_PARSER
#define SLR_PARSER
#include <string>
#include <vector>
#define VTCount 15
#define VNCount 8
struct RULE
{
    std::string no_terminal;
    std::vector<std::string> symbol;
    int length()
    {
        return symbol.size();
    }
};

void ReadRules(const char *path);
void CreateACTIONandGOTO(const char *path);
void SLR();
#endif // !SLR_PARSER

#pragma once
#ifndef SLR_PARSER
#define SLR_PARSER
#include<string>
#define VTCount 15
#define VNCount 8
struct RULE {
	std::string terminal;
	int length;
};

void CreateACTIONandGOTO(const char* path);
void SLR();
#endif // !SLR_PARSER

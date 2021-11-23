#include"LexAnalysis.h"
#include"RecursiveDescentParser.h"
extern TOKEN token;
extern FILE* fp;

void expr();

void factor()
{

}

void term()
{

}

void expr()
{

}

void _bool()
{

}

void stmt()
{

}

void stmts()
{
	stmt();
}

void block()
{
	if (token.value == "{")
		token=GetToken(fp);
	else
	{
		printf("Error\n");
	}
	stmts();
	if (token.value == "{")
		token = GetToken(fp);
	else
	{
		printf("Error\n");
	}

}

void program()
{
	block();
}
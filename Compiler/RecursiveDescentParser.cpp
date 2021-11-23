#include "LexAnalysis.h"
#include "RecursiveDescentParser.h"
extern TOKEN token;
extern FILE *fp;

void expr();

void factor() //factor->(expr) | id | digit
{
    if (token.name == "operator" && token.value == "(")
    {
        printf("factor->(expr)\n");
        token = GetToken();
        expr();
        if (token.name != "operator" && token.value != ")")
        {
            printf("factor() Error\n");
            return;
        }
    }
    else if (token.name == "id")
    {
        printf("factor->id\n");
        token = GetToken();
        return;
    }
    else if (token.name == "digit")
    {
        printf("factor->digit\n");
        token = GetToken();
        return;
    }
    else
    {
        printf("factor() Error\n");
        return;
    }
}

void _term() // _term->* factor _term | / factor _term | epsilon
{
    if (token.name == "operator" && token.value == "*")
    {
        printf("_term->* factor _term\n");
        token = GetToken();
        factor();
        _term();
        return;
    }
    else if (token.name == "operator" && token.value == "/")
    {
        printf("_term->/ factor _term\n");
        token = GetToken();
        factor();
        _term();
        return;
    }
    else // _term->epsilon
    {
        printf("_term->epsilon\n");
        return;
    }
}

void term() // term->factor _term
{
    printf("term->factor _term\n");
    factor();
    _term();
    return;
}

void _expr() // _expr-> + term _expr | - term _expr | epsilon
{
    if (token.name == "operator" && token.value == "+")
    {
        printf("_expr-> + term _expr\n");
        token = GetToken();
        term();
        _expr();
        return;
    }
    else if (token.name == "operator" && token.value == "-")
    {
        printf("_expr-> - term _expr\n");
        token = GetToken();
        term();
        _expr();
        return;
    }
    else // _expr->epsilon
    {
        printf("_expr-> epsilon\n");
        return;
    }
}

void expr() // expr-> term _expr
{
    printf("expr-> term _expr\n");
    term();
    _expr();
    return;
}

void __bool() //__bool-> < expr | <= expr | > expr | >= expr | epsilon
{
    if (token.name == "operator" && token.value == "<")
    {
        printf("__bool-> < expr\n");
        token = GetToken();
        expr();
        return;
    }
    else if (token.name == "operator" && token.value == "<=")
    {
        printf("__bool-> <= expr\n");
        token = GetToken();
        expr();
        return;
    }
    else if (token.name == "operator" && token.value == ">")
    {
        printf("__bool-> > expr\n");
        token = GetToken();
        expr();
        return;
    }
    else if (token.name == "operator" && token.value == ">=")
    {
        printf("__bool-> >= expr\n");
        token = GetToken();
        expr();
        return;
    }
    else //__bool-> epsilon
    {
        printf("__bool-> epsilon\n");
        return;
    }
}

void _bool() //_bool-> expr __bool
{
    printf("_bool-> expr __bool\n");
    expr();
    __bool();
    return;
}

void block();
void stmt();
void _stmt() // _stmt-> else stmt | epsilon
{
    if (token.name == "else")
    {
        printf("_stmt-> else stmt\n");
        token = GetToken();
        stmt();
        return;
    }
    else // _stmt-> epsilon
    {
        printf("epsilon\n");
        return;
    }
}
/*
stmt->	if ( _bool ) stmt _stmt |
		id = expr ; |
		while ( _bool ) stmt |
		do stmt while ( _bool ) |
		break |
		block
*/
void stmt()
{
    if (token.name == "if")
    {
        printf("stmt->if ( _bool ) stmt _stmt\n");
        token = GetToken();
        if (token.name == "operator" && token.value == "(")
        {
            token = GetToken();
            _bool();
            if (token.name == "operator" && token.value == ")")
            {
                token = GetToken();
                stmt();
                _stmt();
            }
        }
    }
    else if (token.name == "id")
    {
        printf("stmt->id = expr ;\n");
        token = GetToken();
        if (token.name == "operator" && token.value == "=")
        {
            token = GetToken();
            expr();
            if (token.name == "operator" && token.value == ";")
            {
                token = GetToken();
                //printf("stmt success\n");
                return;
            }
        }
    }
    else if (token.name == "while")
    {
        printf("stmt->while ( _bool ) stmt\n");
        token = GetToken();
        if (token.name == "operator" && token.value == "(")
        {
            token = GetToken();
            _bool();
            if (token.name == "operator" && token.value == ")")
            {
                token = GetToken();
                stmt();
            }
        }
    }
    else if (token.name == "do")
    {
        printf("do stmt while ( _bool )\n");
        token = GetToken();
        stmt();
        if (token.name == "while")
        {
            token = GetToken();
            if (token.name == "operator" && token.value == "(")
            {
                token = GetToken();
                _bool();
                if (token.name == "operator" && token.value == ")")
                {
                    token = GetToken();
                }
            }
        }
    }
    else if (token.name == "break")
    {
        printf("stmt->break\n");
        token = GetToken();
    }
    else
    {
        printf("stmt->block\n");
        block();
    }
}

void stmts() // stmts-> stmt stmts | epsilon
{
    if (!(token.name == "operator" && token.value == "}"))
    {
        printf("stmts-> stmt stmts\n");
        stmt();
        stmts();
    }
    else
    {
        printf("stmts-> epsilon\n");
        return;
    }
}

void block() // block-> { stmts }
{
    printf("block-> { stmts }\n");
    if (token.name == "operator" && token.value == "{")
    {
        token = GetToken();
        stmts();
        if (token.name == "operator" && token.value == "}")
        {
            token = GetToken();
        }
    }
}

void program() // program-> block
{
    printf("program-> block\n");
    block();
}
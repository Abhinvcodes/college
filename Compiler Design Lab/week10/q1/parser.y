%{
#include <stdio.h>
#include <stdlib.h>

void yyerror(const char *s);
int yylex();
%}

%token INT FLOAT CHAR DOUBLE VOID IDENTIFIER NUMBER
%token COMMA SEMICOLON ASTERISK EQUALS

%%

declaration:
    type_specifier init_declarator_list SEMICOLON { printf("Valid C declaration found!\n"); }
    ;

type_specifier:
    INT | FLOAT | CHAR | DOUBLE | VOID
    ;

init_declarator_list:
    init_declarator
    | init_declarator COMMA init_declarator_list
    ;

init_declarator:
    declarator
    | declarator EQUALS NUMBER
    ;

declarator:
    pointer direct_declarator
    | direct_declarator
    ;

pointer:
    ASTERISK
    | ASTERISK pointer
    ;

direct_declarator:
    IDENTIFIER
    ;

%%

void yyerror(const char *s) {
    fprintf(stderr, "Syntax Error: %s\n", s);
}

int main() {
    printf("Enter a C declaration: ");
    return yyparse();
}

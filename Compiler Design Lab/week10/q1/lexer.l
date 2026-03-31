%{
#include "parser.tab.h"
#include <stdlib.h>
#include <string.h>
%}

%%
"int"       { return INT; }
"float"     { return FLOAT; }
"char"      { return CHAR; }
"double"    { return DOUBLE; }
"void"      { return VOID; }

[a-zA-Z_][a-zA-Z0-9_]* { return IDENTIFIER; }
[0-9]+                  { return NUMBER; }

","         { return COMMA; }
";"         { return SEMICOLON; }
"*"         { return ASTERISK; }
"="         { return EQUALS; }

[ \t\n]     ; /* Skip whitespace */
.           { printf("Unknown character: %s\n", yytext); }

%%

int yywrap() {
    return 1;
}

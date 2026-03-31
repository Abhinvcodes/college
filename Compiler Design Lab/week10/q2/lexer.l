%{
#include "parser.tab.h"
%}

%%
"if"        { return IF; }
"else"      { return ELSE; }
"switch"    { return SWITCH; }
"case"      { return CASE; }
"default"   { return DEFAULT; }
"break"     { return BREAK; }
"("         { return LPAREN; }
")"         { return RPAREN; }
"{"         { return LBRACE; }
"}"         { return RBRACE; }
":"         { return COLON; }
";"         { return SEMICOLON; }
[a-zA-Z_][a-zA-Z0-9_]* { return IDENTIFIER; }
[0-9]+      { return NUMBER; }
[ \t\n]     ; /* ignore whitespace */
.           { printf("Unknown character: %s\n", yytext); }
%%

int yywrap() {
    return 1;
}


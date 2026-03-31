%{
#include "parser.tab.h"
#include <math.h>
%}

%%

[0-9]+(\.[0-9]+)? { yylval.dval = atof(yytext); return NUM; }
"+"               { return PLUS; }
"-"               { return MINUS; }
"*"               { return MULT; }
"/"               { return DIV; }
"^"               { return EXPON; }
"n"               { return NEG; }
"\n"              { return NEWLINE; }
[ \t]             ; /* skip whitespace */
.                 { printf("Unknown character: %s\n", yytext); }

%%

int yywrap() { return 1; }

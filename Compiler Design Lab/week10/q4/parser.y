%{
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

void yyerror(const char *s);
int yylex();
%}

%union {
    double dval;
}

%token <dval> NUM
%token PLUS MINUS MULT DIV EXPON NEG NEWLINE
%type <dval> exp

%%

input:
    | input line
    ;

line:
    NEWLINE
    | exp NEWLINE { printf("\tResult: %.2f\n", $1); }
    ;

exp:
    NUM             { $$ = $1; }
    | exp exp PLUS  { $$ = $1 + $2; }
    | exp exp MINUS { $$ = $1 - $2; }
    | exp exp MULT  { $$ = $1 * $2; }
    | exp exp DIV   { 
                        if ($2 == 0) {
                            yyerror("Division by zero");
                            $$ = 0;
                        } else {
                            $$ = $1 / $2;
                        }
                    }
    | exp exp EXPON { $$ = pow($1, $2); }
    | exp NEG       { $$ = -$1; }
    ;

%%

void yyerror(const char *s) {
    fprintf(stderr, "Error: %s\n", s);
}

int main() {
    printf("Postfix Calculator (Use 'n' for unary negation)\n");
    printf("Example: 3 4 + 2 * n (Result: -14.00)\n");
    yyparse();
    return 0;
}

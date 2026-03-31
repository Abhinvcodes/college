%{
#include <stdio.h>
#include <stdlib.h>

void yyerror(const char *s);
int yylex();
%}

/* Define the union to hold double values */
%union {
    double dval;
}

/* Assign tokens and rules to the dval type */
%token <dval> NUM
%token PLUS MINUS MULT DIV LPAREN RPAREN NEWLINE

/* Define Precedence: Bottom has higher priority */
%left PLUS MINUS
%left MULT DIV
%nonassoc UMINUS  /* For unary minus like -5 */

%type <dval> exp

%%

input:
    | input line
    ;

line:
    NEWLINE
    | exp NEWLINE { printf("\tResult: %.4f\n", $1); }
    | error NEWLINE { yyerrok; } /* Recover from errors */
    ;

exp:
    NUM                 { $$ = $1; }
    | exp PLUS exp      { $$ = $1 + $3; }
    | exp MINUS exp     { $$ = $1 - $3; }
    | exp MULT exp      { $$ = $1 * $3; }
    | exp DIV exp       { 
                            if ($3 == 0) {
                                yyerror("Division by zero");
                                $$ = 0;
                            } else {
                                $$ = $1 / $3;
                            }
                        }
    | MINUS exp %prec UMINUS { $$ = -$2; }
    | LPAREN exp RPAREN { $$ = $2; }
    ;

%%

void yyerror(const char *s) {
    fprintf(stderr, "Error: %s\n", s);
}

int main() {
    printf("Infix Double Calculator.\n");
    yyparse();
    return 0;
}

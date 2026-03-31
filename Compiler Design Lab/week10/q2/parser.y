%{
#include <stdio.h>
#include <stdlib.h>

void yyerror(const char *s);
int yylex();
%}

/* Token Definitions */
%token IF ELSE SWITCH CASE DEFAULT
%token LPAREN RPAREN LBRACE RBRACE COLON SEMICOLON
%token IDENTIFIER NUMBER
%token BREAK

/* Precedence to solve the Dangling Else ambiguity */
%nonassoc LOWER_THAN_ELSE
%nonassoc ELSE

%%

/* The start symbol can be a single statement or a list of them */
program:
    statement_list
    ;

statement_list:
    statement
    | statement_list statement
    ;

statement:
    selection_statement
    | expression_statement
    | compound_statement
    | jump_statement
    | labeled_statement
    ;

/* Decision Making Logic */
selection_statement:
    IF LPAREN expression RPAREN statement %prec LOWER_THAN_ELSE { 
        printf("Parsed: If statement\n"); 
    }
    | IF LPAREN expression RPAREN statement ELSE statement { 
        printf("Parsed: If-Else statement\n"); 
    }
    | SWITCH LPAREN expression RPAREN LBRACE labeled_statement_list RBRACE { 
        printf("Parsed: Switch statement\n"); 
    }
    ;

labeled_statement_list:
    labeled_statement
    | labeled_statement_list labeled_statement
    ;

labeled_statement:
    CASE expression COLON statement { printf("  -> Case label\n"); }
    | DEFAULT COLON statement { printf("  -> Default label\n"); }
    ;

compound_statement:
    LBRACE statement_list RBRACE
    | LBRACE RBRACE
    ;

expression_statement:
    expression SEMICOLON
    | SEMICOLON
    ;

jump_statement:
    BREAK SEMICOLON { printf("  -> Break statement\n"); }
    ;

/* Simplified expression for demonstration */
expression:
    IDENTIFIER
    | NUMBER
    ;

%%

void yyerror(const char *s) {
    fprintf(stderr, "Grammar Error: %s\n", s);
}

int main() {
    printf("Enter C decision statements (Ctrl+D to finish):\n");
    return yyparse();
}

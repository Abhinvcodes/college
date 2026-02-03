%{
#include <stdio.h>
int posint = 0;
int negint = 0;
int floatpos = 0;
int floatneg = 0;
%}

%%
 /* 1. Match Negative Floats first */
-[0-9]+\.[0-9]+    { floatneg++; }

 /* 2. Match Positive Floats (optional + sign) */
\+?[0-9]+\.[0-9]+  { floatpos++; }

 /* 3. Match Negative Integers */
-[0-9]+            { negint++; }

 /* 4. Match Positive Integers (optional + sign) */
\+?[0-9]+          { posint++; }

[ \t\n]            { /* Ignore whitespace */ }
.                  { /* Ignore other characters */ }
%%

int main() {
    printf("Enter numbers (Ctrl+D to finish):\n");
    yylex();
    printf("\n--- Summary ---\n");
    printf("Positive integers: %d\n", posint);
    printf("Negative integers: %d\n", negint);
    printf("Positive floating point: %d\n", floatpos);
    printf("Negative floating point: %d\n", floatneg);
    return 0;
}

int yywrap() { return 1; }

%{
#include <stdio.h>
int words = 0;
int chars = 0;
int blanks = 0;
int lines = 0;
%}

%%
[a-zA-Z_][a-zA-Z0-9_]* { words++; chars += yyleng; } 
[ ]+                   { blanks += yyleng; } /* Counting total spaces */
\n                     { lines++; }
.                      { chars++; } /* Catch other characters like dots or brackets */
%%

int main() {
    printf("Enter string (Ctrl+D to finish):\n");
    yylex();
    printf("\n--- Results ---\n");
    printf("Words: %d\nChars: %d\nBlanks: %d\nLines: %d\n", words, chars, blanks, lines);
    return 0;
}

int yywrap() { return 1; }

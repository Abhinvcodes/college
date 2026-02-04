%{
#include <stdio.h>
int vowels = 0;
int consonants = 0;
%}

%%

[aeiouAEIOU]          { vowels++; }
[a-zA-Z]              { consonants++; }
.                     { /* Ignore everything else (spaces, punctuation, digits) */ }

%%

int main() {
    printf("Enter a string: \n");
    yylex();
    printf("\n--- Results ---\n");
    printf("Vowels: %d\n", vowels);
    printf("Consonants: %d\n", consonants);
    return 0;
}

int yywrap() {
    return 1;
}

%{
#include <stdio.h>
#include <stdlib.h> /* Required for atoi() */

int num[100];
int i = 0;
%}

%%
[0-9]+  { 
          /* Convert string yytext to integer before storing */
          num[i++] = atoi(yytext); 
        }
[ \t\n] { /* ignore whitespace */ }
.       { /* ignore other chars */ }
%%

void printHex(int n) {
    if (n == 0) {
        printf("0");
        return;
    }

    char hex[50];
    int j = 0;

    while (n > 0) {
        int temp = n % 16;
        if (temp < 10)
            hex[j++] = temp + 48; // '0'-'9'
        else
            hex[j++] = temp + 55; // 'A'-'F'
        n = n / 16;
    }

    /* Important: Print the array in REVERSE order */
    for (int k = j - 1; k >= 0; k--) {
        printf("%c", hex[k]);
    }
}

int main() {
    printf("Enter numbers (Ctrl+D to finish):\n");
    yylex();

    printf("\n--- Hexadecimal Results ---\n");
    for(int k = 0; k < i; k++) {
        printf("Decimal %d to Hex: ", num[k]);
        printHex(num[k]);
        printf("\n");
    }
    return 0;
}

int yywrap() { return 1; }

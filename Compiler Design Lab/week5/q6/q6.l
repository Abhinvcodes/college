%{
#include <stdio.h>
#include <ctype.h>
int count = 0;
%}

/* Define a start condition for multi-line comments */
%x COMMENT

%%

 /* 1. Handle Single-line Comments */
"//".* { fprintf(yyout, "%s", yytext); }

 /* 2. Handle Multi-line Comments */
"/*"                { fprintf(yyout, "%s", yytext); BEGIN(COMMENT); }
<COMMENT>"*/"       { fprintf(yyout, "%s", yytext); BEGIN(INITIAL); }
<COMMENT>.          { fputc(yytext[0], yyout); }
<COMMENT>\n         { fputc('\n', yyout); }

 /* 3. Handle Uppercase Conversion (Only in INITIAL state) */
[A-Z]               { 
                      count++; 
                      fputc(tolower(yytext[0]), yyout); 
                    }

 /* 4. Handle all other characters */
.                   { fputc(yytext[0], yyout); }
\n                  { fputc('\n', yyout); }

%%

int main(int argc, char **argv) {
    if (argc < 3) {
        printf("Usage: %s <input_file> <output_file>\n", argv[0]);
        return 1;
    }

    yyin = fopen(argv[1], "r");
    yyout = fopen(argv[2], "w");

    if (!yyin || !yyout) {
        perror("File error");
        return 1;
    }

    yylex();

    fprintf(yyout, "\n\n/* --- Statistics --- */\n");
    fprintf(yyout, "/* Total uppercase characters replaced: %d */\n", count);

    fclose(yyin);
    fclose(yyout);
    return 0;
}

int yywrap() { return 1; }

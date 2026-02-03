%{
#include <stdio.h>
int s_count = 0;
int p_count = 0;
%}

%%

"scanf"     { s_count++; fprintf(yyout, "READ"); }
"printf"    { p_count++; fprintf(yyout, "WRITE"); }

%%

int main(int argc, char **argv) {
    if (argc < 3) {
        printf("Usage: %s <input_file> <output_file>\n", argv[0]);
        return 1;
    }

    // Open input file
    yyin = fopen(argv[1], "r");
    if (!yyin) {
        perror("Error opening input file");
        return 1;
    }

    // Open output file
    yyout = fopen(argv[2], "w");
    if (!yyout) {
        perror("Error creating output file");
        return 1;
    }

    yylex();

    // Append statistics to the end of the output file
    fprintf(yyout, "\n\n/* --- Statistics --- */\n");
    fprintf(yyout, "/* Total scanf replaced: %d */\n", s_count);
    fprintf(yyout, "/* Total printf replaced: %d */\n", p_count);

    fclose(yyin);
    fclose(yyout);
    
    printf("Processing complete. Check %s for results.\n", argv[2]);
    return 0;
}

int yywrap() {
    return 1;
}

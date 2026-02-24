#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>

typedef struct {
    char token_name[100];
    unsigned int row, col;
    char type[50];
} Token;

FILE *f1;
int ROW = 1, COL = 1;
int c;
Token t;
// List of C Keywords
const char *keywords[] = {
    "auto", "break", "case", "char", "const", "continue", "default", "do",
    "double", "else", "enum", "extern", "float", "for", "goto", "if",
    "int", "long", "register", "return", "short", "signed", "sizeof", "static",
    "struct", "switch", "typedef", "union", "unsigned", "void", "volatile", "while"
};

int isDataType(Token t);
int isKeyword(char *buffer);
Token getNextToken();
void error(const char* message);
void skip_whitespace();
void match(char *expected);

void assign_stat();
void identfier_list();
void data_type();
void declarations();
void Program();

int main() {
    f1 = fopen("input.c", "r");
    if (!f1) {
        printf("Error: Could not open input.c\n");
        return 1;
    }

    while (1) {
        t = getNextToken();
        if (t.row == 0) break;

        Program();
        printf("program accepted");
    }
    printf("\n");

    fclose(f1);
    return 0;
}
int isDataType(Token t)
{
    if(strcmp(t.token_name,"int")==0 || strcmp(t.token_name,"char")==0)
        return 1;
    return 0;
}
int isKeyword(char *buffer) {
    for (int i = 0; i < 32; i++) {
        if (strcmp(keywords[i], buffer) == 0) return 1;
    }
    return 0;
}


void Program()
{
    match("main");
    match("(");
    match(")");
    match("{");
    declarations();
    assign_stat();
    t = getNextToken();
    match("}");
}
void declarations()
{
    if(!isDataType(t))
        return;
    data_type();
    identfier_list();
    match(";");
    declarations();
}
void data_type()
{
    if(isDataType(t))
        t=getNextToken();
    else
        error("expected 'int' , 'char' ");
}
void identfier_list()
{
    if(strcmp(t.type, "id")==0){
        t = getNextToken();
        if(strcmp(t.type,",")==0)
        {
            t = getNextToken();
            identfier_list();
        }
        else
            return;
    }
    else
        error("expected 'id'");
}
void assign_stat()
{
    
    if(strcmp(t.type,"id")==0)
    {
        t=getNextToken();
        if(strcmp(t.type,"=")==0)
        {
            t = getNextToken();
            if(strcmp(t.type,"id")==0 || strcmp(t.type,"num")==0)
            {
                t=getNextToken();
                if(strcmp(t.token_name,";")==0)
                    return;
                else
                    error("expected ';'");
            }
            else
                error("expected an 'id' or 'num' token type");
        }
        else
            error("expected '='");
    }
    else
        error("expcted 'id' token type");
}


void match(char *expected) {
    skip_whitespace();
    if (strcmp(t.token_name, expected)==0) {
        skip_whitespace();
        t = getNextToken();
    } else {
        char msg[50];
        sprintf(msg, "Expected '%s'", expected);
        error(msg);
    }
}
void skip_whitespace() {
    while (c == ' ' || c == '\t' || c == '\n' || c == '\r') {
        c=getc(f1);
    }
}

void error(const char* message) {
    if (c == '\0') {
        printf("\nError: %s. Reached End of String unexpectedly.\n", message);
    } else {
        printf("\nError: %s. Found '%s' at position.\n", message, t.token_name);
    }
    fclose(f1);
    exit(1);
}

Token getNextToken() {
    t.token_name[0] = '\0';

    while ((c = fgetc(f1)) != EOF) {
        // 1. Skip Whitespace & Update Line/Col
        if (c == '\n') { ROW++; COL = 1; continue; }
        if (isspace(c)) { COL++; continue; }

        // 2. Skip Preprocessor Directives
        if (c == '#') {
            while ((c = fgetc(f1)) != '\n' && c != EOF);
            ROW++; COL = 1; continue;
        }

        // 3. Skip Comments (Single and Multi-line)
        if (c == '/') {
            int next = fgetc(f1);
            if (next == '/') { // Single line
                while ((c = fgetc(f1)) != '\n' && c != EOF);
                ROW++; COL = 1; continue;
            } else if (next == '*') { // Multi-line
                while (1) {
                    c = fgetc(f1);
                    if (c == '\n') { ROW++; COL = 1; }
                    else COL++;
                    if (c == '*' && (next = fgetc(f1)) == '/') { COL++; break; }
                    if (c == EOF) break;
                }
                continue;
            } else ungetc(next, f1); // Just a division operator
        }

        // --- Start of Token Identification ---
        t.row = ROW; t.col = COL;

        // 4. Identifiers and Keywords
        if (isalpha(c) || c == '_') {
            int i = 0;
            t.token_name[i++] = c;
            while (isalnum(c = fgetc(f1)) || c == '_') {
                if (i < 99) t.token_name[i++] = c;
            }
            ungetc(c, f1);
            t.token_name[i] = '\0';
            COL += i;
            if (isKeyword(t.token_name)) strcpy(t.type, t.token_name);
            else strcpy(t.type, "id");
            return t;
        }

        // 5. Numerical Constants
        if (isdigit(c)) {
            int i = 0;
            t.token_name[i++] = c;
            while (isdigit(c = fgetc(f1))) {
                if (i < 99) t.token_name[i++] = c;
            }
            ungetc(c, f1);
            t.token_name[i] = '\0';
            COL += i;
            strcpy(t.type, "num");
            return t;
        }

        // 6. String Literals
        if (c == '"') {
            int i = 0;
            while ((c = fgetc(f1)) != '"' && c != EOF) {
                if (c == '\n') { ROW++; COL = 1; }
                if (i < 99) t.token_name[i++] = c;
            }
            t.token_name[i] = '\0';
            COL += (i + 2); 
            strcpy(t.type, "string");
            return t;
        }

        // 7. Arithmetic, Relational, and Logical Operators
        t.token_name[0] = c; t.token_name[1] = '\0';
        if (strchr("+-*/%=!><&|", c)) {
            int next = fgetc(f1);
            // Check for compound: ==, !=, <=, >=, ++, --, &&, ||
            if ((next == '=') || 
                (c == '+' && next == '+') || 
                (c == '-' && next == '-') || 
                (c == '&' && next == '&') || 
                (c == '|' && next == '|')) {
                t.token_name[1] = next; t.token_name[2] = '\0';
                COL += 2;
            } else {
                ungetc(next, f1);
                COL += 1;
            }
            strcpy(t.type, t.token_name);
            return t;
        }

        // 8. Special Symbols (parentheses, brackets, commas, etc.)
        if (strchr("(){}[],.;", c)) {
            strcpy(t.type, t.token_name);
            COL++;
            return t;
        }

        // Unknown character
        strcpy(t.type, "unknown");
        COL++;
        return t;
    }
    t.row = 0; // EOF Signal
    return t;
}
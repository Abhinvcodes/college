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

const char *keywords[] = {
    "auto", "break", "case", "char", "const", "continue", "default", "do",
    "double", "else", "enum", "extern", "float", "for", "goto", "if",
    "int", "long", "register", "return", "short", "signed", "sizeof", "static",
    "struct", "switch", "typedef", "union", "unsigned", "void", "volatile", "while"
};

// --- Prototypes ---
void Program();
void declarations();
void identifier_list();
void data_type();
void statement_list();
void statement();
void assign_stat();
void decision_stat();
void dprime();
void expn();
void eprime();
void simple_expn();
void seprime();
void term();
void tprime();
void factor();
void relop();
void addop();
void mulop();

// Helper functions
int isKeyword(char *buffer);
int isDataType();
int isRelop();
int isAddop();
int isMulop();
Token getNextToken();
void error(const char* message);
int matchToken(char *expected);
int matchType(char *expected);

int main() {
    f1 = fopen("input.c", "r");
    if (!f1) {
        printf("Error: Could not open input.c\n");
        return 1;
    }

    t = getNextToken(); // Initialize first token
    Program();
    
    printf("\nProgram accepted successfully.\n");
    fclose(f1);
    return 0;
}

// --- Grammar Implementations ---

void Program() {
    matchToken("main");
    matchToken("(");
    matchToken(")");
    matchToken("{");
    declarations();
    statement_list();
    matchToken("}");
}

void declarations() {
    if (isDataType()) {
        data_type();
        identifier_list();
        matchToken(";");
        declarations();
    }
    // epsilon case: do nothing
}

void data_type() {
    if (strcmp(t.token_name, "int") == 0 || strcmp(t.token_name, "char") == 0) {
        t = getNextToken();
    } else {
        error("Expected data-type (int/char)");
    }
}

void identifier_list() {
    matchType("id");
    if (strcmp(t.token_name, "[") == 0) {
        matchToken("[");
        matchType("num");
        matchToken("]");
    }
    
    if (strcmp(t.token_name, ",") == 0) {
        matchToken(",");
        identifier_list();
    }
}

void statement_list() {
    // Check if current token starts a statement (id for assign, 'if' for decision)
    if (strcmp(t.type, "id") == 0 || strcmp(t.token_name, "if") == 0) {
        statement();
        statement_list();
    }
    // epsilon case
}

void statement() {
    if (strcmp(t.token_name, "if") == 0) {
        decision_stat();
    } else {
        assign_stat();
        matchToken(";");
    }
}

void assign_stat() {
    matchType("id");
    matchToken("=");
    expn();
}

void decision_stat() {
    matchToken("if");
    matchToken("(");
    expn();
    matchToken(")");
    matchToken("{");
    statement_list();
    matchToken("}");
    dprime();
}

void dprime() {
    if (strcmp(t.token_name, "else") == 0) {
        matchToken("else");
        matchToken("{");
        statement_list();
        matchToken("}");
    }
}

// --- Expression Grammar ---

void expn() {
    simple_expn();
    eprime();
}

void eprime() {
    if (isRelop()) {
        relop();
        simple_expn();
    }
}

void simple_expn() {
    term();
    seprime();
}

void seprime() {
    if (isAddop()) {
        addop();
        term();
        seprime();
    }
}

void term() {
    factor();
    tprime();
}

void tprime() {
    if (isMulop()) {
        mulop();
        factor();
        tprime();
    }
}

void factor() {
    if (strcmp(t.type, "id") == 0) {
        matchType("id");
    } else if (strcmp(t.type, "num") == 0) {
        matchType("num");
    } else {
        error("Expected identifier or number");
    }
}

// --- Operators ---

void relop() {
    if (isRelop()) t = getNextToken();
    else error("Expected relational operator");
}

void addop() {
    if (isAddop()) t = getNextToken();
    else error("Expected + or -");
}

void mulop() {
    if (isMulop()) t = getNextToken();
    else error("Expected *, / or %%");
}

// --- Utility Functions ---

int isKeyword(char *buffer) {
    for (int i = 0; i < 32; i++) {
        if (strcmp(keywords[i], buffer) == 0) return 1;
    }
    return 0;
}

int isDataType() {
    return (strcmp(t.token_name, "int") == 0 || strcmp(t.token_name, "char") == 0);
}

int isRelop() {
    char *ops[] = {"==", "!=", "<=", ">=", ">", "<"};
    for(int i=0; i<6; i++) if(strcmp(t.type, ops[i]) == 0) return 1;
    return 0;
}

int isAddop() {
    return (strcmp(t.type, "+") == 0 || strcmp(t.type, "-") == 0);
}

int isMulop() {
    return (strcmp(t.type, "*") == 0 || strcmp(t.type, "/") == 0 || strcmp(t.type, "%") == 0);
}

int matchToken(char *expected) {
    if (strcmp(t.token_name, expected) == 0) {
        t = getNextToken();
        return 1;
    }
    char msg[100];
    sprintf(msg, "Expected token '%s'", expected);
    error(msg);
    return 0;
}

int matchType(char *expected) {
    if (strcmp(t.type, expected) == 0) {
        t = getNextToken();
        return 1;
    }
    char msg[100];
    sprintf(msg, "Expected type '%s'", expected);
    error(msg);
    return 0;
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

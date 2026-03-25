/*
  Grammar:
  S  -> a | > | (T)
  T  -> ST'
  T' -> ,ST' | ε

  FIRST Sets:
  FIRST(S)  = { a, >, ( }
  FIRST(T)  = { a, >, ( }
  FIRST(T') = { ,, ε }

  FOLLOW Sets:
  FOLLOW(S)  = { $, ,, ) }
  FOLLOW(T)  = { ) }
  FOLLOW(T') = { ), $ }
*/

#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

char *cursor;

// Prototypes
void S();
void T();
void T_prime();
void skip_whitespace();

// Improved error reporting
void error(const char* message) {
    if (*cursor == '\0') {
        printf("\nError: %s. Reached End of String unexpectedly.\n", message);
    } else {
        printf("\nError: %s. Found '%c' at position.\n", message, *cursor);
    }
    exit(1);
}

// Moves cursor forward if it matches, else throws specific error
void match(char expected) {
    skip_whitespace();
    if (*cursor == expected) {
        cursor++;
        skip_whitespace();
    } else {
        char msg[50];
        sprintf(msg, "Expected '%c'", expected);
        error(msg);
    }
}

// Helper to ignore spaces/tabs
void skip_whitespace() {
    while (*cursor == ' ' || *cursor == '\t' || *cursor == '\n' || *cursor == '\r') {
        cursor++;
    }
}

// S -> a | > | (T)
void S() {
    skip_whitespace();
    if (*cursor == 'a') {
        match('a');
    } else if (*cursor == '>') {
        match('>');
    } else if (*cursor == '(') {
        match('(');
        T();
        match(')');
    } else {
        error("Expected 'a', '>', or '('");
    }
}

// T -> ST'
void T() {
    S();
    T_prime();
}

// T' -> ,ST' | epsilon
void T_prime() {
    skip_whitespace();
    if (*cursor == ',') {
        match(',');
        S();
        T_prime();
    } 
    // Epsilon case: If it's not a comma, we check if the character 
    // is in the FOLLOW set of T' (which is { ) }) or end of string ($).
    else if (*cursor == ')' || *cursor == '\0') {
        return; 
    } else {
        error("Expected ',' or ')'");
    }
}

int main() {
    char input[200];
    
    printf("Recursive Descent Parser for Grammar:\n");
    printf("S -> a | > | (T)\n");
    printf("T -> ST'\n");
    printf("T' -> ,ST' | ε\n\n");
    
    printf("Enter a string to parse: ");
    // Using fgets to allow spaces in the input string
    if (fgets(input, sizeof(input), stdin)) {
        cursor = input;
        
        // Start parsing from the start symbol S
        S(); 
        
        skip_whitespace(); // Final check for trailing junk
        if (*cursor == '\0') {
            printf("Success! The string is valid according to the grammar.\n");
        } else {
            error("Trailing characters after valid expression");
        }
    }

    return 0;
}

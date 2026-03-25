/*
S -> aAcBe
A -> bA'
A' -> bA'|ε
B -> d

FIRST
S = {a}
A = {b}
A' = {b,ε}
B = {d}

FOLLOW
S = {$}
A = {c}
A' = {c}
B = {e}
*/
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

char *cursor;

// Prototypes
void S();
void A();
void A_prime();
void B();
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

int main(){
	char input[100];
	printf("enter string: ");
	
	if (fgets(input, sizeof(input), stdin)) {
		cursor = input;
		
		S(); 
        
		skip_whitespace(); 
		if (*cursor == '\0') {
		    printf("Success! The string is valid according to the grammar.\n");
		} else {
		    error("Trailing characters after valid expression");
		}
        }
    	return 0;
}

void S(){
    if(*cursor == 'a'){
        match('a');
        A();
        if(*cursor == 'c'){
            match('c');
            B();
            if(*cursor == 'e')
                match('e');
            else
                error("expected e");
        }
        else
            error("expected c");
    }
    else
        error("expected a");
}
void A(){
    if(*cursor == 'b'){
        match('b');
        A_prime();
    }else
        error("expected b");
}
void A_prime(){
    if(*cursor == 'b'){
        match('b');
        A_prime();
    }else if(*cursor == 'c'){
        return;
    }else
        error("expected 'b' or 'c'");
}
void B(){
    if(*cursor == 'd'){
        match('d');
    }else
        error("expected d");
}
void skip_whitespace() {
    while (*cursor == ' ' || *cursor == '\t' || *cursor == '\n' || *cursor == '\r') {
        cursor++;
    }
}

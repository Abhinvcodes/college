/*
S -> UVW
U -> (S) | aSb | d
V -> aV | ε
W -> cW | ε

FIRST
W = {c,ε}
V = {a,ε}
U = {(,a,d}
S = {(,a,d}

FOLLOW
S = {$,),b)
U = {a,c,$,),b}
V = {c,$,),b}
W = {$,),b}
*/
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

char *cursor;

// Prototypes
void S();
void U();
void V();
void W();
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
	skip_whitespace();
	U();
	V();
	W();
}
void U(){
	skip_whitespace();
	if(*cursor == '('){
		match('(');
		S();
		match(')');
	}else if(*cursor == 'a'){
		match('a');
		S();
		match('b');
	}else if(*cursor == 'd'){
		match('d');
	}
	else{
		error("Expected '(', 'a', or 'd'");
	}	
}
void V(){
	skip_whitespace();
	if(*cursor == 'a'){
		match('a');
		V();
	}else if(*cursor == 'c' || *cursor == '\0'|| *cursor == ')' || *cursor == 'b'){
		return;
	}else{
		error("expected 'a','c','eof',')','b'");
	}
}
void W(){
	skip_whitespace();
	if(*cursor == 'c'){
		match('c');
		W();
	}else if(*cursor == '\0' || *cursor == ')' || *cursor == 'b'){
		return;
	}else
		error("expected 'c','EOF',')','b'"); 
}
void skip_whitespace() {
    while (*cursor == ' ' || *cursor == '\t' || *cursor == '\n' || *cursor == '\r') {
        cursor++;
    }
}

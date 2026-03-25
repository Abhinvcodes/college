/*
S -> (L) | a
L -> SL'
L' -> ,SL' | ε

FIRST
S = {(,a}
L = {(,a}
L' = {, , ε}

FOLLOW
S = {, , ), $}
L = {)}
L' = {)}
*/
#include <stdio.h>
#include <stdlib.h>

char *cursor;
void S();
void L();
void L_prime();

void skip_whitespace() {
    while (*cursor == ' ' || *cursor == '\t' || *cursor == '\n' || *cursor == '\r') {
        cursor++;
    }
}
void error(const char *message){
    if (*cursor == '\0') {
        printf("\nError: %s. Reached End of String unexpectedly.\n", message);
    } else {
        printf("\nError: %s. Found '%c' at position.\n", message, *cursor);
    }
    exit(1);
}
void match(char expected){
    if(*cursor == expected){
        cursor++;
        skip_whitespace();
    }else{
        char msg[50];
        sprintf(msg, "Expected '%c'", expected);
        error(msg);
    }
}
void S(){
    if(*cursor == '('){
        match('(');
        L();
        match(')');
    }else if (*cursor == 'a'){
        match('a');
    }else
        error("expected '(' or 'a'");
}
void L_prime(){
    if(*cursor ==','){
        match(',');
        S();
        L_prime();
    }
    else if(*cursor == ')'){
        return;
    }else
        error("expected ','");
}
void L(){
    S();        // Call S (handles both '(' and 'a')
    L_prime();  // Then call L'
}
int main()
{
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
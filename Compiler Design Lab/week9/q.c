#include <stdio.h>
#include <string.h>

typedef struct {
    char type; // 's', 'r', 'a', 'e'
    int value;
} Action;

// Paste your generated tables here
#define NUM_STATES 12
#define NUM_TERMS 6
Action action_table[NUM_STATES][NUM_TERMS] = {
    { {'s', 1}, {'e', 0}, {'e', 0}, {'s', 2}, {'e', 0}, {'e', 0} }, // State 0
    { {'e', 0}, {'r', 6}, {'r', 6}, {'e', 0}, {'r', 6}, {'r', 6} }, // State 1
    { {'s', 1}, {'e', 0}, {'e', 0}, {'s', 2}, {'e', 0}, {'e', 0} }, // State 2
    { {'e', 0}, {'s', 7}, {'e', 0}, {'e', 0}, {'e', 0}, {'a', 0} }, // State 3
    { {'e', 0}, {'r', 2}, {'s', 8}, {'e', 0}, {'r', 2}, {'r', 2} }, // State 4
    { {'e', 0}, {'r', 4}, {'r', 4}, {'e', 0}, {'r', 4}, {'r', 4} }, // State 5
    { {'e', 0}, {'s', 7}, {'e', 0}, {'e', 0}, {'s', 9}, {'e', 0} }, // State 6
    { {'s', 1}, {'e', 0}, {'e', 0}, {'s', 2}, {'e', 0}, {'e', 0} }, // State 7
    { {'s', 1}, {'e', 0}, {'e', 0}, {'s', 2}, {'e', 0}, {'e', 0} }, // State 8
    { {'e', 0}, {'r', 5}, {'r', 5}, {'e', 0}, {'r', 5}, {'r', 5} }, // State 9
    { {'e', 0}, {'r', 1}, {'s', 8}, {'e', 0}, {'r', 1}, {'r', 1} }, // State 10
    { {'e', 0}, {'r', 3}, {'r', 3}, {'e', 0}, {'r', 3}, {'r', 3} }, // State 11
};
int goto_table[NUM_STATES][3] = {
    { 3, 4, 5 }, // State 0
    { -1, -1, -1 }, // State 1
    { 6, 4, 5 }, // State 2
    { -1, -1, -1 }, // State 3
    { -1, -1, -1 }, // State 4
    { -1, -1, -1 }, // State 5
    { -1, -1, -1 }, // State 6
    { -1, 10, 5 }, // State 7
    { -1, -1, 11 }, // State 8
    { -1, -1, -1 }, // State 9
    { -1, -1, -1 }, // State 10
    { -1, -1, -1 }, // State 11
};

// Rules for reduction: {LHS_index, RHS_length}
// This must match your RULES list in Python
int lhs_nt[] = { -1, 0, 0, 1, 1, 2, 2 }; // E'=ignore, E=0, T=1, F=2
int rhs_len[] = { 0, 3, 1, 3, 1, 3, 1 };

int get_token_id(char* lexeme) {
    if (strcmp(lexeme, "id") == 0) return 0;
    if (strcmp(lexeme, "+") == 0)  return 1;
    if (strcmp(lexeme, "*") == 0)  return 2;
    if (strcmp(lexeme, "(") == 0)  return 3;
    if (strcmp(lexeme, ")") == 0)  return 4;
    if (strcmp(lexeme, "$") == 0)  return 5;
    return -1; // Unknown token
}
#include <string.h>

int tokenize(char* input_str, int* token_array) {
    char temp[100];
    strcpy(temp, input_str); // Work on a copy to keep original safe
    
    int count = 0;
    char* token = strtok(temp, " ");
    
    while (token != NULL) {
        int id = get_token_id(token);
        if (id != -1) {
            token_array[count++] = id;
        } else {
            printf("Lexical Error: Unknown token '%s'\n", token);
            return -1; 
        }
        token = strtok(NULL, " ");
    }
    return count; // Returns how many tokens we found
}

int main() {
    char input_text[100];
    int input_tokens[100];
    
    printf("Enter expression (separate tokens with spaces, end with $):\n");
    // Example input: id + id * id $
    fgets(input_text, 100, stdin);
    input_text[strcspn(input_text, "\n")] = 0; // Remove newline character

    int num_tokens = tokenize(input_text, input_tokens);
    if (num_tokens <= 0) return 1;

    // --- Start Parsing ---
    int stack[100];
    int top = 0;
    stack[top] = 0; 
    int ip = 0; // Input Pointer

    while (ip < num_tokens) {
        int s = stack[top];
        int a = input_tokens[ip];
        Action act = action_table[s][a];

        if (act.type == 's') {
            printf("Shift: pushing state %d\n", act.value);
            stack[++top] = act.value;
            ip++;
        } 
        else if (act.type == 'r') {
            int rule = act.value;
            printf("Reduce: rule %d\n", rule);
            top -= rhs_len[rule]; 
            int state_after_pop = stack[top];
            stack[++top] = goto_table[state_after_pop][lhs_nt[rule]];
        } 
        else if (act.type == 'a') {
            printf("SUCCESS: String is syntactically correct!\n");
            break;
        } 
        else {
            printf("ERROR: Unexpected token at position %d\n", ip);
            break;
        }
    }
    return 0;
}
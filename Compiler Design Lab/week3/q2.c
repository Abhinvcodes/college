#include <stdio.h>
#include <ctype.h>
#include <errno.h>
#include <stdlib.h>
#include <string.h>

typedef struct{
	char token_name[10];
	unsigned int row,col;
}token;

int CommentedLine(char *buffer);
int preProcessor(char *buffer);
void generateIdToken(char *tokenizedString,char *buffer,int left,int right);
void tokenize(char *buffer,char *tokenizedString);

const char keywords[][10] = {
    "auto",     "break",    "case",     "char",
    "const",    "continue", "default",  "do",
    "double",   "else",     "enum",     "extern",
    "float",    "for",      "goto",     "if",
    "int",      "long",     "register", "return",
    "short",    "signed",   "sizeof",   "static",
    "struct",   "switch",   "typedef",  "union",
    "unsigned", "void",     "volatile", "while",
    "{",	"}"
};
const int keyword_len = sizeof(keywords)/sizeof(keywords[0]);
static int ROW = 1;

int main()
{
	FILE *f1,*f2;
	char buffer[1024];
	
	
	f1 = fopen("input.c","r");
	if(f1 == NULL)
	{
		perror("input file error");
		exit(1);
	}
	f2 = fopen("output.c","w");
	if(f2 == NULL)
	{
		perror("write file error");
		exit(1);
	}
	
	while(fgets(buffer,1023,f1))
	{
		printf("%s",buffer);
		if(CommentedLine(buffer) || preProcessor(buffer))
			continue;
		char *tokenizedString = (char *)malloc(sizeof(char)*1024);
		tokenizedString[0] = '\0';
		tokenize(buffer, tokenizedString);
		
		strcat(tokenizedString,"\n");
		printf("%s",tokenizedString);
		fprintf(f2,tokenizedString);
		
		free(tokenizedString);
		ROW++;
	}
	fclose(f1);
	fclose(f2);
	return 0;
}

void generateIdToken(char *tokenizedString,char *buffer,int left,int right)
{
	char lexeme[50];
	int i, j = 0;
	
	for (i = left; i <= right; i++) {
	    lexeme[j++] = buffer[i];
	}
	lexeme[j] = '\0'; // Finalize the string
	
	for(int i = 0;i < keyword_len;i++)
	{
		if(strcmp(keywords[i], lexeme) == 0)
		{
			char temp[50];
			snprintf(temp, sizeof(temp), "<%s, %d, %d>", keywords[i],ROW,left); // Check 1
			if (strlen(tokenizedString) + strlen(temp) < 1023) {      // Check 2
			    strcat(tokenizedString, temp);
			}
			return;
		}
	}
	char temp[50];
	snprintf(temp, sizeof(temp), "<%s, %d, %d>",lexeme,ROW,left);
	if (strlen(tokenizedString) + strlen(temp) < 1023) {
		strcat(tokenizedString, temp);
	}
}

void tokenize(char *buffer, char *tokenizedString) {
    int lb = 0, fp = 0;

    while (buffer[lb] != '\0') {
        fp = lb;

        // 1. Skip Whitespace
        if (isspace(buffer[lb])) {
            lb++;
            continue;
        }

        // 2. Identifiers
        if (isalpha(buffer[lb])) {
            while (isalnum(buffer[fp])) fp++; // alnum handles letters and numbers in IDs
            generateIdToken(tokenizedString, buffer, lb, fp - 1);
            lb = fp;
        }
        // 3. Plus/Increment
        else if (buffer[lb] == '+') {
            if (buffer[lb + 1] == '+') {
                generateIdToken(tokenizedString, buffer, lb, lb + 1);
                lb += 2;
            } else {
                generateIdToken(tokenizedString, buffer, lb, lb);
                lb++;
            }
        }
        // 4. Equals / Relational ==
        else if (buffer[lb] == '=') {
            if (buffer[lb + 1] == '=') {
                generateIdToken(tokenizedString, buffer, lb, lb + 1);
                lb += 2;
            } else {
                // IMPORTANT: Handle assignment or just skip if not needed
                lb++; 
            }
        }
        // 5. Less Than / Less Than Equal
        else if (buffer[lb] == '<') {
            if (buffer[lb + 1] == '=') {
                generateIdToken(tokenizedString, buffer, lb, lb + 1);
                lb += 2;
            } else {
                generateIdToken(tokenizedString, buffer, lb, lb);
                lb++;
            }
        }
        // 6. greater than / greater than equal
        else if (buffer[lb] == '>') {
            if (buffer[lb + 1] == '=') {
                generateIdToken(tokenizedString, buffer, lb, lb + 1);
                lb += 2;
            } else {
                generateIdToken(tokenizedString, buffer, lb, lb);
                lb++;
            }
        }
        // 7. Logical AND
        else if (buffer[lb] == '&' && buffer[lb + 1] == '&') {
            generateIdToken(tokenizedString, buffer, lb, lb + 1);
            lb += 2;
        }
        //8. {
        else if(buffer[lb] == '{'){
        	generateIdToken(tokenizedString,buffer,lb,lb);
        	lb+=1;
        }
        //9. }
        else if(buffer[lb] == '}'){
        	generateIdToken(tokenizedString,buffer,lb,lb);
        	lb+=1;
        }
        //10. (
        else if(buffer[lb] == '('){
        	generateIdToken(tokenizedString,buffer,lb,lb);
        	lb+=1;
        }
        //11. (
        else if(buffer[lb] == ')'){
        	generateIdToken(tokenizedString,buffer,lb,lb);
        	lb+=1;
        }
        // 12. Catch-all for unknown characters (Prevents Infinite Loop)
        else {
            lb++; 
        }
    }
}

int CommentedLine(char *buffer)
{
	static int multiline = 0;
	int lb=0;
	while(buffer[lb] == ' ')
		lb++;
	if(multiline)
	{
		while(buffer[lb] != '\0')
		{
			if(buffer[lb] == '*' && buffer[lb+1] == '/')
				multiline = 0;
			lb++;
		}
		return 1;
	}
	if (buffer[lb] == '/' && buffer[lb+1] == '/')
		return 1;
	else if(buffer[lb] == '/' && buffer[lb+1] == '*')
	{
		multiline = 1;
		return 1;
	}	
	return 0;
}

int preProcessor(char *buffer)
{
	int lb=0;
	while(buffer[lb] == ' ')
		lb++;
	if(buffer[lb] == '#')
		return 1;
	return 0;
}

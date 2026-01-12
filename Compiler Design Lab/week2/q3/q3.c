#include <stdio.h>
#include <string.h>
#include <ctype.h>

static const char *c_keywords[] = {
    "auto", "break", "case", "char", "const", "continue", "default", "do", "double", "else",
    "enum", "extern", "float", "for", "goto", "if", "int", "long", "register", "return",
    "short", "signed", "sizeof", "static", "struct", "switch", "typedef", "union", "unsigned",
    "void", "volatile", "while"};
static const size_t c_keywords_count = sizeof(c_keywords) / sizeof(c_keywords[0]);

void str_to_upper(char *word)
{
    for (int i = 0; i < strlen(word); i++)
        word[i] = toupper(word[i]);
}

void replaceWord(char *buffer, char *word, int index)
{
    for (int i = 0; i < strlen(word); i++)
        buffer[index + i] = word[i];
}

void is_keyword(char *buffer)
{
    char word[100] = {0};
    int k = 0, tidx;
    for (int i = 0; i < strlen(buffer); i++)
    {
        if (isalpha(buffer[i]))
        {
            k = 0;
            tidx = 0;
            while (isalpha(buffer[i + tidx]))
            {
                word[k++] = buffer[i + tidx];
                tidx++;
            }
            word[k] = '\0';
            for (int j = 0; j < c_keywords_count; j++)
                if (strcmp(word, c_keywords[j]) == 0)
                {
                    str_to_upper(word);
                    replaceWord(buffer, word, i);
                    i += strlen(word);
                    continue;
                }
        }
    }
}

int main(void)
{
    FILE *f1 = fopen("input.c", "r");
    FILE *f2 = fopen("output.txt", "w");
    if (!f1 || !f2)
        return 1;

    char buffer[1024];
    while (fgets(buffer, 1023, f1) != NULL)
    {
        is_keyword(buffer);
        fputs(buffer, f2);
    }

    fclose(f1);
    fclose(f2);
    return 0;
}

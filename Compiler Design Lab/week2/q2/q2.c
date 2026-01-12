#include <stdio.h>

int main()
{
    FILE *f1, *f2;

    f1 = fopen("input.c", "r");
    f2 = fopen("output.txt", "w");

    char c = getc(f1);
    while (c != EOF)
    {
        if (c == '#')
        {
            while (c != '\n')
                c = getc(f1);
            if (c == '\n')
            {
                c = getc(f1);
                continue;
            }
        }
        putc(c, f2);
        c = getc(f1);
    }
    fclose(f1);
    fclose(f2);
    return 0;
}
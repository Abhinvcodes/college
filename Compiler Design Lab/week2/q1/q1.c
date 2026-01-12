#include <stdio.h>

int main()
{
    FILE *f1, *f2;

    f1 = fopen("input.txt", "r");
    f2 = fopen("output.txt", "w");

    char c = getc(f1);
    char lastchar = c;
    while (c != EOF)
    {
        if (lastchar == ' ' && c == ' ')
        {
            while (c == ' ')
                c = getc(f1);
            putc(c, f2);
        }
        else
            putc(c, f2);
        lastchar = c;
        c = getc(f1);
    }
    fclose(f1);
    fclose(f2);
    return 0;
}
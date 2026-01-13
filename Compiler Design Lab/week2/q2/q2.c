#include <stdio.h>

int main()
{
    FILE *f1, *f2;

    f1 = fopen("input.c", "r");
    f2 = fopen("output.txt", "w");

    char c = getc(f1);
    char lastchar = c;
    int ignore = 0;
    while (c != EOF)
    {
    	if(lastchar == '/' && c == '*')
    	{
    		putc(c, f2);

    		do {
        		lastchar = c;
        		c = getc(f1);

        		if (c == EOF) break;   // safety check
        		putc(c, f2);

    		} while (!(lastchar == '*' && c == '/'));
    		c = getc(f1);
    	}
    	if(lastchar == '/' && c == '/')
    	{
    		putc(lastchar,f2);
		while(c != '\n'){
			c = getc(f1);
			putc(c,f2);
		}
		continue;
    	}
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
        lastchar = c;
        c = getc(f1);
    }
    fclose(f1);
    fclose(f2);
    return 0;
}

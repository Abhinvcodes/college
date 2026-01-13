#include <stdio.h>
#include <stdlib.h>

int main()
{
    FILE *f;
    char filename[100],c;
    int countlines = 0;
    int charcount = 0;

    printf("enter filename:\n");
    scanf("%s",filename);

    if((f = fopen(filename,"r")) == NULL)
    {
        printf("%s may not exist or cannot be opened\n");
        exit(0);
    }

    c = fgetc(f);
    charcount++;
    while(c != EOF)
    {
        if(c == '\n')
            countlines++;
        charcount++;
        c = fgetc(f);
    }
    fclose(f);
    printf("lines: %d\ncharacter count: %d\n",countlines,charcount);
    return 0;
}
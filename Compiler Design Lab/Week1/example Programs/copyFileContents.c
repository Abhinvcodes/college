#include <stdlib.h>
#include <stdio.h>

int main()
{
    FILE *f1,*f2;
    char filename[100],c;
    printf("enter file name to read\n");
    scanf("%s",filename);

    f1 = fopen(filename,"r");
    if(f1 == NULL)
    {
        printf("%s may not exists or cannot be opened\n",filename);
        exit(0);
    }

    printf("enter the filename to open for writing\n");
    scanf("%s",filename);

    f2 = fopen(filename,"w+");
    if(f2 == NULL)
    {
        printf("%s may not exists or cannot be opened\n",filename);
        exit(0);
    }

    c = fgetc(f1);
    while(c != EOF)
    {
        fputc(c,f2);
        c = fgetc(f1);
    }

    printf("\nContents copied to %s\n",filename);
    fclose(f1);
    fclose(f2);
    return 0;
}
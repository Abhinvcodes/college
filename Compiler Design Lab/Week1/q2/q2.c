#include <stdio.h>
#include <stdlib.h>

int main()
{
	FILE *f1,*f2;
	char filename[100],c;
	int size;
	printf("enter filename to copy: ");
	scanf("%s",filename);

	if((f1 = fopen(filename,"rb")) == NULL)
	{
		perror("file error");
		return 1;
	}

	printf("enter filename to write to: ");
	scanf("%s",filename);
	
	if((f2 = fopen(filename,"wb")) == NULL)
	{
		perror("file error");
		return 1;
	}
	
	fseek(f1,0,SEEK_END);
	size = ftell(f1);

	for(long i = size-1;i>=0;i--)
	{
		fseek(f1,i,SEEK_SET);
		c = fgetc(f1);
		fputc(c,f2);
	}
	fclose(f1);
	fclose(f2);
	return 0;
}
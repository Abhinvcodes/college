#include <stdio.h>
#include <stdlib.h>

int main()
{
	FILE *f1,*f2,*f3;
	char line1[1024],line2[1024];

	f1 = fopen("file1","r");
	f2 = fopen("file2","r");
	f3 = fopen("file3","w");

	if(!f1 || !f2 || !f3)
	{
		perror("file opening error");
		return 1;
	}

	while(fgets(line1,sizeof(line1),f1) &&  fgets(line2,sizeof(line2),f2) )
	{
		fputs(line1,f3);
		fputs(line2,f3);
	}

	while(fgets(line1,sizeof(line1),f1))
		fputs(line1,f3);
	
	while(fgets(line2,sizeof(line2),f2))
		fputs(line2,f3);

	printf("operation complete\n");
	fclose(f1);
	fclose(f2);
	fclose(f3);
	return 0;
}
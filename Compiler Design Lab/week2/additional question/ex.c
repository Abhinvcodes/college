#include <stdio.h>
#include <string.h>

int main()
{
	char sent[] = "void add(int a, int b)";
	for(char *p = strtok(sent," (),"); p != NULL;p = strtok(NULL," (),"))
		printf("%s\n",p);
	return 0;
}

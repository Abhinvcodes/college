#include <stdio.h>
//#include <stdio.h>
/*
this is multiline comment
*/
int main()
{
	printf("hello world");
	int a[4]={1,2,3,4};
	int b[4]={5,6,7,8};
	int c[4];
	for(int i = 0;i < 4;i++)
		c[i] = a[i]+b[i];
		printf("%d",c[i]);
	return 0;
}


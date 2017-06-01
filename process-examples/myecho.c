#include <stdio.h>
#include <stdlib.h>

void main() 
{
	char buf[1024] ;
	while (scanf("%s", buf) != EOF) 
		printf("%s\n", buf) ;
}

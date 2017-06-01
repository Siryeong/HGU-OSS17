#include <stdio.h>
#include <unistd.h>

void main()
{
	printf("Let's execute iter's.\n") ;
	if (fork() == 0) 
		execl("./iter", "iter", NULL) ;
	if (fork() == 0) 
		execl("./iter", "iter", NULL) ;
	if (fork() == 0) 
		execl("./iter", "iter", NULL) ;
	printf("Done.\n") ;
}

#include <stdio.h>
#include <unistd.h>

void main()
{
	pid_t pid ; 

	printf("Let's execute iter.\n") ;
	if ((pid = fork()) == 0) {
		execl("./iter", "iter", NULL) ;
	}
	printf("My child %d\n", pid) ;
	printf("Done.\n") ;
}

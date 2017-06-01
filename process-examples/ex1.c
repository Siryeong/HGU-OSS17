#include <stdio.h>
#include <unistd.h>

void main(int args, char ** argv)
{
	printf("Let's execute iter.\n") ;
	execl("./iter", "iteration", NULL) ;
	printf("Done.\n") ;
}

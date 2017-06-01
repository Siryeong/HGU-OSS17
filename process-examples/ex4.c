#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

void main()
{
	pid_t pid ;
	int s ;

	int i ;

	printf("Let's execute iter.\n") ;

	for (i = 0 ; i < 10 ; i++) {
		if (fork() == 0) 
			execl("./iter", "iter","300", NULL) ;
	}
	for (i = 0 ; i < 10 ; i++) {
		pid = wait(&s) ;
		printf("[%d] terminated.\n", pid) ;
	}
	printf("Done.\n") ;
}

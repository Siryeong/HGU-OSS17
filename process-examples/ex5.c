#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

void main()
{
	pid_t pid ;
	int s, i ;

	printf("Let's execute prime.\n") ;
	if ((pid = fork()) == 0)
		execl("./prime", "prime", NULL) ;

	sleep(3) ;
	kill(pid, SIGINT) ;
	printf("RIP.\n") ;
}

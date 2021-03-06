#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

static pid_t pid ;

void handler(int signum)
{
	int s ;
	kill(pid, SIGINT) ;
	wait(&s) ;
	printf("Bye.\n") ;
}

void main()
{
	int s ;

	signal(SIGINT, handler) ;

	printf("Let's execute prime.\n") ;
	if ((pid = fork()) == 0) {
		execl("./prime", "prime", NULL) ;
	}
	waitpid(pid, &s, 0) ;
}

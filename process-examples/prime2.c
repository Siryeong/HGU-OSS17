#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

static int max = -1 ; 

void handler(int signum)
{
	if (signum == SIGINT) {
		printf("\n%d\n", max) ;
		exit(0) ;
	}
}

void main()
{
	int i, j ;

	signal(SIGINT, handler) ;

	for (i = 2 ; ; i++) {
		for (j = 2 ; j < i ; j++) {
			if (i % j == 0)
				break ;
		}
		if (j == i)
			max = i ;
	}
}

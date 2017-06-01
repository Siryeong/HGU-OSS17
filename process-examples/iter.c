#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>

void main(int args, char ** argc) 
{
	int i = 0 ;
	int n = 0 ;

	srand(time(NULL)) ;

	if (args == 2)
		n = atoi(argc[1]) ;
	else
		n = 10 ;

	for (i = 0 ; i < n ; i++) {		
		printf("%d\n", i) ;
		usleep((rand() % 100) * 100) ;
	}
	exit(0) ;
}

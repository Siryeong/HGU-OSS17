#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <search.h>
#include <unistd.h>
#include <string.h>
#include <errno.h>
#define MAX_STUDENTS	100


//done:TODO: please someone write a build script.

int n_students = 0 ;
int n_teams = 0 ;
int students[MAX_STUDENTS] ;	// TODO: allow an arbitrary number of students can come from the input.
int team[MAX_STUDENTS] ;
int n_team_members[MAX_STUDENTS / 2] ;
int conflict[MAX_STUDENTS][MAX_STUDENTS] ;

int read_student_list(char* fileName) 
{
	FILE * fp ;
	char * b ;
	int i ; 

	fp = fopen(fileName, "r") ; //done(TODO: allow a user can give a different file name as an argument.)
	if( fp == NULL){ //(add code)fix bug Print errors when a non-existent file name is input 
		printf("Not vaild file name \n"); 
		exit(1);  
	}

	while (feof(fp) == 0) {
		if (fscanf(fp, "%d", &(students[n_students])) == 1)
			n_students++ ;
	}
	fclose(fp) ;

	n_teams = n_students / 2 ;

	for (i = 0 ; i < n_students ; i++) 
		conflict[i][i] = 0 ;
			
	// DONE(TODO: check if a given student ID is valid.)
	for(i = 0 ; i <n_students ; i++)
		if(!(20000000<students[i] && students[i]<21800000)){
			fprintf(stderr,"Invalid student ID was detected. \n");
			exit(1);
			}//Cause an error ,if student id is not in the range.
}

int get_student_index(int id) 
{
	int i = 0 ;
	for (i = 0 ; i < n_students ; i++) {
		if (students[i] == id)
			return i ;
	}
	return -1 ;
}

void read_conflict(char * fname)
{
	FILE * fp ;
	char * b = NULL ;
	size_t n = 0 ;
	extern int errno;

	fp = fopen(fname, "r") ;  // TODO: handle file errors, //fixing
	if(fp == NULL)//Handling file errors using strerror
	{
		fprintf(stderr,"File Read Error:%s\n",strerror(errno));
	}
	while (getline(&b, &n, fp) > 0) {
		int n_members ;
		int m1, m2, m3;
		int i1, i2, i3 ;

		n_members = sscanf(b, "%d %d %d", &m1, &m2, &m3) ;
		free(b) ;

		if (n_members <= 1) {
			fprintf(stderr, "Input Error: The file has a case where the team is composed alone!") ; //Done(TODO: need a better error message.)
			exit(1) ;
		}

		i1 = get_student_index(m1) ;
		i2 = get_student_index(m2) ;

		if (i1 == -1 || i2 == -1) 
			exit(1) ;

		conflict[i1][i2] = 1 ;
		conflict[i2][i1] = 1 ;

		if (n_members >= 3) {
			i3 = get_student_index(m3) ;
			conflict[i1][i3] = 1 ;
			conflict[i3][i1] = 1 ;
			conflict[i2][i3] = 1 ;
			conflict[i3][i2] = 1 ;
		}
	}
	//TODO: check if the given information is valid.
}

int _assign_team(int id) {
	int is_team_feasible[MAX_STUDENTS / 2] ;
	int n_feasible_teams = 0 ;
	int n_max_members = n_students % 2 + 2;//When the number of students is even 3-memberd team cannot be made
	int i = 0 ; 
	int r = 0 ;
	int c = 0 ;

	for (i = 0 ; i < n_teams ; i++) {
		is_team_feasible[i] = (n_team_members[i] < n_max_members) ? 1 : 0 ;
		if (n_team_members[i] == 3) {
			for (i = 0 ; i < n_teams ; i++) 
				is_team_feasible[i] = (n_team_members[i] < 2) ? 1 : 0 ;			
			break ;
		}
	}
	for (i = 0 ; i < id ; i++) {		
		if (conflict[id][i] == 1)
			is_team_feasible[team[i]] = 0 ;
	}
	for (i = 0 ; i < n_teams ; i++) {		
		if (is_team_feasible[i] == 1)
			n_feasible_teams++ ;
	}

	while (n_feasible_teams > 0) {
		r = rand() % n_feasible_teams ; 		
		for (i = 0 ; i < n_teams ; i++) {
			if (is_team_feasible[i] == 1) {
				if (r == 0) {
					c = i ;
					break ;
				}
				else {
					r-- ;
				}					
			}
		}
		team[id] = c ;
		n_team_members[c]++ ;
		if (id + 1 < n_students) {
			if (_assign_team(id + 1) == 1)
				return 1 ;
		}
		else {
			return 1 ;
		}
		team[id] = -1 ;
		n_team_members[c]-- ;
		is_team_feasible[c] = 0 ;
		n_feasible_teams-- ;
	}
	return 0 ;
}

void find_team_assignments()
{
	if (_assign_team(0) == 0) {
		fprintf(stderr, "Fail to find a feasible assignment.\n") ;
		exit(1) ;
	}
}

void print_team_assignment() 
{
	int t, s ;

	for (t = 0 ; t < n_teams ; t++) {
		for (s = 0 ; s < n_students ; s++) {
			if (team[s] == t)
				printf("%d ", students[s]) ;
		}
		printf("\n") ;
	}
}


void main(int argc, char ** argv) 
{	
	char c ; 
	char * fconflict = NULL ;
	char * fileName = NULL;

	while ((c = getopt(argc, argv, "hpf:")) != -1) {
		switch (c) {
			case 'p':
				fconflict = optarg ;
				break ;

			case 'h':
				printf("-p <filename>	Filename that contains the team list from the last lab session\n");
				printf("-f <filename>	Filename that contains every student id in class\n");
				printf("-h	Display these usage instructions\n");
				// Please someone make a help message here. // Complete
				break ;
			
			case 'f':
				fileName = optarg;
				break;

			default:
				fprintf(stderr, "Invalid argument the argument: flag should be one of p, f, h ; f should be followed by 'file name'\n") ; 
				// Please someone make a better error message. // done
				exit(1) ;
		}
	}
	
	if(fileName != NULL)	
		read_student_list(fileName);

	if (fconflict != NULL)
		read_conflict(fconflict) ;
	find_team_assignments() ;
	print_team_assignment() ;
	exit(0) ;
}

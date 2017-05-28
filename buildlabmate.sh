#!/bin/bash

#You must change the permissions before running the bash script.
#chmod 777 ./buildlabmate.sh

gcc -o labmate labmate.c

./labmate $1 $2


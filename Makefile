labmate: labmate.o students
	gcc -o labmate labmate.o
	./labmate -f students.txt
labmate.o: labmate.c
	git pull
	gcc -c labmate.c
students: students.txt
	git pull
clean:
	rm *.o labmate

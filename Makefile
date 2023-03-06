EXECS = a.out
OBJS = main.o book.o member.o datefunctions.o librarianfunctions.o memberfunctions.o io.o

main: main.o book.o member.o datefunctions.o librarianfunctions.o memberfunctions.o io.o
	gcc main.o book.o member.o datefunctions.o librarianfunctions.o memberfunctions.o io.o

main.o: main.c utils.h
	gcc -c main.c

book.o: book.c utils.h
	gcc -c book.c

member.o: member.c utils.h
	gcc -c member.c

datefunctions.o: datefunctions.c utils.h
	gcc -c datefunctions.c

librarianfunctions.o: librarianfunctions.c utils.h
	gcc -c librarianfunctions.c

memberfunctions.o: memberfunctions.c utils.h
	gcc -c memberfunctions.c

io.o: io.c utils.h
	gcc -c io.c

clean:
	rm -f $(OBJS) $(EXECS)







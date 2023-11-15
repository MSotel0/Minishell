miniShell: miniShell.c fragmenta.o
	gcc  -Wall miniShell.c fragmenta.o -o miniShell
	./miniShell
fragmenta.o: fragmenta.c
	gcc -c fragmenta.c
clean:
	rm *.o

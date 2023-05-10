CC=gcc
CFLAGS=-Wall

all: myavl

myavl: myavl.o remove_avl.o insere_avl.o manipula_avl.o
	$(CC) $(CFLAGS) myavl.o remove_avl.o insere_avl.o manipula_avl.o -o myavl

myavl.o: myavl.c
	$(CC) -c $(CFLAGS) myavl.c -o myavl.o

remove_avl.o: remove_avl.c
	$(CC) -c $(CFLAGS) remove_avl.c -o remove_avl.o

insere_avl.o: insere_avl.c
	$(CC) -c $(CFLAGS) insere_avl.c -o insere_avl.o

manipula_avl.o: manipula_avl.c
	$(CC) -c $(CFLAGS) manipula_avl.c -o manipula_avl.o

clean:
	rm -f *.o

purge: 
	rm -f *.o myavl
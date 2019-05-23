CC = gcc
CFLAGS = -W -Wall
EXEC = main
OBJS = main.o SGF.o primitives.o
 
all: $(EXEC)
 
$(EXEC): $(OBJS) 
	$(CC) $(CFLAGS) -o $(EXEC) $(OBJS) 
 
main.o: main.c
	$(CC) $(CFLAGS) -c main.c -o main.o
         
SGF.o: SGF.c SGF.h
	$(CC) $(CFLAGS) -c SGF.c -o SGF.o
	
primitives.o: primitives.c primitives.h
	$(CC) $(CFLAGS) -c primitives.c -o primitives.o
 
clean:
	rm *.o
 
mrproper: clean
	rm $(EXEC)

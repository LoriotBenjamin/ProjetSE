CC = gcc
CFLAGS = -W -Wall
EXEC = main
OBJS = main.o SGF.o
 
all: $(EXEC)
 
$(EXEC): $(OBJS) 
	$(CC) $(CFLAGS) -o $(EXEC) $(OBJS) 
 
main.o: main.c
	$(CC) $(CFLAGS) -c main.c -o main.o
         
SGF.o: SGF.c SGF.h
	$(CC) $(CFLAGS) -c SGF.c -o SGF.o
 
clean:
	rm *.o
 
mrproper: clean
	rm $(EXEC)

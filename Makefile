EXEC = Server
CC = gcc
CFLAGS= -I.-Wunused -Wuninitialized -g  -Os 
SOURCE = server.c 
DEBUG=
all: $(EXEC)

$(EXEC):
	$(CC)  -O $(CFLAGS) -o $@ $(SOURCE) -lc -lpthread 

clean:
	-rm -f $(EXEC) *.o *.elf *.gdb

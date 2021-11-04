CC = gcc
CFLAGS = -O2 -Wall -Wextra
LDFLAGS =

TARGET = forests
HEADERS = bst.h library.h read.h struct.h
FILES = bst.c library.c main.c read.c
OBJ = $(FILES:.c=.o)

.PHONY: clean all

all: $(TARGET)
	
bst.o: bst.c bst.h struct.h library.h
	$(CC) $(CFLAGS) -c $< 

library.o: library.c library.h struct.h
	$(CC) $(CFLAGS) -c $< 
        
read.o: read.c read.h struct.h library.h bst.h
	$(CC) $(CFLAGS) -c $< 
      
main.o: main.c struct.h read.h library.h bst.h
	$(CC) $(CFLAGS) -c $< 

forests: $(OBJ)
	$(CC) $(CFLAGS) $(LDFLAGS) -o $@ $^

clean:
	rm -f $(OBJ) $(TARGET)


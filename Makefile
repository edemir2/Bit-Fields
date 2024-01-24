CC = gcc
CFLAGS = -Wall -std=c18 -ggdb

test : testBitFields 
	./testBitFields
	
gdb : testBitFields
	gdb testBitFields
	
testBitFields : testBitFields.c bitFields.c bitFields.h	
	$(CC) $(CFLAGS) -o testBitFields  testBitFields.c bitFields.c
	
clean :
	-rm testBitFields
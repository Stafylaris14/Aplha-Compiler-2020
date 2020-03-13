dataStructs: 
	gcc  -c dataStructs/commentStack.c
	gcc  -c dataStructs/linkedList.c
	gcc  -c dataStructs/symb.c
	gcc  -c utilities/parserUtilities.c


parser: parser.y 
	bison --yacc --defines --output=parser.c parser.y

scanner:scanner.l 
	flex -o scanner.c scanner.l	

compiler: parser scanner 

	gcc -c parser.c dataStructs/symb.c utilities/parserUtilities.c
	gcc -c scanner.c dataStructs/commentStack.c dataStructs/linkedList.c 
	gcc -o calc parser.o scanner.o  linkedList.o commentStack.o symb.o parserUtilities.o

clean:
	rm -f scanner.c
	rm -f scanner
	rm -f *.o
	rm -f parser.c
	rm -f parser.h
	rm -f calc





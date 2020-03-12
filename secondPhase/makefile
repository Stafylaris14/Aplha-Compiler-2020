dataStructs: dataStructs/linkedList.c dataStructs/commentStack.c
	gcc  -c dataStructs/commentStack.c
	gcc  -c dataStructs/linkedList.c
	gcc  -c dataStructs/symb.c


parser: parser.y 
	bison --yacc --defines --output=parser.c parser.y

scanner:scanner.l 
	flex -o scanner.c scanner.l	

compiler: parser scanner
	gcc -c parser.c dataStructs/symb.c
	gcc -c scanner.c dataStructs/commentStack.c dataStructs/linkedList.c 
	gcc -o calc parser.o scanner.o  linkedList.o commentStack.o symb.o

clean:
	rm -f scanner.c
	rm -f scanner
	rm -f *.o
	rm -f parser.c
	rm -f parser.h





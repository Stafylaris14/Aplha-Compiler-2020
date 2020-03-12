dataStructs: dataStructs/linkedList.c dataStructs/commentStack.c
	gcc  -c dataStructs/commentStack.c
	gcc  -c dataStructs/linkedList.c
	gcc  -c dataStructs/symb.c

# edw ftiaxnw to parser.c
parser: parser.y dataStructs
	bison --yacc --defines --output=parser.c parser.y

scanner:scanner.l parser
	flex -o scanner.c scanner.l	

lex:
	flex -o scanner.c scanner.l

compiler:parser scanner 
	gcc -c scanner.c 
	gcc -c parser.c
	gcc -c dataStructs/linkedList.c 
	gcc -c dataStructs/commentStack.c 
	gcc -c dataStructs/symb.c
	gcc -o calc scanner.o parser.o linkedList.o commentStack.o symb.o

clean:
	rm -f scanner.c
	rm -f scanner
	rm -f *.o
	rm -f parser.c
	rm -f parser.h





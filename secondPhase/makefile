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

compiler:scanner parser
	gcc -o calc scanner.c parser.c linkedList.c commentStack.c symb.c

clean:
	rm -f scanner.c
	rm -f scanner
	rm -f *.o
	rm -f parser.c
	rm -f parser.h
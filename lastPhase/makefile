compiler: parser scanner 
	gcc -c  utilities/targetCode.c utilities/quad.c avm.c
	gcc -c  scanner.c dataStructs/commentStack.c dataStructs/linkedList.c 
	gcc -c  parser.c dataStructs/symb.c utilities/parserUtilities.c dataStructs/scopeList.c 
	gcc -o calc avm.o targetCode.o quad.o parser.o scanner.o  linkedList.o commentStack.o symb.o parserUtilities.o scopeList.o  
	



wall: parser scanner 
	gcc -Wall -c parser.c dataStructs/symb.c utilities/parserUtilities.c dataStructs/scopeList.c
	gcc -Wall -c scanner.c dataStructs/commentStack.c dataStructs/linkedList.c 
	gcc -Wall -o calc parser.o scanner.o  linkedList.o commentStack.o symb.o parserUtilities.o scopeList.o

dataStructs: 
	gcc  -c dataStructs/commentStack.c
	gcc  -c dataStructs/linkedList.c
	gcc  -c dataStructs/symb.c
	gcc  -c utilities/parserUtilities.c


parser: parser.y 
	bison --yacc --defines --output=parser.c parser.y

scanner:scanner.l 
	flex -o scanner.c scanner.l	


compiler-debug:parser scanner 
	gcc -c -g parser.c dataStructs/symb.c utilities/parserUtilities.c dataStructs/scopeList.c 
	gcc -c -g scanner.c dataStructs/commentStack.c dataStructs/linkedList.c 
	gcc -c -g  utilities/quad.c  utilities/targetCode.c avm.c
	gcc -o  calc -g parser.o avm.o scanner.o  linkedList.o commentStack.o symb.o parserUtilities.o scopeList.o quad.o targetCode.o
	gdb calc
clean:
	rm -f scanner.c
	rm -f scanner
	rm -f *.o
	rm -f parser.c
	rm -f parser.h
	rm -f calc





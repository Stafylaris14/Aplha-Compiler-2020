scanner:scanner.l dataStructs/linkedList.c dataStructs/commentStack.c

	flex -o scanner.c scanner.l
	gcc -c dataStructs/commentStack.c
	gcc -c dataStructs/linkedList.c
	gcc -c scanner.c
	gcc -o scanner scanner.o linkedList.o commentStack.o
lex:
	flex -o scanner.c scanner.l
	

test:scanner
	./scanner Testfile.txt


clean:
	rm -f scanner.c
	rm -f scanner
	rm -f *.o
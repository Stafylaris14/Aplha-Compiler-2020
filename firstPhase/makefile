lex:
	flex -o scanner.c scanner.l
	



scanner:scanner.c linkedList.c
	gcc -c linkedList.c
	gcc -c scanner.c
	gcc -o scanner scanner.o linkedList.o

test:
	./scanner Testfile.txt


clean:
	rm -f scanner.c
	rm -f scanner
lex:
	flex -o scanner.c scanner.l
	gcc scanner.c -o scanner


test:
	./scanner Testfile.txt


clean:
	rm -f scanner.c
	rm -f scanner
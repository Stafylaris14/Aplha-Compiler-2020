
scanner:scanner.l dataStructs/linkedList.c dataStructs/commentStack.c
	flex -o scanner.c scanner.l
	gcc  -c dataStructs/commentStack.c
	gcc  -c dataStructs/linkedList.c
	gcc  -c scanner.c
	gcc  -o scanner scanner.o linkedList.o commentStack.o

parser: scanner
	bison --yacc --defines --output=parser.c parser.y

lex:
	flex -o scanner.c scanner.l
	
test:scanner
	./scanner Testfile.txt

compiler:scanner parser
	gcc -o calc scanner.c parser.c


clean:
	rm -f scanner.c
	rm -f scanner
	rm -f *.o
	rm -f parser.c
	rm -f parser.h

comments:scanner
	./scanner ../testfiles/phase1/comments_error1.alpha
	./scanner ../testfiles/phase1/comments_error2.alpha
	./scanner ../testfiles/phase1/comments.alpha

string:
	./scanner ../testfiles/phase1/string.alpha
	./scanner ../testfiles/phase1/string_err2.alpha




scanner:scanner.l dataStructs/linkedList.c dataStructs/commentStack.c
	flex -o scanner.c scanner.l
	gcc  -c dataStructs/commentStack.c
	gcc  -c dataStructs/linkedList.c
	gcc  -c scanner.c
	gcc  -o scanner scanner.o linkedList.o commentStack.o
lex:
	flex -o scanner.c scanner.l
	
test:scanner
	./scanner Testfile.txt


clean:
	rm -f scanner.c
	rm -f scanner
	rm -f *.o

comments:scanner
	./scanner ../testfiles/phase1/comments_error1.alpha
	./scanner ../testfiles/phase1/comments_error2.alpha
	./scanner ../testfiles/phase1/comments.alpha

string:
	./scanner ../testfiles/phase1/string.alpha
	# echo "SECONDTEST"
	./scanner ../testfiles/phase1/string_err2.alpha
maxSeq: maxSeq.o test-subseq.o
	gcc -o maxSeq maxSeq.o test-subseq.o
maxSeq.o: maxSeq.c
	gcc -pedantic -std=gnu99 -Wall -Werror -c maxSeq.c
test-subseq.o: test-subseq.c
	gcc -pedantic -std=gnu99 -Wall -Werror -c test-subseq.c

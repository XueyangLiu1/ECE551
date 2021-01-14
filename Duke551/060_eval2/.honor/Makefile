CFLAGS=-std=gnu99 -pedantic -Wall -Werror -ggdb3
PROGS=story-step1 story-step2 story-step3 story-step4
OBJS=$(patsubst %,%.o,$(PROGS)) rand_story.o
all: $(PROGS)
story-step%: story-step%.o rand_story.o provided.o
	gcc -o $@ $^
%.o: %.c
	gcc $(CFLAGS) -c $<

.PHONY: clean
clean:
	rm -f *~ $(PROGS) $(OBJS)

rand_story.o: rand_story.h

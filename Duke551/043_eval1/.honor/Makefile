CFLAGS=-std=gnu99 -Werror -Wall -pedantic -ggdb3
all: printCountries printRunningAvg printCumulative printDailyMax
print%: print%.o pandemic.c
	gcc $(CFLAGS) pandemic.c $< -o $@

.PHONY: clean
clean:
	rm -f *~ printCountries printRunningAvg printCumulative printDailyMax

CPPFLAGS=-std=gnu++98 -pedantic -Wall -Werror -ggdb3
vector2d: main.o vector.o
	g++ -o vector2d main.o vector.o
main.o: main.cpp
	g++ $(CPPFLAGS) -c main.cpp
vector.o: vector.cpp vector.hpp
	g++ $(CPPFLAGS) -c vector.cpp

.PHONY: clean
clean:
	rm -f *.o *~ vector2d

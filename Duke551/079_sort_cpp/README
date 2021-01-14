Earlier in the semester, you wrote a C program to read strings from
input file(s), sort them, and print them out.

In this problem, you will repeat that task (your program should behave
exactly the same way); however you will do it in C++, using the proper
C++ tools. You should call your file sortLines.cpp. 

  - You should use C++'s streams to read the input (opening
    std::ifstreams to read files or using std::cin to read from
    standard input). 
  - You should use std::vector to hold the strings that you read in. 
  - You should use std::sort to sort the vector (see
    http://www.cplusplus.com/reference/algorithm/sort/ for reference) 
  - You should then print the strings using std::cout.
  - You should NOT use FILE, malloc, realloc, qsort, or printf.

======================================================================
From the previous README:

Specifically, this program should take 0 or more command line
arguments. 
  - If no arguments (other than its own name) are provided (argc ==
    1), then your program should read from standard input, sort the
    lines of input, print the results, free memory, and exit
    successfully.
  - If 1 or more arguments are provided (argc > 1), then your program
    should treat each argument as an input file name. It should open
    that file, read all of the lines of data in it, sort the lines,
    print the results, free the memory, and close the file. If any
    errors occur, your program should print an appropriate error
    message and exit with EXIT_FAILURE. If no errors occur, your
    program should indicate its success after processing all of the
    files.

Note that we now place *no* restriction on the length of any
individual line of input. You should therefore use the getline
function to read an arbitrarily long line of input, dynamically
allocating space for it as needed. See the man page for getline for
more details.

You should make sure your program valgrinds cleanly, including no
memory leaks before you submit it. As always, submit your code for
grading. 

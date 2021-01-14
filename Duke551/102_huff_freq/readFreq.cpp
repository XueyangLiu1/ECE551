#include "readFreq.h"

#include <stdio.h>

#include <cstdlib>
#include <fstream>

void printSym(std::ostream & s, unsigned sym) {
  if (sym > 256) {
    s << "INV";
  }
  else if (sym == 256) {
    s << "EOF";
  }
  else if (isprint(sym)) {
    char c = sym;
    s << "'" << c << "'";
  }
  else {
    std::streamsize w = s.width(3);
    s << std::hex << sym << std::dec;
    s.width(w);
  }
}
uint64_t * readFrequencies(const char * fname) {
  //WRITE ME!
  std::ifstream f(fname);
  char chr;
  uint64_t * chrCounts;
  chrCounts = new uint64_t[257]();
  while (f.get(chr)) {
    chrCounts[(unsigned char)chr]++;
  }
  chrCounts[256] = 1;
  return chrCounts;
}

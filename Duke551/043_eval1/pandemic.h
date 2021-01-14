#ifndef __PANDEMIC_H__
#define __PANDEMIC_H__

#include <stdint.h>
#include <stdlib.h>

#define MAX_NAME_LEN 64

struct country_tag {
  char name[64];
  uint64_t population;
};
typedef struct country_tag country_t;

country_t parseLine(char * line);

void calcRunningAvg(unsigned * data, size_t n_days, double * avg);

void calcCumulative(unsigned * data, size_t n_days, uint64_t pop, double * cum);

void printCountryWithMax(country_t * countries,
                         size_t n_countries,
                         unsigned ** data,
                         size_t n_days);

#endif

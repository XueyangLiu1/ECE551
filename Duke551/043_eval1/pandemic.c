#include "pandemic.h"

#include <stdio.h>
#include <string.h>

country_t parseLine(char * line) {
  country_t ans;
  ans.name[0] = '\0';
  ans.population = 0;
  //initialize ans
  const char comma = ',';
  const char dash = '-';
  //comma for strchr and dash is used to eliminate the negative numbers
  char * population_p = strchr(line, comma);
  if (population_p == NULL) {
    fprintf(stderr, "Format error: No comma in the line!");
    exit(EXIT_FAILURE);
  }
  size_t name_len = population_p - line;
  //find the position of the comma and calculate the length of the country name
  if (name_len > MAX_NAME_LEN) {
    fprintf(stderr, "The country name is too long!");
    exit(EXIT_FAILURE);
  }
  //make sure the country name can fit in ans.name
  memset(ans.name, '\0', sizeof(ans.name));
  strncpy(ans.name, line, name_len);
  //initialize ans.name and copy the name to ans.name
  char * endptr;
  uint64_t converted = strtoll(population_p + 1, &endptr, 10);
  //convert the population part(decimal based) to uint64_t, the first non-number char met is pointed by endptr
  if (*endptr != '\n' || *(population_p + 1) == dash) {
    fprintf(stderr, "The format of population is wrong!");
    exit(EXIT_FAILURE);
  }
  //make sure the population part is pure number and is not negative
  //becasue strtoll can not detect the negative error
  //small problem: whether the population can fit into uint64_t is not verified
  ans.population = converted;
  return ans;
}

void calcRunningAvg(unsigned * data, size_t n_days, double * avg) {
  if (data == NULL) {
    fprintf(stderr, "Data array is null!");
    exit(EXIT_FAILURE);
  }
  if (avg == NULL) {
    fprintf(stderr, "Avg array to write is null!");
    exit(EXIT_FAILURE);
  }
  if (n_days < 7) {
    fprintf(stderr, "Not enough data!");
    exit(EXIT_FAILURE);
  }
  double one = 1;
  //double one is used to convert the type unsigned and size_t
  //since they use less bits than double, the compiler will convert them when operating them with one
  unsigned * to_del = data;
  unsigned * to_add = data + 7;
  double sum = 0;
  for (size_t i = 0; i < 7; i++) {
    sum = sum + *(data + i) * one;
  }
  //sum up from data[0] to data[6]
  *avg = sum / 7;
  //write the first seven-day avg
  if (n_days > 7) {
    for (size_t j = 1; j < n_days - 6; j++) {
      sum = sum - *to_del * one + *to_add * one;
      *(avg + j) = sum / 7;
      to_del++;
      to_add++;
    }
  }
  //if n_days>7, for the 8th day and following ones
  //sub the first day from sum and add the new day in the sequence
  //then calculate the avg and putwrite it to *avg
}

void calcCumulative(unsigned * data, size_t n_days, uint64_t pop, double * cum) {
  if (cum == NULL) {
    fprintf(stderr, "Cum array to write is null!");
    exit(EXIT_FAILURE);
  }
  if (data == NULL) {
    fprintf(stderr, "Data array is null!");
    exit(EXIT_FAILURE);
  }
  if (pop == 0) {
    fprintf(stderr, "Population should be larger than 0!");
    exit(EXIT_FAILURE);
  }
  //if pop==0, the following calculation will make no sense.
  double one = 1;
  double hundred_thousand = 100000;
  double popu = pop * one;
  double sum = 0;
  for (size_t i = 0; i < n_days; i++) {
    sum = sum + *(data + i) * one;
    *(cum + i) = hundred_thousand * (sum / popu);
  }
  //keep track of sum, each time add the new day's data to it and calculate
}

void printCountryWithMax(country_t * countries,
                         size_t n_countries,
                         unsigned ** data,
                         size_t n_days) {
  if (countries == NULL) {
    fprintf(stderr, "Countries array is null!");
    exit(EXIT_FAILURE);
  }
  if (data == NULL) {
    fprintf(stderr, "Data array is null!");
    exit(EXIT_FAILURE);
  }
  unsigned max = 0;
  char * name = NULL;
  for (size_t i = 0; i < n_days; i++) {
    for (size_t j = 0; j < n_countries; j++) {
      if (data[j][i] >= max) {
        name = countries[j].name;
        max = data[j][i];
      }
    }
  }
  printf("%s has the most daily cases with %u\n", name, max);
}

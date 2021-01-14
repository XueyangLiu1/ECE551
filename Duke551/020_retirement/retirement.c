#include <stdio.h>
#include <stdlib.h>

struct _retire_info {
  int months;
  double contribution;
  double rate_of_return;
};
typedef struct _retire_info retire_info;
double cal_one_month(double month_initial, double month_rate, double contribution) {
  double interest = month_initial * month_rate;
  double result = interest + month_initial + contribution;
  return result;
}
void retirement(int startAge, double initial, retire_info working, retire_info retired) {
  {
    double month_rate = working.rate_of_return / 12;
    while (working.months > 0) {
      printf(
          "Age %3d month %2d you have $%.2lf\n", startAge / 12, startAge % 12, initial);
      initial = cal_one_month(initial, month_rate, working.contribution);
      startAge += 1;
      working.months -= 1;
    }
  }
  {
    double month_rate = retired.rate_of_return / 12;
    while (retired.months > 0) {
      printf(
          "Age %3d month %2d you have $%.2lf\n", startAge / 12, startAge % 12, initial);
      initial = cal_one_month(initial, month_rate, retired.contribution);
      startAge += 1;
      retired.months -= 1;
    }
  }
}
int main() {
  retire_info working;
  working.months = 489;
  working.contribution = 1000;
  working.rate_of_return = 0.045;
  retire_info retired;
  retired.months = 384;
  retired.contribution = -4000;
  retired.rate_of_return = 0.01;
  retirement(327, 21345, working, retired);
  return EXIT_SUCCESS;
}

#include <stdint.h>
#include <stdlib.h>
#include <stdbool.h>
#include <stdio.h>

const uint32_t n_default = 2000;

const uint32_t nmonths = 12;
const uint32_t mdaysn[] = { 31,28,31,30,31,30,31,31,30,31,30,31 };
const uint32_t mdaysl[] = { 31,29,31,30,31,30,31,31,30,31,30,31 };

static bool
year_isleap(uint32_t year) {
  return (year % 4 == 0) && ((year % 100 != 0) || (year % 400 == 0));
}

static const uint32_t *
year_mdays(uint32_t year) {
  return year_isleap(year) ? mdaysl : mdaysn;
}

uint32_t
solve(uint32_t n) {
  uint32_t result = 0;

  for (uint32_t year = 1900, day = 1; year <= n; ++year) {
    const uint32_t *mdays = year_mdays(year);
    for (uint32_t i = 0; i < nmonths; ++i) {
      if (year >= 1901 && day == 0) ++result;
      day = (day + mdays[i]) % 7;
    }
  }

  return result;
}

int
main(int argc, char* argv[]) {
  if (argc <= 1) {
    printf("solve(%u) = %u\n", n_default, solve(n_default));
  } else {
    for (int i = 1; i < argc; ++i) {
      uint32_t n = strtoul(argv[i], NULL, 0);
      printf("solve(%u) = %u\n", n, solve(n));
    }
  }
  return 0;
}

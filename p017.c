#include <stdint.h>
#include <stdlib.h>
#include <stdbool.h>
#include <stdio.h>

#define CHARLEN(x) (sizeof(x) - 1)

const uint64_t n_default = 1000;

uint64_t ones[] = {
  CHARLEN(""),
  CHARLEN("one"),
  CHARLEN("two"),
  CHARLEN("three"),
  CHARLEN("four"),
  CHARLEN("five"),
  CHARLEN("six"),
  CHARLEN("seven"),
  CHARLEN("eight"),
  CHARLEN("nine"),
  CHARLEN("ten"),
  CHARLEN("eleven"),
  CHARLEN("twelve"),
  CHARLEN("thirteen"),
  CHARLEN("fourteen"),
  CHARLEN("fifteen"),
  CHARLEN("sixteen"),
  CHARLEN("seventeen"),
  CHARLEN("eighteen"),
  CHARLEN("nineteen"),
};

uint64_t tens[] = {
  CHARLEN(""),
  CHARLEN(""),
  CHARLEN("twenty"),
  CHARLEN("thirty"),
  CHARLEN("forty"),
  CHARLEN("fifty"),
  CHARLEN("sixty"),
  CHARLEN("seventy"),
  CHARLEN("eighty"),
  CHARLEN("ninety"),
};

uint64_t hundred = CHARLEN("hundred");
uint64_t thousand = CHARLEN("thousand");
uint64_t and = CHARLEN("and");

static uint64_t
count_letters(uint64_t x) {
  uint64_t result = 0;
  uint64_t d1 = x % 10;
  uint64_t d11 = x % 100;
  uint64_t d10 = (x /= 10) % 10;
  uint64_t d100 = (x /= 10) % 10;
  uint64_t d1000 = (x /= 10) % 10;
  bool any = false;

  if (d1000 > 0) {
    result += ones[d1000] + thousand;
    any = true;
  }
  if (d100 > 0) {
    if (any) result += and;
    result += ones[d100] + hundred;
    any = true;
  }
  if (d11 == 0) {
    // pass
  } else if (d11 < 20) {
    if (any) result += and;
    result += ones[d11];
  } else {
    if (any) result += and;
    result += tens[d10] + ones[d1];
  }

  return result;
}

uint64_t
solve(uint64_t n) {
  uint64_t result = 0;

  for (uint64_t i = 1; i <= n; ++i) {
    result += count_letters(i);
  }

  return result;
}

int
main(int argc, char* argv[]) {
  if (argc <= 1) {
    printf("solve(%lu) = %lu\n", n_default, solve(n_default));
  } else {
    for (int i = 1; i < argc; ++i) {
      uint64_t n = strtoul(argv[i], NULL, 0);
      printf("solve(%lu) = %lu\n", n, solve(n));
    }
  }
  return 0;
}

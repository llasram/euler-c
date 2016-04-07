#include <stdint.h>
#include <stdlib.h>
#include <stdbool.h>
#include <stdio.h>
#include <math.h>

const uint64_t n_default = 1000;

uint64_t
solve(uint64_t n) {
  // 1 byte per decimal digit: wasteful but simple
  size_t nalloc = ceil((double)n * log(2) / log(10));
  uint8_t *digits = calloc(nalloc, sizeof(uint8_t));

  digits[0] = 2;
  uint32_t nused = 1;
  while (--n) {
    uint32_t carry = 0;
    uint32_t i = 0;
    for (i = 0; i < nused || carry; ++i) {
      uint32_t value = carry + 2 * digits[i];
      digits[i] = value % 10;
      carry = value / 10;
    }
    nused = i;
  }

  uint64_t sum = 0;
  for (uint64_t i = 0; i < nused; ++i) {
    sum += digits[i];
  }

  free(digits);

  return sum;
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

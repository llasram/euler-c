#include <stdint.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <stdio.h>
#include <math.h>

const uint64_t n_default = 100;

static uint8_t *
grow(uint8_t *digits, size_t *nallocp) {
  size_t nalloc = *nallocp;
  size_t prev = nalloc;
  nalloc = (size_t)ceil(1.618 * (double)nalloc);
  digits = realloc(digits, nalloc);
  memset(&digits[prev], 0, nalloc - prev);
  *nallocp = nalloc;
  return digits;
}

uint64_t
solve(uint64_t n) {
  // 1 byte per decimal digit: wasteful but simple
  size_t nalloc = 1;
  uint8_t *digits = calloc(nalloc, sizeof(uint8_t));

  uint32_t nused = 1;
  digits[0] = 1;

  for (uint32_t x = 2; x <= n; ++x) {
    uint32_t carry = 0;
    uint32_t i = 0;
    for (i = 0; i < nused || carry; ++i) {
      if (i >= nalloc) digits = grow(digits, &nalloc);
      uint32_t value = carry + x * digits[i];
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

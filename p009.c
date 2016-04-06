#include <stdint.h>
#include <stdlib.h>
#include <stdbool.h>
#include <stdio.h>
#include <math.h>

const uint64_t n_default = 1000;

uint64_t
solve(uint64_t n) {
  uint64_t result = 0;

  for (uint64_t a = 2; a < n; ++a) {
    for (uint64_t b = 1; b < a; ++b) {
      uint64_t c = n - a - b;
      uint64_t c2 = c*c;
      uint64_t h2 = a*a + b*b;
      if (h2 > c2) break;
      if (h2 < c2) continue;
      result = a * b * c;
      goto found;
    }
  }

 found:
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

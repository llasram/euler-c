#include <stdint.h>
#include <stdlib.h>
#include <stdbool.h>
#include <stdio.h>
#include <math.h>

const uint64_t n_default = 20;

static uint64_t
gcd(uint64_t a, uint64_t b) {
  while (b) {
    uint64_t b1 = a % b;
    a = b; b = b1;
  }
  return a;
}

uint64_t
solve(uint64_t n) {
  // For an n×n grid there are 2n total steps.  We must select n of those steps
  // to be down steps; the remainder are implicitly right steps.  The number of
  // different ways of choosing those n down steps is 2n choose n.
  uint64_t num = 1, den = 1;
  for (uint64_t i = 1; i <= n; ++i) {
    num *= n + i; den *= i;
    uint64_t q = gcd(num, den);
    num /= q; den /= q;
  }
  return num;
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

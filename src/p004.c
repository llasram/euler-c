#include <stdint.h>
#include <stdlib.h>
#include <stdbool.h>
#include <stdio.h>
#include <math.h>

const uint64_t n_default = 3;

static inline bool
ispalindrome(uint64_t x) {
  uint64_t t = x;
  uint64_t y = 0;
  while (t > 0) {
    y = (y * 10) + (t % 10);
    t = t / 10;
  }
  return x == y;
}

uint64_t
solve(uint64_t n) {
  uint64_t result = 0;
  uint64_t lower = pow(10, n - 1);
  uint64_t upper = lower * 10;
  for (uint64_t i = lower; i < upper; ++i) {
    for (uint64_t j = i; j < upper; ++j) {
      uint64_t x = i * j;
      if (x > result && ispalindrome(x)) {
        result = x;
      }
    }
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

#include <stdint.h>
#include <stdlib.h>
#include <stdbool.h>
#include <stdio.h>
#include <math.h>

const uint64_t n_default = 100;

uint64_t
solve(uint64_t n) {
  uint64_t result = 0;
  for (uint64_t i = 1; i < n; ++i) {
    for (uint64_t j = i + 1; j <= n; ++j) {
      result += 2 * i * j;
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

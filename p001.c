#include <stdint.h>
#include <stdlib.h>
#include <stdio.h>

const uint64_t n_default = 1000;

uint64_t
solve(uint64_t n) {
  uint64_t sum = 0;
  for (uint64_t i = 1; i < n; ++i) {
    if (i % 3 == 0 || i % 5 == 0) {
      sum += i;
    }
  }
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

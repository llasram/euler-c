#include <stdint.h>
#include <stdlib.h>
#include <stdio.h>

const uint64_t n_default = 1000;

uint64_t
sumto(uint64_t n, uint64_t m) {
  n = (n - 1) / m;
  return m * (n + 1) * n / 2;
}

uint64_t
solve(uint64_t n) {
  return sumto(n, 3) + sumto(n, 5) - sumto(n, 15);
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

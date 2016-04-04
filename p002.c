#include <stdint.h>
#include <stdlib.h>
#include <stdio.h>

uint64_t
solve(uint64_t n) {
  uint64_t sum = 0;
  uint64_t f0 = 1;
  uint64_t f = 1;
  while (f < n) {
    if ((f & 1) == 0) sum += f;
    uint64_t f1 = f0 + f;
    f0 = f;
    f = f1;
  }
  return sum;
}

int
main(int argc, char* argv[]) {
  if (argc <= 1) {
    printf("solve(4000000) = %lu\n", solve(4000000));
  } else {
    for (int i = 1; i < argc; ++i) {
      uint64_t n = strtoul(argv[i], NULL, 0);
      printf("solve(%lu) = %lu\n", n, solve(n));
    }
  }
  return 0;
}

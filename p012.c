#include <stdint.h>
#include <stdlib.h>
#include <stdio.h>
#include <math.h>

const uint64_t n_default = 500;

const uint64_t bound = 1UL << 27;
const uint64_t ntrinum = 92682;

uint64_t
solve(uint64_t n) {
  uint64_t result = 0;
  uint64_t nfactors[ntrinum];
  uint64_t trinums[ntrinum];

  trinums[0] = nfactors[0] = 0;
  for (uint64_t i = 1; i < ntrinum; ++i) {
    trinums[i] = trinums[i - 1] + i;
    nfactors[i] = 1;
  }

  uint64_t i = 2;
  for (uint64_t x = 2; x < bound; ++x) {
    while (trinums[i] < x) ++i;
    uint64_t j = i;
    uint64_t t = trinums[j];
    for (uint64_t y = x; y < bound; y += x) {
      while (y >= t) {
        if (y == t && ++nfactors[j] > n && y == x) {
          result = t;
          goto found;
        }
        t = trinums[++j];
      }
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

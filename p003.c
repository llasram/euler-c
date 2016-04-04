#include <stdint.h>
#include <stdlib.h>
#include <stdbool.h>
#include <stdio.h>
#include <math.h>

const uint64_t n_default = 600851475143;

static inline bool
bitvec_get(uint32_t *bitvec, size_t index) {
  size_t word = index / 32;
  size_t bit = 1 << (index & 31);
  return (bitvec[word] & bit) != 0;
}

static inline void
bitvec_set(uint32_t *bitvec, size_t index, bool value) {
  size_t word = index / 32;
  size_t bit = 1 << (index & 31);
  bitvec[word] = value
    ? (bitvec[word] | bit)
    : (bitvec[word] & ~bit);
}

uint64_t
solve(uint64_t n) {
  uint64_t result = 0;
  uint64_t sqrt_n = (uint64_t)floor(sqrt((double)n));
  uint32_t *composites = calloc((sqrt_n / 32) + 1, sizeof(uint32_t));

  for (uint64_t x = 3; x <= sqrt_n; x += 2) {
    if (bitvec_get(composites, x)) continue;
    for (uint64_t i = x; i <= sqrt_n; i += x) bitvec_set(composites, i, true);
    if (n % x == 0) result = x;
  }

  free(composites);

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

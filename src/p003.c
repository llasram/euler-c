#include <stdint.h>
#include <stdlib.h>
#include <stdbool.h>
#include <stdio.h>
#include <math.h>

#define max(a, b) ({         \
  __typeof__ (a) _a = (a);   \
  __typeof__ (b) _b = (b);   \
  _a > _b ? _a : _b;         \
})

const uint64_t n_default = 600851475143;

typedef uint32_t bitvec_t;

static inline bitvec_t *
bitvec_new(size_t n) {
  return calloc((n + 31) / 32, sizeof(uint32_t));
}

static inline bool
bitvec_get(bitvec_t *bitvec, size_t index) {
  size_t word = index / 32;
  size_t bit = 1 << (index & 31);
  return (bitvec[word] & bit) != 0;
}

static inline void
bitvec_set(bitvec_t *bitvec, size_t index, bool value) {
  size_t word = index / 32;
  size_t bit = 1 << (index & 31);
  bitvec[word] = value
    ? (bitvec[word] | bit)
    : (bitvec[word] & ~bit);
}

static uint64_t
bound_for(uint64_t n) {
  return (max(3UL, (uint64_t)floor(sqrt((double)n))) - 3) / 2 + 1;
}

uint64_t
solve(uint64_t n) {
  uint64_t zeros = __builtin_ctz(n);
  n >>= zeros;
  uint64_t result = zeros ? 2 : 1;
  uint64_t bound = bound_for(n);
  // Bit vector of whether 2*i + 3 is known composite
  bitvec_t *composites = bitvec_new(bound);

  for (uint64_t i = 0; i < bound; ++i) {
    if (bitvec_get(composites, i)) continue;
    uint64_t x = 2*i + 3;
    // Iterating indices by x iterates projected values by 2*x
    for (uint64_t j = i + x; j < bound; j += x) bitvec_set(composites, j, true);
    if (n % x != 0) continue;
    result = x;
    do n = n / x; while (n % x == 0);
    bound = bound_for(n);
  }
  if (n > result) {
    result = n;
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

#include <stdint.h>
#include <stdlib.h>
#include <stdbool.h>
#include <stdio.h>
#include <math.h>

const uint64_t n_default = 500;
const uint64_t bound = 1UL << 14;

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

static uint64_t *
primes_below(uint64_t bound, uint64_t *nprimes) {
  uint64_t nbits = (bound + 1) / 2;
  bitvec_t *composites = bitvec_new(nbits);
  uint64_t nprimes1 = 1;

  for (uint64_t i = 0; i < nbits; ++i) {
    if (bitvec_get(composites, i)) continue;
    uint64_t x = 2*i + 3;
    for (uint64_t j = i + x; j < nbits; j += x)
      bitvec_set(composites, j, true);
    nprimes1 += 1;
  }

  uint64_t *primes = calloc(nprimes1, sizeof(uint64_t));
  primes[0] = 2;
  for (uint64_t i = 0, j = 0; i < nbits; ++i) {
    if (bitvec_get(composites, i)) continue;
    primes[++j] = 2*i + 3;
  }

  free(composites);

  *nprimes = nprimes1;
  return primes;
}

uint64_t
solve(uint64_t n) {
  uint64_t nprimes = 0;
  uint64_t *primes = primes_below(bound, &nprimes);

  uint64_t t = 0;
  for (uint64_t i = 1;; ++i) {
    t += i;
    uint64_t t1 = t;
    uint64_t nfactors = 1;
    for (uint64_t j = 0; t1 > 1; ++j) {
      uint64_t p = primes[j];
      uint64_t q = 1;
      while (t1 % p == 0) { q += 1; t1 /= p; }
      nfactors *= q;
    }
    if (nfactors > n) break;
  }

  free(primes);

  return t;
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

#include <stdint.h>
#include <stdlib.h>
#include <stdbool.h>
#include <stdio.h>
#include <math.h>

#define unused __attribute__((__unused__))

#define max(a, b) ({         \
  __typeof__ (a) _a = (a);   \
  __typeof__ (b) _b = (b);   \
  _a > _b ? _a : _b;         \
})

const uint64_t dtriangle = 15;
const uint64_t triangle[] = {
  75,
  95,64,
  17,47,82,
  18,35,87,10,
  20, 4,82,47,65,
  19, 1,23,75, 3,34,
  88, 2,77,73, 7,63,67,
  99,65, 4,28, 6,16,70,92,
  41,41,26,56,83,40,80,70,33,
  41,48,72,33,47,32,37,16,94,29,
  53,71,44,65,25,43,91,52,97,51,14,
  70,11,33,28,77,73,17,78,39,68,17,57,
  91,71,52,38,17,14,91,43,58,50,27,29,48,
  63,66, 4,68,89,53,67,30,73,16,69,87,40,31,
   4,62,98,27,23, 9,70,98,73,93,38,53,60, 4,23,
};

uint64_t
solve(void) {
  uint64_t n = dtriangle;
  const uint64_t *row = &triangle[(n - 1) * n / 2];
  uint64_t state[n];
  for (uint32_t i = 0; i < n; ++i) state[i] = row[i];

  for (uint32_t i = 0; i < dtriangle; ++i) {
    row -= --n;
    for (uint32_t j = 0; j < n; ++j) {
      state[j] = row[j] + max(state[j], state[j + 1]);
    }
  }

  return state[0];
}

int
main(unused int argc, unused char* argv[]) {
  printf("solve() = %lu\n", solve());
  return 0;
}

#include <stdint.h>
#include <stdlib.h>
#include <stdbool.h>
#include <stdio.h>
#include <math.h>

#define MAX_STATES (7)

const uint64_t n_default = 30;

uint64_t
solve(uint64_t n) {
  unsigned long bystate[MAX_STATES] = { 1, 0 };
  unsigned long bystate1[MAX_STATES] = { 0 };

  for (unsigned int i = 0; i < n; ++i) {
    for (unsigned int s = 0; s < MAX_STATES; ++s) {
      if (s == 3) continue;
      bystate1[s & 4] += bystate[s]; // O
      if (s < 4) bystate1[4] += bystate[s]; // L
      if ((s & 3) < 2) bystate1[s + 1] += bystate[s]; // A
    }
    for (unsigned int s = 0; s < MAX_STATES; ++s) {
      bystate[s] = bystate1[s];
      bystate1[s] = 0;
    }
  }

  uint64_t result = 0;
  for (unsigned int s = 0; s < MAX_STATES; ++s) {
    result += bystate[s];
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

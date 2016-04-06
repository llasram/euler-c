#include <stdint.h>
#include <stdlib.h>
#include <stdbool.h>
#include <stdio.h>
#include <math.h>

const uint32_t n_default = (uint32_t)1e6;

uint32_t
solve(uint32_t n) {
  uint32_t result = 0;
  uint32_t *state = malloc(n * sizeof(uint32_t));
  for (uint32_t i = 0; i < n; ++i) state[i] = i;

  bool finished = false;
  do {
    finished = true;
    for (uint32_t i = 1; i < n; ++i) {
      uint32_t i1 = state[i];
      if (i1 == 1) continue;
      finished = false;
      state[i] = (i1 % 2 == 0) ? (i1 / 2) : (3*i1 + 1);
      result = i;
    }
  } while (!finished);

  free(state);

  return result;
}

int
main(int argc, char* argv[]) {
  if (argc <= 1) {
    printf("solve(%u) = %u\n", n_default, solve(n_default));
  } else {
    for (int i = 1; i < argc; ++i) {
      uint32_t n = (uint32_t)strtoul(argv[i], NULL, 0);
      printf("solve(%u) = %u\n", n, solve(n));
    }
  }
  return 0;
}

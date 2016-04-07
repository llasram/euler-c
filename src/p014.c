#include <stdint.h>
#include <stdlib.h>
#include <stdbool.h>
#include <stdio.h>
#include <math.h>

const uint32_t n_default = (uint32_t)1e6;

uint32_t
solve(uint32_t n) {
  uint32_t result = 0;
  uint32_t bound = n - 2;
  uint32_t *num = malloc(bound * sizeof(uint32_t));
  uint32_t *state = malloc(bound * sizeof(uint32_t));
  uint32_t *done = calloc(n, sizeof(uint32_t));

  for (uint32_t i = 0; i < bound; ++i) {
    state[i] = num[i] = i + 2;
  }
  done[0] = done[1] = 1;

  uint32_t live = bound;
  uint32_t len_max = 0;
  uint32_t len = 1;
  while (live > 0) {
    uint32_t i_live = 0;
    for (uint32_t i = 0; i < live; ++i) {
      uint32_t m = num[i];
      uint32_t x = state[i];
      x = (x % 2 == 0) ? (x / 2) : (3*x + 1);
      if (x < n && done[x] > 0) {
        done[m] = len + done[x];
        if (done[m] > len_max) {
          len_max = done[m];
          result = m;
        }
      } else {
        state[i_live] = x;
        num[i_live] = m;
        i_live += 1;
      }
    }
    live = i_live;
    len += 1;
  }

  free(done);
  free(state);
  free(num);

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

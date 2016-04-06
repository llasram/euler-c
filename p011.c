#include <stdint.h>
#include <stdlib.h>
#include <stdbool.h>
#include <stdio.h>
#include <math.h>

#define min(a, b) ({         \
  __typeof__ (a) _a = (a);   \
  __typeof__ (b) _b = (b);   \
  _a < _b ? _a : _b;         \
})

#define max(a, b) ({         \
  __typeof__ (a) _a = (a);   \
  __typeof__ (b) _b = (b);   \
  _a > _b ? _a : _b;         \
})

const uint64_t n_default = 4;

const int32_t dgrid = 20;
const uint64_t grid[] = {
   8, 2,22,97,38,15, 0,40, 0,75, 4, 5, 7,78,52,12,50,77,91, 8,
  49,49,99,40,17,81,18,57,60,87,17,40,98,43,69,48, 4,56,62, 0,
  81,49,31,73,55,79,14,29,93,71,40,67,53,88,30, 3,49,13,36,65,
  52,70,95,23, 4,60,11,42,69,24,68,56, 1,32,56,71,37, 2,36,91,
  22,31,16,71,51,67,63,89,41,92,36,54,22,40,40,28,66,33,13,80,
  24,47,32,60,99, 3,45, 2,44,75,33,53,78,36,84,20,35,17,12,50,
  32,98,81,28,64,23,67,10,26,38,40,67,59,54,70,66,18,38,64,70,
  67,26,20,68, 2,62,12,20,95,63,94,39,63, 8,40,91,66,49,94,21,
  24,55,58, 5,66,73,99,26,97,17,78,78,96,83,14,88,34,89,63,72,
  21,36,23, 9,75, 0,76,44,20,45,35,14, 0,61,33,97,34,31,33,95,
  78,17,53,28,22,75,31,67,15,94, 3,80, 4,62,16,14, 9,53,56,92,
  16,39, 5,42,96,35,31,47,55,58,88,24, 0,17,54,24,36,29,85,57,
  86,56, 0,48,35,71,89, 7, 5,44,44,37,44,60,21,58,51,54,17,58,
  19,80,81,68, 5,94,47,69,28,73,92,13,86,52,17,77, 4,89,55,40,
   4,52, 8,83,97,35,99,16, 7,97,57,32,16,26,26,79,33,27,98,66,
  88,36,68,87,57,62,20,72, 3,46,33,67,46,55,12,32,63,93,53,69,
   4,42,16,73,38,25,39,11,24,94,72,18, 8,46,29,32,40,62,76,36,
  20,69,36,41,72,30,23,88,34,62,99,69,82,67,59,85,74, 4,36,16,
  20,73,35,29,78,31,90, 1,74,31,49,71,48,86,81,16,23,57, 5,54,
   1,70,54,71,83,51,54,69,16,92,33,48,61,43,52, 1,89,19,67,48,
};

typedef struct pos_t {
  int32_t i;
  int32_t j;
} pos_t;

typedef enum state_t {
  STATE_CONT,
  STATE_RESET,
  STATE_DONE,
} state_t;

typedef state_t (*traversal_t)(pos_t *pos);

static state_t
traversal_rows(pos_t *pos) {
  if (pos->i == -1 && pos->j == -1) {
    pos->i = pos->j = 0;
    return STATE_RESET;
  } else if (++pos->j < dgrid) {
    return STATE_CONT;
  } else if (pos->j = 0, ++pos->i < dgrid) {
    return STATE_RESET;
  } else {
    return STATE_DONE;
  }
}

static state_t
traversal_cols(pos_t *pos) {
  if (pos->i == -1 && pos->j == -1) {
    pos->i = pos->j = 0;
    return STATE_RESET;
  } else if (++pos->i < dgrid) {
    return STATE_CONT;
  } else if (pos->i = 0, ++pos->j < dgrid) {
    return STATE_RESET;
  } else {
    return STATE_DONE;
  }
}

static state_t
traversal_diagdr(pos_t *pos) {
  if (pos->i == -1 && pos->j == -1) {
    pos->i = dgrid - 1;
    pos->j = 0;
    return STATE_RESET;
  } else if (pos->i == 0 && pos->j == dgrid - 1) {
    return STATE_DONE;
  }
  pos->i += 1; pos->j += 1;
  if (pos->i < dgrid && pos->j < dgrid) {
    return STATE_CONT;
  } else {
    int32_t d = min(pos->i, ++pos->j);
    pos->i -= d;
    pos->j -= d;
    return STATE_RESET;
  }
}

static state_t
traversal_diagdl(pos_t *pos) {
  if (pos->i == -1 && pos->j == -1) {
    pos->i = dgrid - 1;
    pos->j = dgrid - 1;
    return STATE_RESET;
  } else if (pos->i == 0 && pos->j == 0) {
    return STATE_DONE;
  }
  pos->i += 1; pos->j -= 1;
  if (pos->i < dgrid && 0 <= pos->j) {
    return STATE_CONT;
  } else {
    int32_t d = min(pos->i, dgrid - --pos->j);
    pos->i -= d;
    pos->j += d;
    return STATE_RESET;
  }
}

static inline uint64_t
grid_get(pos_t *pos) {
  return grid[(pos->i * dgrid) + pos->j];
}

static uint64_t
traverse(uint64_t n, traversal_t next) {
  uint64_t result = 0;
  pos_t pos = { -1, -1 };
  state_t state = next(&pos);
  uint64_t p = 1, z = 0, m = 0;
  uint64_t hist[n];

  for (; state != STATE_DONE; state = next(&pos)) {
    if (state == STATE_RESET) { p = 1; z = 0; m = 0; }

    if (m >= n) {
      uint64_t x0 = hist[m % n];
      if (x0 == 0) --z; else p /= x0;
    }
    uint64_t x1 = grid_get(&pos);
    if (x1 == 0) ++z; else p *= x1;
    hist[m % n] = x1;
    if (++m >= n && !z && p > result) {
      result = p;
    }
  }

  return result;
}

uint64_t
solve(uint64_t n) {
  uint64_t result = 0;

  result = max(result, traverse(n, &traversal_rows));
  result = max(result, traverse(n, &traversal_cols));
  result = max(result, traverse(n, &traversal_diagdr));
  result = max(result, traverse(n, &traversal_diagdl));

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

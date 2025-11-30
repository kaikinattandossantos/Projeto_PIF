#include "rnd.h"
#include <stdlib.h>
#include <time.h>

void rnd_init(void) {
    srand(time(NULL));
}

int rand_int_inclusive(int min, int max) {
    if (max < min) return min;
    return min + rand() % (max - min + 1);
}
#include <stdlib.h>
#include <time.h>
#include "rnd.h"

void rnd_init() {
    srand((unsigned int) time(NULL));
}

int rand_int_inclusive(int a, int b) {
    if (b < a) { int t = a; a = b; b = t; }
    int range = b - a + 1;
    return a + (rand() % range);
}

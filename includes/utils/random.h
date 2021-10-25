//
// Created by drayr on 24/10/2021.
//

#ifndef MAPDA_RANDOM_H
#define MAPDA_RANDOM_H

#include <stdlib.h>

#define EVEN_RAND(m, n)(((m / 2) + rand() % ((n - m + 2) / 2)) * 2)
#define RAND(m, n)(rand() % (n + 1 - m) + m)

#endif //MAPDA_RANDOM_H

//
// Created by drayr on 23/10/2021.
//

#ifndef MAPDA_BITS_H
#define MAPDA_BITS_H

#include <stdbool.h>

#define SET_BIT(n, pos)(n |= 1UL << pos)
#define CLEAR_BIT(n, pos)(n &= ~(1UL << pos))
#define TOGGLE_BIT(n, pos)(n ^= 1UL << pos)
#define CHECK_BIT(n, pos)((n >> pos) & 1U)
#define CHANGE_NTH_BIT_TO(n, pos, x)(n ^= (-x ^ n) & (1UL << n))

#endif //MAPDA_BITS_H

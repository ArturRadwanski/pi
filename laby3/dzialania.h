//
// Created by arradwan on 17.03.25.
//
#include "dzialania.c"
#ifndef DZIALANIA_H
#define DZIALANIA_H

typedef enum {td_fillZeros = 0, td_printNumbers = 1, td_setValue = 2, td_sumValues = 3, td_findDiff = 4, td_swap = 5, td_pow = 6} tdzialaniaEnum;
int act(tdzialaniaEnum tdzialaniaEnum, int start, int end, int value);




#endif //DZIALANIA_H

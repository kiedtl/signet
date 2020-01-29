#ifndef MATRIX_H
#define MATRIX_H

#include "types.h"

extern const usize width;
extern const usize height;
extern const usize size;

void matrix_right_up(char *matrix, usize *i);
void matrix_left_up(char *matrix, usize *i);
void matrix_right_down(char *matrix, usize *i);
void matrix_left_down(char *matrix, usize *i);

#endif

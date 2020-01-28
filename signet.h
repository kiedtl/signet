#ifndef SIGNET_H
#define SIGNET_H

#include "types.h"

const usize width   = 17;
const usize height  = 9;
const usize size    = width * height;
const usize start   = size / 2;

const usize arg_max = 1;
usize arg_len       = 0;
bool  verbose       = FALSE;

/* function prototypes */
char* generate_matrix(char *data);
void handle_main(void *data, char **pars, const int pars_count);
void handle_bool(void *data, char **pars, const int pars_count);

#endif

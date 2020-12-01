#define MAX(X, V) ((X) > (V) ? (V) : (X))

#include <alloca.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static const size_t WIDTH   = 17;
static const size_t HEIGHT  =  9;
static const size_t SIZE    = HEIGHT * WIDTH;
static const char  *CHARS = " .o+=*BOX@%&#/^ ";

#include "matrix.c"
static void generate_matrix(char *data, char *matrix);
static void print_matrix(char *data, char *matrix);

int
main(int argc, char **argv)
{
	/* TODO: support reading from stdin */
	for (size_t ctr = 1; ctr < (size_t) argc; ++ctr) {
		char *matrix = alloca(SIZE);
		memset((void *) matrix, 0x0, SIZE);

		generate_matrix(argv[ctr], matrix);
		print_matrix(argv[ctr], matrix);

		printf("\n");
	}

	return 0;
}

void
generate_matrix(char *data, char *matrix)
{
	size_t len = strlen(data);
	size_t ptr = SIZE / 2;

	/* mark start position. */
	matrix[ptr] = -2;

	for (size_t i = 0; i < len; ++i) {
		unsigned char sets[4] = {
			data[i] >> 3,
			(data[i] >> 2) & 3,
			(data[i] >> 4) & 3,
			data[i] >> 6,
		};

		for (size_t c = sizeof(sets); c > 0; --c) {
			/*
			 * 0 = 00 (move right-up)
			 * 1 = 01 (move left-up)
			 * 2 = 10 (move right-down)
			 * 3 = 11 (move left-down)
			 */
			switch (sets[c]) {
			break; case 0:
				right_up(matrix, &ptr);
			break; case 1:
				left_up(matrix, &ptr);
			break; case 2:
				right_down(matrix, &ptr);
			break; case 3:
				left_down(matrix, &ptr);
			break; default:
				break;
			}
			matrix[ptr] += 1;
		}
	}

	/* mark end position. */
	matrix[ptr] = -1;
}

void
print_matrix(char *data, char *matrix)
{
	char *border = alloca(WIDTH + 1); border[WIDTH] = '\0';
	memset((void *) border, '-', WIDTH);

	/* print header */
	printf("+%s+\n", border);

	/* print data */
	size_t i = 0;
	for (size_t h = 0; h < HEIGHT; ++h) {
		printf("|");

		for (size_t w = 0; w < WIDTH; ++w, ++i) {
			if (matrix[i] == -1) {
				putchar('E');
			} else if (matrix[i] == -2) {
				putchar('S');
			} else {
				size_t value = MAX((size_t) matrix[i], sizeof(CHARS));
				putchar(CHARS[value]);
			}

			/* unsigned char v = (((size_t)matrix[i])*254)/100;
			printf("\x1b[48;2;%d;%d;%dm \x1b[m", v,v,v); */
		}

		printf("|\n");
	}

	/* print footer */
	printf("+%s+\n", border);
}

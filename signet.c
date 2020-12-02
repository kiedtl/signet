#include <stdio.h>
#include <string.h>
#include <unistd.h>

/* dimensions of matrix. */
static const size_t WIDTH  = 17;
static const size_t HEIGHT =  9;
static const size_t SIZE   = HEIGHT * WIDTH;

/* characters used to print matrix. S and E are special values
 * used to store the start and end positions. */
static const char *CHARS = " .o+=*BOX@%&#/^SE";
static const size_t MAX_CELL_VALUE = 14;

#include "matrix.c"
static void (*const MOVEMENTS[])(size_t *) = {
	&right_up, &left_up, &right_down, &left_down,
};

static void mkmatrix(char *data, size_t *matrix);
static void display(size_t *matrix);

static _Bool istty = 0;

int
main(int argc, char **argv)
{
	istty = isatty(STDOUT_FILENO);

	/* TODO: support reading from stdin */
	for (size_t ctr = 1; ctr < (size_t) argc; ++ctr) {
		size_t matrix[SIZE];
		for (size_t i = 0; i < SIZE; ++i) matrix[i] = 0;

		mkmatrix(argv[ctr], (size_t *) &matrix);
		display((size_t *) &matrix);
	}

	return 0;
}

static void
mkmatrix(char *data, size_t *matrix)
{
	size_t len = strlen(data);
	size_t ptr = SIZE / 2;

	for (size_t i = 0; i < len; ++i) {
		unsigned char bits[] = {
			data[i] >> 6,
			(data[i] >> 4) & 3,
			(data[i] >> 2) & 3,
			data[i] >> 3,
		};

		for (size_t c = 0; c < 3; ++c) {
			/*
			 * 0 = 00 (move right-up)
			 * 1 = 01 (move left-up)
			 * 2 = 10 (move right-down)
			 * 3 = 11 (move left-down)
			 */
			(*MOVEMENTS[bits[c]])(&ptr);

			if (matrix[ptr] <= MAX_CELL_VALUE)
				++matrix[ptr];
		}
	}

	/* mark start/end position. */
	matrix[SIZE / 2] = 15;
	matrix[ptr] = 16;
}

static void
display(size_t *matrix)
{
	char border[WIDTH + 1]; border[WIDTH] = '\0';
	memset((void *) &border, '-', WIDTH);

	printf("+%s+\n", (char *) &border);

	size_t i = 0;
	for (size_t h = 0; h < HEIGHT; ++h) {
		printf("|");

		for (size_t w = 0; w < WIDTH; ++w, ++i) {
			unsigned char value = CHARS[matrix[i]];

			/* print the start/end positions (S or E in bold
			 * using terminal escape sequences, if stdout is a
			 * terminal */
			if (matrix[i] > MAX_CELL_VALUE && istty)
				printf("\x1b[1m%c\x1b[m", value);
			else
				putchar(value);
		}

		printf("|\n");
	}

	printf("+%s+\n\n", (char *) &border);
}

#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>

/* dimensions of matrix. */
static const size_t WIDTH  = 20;
static const size_t HEIGHT = 11;
static const size_t SIZE   = HEIGHT * WIDTH;

/* characters used to print matrix. S and E are special values
 * used to store the start and end positions. */
static const char *CHARS = " .o+=*BOX@%&#/^SE";
static const size_t MAX_CELL_VALUE = 14;

#include "matrix.c"
static void (*const MOVEMENTS[])(size_t *) = {
	&right_up, &left_up, &right_down, &left_down,
};

static _Bool istty = 0;

static _Bool hexinput = 0;

static void
mkmatrix(char *data, size_t *matrix)
{
	size_t len = strlen(data);
	size_t start = SIZE / 2, ptr = start;

	if (hexinput) {
		if (len % 2) { /* hex should have an even number of characters */
			fprintf(stderr, "Invalid hex input\n");
			exit(1);
		}
		len /= 2;
	}

	for (size_t i = 0; i < len; ++i) {
		char byte;
		if (hexinput) {
			if (sscanf(&data[2 * i], "%2hhx", (unsigned char*)&byte) != 1) {
				fprintf(stderr, "Invalid hex input\n");
				exit(1);
			}
		} else {
			byte = data[i];
		}

		unsigned char bits[] = {
			byte >> 6,
			(byte >> 4) & 3,
			(byte >> 2) & 3,
			byte & 3,
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
	matrix[start] = 15, matrix[ptr] = 16;
}

static void
display(char *label, size_t *matrix)
{
	char border[WIDTH + 1]; border[WIDTH] = '\0';
	memset((void *) &border, '-', WIDTH);

	if (label)
		printf("%s\n", label);
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
				printf("\x1b[31m%c\x1b[m", value);
			else
				putchar(value);
		}

		printf("|\n");
	}

	printf("+%s+\n\n", (char *) &border);
}

static void
readstdin(void)
{
	char buf[4096] = {0};
	char *bufptr = (char *)&buf, *p = bufptr;
	size_t matrix[SIZE];

	int c;
	while ((c = fgetc(stdin)) != EOF) {
		switch (c) {
		break; case '\n':
			*p = '\0';

			for (size_t i = 0; i < SIZE; ++i)
				matrix[i] = 0;

			mkmatrix(strsep(&bufptr, " "), matrix);
			strsep(&bufptr, " ");
			display(strsep(&bufptr, " "),  matrix);

			buf[0] = '\0', bufptr = p = (char *)&buf;
		break; default:
			*p = c, ++p;
		}
	}
}

int
main(int argc, char **argv)
{
	istty = isatty(STDOUT_FILENO);

	int opt;
	while ((opt = getopt(argc, argv, "x")) != -1) {
		switch (opt) {
			case 'x':
				hexinput = 1;
				break;
			default:
				fprintf(stderr, "Usage: %s [-x] [hash ...]\n", argv[0]);
				return 1;
		}
	}

	if (argc == optind) {
		readstdin();
		return 1;
	}

	for (size_t ctr = optind; ctr < (size_t)argc; ++ctr) {
		size_t matrix[SIZE];
		for (size_t i = 0; i < SIZE; ++i) matrix[i] = 0;

		mkmatrix(argv[ctr], (size_t *)&matrix);
		display(NULL, (size_t *)&matrix);
	}

	return 0;
}

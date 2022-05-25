#include <err.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <stdbool.h>
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

static _Bool istty = false;
static _Bool hexinput = true;

/* char -> number in base 16. atoi for hex input. */
static unsigned char
hex(unsigned char input)
{
	if (input >= '0' && input <= '9') {
		return input - '0';
	} else if (input >= 'a' && input <= 'f') {
		return 10 + input - 'a';
	} else if (input >= 'A' && input <= 'F') {
		return 10 + input - 'A';
	} else {
		errx(1, "0x%02x ('%c'): Invalid hex input.", input, input);
	}
}

static void
mkmatrix(char *data, size_t *matrix)
{
	size_t len = strlen(data);
	size_t start = SIZE / 2, ptr = start;

	if (hexinput) {
		if (len % 2 != 0) {
			/* hex should have an even number of characters */
			errx(1, "Invalid hex input.");
		}
	}

	for (size_t i = 0; i < len;) {
		char byte = hexinput ? (hex(data[i]) * 16) + hex(data[i + 1]) : data[i];

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

		i += hexinput ? 2 : 1;
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

			memset(matrix, 0x0, sizeof(matrix));

			mkmatrix(strsep(&bufptr, " "), matrix);

			/* Stupid glibc strsep returns 0x1 instead of NULL
			 * sometimes */
			if ((size_t)bufptr > 1) strsep(&bufptr, " ");
			char *label = (size_t)bufptr > 1 ? strsep(&bufptr, " ") : NULL;

			display(label, matrix);

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
	while ((opt = getopt(argc, argv, "hVa")) != -1) {
		switch (opt) {
		break; case 'a':
			hexinput = false;
		break; case 'V':
			fprintf(stdout, "signet v"VERSION"\n");
			return 0;
		break; case 'h': default:
			fprintf(stderr, "Usage: %s [-hV] [-a] [hash ...]\n", argv[0]);
			return opt == 'h' ? 0 : 1;
		break;
		}
	}

	if (argc == optind) {
		readstdin();
		return 0;
	}

	for (size_t ctr = optind; ctr < (size_t)argc; ++ctr) {
		size_t matrix[SIZE];
		for (size_t i = 0; i < SIZE; ++i) matrix[i] = 0;

		mkmatrix(argv[ctr], (size_t *)&matrix);
		display(NULL, (size_t *)&matrix);
	}

	return 0;
}

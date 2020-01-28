#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "types.h"
#include "argoat.h"
#include "signet.h"

int
main(int argc, char **argv)
{
	/* parse options with argoat */
	char *args[arg_max];

	const struct argoat_sprig sprigs[3] = {
		{ NULL,      0, NULL,             handle_main },
		{ "verbose", 0, (void*) &verbose, handle_bool },
		{ "v",       0, (void*) &verbose, handle_bool },
	};

	struct argoat opts = { sprigs, sizeof(sprigs), args, 0, arg_max };
	argoat_graze(&opts, argc, argv);

	char *data;

	/* TODO: support reading from stdin */
	if (arg_len > 0)
		data = args[0];
	else {
		if (verbose)
			fprintf(stderr, "warn: no arguments, exiting now...\n");
		return 0;
	}

	char matrix[size];
	for (usize i = 0; i < size; ++i) {
		matrix[i] = 0;
	}

	generate_matrix(data, (char*) &matrix);
	print_matrix((char*) &matrix);
	return 0;
}

void
generate_matrix(char *data, char *matrix)
{
	usize len = strlen(data);
	char *ptr = &matrix[start];

	for (usize i = 0; i < len; ++i) {
		u8 sets[4] = {
			data[i] >> 3,
			(data[i] >> 2) & 3,
			(data[i] >> 4) & 3,
			data[i] >> 6,
		};

		for (usize c = 0; c < sizeof(sets); ++c) {
			/*
			 * 0 = 00 (move right-up)
			 * 1 = 01 (move left-up)
			 * 2 = 10 (move right-down)
			 * 3 = 11 (move left-down)
			 */
			switch (sets[c]) {
			case 0:
				ptr = ptr - (width - 1);
				break;
			case 1:
				ptr = ptr + (width + 1);
				break;
			case 2:
				ptr = ptr - (width + 1);
				break;
			case 3:
				ptr = ptr + (width - 1);
				break;
			}
			++(*ptr);
		}
	}
}

void
print_matrix(char *matrix)
{
	/* print header */
	puts("┌───────────────────────────────────┐");

	/* print data */
	usize i = 0;
	for (usize h = 0; h < height; ++h) {
		fprintf(stdout, "│");

		for (usize w = 0; w < width; ++w) {
			switch (matrix[i]) {
			case 0:
				putchar(' ');
				break;
			case 1:
				putchar('.');
				break;
			case 2:
				putchar('o');
				break;
			case 3:
				putchar('+');
				break;
			case 4:
				putchar('=');
				break;
			case 5:
				putchar('*');
				break;
			case 6:
				putchar('8');
				break;
			case 7:
				putchar('O');
				break;
			case 8:
				putchar('X');
				break;
			case 9:
				putchar('@');
				break;
			case 10:
				putchar('%');
				break;
			case 11:
				putchar('&');
				break;
			case 12:
				putchar('#');
				break;
			case 13:
				putchar('/');
				break;
			case 14:
				putchar('^');
				break;
			case 15:
				putchar('S');
				break;
			case 16:
				putchar('E');
				break;
			}
			++i;
		}

		puts("│");
	}

	/* print footer */
	puts("└───────────────────────────────────┘");
}

void
handle_main(void *data, char **pars, const int pars_count)
{
	arg_len = (usize) pars_count;
}

void
handle_bool(void *data, char **pars, const int pars_count)
{
	*((bool*) data) = TRUE;
}

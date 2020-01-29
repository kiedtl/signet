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

	const struct argoat_sprig sprigs[8] = {
		{ NULL,      0, NULL,             handle_main },
		{ "verbose", 0, (void*) &verbose, handle_bool },
		{ "v",       0, (void*) &verbose, handle_bool },
		{ "ascii",   0, (void*) &ascii,   handle_bool },
		{ "a",       0, (void*) &ascii,   handle_bool },
		{ "help",    0, NULL,             help        },
		{ "h",       0, NULL,             help        },
		{ "version", 0, NULL,             version     },
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
	if (ascii)
		puts("+-----------------------------------+");
	else
		puts("┌───────────────────────────────────┐");

	/* print data */
	usize i = 0;
	for (usize h = 0; h < height; ++h) {
		if (ascii)
			fprintf(stdout, "|");
		else
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

		if (ascii)
			puts("|");
		else
			puts("│");
	}

	/* print footer */
	if (ascii)
		puts("+-----------------------------------+");
	else
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

void
version(void *data, char **pars, const int pars_count)
{
	fprintf(stdout, "signify v%s\n", VERSION);
}

void
help(void *data, char **pars, const int pars_count)
{
	fprintf(stderr, "usage: signify [OPTIONS] [DATA]\n");
	fprintf(stderr, "Easily compare the data by printing an SSH randomart-like\n");
	fprintf(stderr, "ASCII art derived from provided data.\n");
	fprintf(stderr, "OPTIONS:\n");
	fprintf(stderr, "    -a, --ascii    Use ASCII characters instead of Unicode.\n");
	fprintf(stderr, "    -v, --verbose  Print verbose information.\n");
	fprintf(stderr, "    -h, --help     Print this help message and exit.\n");
	fprintf(stderr, "        --version  Print version and exit.\n\n");
	fprintf(stderr, "EXAMPLES:\n");
	fprintf(stderr, "    signify $(b2sum file)\n\n");
	fprintf(stderr, "Report bugs to https://github.com/kiedtl/signify.\n");
}

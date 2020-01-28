#include <stdlib.h>
#include <stdio.h>
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

	generate_matrix(data);
	fprintf(stdout, "%s\n", data);
	return 0;
}

char*
generate_matrix(char *data)
{
	return data;
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

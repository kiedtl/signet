#include "matrix.h"
#include "types.h"

void
matrix_right_up(char *matrix, usize *i)
{
	/*
	 * check if on top row,
	 * excluding top-right corner
	 */
	if (*i < (width - 1))
		++(*i);
	/* check if top-right corner */
	else if (*i == (width - 1)) {
		/* do nothing */
	}
	/*
	 * check if right border or bottom-right corner
	 */
	else if (*i % width == (width - 1)
			&& *i < (size - 1))
		*i -= width;
	else
		*i -= width - 1;
}

void
matrix_left_up(char *matrix, usize *i)
{
	/*
	 * check if on top row,
	 * excluding top-left corner,
	 * and move left instead.
	 */
	if (*i < width && *i != 0)
		--(*i);
	/*
	 * check if on top-left corner
	 */
	else if (*i == 0) {
		/* do nothing */
	}
	/*
	 * check if on left edge,
	 * and move up instead
	 */
	else if (*i % width == 0)
		*i -= width;
	else
		*i -= width + 1;
}

void
matrix_right_down(char *matrix, usize *i)
{
	/* check if on bottom-right corner */
	if (*i == width - 1) {
		/* do nothing */
	}
	/*
	 * check if on bottom edge,
	 * excluding bottom-right corner,
	 * and move right
	 */
	else if (*i != (size - 1) && *i > (size - width))
		++(*i);
	/* check if on right edge and move down */
	else if (*i != (size - 1) && *i % width == (width - 1))
		*i += width;
	else
		*i += width + 1;
}

void
matrix_left_down(char *matrix, usize *i)
{
	/* check if on bottom-left corner */
	if (*i == (size - (width - 1))) {
		/* do nothing */
	}
	/*
	 * check if on bottom edge,
	 * excluding bottom-left corner,
	 * and move left
	 */
	else if (*i > (size - (width - 1)))
		--(*i);
	/* check if on left edge and move down */
	else if (*i % width == 0)
		*i += width;
	else
		*i += width - 1;
}

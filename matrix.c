static void
right_up(int *matrix, size_t *i)
{
	/*
	 * check if on top row,
	 * excluding top-right corner
	 */
	if (*i < (WIDTH - 1))
		++(*i);
	/* check if top-right corner */
	else if (*i == (WIDTH - 1))
		; /* do nothing */
	/*
	 * check if right border or bottom-right corner
	 */
	else if (*i % WIDTH == (WIDTH - 1)
			&& *i < (SIZE - 1))
		*i -= WIDTH;
	else
		*i -= WIDTH - 1;
}

static void
left_up(int *matrix, size_t *i)
{
	/*
	 * check if on top row,
	 * excluding top-left corner,
	 * and move left instead.
	 */
	if (*i < WIDTH && *i != 0)
		--(*i);
	/*
	 * check if on top-left corner
	 */
	else if (*i == 0)
		; /* do nothing */
	/*
	 * check if on left edge,
	 * and move up instead
	 */
	else if (*i % WIDTH == 0)
		*i -= WIDTH;
	else
		*i -= WIDTH + 1;
}

static void
right_down(int *matrix, size_t *i)
{
	/* check if on bottom-right corner */
	if (*i == WIDTH - 1)
		; /* do nothing */
	/*
	 * check if on bottom edge,
	 * excluding bottom-right corner,
	 * and move right
	 */
	else if (*i != (SIZE - 1) && *i > (SIZE - WIDTH))
		++(*i);
	/* check if on right edge and move down */
	else if (*i != (SIZE - 1) && *i % WIDTH == (WIDTH - 1))
		*i += WIDTH;
	else
		*i += WIDTH + 1;
}

static void
left_down(int *matrix, size_t *i)
{
	/* check if on bottom-left corner */
	if (*i == (SIZE - (WIDTH - 1)))
		; /* do nothing */
	/*
	 * check if on bottom edge,
	 * excluding bottom-left corner,
	 * and move left
	 */
	else if (*i > (SIZE - (WIDTH - 1)))
		--(*i);
	/* check if on left edge and move down */
	else if (*i % WIDTH == 0)
		*i += WIDTH;
	else
		*i += WIDTH - 1;
}

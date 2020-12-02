static void
right_up(size_t *i)
{
	if (*i < (WIDTH - 1)) {
		/* top row (excluding top-right corner */
		++(*i);
	} else if (*i == (WIDTH - 1)) {
		/* top-right corner */
	} else if (*i % WIDTH == (WIDTH - 1) && *i < (SIZE - 1)) {
		/* right side or bottom-right corner */
		*i -= WIDTH;
	} else {
		*i -= WIDTH - 1;
	}
}

static void
left_up(size_t *i)
{
	if (*i < WIDTH && *i != 0) {
		/* top row, excluding top-left corner */
		--(*i);
	} else if (*i == 0) {
		/* top-left corner */
	} else if (*i % WIDTH == 0) {
		/* left side */
		*i -= WIDTH;
	} else {
		*i -= WIDTH + 1;
	}
}

static void
right_down(size_t *i)
{
	if (*i == WIDTH - 1) {
		/* bottom-right corner */
	} else if (*i != (SIZE - 1) && *i > (SIZE - WIDTH)) {
		/* bottom edge, excluding bottom-right corner */
		++(*i);
	} else if (*i != (SIZE - 1) && *i % WIDTH == (WIDTH - 1)) {
		/* check if on right edge */
		*i += WIDTH;
	} else {
		*i += WIDTH + 1;
	}
}

static void
left_down(size_t *i)
{
	if (*i == (SIZE - (WIDTH - 1))) {
		/* bottom-left corner */
	} else if (*i > (SIZE - (WIDTH - 1))) {
		/* bottom side, excluding bottom-left corner */
		--(*i);
	} else if (*i % WIDTH == 0) {
		/* left side */
		*i += WIDTH;
	} else {
		*i += WIDTH - 1;
	}
}

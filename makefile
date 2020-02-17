#
# signet: easy verification
# (c) Kied Llaentenn
# See the LICENSE for more information
#

NAME	= signet
WARNING	= -Wall -Wextra -pedantic -Wmissing-prototypes \
	  -Wold-style-definition -Wno-unused-parameter

INC	= -I. -Isub/ccommon/

CC	= gcc
CFLAGS	= -std=c99 $(WARNING) $(INC) -fno-stack-protector
LDFLAGS	= -fuse-ld=gold

SRC	= argoat.c matrix.c signet.c
OBJ	= $(SRC:.c=.o)

DESTDIR = /
PREFIX	= /usr/local/

all: debug

clean:
	rm -f $(NAME) $(OBJ)

.c.o:
	$(CC) $(CFLAGS) $(CFLAGS_OPT) -c $<

debug: CFLAGS_OPT := -ggdb
debug: $(NAME)

release: CFLAGS_OPT := -O4 -s
release: $(NAME)

$(NAME): $(OBJ)
	$(CC) -o $@ $^ $(CFLAGS) $(CFLAGS_OPT) $(LDFLAGS)

install: $(NAME)
	install -m755 ./$(NAME) $(DESTDIR)/$(PREFIX)/bin/$(NAME)

uninstall:
	rm -f $(DESTDIR)/$(PREFIX)/bin/$(NAME)

.PHONY: all debug release clean install uninstall

#
# signet: easily compare TLS certificates, hashes, etc
# https://github.com/lptstr/signet
#
# (c) Kiëd Llaentenn and contributors
# See the LICENSE.md file for more information
#

include config.mk

BIN     = signet

SRC     = signet.c
OBJ     = $(SRC:.c=.o)

WARNING = -Wall -Wpedantic -Wextra -Wold-style-definition \
	  -Wmissing-prototypes -Winit-self -Wfloat-equal -Wstrict-prototypes \
	  -Wredundant-decls -Wendif-labels -Wstrict-aliasing=2 -Woverflow \
	  -Wformat=2 -Wmissing-include-dirs -Wno-trigraphs \
	  -Wno-format-nonliteral -Wno-incompatible-pointer-types \
	  -Wno-unused-parameter
INC     = -I.
DEF     =
CFLAGS  = -std=c99 $(WARNING) $(INC)
LDFLAGS = -fuse-ld=$(LD)

all: man/$(BIN).1 debug

.c.o:
	@printf "    %-8s%s\n" "CC" $@
	$(CMD)$(CC) $(CFLAGS) $(CFLAGS_OPT) -c $< -o $(<:.c=.o)

debug: CFLAGS_OPT  := $(DEBUG_CFLAGS)
debug: LDFLAGS_OPT := $(DEBUG_LDFLAGS)
debug: $(BIN)

release: CFLAGS_OPT  := $(RELEASE_CFLAGS)
release: LDFLAGS_OPT := $(RELEASE_LDFLAGS)
release: $(BIN)

$(BIN): $(OBJ) $(LIBUTF) $(SQLITE)
	@printf "    %-8s%s\n" "CCLD" $@
	$(CMD)$(CC) -o $@ $^ $(CFLAGS) $(CFLAGS_OPT) $(LDFLAGS) $(LDFLAGS_OPT)

man/$(BIN).1: man/$(BIN).scd
	@printf "    %-8s%s\n" "SCDOC" $@
	$(CMD)scdoc < $^ > $@

clean:
	$(CMD)rm -f $(BIN) $(OBJ) man/$(BIN).1
	$(CMD)rm -rf dist/ *.xz

dist: clean
	$(CMD)mkdir -p dist
	$(CMD)cp -r config.mk Makefile *.md lib man src sub \
		dist
	$(CMD)tar -cvf - dist | xz -qcT 0 > lcharmap-v$(VERSION).tar.xz
	$(CMD)rm -rf dist

install: $(BIN) man/$(BIN).1 lib/chars.db
	$(CMD)install -Dm755 $(BIN) $(DESTDIR)/$(PREFIX)/bin/$(BIN)
	$(CMD)install -Dm644 man/$(BIN).1 $(DESTDIR)/$(PREFIX)/share/man/man1/$(BIN).1

uninstall:
	$(CMD)rm -f $(DESTDIR)/$(PREFIX)/bin/$(BIN)
	$(CMD)rm -f $(DESTDIR)/$(PREFIX)/share/man/man1/$(BIN).1

.PHONY: all debug release clean dist install uninstall

#
# signet: easily compare TLS certificates, hashes, etc
# https://github.com/lptstr/signet
#
# (c) Kiëd Llaentenn and contributors
# See the LICENSE.md file for more information
#

include config.mk

VERSION = 0.2.0
BIN     = signet
PKGNAME  = $(NAME)-$(shell uname -s)-$(shell uname -m)-$(VERSION)

SRC     = signet.c
OBJ     = $(SRC:.c=.o)

WARNING  = -Wall -Wpedantic -Wextra -Wold-style-definition -Wmissing-prototypes \
           -Winit-self -Wfloat-equal -Wstrict-prototypes -Wredundant-decls \
           -Wendif-labels -Wstrict-aliasing=2 -Woverflow -Wformat=2 -Wtrigraphs \
           -Wmissing-include-dirs -Wno-format-nonliteral -Wunused-parameter \
           -Wincompatible-pointer-types \
           -Werror=implicit-function-declaration -Werror=return-type
DEF      = -DVERSION=\"$(VERSION)\"
INC     = -I.
DEF     =
CFLAGS  = -std=c99 $(DEF) $(WARNING) $(INC) -funsigned-char
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

dist: release $(BIN).1
	$(CMD)mkdir $(PKGNAME)
	$(CMD)cp $(BIN)   $(PKGNAME)
	$(CMD)cp $(BIN).1 $(PKGNAME)
	$(CMD)tar -cf - $(PKGNAME) | xz -qcT0 > $(PKGNAME).tar.xz
	$(CMD)rm -rf $(PKGNAME)

install: $(BIN) man/$(BIN).1 lib/chars.db
	$(CMD)install -Dm755 $(BIN) $(DESTDIR)/$(PREFIX)/bin/$(BIN)
	$(CMD)install -Dm644 man/$(BIN).1 $(DESTDIR)/$(PREFIX)/share/man/man1/$(BIN).1

uninstall:
	$(CMD)rm -f $(DESTDIR)/$(PREFIX)/bin/$(BIN)
	$(CMD)rm -f $(DESTDIR)/$(PREFIX)/share/man/man1/$(BIN).1

.PHONY: all debug release clean dist install uninstall

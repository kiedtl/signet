#
# signet: easily compare certificates, hashes, etc
# https://github.com/lptstr/signet
#
# (c) Kiëd Llaentenn and contributors
# See the LICENSE.md file for more information
#

CMD = @

DESTDIR =
PREFIX  = /usr/local

CC = cc
LD = bfd

RELEASE_CFLAGS  = -Os -mtune=native -march=native 
RELEASE_LDFLAGS = -flto -s
DEBUG_CFLAGS    = -Og -ggdb
DEBUG_LDFLAGS   =

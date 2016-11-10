SUBDIRS = lib dynamic_lib src oob
#SUBDIRS = 
AM_MAKEFLAGS = --no-print-directory
AM_YFLAGS = -Wno-yacc -Wno-other

AM_TESTS_ENVIRONMENT = top_srcdir="$(top_srcdir)"
export top_srcdir

test_ldflags = -no-install
${check_PROGRAMS}: LDFLAGS+="${test_ldflags}"

ACLOCAL_AMFLAGS = -I m4 --install -lpthread

check_PROGRAMS=
TESTS	= $(check_PROGRAMS)

AUTOMAKE_OPTIONS	= subdir-objects
EXTRA_DIST = src/* tests/* dynamic_lib/* lib/* include/* m4/* build.sh Makefile config.status

include tests/Makefile.am
include oob/Makefile.am

#                                               -*- Autoconf -*-
# Process this file with autoconf to produce a configure script.

AC_PREREQ([2.69])
AC_INIT([iproxy], [1.0.0])
#AM_INIT_AUTOMAKE([foreign subdir-objects])
AM_INIT_AUTOMAKE([foreign])
LT_INIT()

# Checks for programs.
AC_PROG_CC

# Checks for libraries.
#AC_PROG_RANLIB
AC_PROG_LIBTOOL

# Checks for header files.
#AC_CHECK_HEADERS([stdlib.h])
AC_CONFIG_HEADERS([config.h])

# Checks for typedefs, structures, and compiler characteristics.

# Checks for library functions.
AC_C_CONST
AC_OUTPUT(Makefile 
		src/Makefile
		lib/Makefile
		dynamic_lib/Makefile
		)

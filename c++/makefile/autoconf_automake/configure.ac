AC_INIT([myprogram], [1.0], [bugs@myprogram.com])

AC_PROG_CC
AC_PROG_CXX
AC_PROG_INSTALL
AC_CHECK_LIB([m], [sin])

CFLAGS="-Wall -O2"
AC_SUBST([CFLAGS])
LIBS="-lm"
AC_SUBST([LIBS])

PKG_CHECK_MODULES([GTK], [gtk+-3.0 >= 3.0.0])

AC_OUTPUT([Makefile])


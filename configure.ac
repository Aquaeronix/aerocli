#This line defines the name of the output tarball
AC_INIT([aerocli],[2.1],[barracks510@gmail.com])
AC_CONFIG_SRCDIR([src/aerocli.c])
#this line defines what compilation flags will be used
m4_pattern_allow([AM_PROG_AR])
AM_PROG_AR
LT_INIT
AM_INIT_AUTOMAKE
# DEFINE YOUR OWN HEADERS CHECK - DO NOT DELETE THIS LINE
#this line defines what libraries should be used during building
AC_CHECK_LIB([pthread],[pthread_create])
AC_CHECK_LIB([pthread],[pthread_join])
# DEFINE YOUR OWN LIBRARY CHECK - DO NOT DELETE THIS LINE
AC_PROG_CC
AC_CONFIG_HEADERS([config.h])
#This line defines where Makefiles are stored for projects and sources
AC_CONFIG_FILES([
  Makefile
  src/Makefile
  include/Makefile
])
AC_OUTPUT

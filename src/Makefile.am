AM_CFLAGS = -Wall -Werror -ansi -std=gnu99 -pedantic -DAQ5_DETECT_FW

lib_LTLIBRARIES = libaquaero5.la
libaquaero5_la_SOURCES = libaquaero5.c
libaquaero5_la_CPPFLAGS = -I$(top_srcdir)/include
libaquaero5_la_LDFLAGS = -version-info 1:0

bin_PROGRAMS = aerocli
aerocli_SOURCES = aerocli.c
aerocli_LDFLAGS = $(top_builddir)/src/libaquaero5.la
aerocli_CPPFLAGS = -I$(top_srcdir)/include


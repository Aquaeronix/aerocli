# Copyright 2012 lynix <lynix47@gmail.com>
# Copyright 2013 JinTu <JinTu@praecogito.com>, lynix <lynix47@gmail.com>
#
# This file is part of aerotools-ng.
#
# aerotools-ng is free software: you can redistribute it and/or modify
# it under the terms of the GNU General Public License as published by
# the Free Software Foundation, either version 3 of the License, or
# (at your option) any later version.
#
# aerotools-ng is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
# GNU General Public License for more details.
#
# You should have received a copy of the GNU General Public License
# along with aerotools-ng. If not, see <http://www.gnu.org/licenses/>.

CC = gcc
CFLAGS = -Wall -ansi -std=gnu99 -pedantic -I /usr/include -O2

# location of external library: jsonrpc-c
ifndef JRPCC_PREFIX
	#JRPCC_PREFIX = /usr
	JRPCC_PREFIX = /usr/local
endif

# Uncomment the following line if using firmware 1027.
#CFLAGS += -D'AQ5_FW_TARGET=1027'

# Uncomment this if you want to debug
#CFLAGS += -D'DEBUG=TRUE'

ifdef DEBUG  
	CFLAGS += -g
endif

LIB_OBJS=obj/libaquaero5.o


.PHONY: all default clean

default : bin/aerocli

all : bin/aerocli bin/aq5rpcd lib/libaquaero5.a lib/libaquaero5.so

bin/aerocli: obj/aerocli.o obj/libaquaero5.o
	$(CC) $(CFLAGS) $(LDFLAGS) -o $@ $^
	
obj/aerocli.o: src/aerocli.c src/libaquaero5.h
	$(CC) $(CFLAGS) -o $@ -c $<
	
obj/libaquaero5.o: src/libaquaero5.c src/libaquaero5.h \
		src/aquaero5-user-strings.h src/aquaero5-offsets.h
	$(CC) $(CFLAGS) -fPIC -o $@ -c $<

bin/aq5rpcd: obj/aq5rpcd.o obj/libaquaero5.o
	$(CC) $(CFLAGS) -L $(JRPCC_PREFIX)/lib -ljsonrpcc -o $@ $^
  
obj/aq5rpcd.o: src/aq5rpcd.c $(JRPCC_PREFIX)/include/jsonrpc-c.h
	$(CC) $(CFLAGS) -I $(JRPCC_PREFIX)/include -I /usr/include/libev/ -o $@ -c $<


# Static library file
lib/libaquaero5.a: $(LIB_OBJS)
	ar cr $@ $^

# Dynamic library file
lib/libaquaero5.so: $(LIB_OBJS)
	$(CC) -shared -o $@ $^

clean :
	rm -f bin/aerocli bin/aq5rpcd obj/*.o lib/*.a lib/*.so

install :
	install -C -groot -oroot bin/aerocli /usr/local/sbin

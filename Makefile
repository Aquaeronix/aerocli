# Copyright 2012 lynix <lynix47@gmail.com>
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

# Uncomment the following line if using firmware 1027.
# CFLAGS += -D'AQ5_FW_TARGET=1027'

ifdef DEBUG  
	CFLAGS += -g
endif


LIB_OBJS=obj/libaquaero5.o

.PHONY: all default clean install 

$(shell mkdir -p bin/ obj/ lib/)
	
default : bin/aerocli

all : bin/aerocli lib/libaquaero5.a lib/libaquaero5.so

bin/aerocli: obj/aerocli.o obj/libaquaero5.o
	$(CC) $(CFLAGS) $(LDFLAGS) -o $@ $^

obj/aerocli.o: src/aerocli.c src/libaquaero5.h
	$(CC) $(CFLAGS) -o $@ -c $<

obj/libaquaero5.o: src/libaquaero5.c src/libaquaero5.h \
		src/aquaero5-user-strings.h src/aquaero5-offsets.h
	$(CC) $(CFLAGS) -fPIC -o $@ -c $<

# Static library file
lib/libaquaero5.a: $(LIB_OBJS)
	ar cr $@ $^

# Dynamic library file
lib/libaquaero5.so: $(LIB_OBJS)
	$(CC) -shared -o $@ $^

clean :
	rm -f bin/aerocli obj/*.o lib/*.a lib/*.so

install :
	$(shell mkdir -p $(INSTALL_PATH)/bin/ $(INSTALL_PATH)/obj/ $(INSTALL_PATH)/lib/)
	install -C bin/aerocli $(DESTDIR)/bin
	install -C obj/aerocli.o $(DESTDIR)/obj
	install -C obj/libaquaero5.o $(DESTDIR)/obj
	install -C lib/libaquaero5.so $(DESTDIR)/lib

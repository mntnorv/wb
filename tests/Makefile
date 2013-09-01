#
# Copyright 2013 Mantas Norvaiša
# 
# This file is part of wb.
# 
# wb is free software: you can redistribute it and/or modify
# it under the terms of the GNU General Public License as published by
# the Free Software Foundation, either version 3 of the License, or
# (at your option) any later version.
# 
# wb is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
# GNU General Public License for more details.
# 
# You should have received a copy of the GNU General Public License
# along with wb.  If not, see <http://www.gnu.org/licenses/>.
#

# Compiler flags
INCLUDES = -Iunity -I../src -I/usr/include/libxml2/ -I/usr/include/tidy/
DEFINES = -DVERSION=\"test\"

CFLAGS = -g -Wall $(INCLUDES) $(DEFINES)
LDFLAGS = $(LIBS)

# Filenames
SOURCES = $(sort $(wildcard *.c))
UNITY = unity/unity.c
UNITY_OBJ = unity.o
OBJECTS = $(SOURCES:.c=.o) $(UNITY_OBJ)
EXECUTABLES = $(SOURCES:.c=)
ADDITIONAL_FILES = Makefile README.md COPYING

all: $(UNITY) $(SOURCES) $(EXECUTABLES)

.c.o:
	$(CC) -c $(CFLAGS) $<

$(UNITY_OBJ):
	$(CC) -c $(CFLAGS) $(UNITY) -o $(UNITY_OBJ)

$(EXECUTABLES): $(OBJECTS)
	$(CC) $@.o $(UNITY_OBJ) $(LDFLAGS) -o $@

test: all
	@./run_tests.sh $(EXECUTABLES)

clean:
	rm -f $(EXECUTABLES) $(OBJECTS)

.PHONY: clean test

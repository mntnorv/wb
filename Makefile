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

# App info
APPNAME = wb
VERSION = 0.1

# Compiler flags
INCLUDES = -I/usr/include/libxml2/ -I/usr/include/tidy/
LIBS = -lcurl -ltidy -lxml2
DEFINES = -DVERSION=\"$(VERSION)\"

CFLAGS = -g -Wall -Werror -pedantic $(INCLUDES) $(DEFINES)
LDFLAGS = $(LIBS)

# Compiler
CC = clang

# Filenames
SOURCES = wb.c args.c base64.c net.c str_list.c url_enc.c xml.c xpath.c
OBJECTS = $(SOURCES:.c=.o)
EXECUTABLE = wb
ADDITIONAL_FILES = Makefile README.md COPYING

all: $(SOURCES) $(EXECUTABLE)
	
$(EXECUTABLE): $(OBJECTS)
	$(CC) $(OBJECTS) $(LDFLAGS) -o $@

.c.o:
	$(CC) -c $(CFLAGS) $<

clean:
	rm -f $(EXECUTABLE) $(OBJECTS)

dist: clean
	mkdir -p $(APPNAME)-$(VERSION)
	cp -R $(ADDITIONAL_FILES) $(SOURCES) $(APPNAME)-$(VERSION)
	tar -cf $(APPNAME)-$(VERSION).tar $(APPNAME)-$(VERSION)
	gzip $(APPNAME)-$(VERSION).tar
	rm -rf $(APPNAME)-$(VERSION)

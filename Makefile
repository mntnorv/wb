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
export APPNAME = wb
export VERSION = 0.2.1
export DATE = 2013-12-04

# Filenames
export EXECUTABLE = wb
export MANPAGE = wb.1

# Libs
export LIBS = -lcurl -ltidy -lxml2

# Compiler
export CC ?= clang

# Directories
export LOCAL_BIN_DIR = $(CURDIR)/bin

PREFIX ?= /usr
BINDIR = $(PREFIX)/bin
MANDIR = $(PREFIX)/share/man/man1

# Dist files
DIST_PATTERNS = *.[ch] *.sh Makefile
DIST_DIRS = src tests tests/unity
DIST_FILES = Makefile COPYING README.md wb.1 $(foreach dir, $(DIST_DIRS), $(foreach pattern, $(DIST_PATTERNS), $(wildcard $(dir)/$(pattern))))
TARNAME = $(APPNAME)-$(VERSION)
TARFILE = $(TARNAME).tar.gz

all:
	mkdir -p "$(LOCAL_BIN_DIR)"
	@$(MAKE) -C src

install:
	install -Dm755 "$(LOCAL_BIN_DIR)/$(EXECUTABLE)" "$(DESTDIR)$(BINDIR)/$(EXECUTABLE)"
	install -Dm644 "$(MANPAGE)" "$(DESTDIR)$(MANDIR)/$(MANPAGE)"
	@sed -i -e 's/@VERSION@/'$(VERSION)'/' "$(DESTDIR)$(MANDIR)/$(MANPAGE)"
	@sed -i -e 's/@DATE@/'$(DATE)'/' "$(DESTDIR)$(MANDIR)/$(MANPAGE)"
	gzip -9 -f "$(DESTDIR)$(MANDIR)/$(MANPAGE)"

dist: $(TARFILE)

test:
	@$(MAKE) -C tests test

clean:
	rm -rf "$(LOCAL_BIN_DIR)" "$(TARFILE)"
	@$(MAKE) -C src clean
	@$(MAKE) -C tests clean

$(TARFILE): $(DIST_FILES)
	rm -rf $(TARFILE) $(TARNAME)
	mkdir $(TARNAME)
	rsync -R $(DIST_FILES) $(TARNAME)
	tar -czf $(TARFILE) $(TARNAME)
	rm -rf $(TARNAME)

.PHONY: install clean test dist

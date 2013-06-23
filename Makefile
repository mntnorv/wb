# wb.c Makefile
# Version
APPNAME = wb.c
VERSION = 0.1

# Compiler options
CC=gcc
CFLAGS=-Wall -Werror -pedantic -g
LDFLAGS=-lcurl -ltidy -lxml2

# Filenames
SOURCES=wb.c
OBJECTS=$(SOURCES:.c=.o)
EXECUTABLE=wb

all: $(SOURCES) $(EXECUTABLE)
	
$(EXECUTABLE): $(OBJECTS)
	$(CC) $(OBJECTS) $(LDFLAGS) -o $@

.c.o:
	$(CC) -c $(CFLAGS) $<

clean:
	rm -f $(EXECUTABLE) $(OBJECTS)

dist: clean
	mkdir -p $(APPNAME)-$(VERSION)
	cp -R Makefile README.md $(SOURCES) $(APPNAME)-$(VERSION)
	tar -cf $(APPNAME)-$(VERSION).tar $(APPNAME)-$(VERSION)
	gzip $(APPNAME)-$(VERSION).tar
	rm -rf $(APPNAME)-$(VERSION)

check:
	
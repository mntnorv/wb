# wb.c Makefile
# App info
APPNAME = wb.c
VERSION = 0.1

# Compiler flags
INCLUDES = -I/usr/include/libxml2/ -I/usr/include/tidy/
LIBS = -lcurl -ltidy -lxml2
DEFINES = -DVERSION=\"$(VERSION)\"

CFLAGS = -g -Wall -Werror -pedantic $(INCLUDES) $(DEFINES)
LDFLAGS = $(LIBS)

# Compiler
CC = gcc

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
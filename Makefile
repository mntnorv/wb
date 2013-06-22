CC=gcc
CFLAGS=-c -Wall -Werror -pedantic -g
LDFLAGS=-lcurl -ltidy -lxml2
SOURCES=wb.c
OBJECTS=$(SOURCES:.c=.o)
EXECUTABLE=wb

all: $(SOURCES) $(EXECUTABLE)
	
$(EXECUTABLE): $(OBJECTS) 
	$(CC) $(OBJECTS) $(LDFLAGS) -o $@

.c.o:
	$(CC) $(CFLAGS) $< -o $@
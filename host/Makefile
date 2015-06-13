CC = gcc
CFLAGS = -I.
TARGET = remote
DEPS = remote.h
SOURCES = main.c remote.c
OBJECTS = $(SOURCES:.c=.o)

LDFLAGS = -lhidapi

all: $(TARGET)

$(TARGET): $(OBJECTS)
	$(CC) $(CFLAGS) $(LDFLAGS) -o $(TARGET) $(OBJECTS)

clean:
	rm -rf $(OBJECTS)
	rm -rf $(TARGET)

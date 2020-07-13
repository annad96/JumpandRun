TARGET = jumpandrun
LIBS = -lncurses
CC = g++
CFLAGS = -g -Wall -std=c++11

.PHONY: default all clean run $(TARGET)

default: $(TARGET)
all: default

SOURCES = $(wildcard *.cpp) $(wildcard */*.cpp)
HEADERS = $(wildcard *.h) $(wildcard */*.h)

$(TARGET):
	$(CC) $(SOURCES) $(CFLAGS) $(LIBS) -o $@

run:
	./$(TARGET)

clean:
	-rm -f $(TARGET)


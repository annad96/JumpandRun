TARGET = dino
LIBS = -lncurses
CC = g++
CFLAGS = -g -Wall -std=c++11
.PHONY: default all clean run $(TARGET)
default: $(TARGET)
all: default
SOURCES = JumpAndRun/BoxObstacle.cpp JumpAndRun/Dino.cpp JumpAndRun/Floor.cpp JumpAndRun/Game.cpp \
      JumpAndRun/Rectangle.cpp JumpAndRun/Terminal.cpp JumpAndRun/main.cpp
$(TARGET):
    $(CC) $(SOURCES) $(CFLAGS) $(LIBS) -o $@
run:
    ./$(TARGET)
    
clean:
    -rm -f $(TARGET)
	

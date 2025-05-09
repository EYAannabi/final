CXX = g++
CXXFLAGS = -Wall -std=c++17 -Iinclude
LDFLAGS = `sdl2-config --libs` -lSDL2_image

SRC = $(wildcard src/*.cpp)
OBJ = $(SRC:.cpp=.o)
MAIN = main.cpp
TARGET = village

all: $(TARGET)

$(TARGET): $(OBJ) $(MAIN)
	$(CXX) $(CXXFLAGS) $^ -o $@ $(LDFLAGS)

clean:
	rm -f $(OBJ) $(TARGET)


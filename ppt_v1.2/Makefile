CXX := g++
CXXFLAGS := -std=c++20 -I./src -I./src/app -I./src/objects

# Executable name
TARGET := ppt

# Collect all .cpp files under src/
SRC := $(shell find src -name '*.cpp')
OBJ := $(SRC:.cpp=.o)

# Main file
MAIN := main.cpp

# Default build
all: $(TARGET)

$(TARGET): $(MAIN) $(OBJ)
	$(CXX) $(CXXFLAGS) $^ -o $@

# Compile all .cpp → .o
%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Cleanup
clean:
	rm -f $(OBJ) $(TARGET)

.PHONY: all clean

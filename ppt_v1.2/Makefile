CXX := g++

# Common flags
CXXFLAGS := -std=c++20 -I./src -I./src/app -I./src/objects
LDFLAGS :=

# Debug flags
DEBUG_FLAGS := -g -O0 -fsanitize=address,undefined -fno-omit-frame-pointer
DEBUG_LDFLAGS := -fsanitize=address,undefined

# Executable name
TARGET := ppt

# Collect all .cpp files under src/
SRC := $(shell find src -name '*.cpp')
OBJ := $(SRC:.cpp=.o)

# Main file
MAIN := main.cpp

# Default build (release)
all: $(TARGET)

$(TARGET): $(MAIN) $(OBJ)
	$(CXX) $(CXXFLAGS) $(LDFLAGS) $^ -o $@

# Compile all .cpp → .o
%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Debug build
debug: CXXFLAGS += $(DEBUG_FLAGS)
debug: LDFLAGS += $(DEBUG_LDFLAGS)
debug: clean $(TARGET)

# Cleanup
clean:
	rm -f $(OBJ) $(TARGET)

.PHONY: all clean debug

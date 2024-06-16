# gilada8892@gmail.com
# Compiler to use
CXX = g++

# Compiler flags
CXXFLAGS = -Wall -g

# Main target executable
TARGET = Catan

# Test target executable
TEST_TARGET = test_catan

# Source files
SRCS = main.cpp Catan.cpp Player.cpp Board.cpp Resource.cpp Building.cpp Land.cpp test.cpp  Vertex.cpp Road.cpp Card.cpp

# Object files (derived from source files)
OBJS = $(SRCS:.cpp=.o)

# Default target
all: $(TARGET) $(TEST_TARGET)

# Rule to link object files and create the main executable
$(TARGET): $(filter-out test.o, $(OBJS))
	$(CXX) $(CXXFLAGS) -o $(TARGET) $(filter-out test.o, $(OBJS))

# Rule to link object files and create the test executable
$(TEST_TARGET): $(filter-out main.o, $(OBJS))
	$(CXX) $(CXXFLAGS) -o $(TEST_TARGET) $(filter-out main.o, $(OBJS))

# Rule to compile source files into object files
%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Clean target to remove generated files
clean:
	rm -f $(OBJS) $(TARGET) $(TEST_TARGET)

# Phony targets (targets that are not actual files)
.PHONY: all clean

# Custom target to build both executables and run catan
catan: $(TARGET) $(TEST_TARGET)
	./$(TARGET)

# Define the C++ version
CXX_STANDARD = c++23

# Define the compiler to be used
CXX = g++

# Define the compiler options (-O3 Compiler Optimization)
CXXFLAGS = -std=$(CXX_STANDARD) -Wall -Wextra -Wpedantic -MP -MMD -O3 -g


# Libraries to link (-lGL for DearImgUI)
LIBS = -lsfml-graphics -lsfml-window -lsfml-system -lGL

# Name of the executable
EXECUTABLE = raycasting

# Define the source files
#SOURCES = ./src/main.cpp ./src/map.cpp
SOURCES = ./src/*.cpp

# Define the "all" rule that depends on the $(EXECUTABLE) file
all: create_new $(EXECUTABLE)

# Define the rule to clean the generated files
clean:
	@echo "-----------------------------------"
	@echo "Cleaning build..."
	rm -rf build
	@echo "Done."

# Define the rule to create the "build" directory and generate the build files for the project using the "cmake" command
create_new: clean
	@echo "-----------------------------------"
	@echo "Creating directory and building..."
	mkdir -p build
#	cd build && cmake ..
	cd build
	@echo "Done."

# Define the rule to compile the source files into the $(EXECUTABLE) file
$(EXECUTABLE): $(SOURCES)
	@echo "-----------------------------------"
	@echo "Rule to compile the source files..."
	$(CXX) $(CXXFLAGS) $(SOURCES) $(LIBS) -o build/$(EXECUTABLE)
	@echo "-----------------------------------"
	@echo "Running the executable..."
	./build/$(EXECUTABLE)
	@echo "Done."

# For debug
# gdb ./build/$(EXECUTABLE)

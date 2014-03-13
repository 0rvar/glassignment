SOURCES = guicontrol.cpp guicallback.cpp camera.cpp geometry.cpp model.cpp timer.cpp shadertools.cpp

CXX=g++
RM=rm -f
DFLAGS  = -O0 -g3 -ggdb3 -fno-inline
#DFLAGS = -O2
WFLAGS   = -Wall -ansi -g -std=c++11 -Isrc/
GLFLAGS  = `pkg-config --cflags gtk+-2.0`
LGLFLAGS = `pkg-config --libs gtk+-2.0` -lGL -lGLEW -lGLU -lglut -g
CXXFLAGS = $(WFLAGS) $(DFLAGS) $(GLFLAGS)
LDFLAGS  =  -export-dynamic -lXext -lX11 $(LGLFLAGS)

# Build object list from source list (build/&.o)
OBJECTS = $(patsubst %.cpp,build/%.o,$(SOURCES))
# Build test object list from ALL cpp files in tests/ (build/tests/%.o)
TESTS = $(patsubst tests/%.cpp,build/tests/%.o,$(shell echo tests/*.cpp))

all: main
.PHONY: test clean

# Link main with objects
main: $(OBJECTS) build/main.o
	$(CXX) $(OBJECTS) build/main.o -o $@ $(LDFLAGS)

# Build objects
build/%.o: src/%.cpp src/%.hpp
	$(CXX) $(CXXFLAGS) -c $< -o $@ 


# Remove everything in build/ and build/tests
clean:
	$(RM) build/*.o build/tests/*


# Run the test runner
test: build/tests/runner
	build/tests/runner

# Link the test runner from all build/tests objects
build/tests/runner: $(TESTS) $(OBJECTS)
	$(CXX) $(OBJECTS) $(TESTS) -o $@ $(LDFLAGS)

# Build test objects
build/tests/%.o: tests/%.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@
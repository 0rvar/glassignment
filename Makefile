CXX=g++
RM=rm -f
CPPFLAGS = -g -Isrc/ -ansi -std=c++11 -Wall
LDFLAGS = -g
LDLIBS = -lGL -lGLU -lglut -lGLEW
SOURCES = transform.cpp matrix.cpp vertex.cpp off.cpp timer.cpp shadertools.cpp

# Build object list from source list (build/&.o)
OBJECTS = $(patsubst %.cpp,build/%.o,$(SOURCES))
# Build test object list from ALL cpp files in tests/ (build/tests/%.o)
TESTS = $(patsubst tests/%.cpp,build/tests/%.o,$(shell echo tests/*.cpp))

all: main
.PHONY: test clean

# Link main with objects
main: $(OBJECTS) build/main.o
	$(CXX) $(OBJECTS) build/main.o -o $@ $(LDFLAGS) $(LDLIBS)

# Build objects
build/%.o: src/%.cpp
	$(CXX) $(CPPFLAGS) -c $< -o $@ 


# Remove everything in build/ and build/tests
clean:
	$(RM) build/*.o build/tests/*


# Run the test runner
test: build/tests/runner
	build/tests/runner

# Link the test runner from all build/tests objects
build/tests/runner: $(TESTS)
	$(CXX) $(OBJECTS) $(TESTS) -o $@ $(LDFLAGS) $(LDLIBS)

# Build test objects
build/tests/%.o: tests/%.cpp $(OBJECTS)
	$(CXX) $(CPPFLAGS) -c $< -o $@
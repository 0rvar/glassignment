CC=gcc
CXX=g++
RM=rm -f
CPPFLAGS = -g -Isrc/
LDFLAGS = -g
LDLIBS = -lGL -lGLU -lglut
SOURCES = Transform.cpp Vertex.cpp off.cpp

OBJECTS = $(patsubst %.cpp,build/%.o,$(SOURCES))
TESTS = $(patsubst tests/%.cpp,build/tests/%.o,$(shell echo tests/*.cpp))

all: main
.PHONY: test clean


main: $(OBJECTS)
	$(CXX) $(OBJECTS) src/main.cpp -o $@ $(LDFLAGS) $(LDLIBS)

build/%.o: src/%.cpp
	$(CXX) $(CPPFLAGS) -c $< -o $@ 


clean:
	$(RM) build/*.o build/tests/*


test: build/tests/runner
	build/tests/runner

build/tests/runner: $(TESTS)
	$(CXX) $(OBJECTS) $(TESTS) -o $@ $(LDFLAGS) $(LDLIBS)

build/tests/%.o: tests/%.cpp $(OBJECTS)
	$(CXX) $(CPPFLAGS) -c $< -o $@
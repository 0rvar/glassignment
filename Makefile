CC=gcc
CXX=g++
RM=rm -f
CPPFLAGS = -g -Isrc/
LDFLAGS = -g
LDLIBS = -lGL -lGLU -lglut
SOURCES = Transform.cpp Vertex.cpp off.cpp

OBJECTS = $(patsubst %.cpp,build/%.o,$(SOURCES))
TESTS = $(patsubst tests/%.cpp,build/tests/%,$(shell echo tests/*.cpp))

all: main

main: $(OBJECTS)
	$(CXX) $(OBJECTS) src/main.cpp -o $@ $(LDFLAGS) $(LDLIBS)

build/%.o: src/%.cpp
	$(CXX) $(CPPFLAGS) -c $< -o $@ 

.PHONY: test
test: $(TESTS)
	$(foreach test,$(TESTS),$(test))

build/tests/%: tests/%.cpp $(OBJECTS)
	$(CXX) $(OBJECTS) $(CPPFLAGS) $< -o $@ $(LDFLAGS) $(LDLIBS)

clean:
	$(RM) build/*.o build/tests/*
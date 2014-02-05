/* 
 * File:   offtest.cpp
 * Author: orvar
 *
 * Created on 31-Jan-2014, 17:11:38
 */

#include <stdlib.h>
#include <iostream>
#include "off.hpp"

/*
 * Simple C++ Test Suite
 */

void testParseOFFface() {
    std::string line ("5 1 2 3 4 5");
    std::vector<int> r = parseOFFface(line);
    if (r.size() != 5 || r[0] != 1 || r[1] != 2 || r[2] != 3 || r[3] != 4 || r[4] != 5) {
        std::cout << "%TEST_FAILED% time=0 testname=testParseOFFface (offtest) message=error message sample" << std::endl;
    }
}

void testParseOFFheader() {
    std::string line ("8 6 24");
    OFFHeader h = parseOFFheader(line);
    if (h.numVertices != 8 || h.numFaces != 6 || h.numEdges != 24) {
        std::cout << "%TEST_FAILED% time=0 testname=testParseOFFheader (offtest) message=error message sample" << std::endl;
    }
}

void testParseOFFvertex() {
    std::string line ("0 1 2");
    Vertex* result = parseOFFvertex(line);
    if (result->x != 0.0 || result->y != 1.0 || result->z != 2.0) {
        std::cout << "%TEST_FAILED% time=0 testname=testParseOFFvertex (offtest) message=error message sample" << std::endl;
    }
}

void testParseOFF() {
    std::string content ("OFF\n8 6 24\n0 0 0\n0 0 1\n0 1 0\n0 1 1\n1 0 0\n1 0 1\n1 1 0\n1 1 1\n4 0 1 3 2\n4 2 3 7 6\n4 4 6 7 5\n4 0 4 5 1\n4 1 5 7 3\n4 0 2 6 4");
    std::vector<Vertex*> result = parseOFF(content);
    if (result.size() != 12*3) {
        std::cout << "%TEST_FAILED% time=0 testname=testParseOFF (offtest) message=size was not 12*3: " << result.size() << std::endl;
    }
}

int main(int argc, char** argv) {
    std::cout << "%SUITE_STARTING% offtest" << std::endl;
    std::cout << "%SUITE_STARTED%" << std::endl;

    std::cout << "%TEST_STARTED% testParseOFFface (offtest)" << std::endl;
    testParseOFFface();
    std::cout << "%TEST_FINISHED% time=0 testParseOFFface (offtest)" << std::endl;

    std::cout << "%TEST_STARTED% testParseOFFheader (offtest)" << std::endl;
    testParseOFFheader();
    std::cout << "%TEST_FINISHED% time=0 testParseOFFheader (offtest)" << std::endl;

    std::cout << "%TEST_STARTED% testParseOFFvertex (offtest)" << std::endl;
    testParseOFFvertex();
    std::cout << "%TEST_FINISHED% time=0 testParseOFFvertex (offtest)" << std::endl;
    
    std::cout << "%TEST_STARTED% testParseOFF (offtest)" << std::endl;
    testParseOFF();
    std::cout << "%TEST_FINISHED% time=0 testParseOFF (offtest)" << std::endl;

    std::cout << "%SUITE_FINISHED% time=0" << std::endl;

    return (EXIT_SUCCESS);
}


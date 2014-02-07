#include <ctime>
#include <iostream>
#include <string>

#include "timer.hpp"

Timer::Timer(): title("Execution") {
  start = clock();
}

Timer::Timer(std::string t): title(t) {
  start = clock();
}

void Timer::Restart(std::string t) {
  title = std::string(t);
  start = clock();
}

void Timer::Report() {
  double elapsed = double(clock() - start) / (CLOCKS_PER_SEC / 1000.0);
  std::cout << title \
            << " completed in " \
            << elapsed \
            << "ms" \
            << std::endl;
}

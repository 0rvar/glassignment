#include <ctime>
#include <string>

#ifndef TIMER_HPP
#define TIMER_HPP

class Timer {
private:
  clock_t start;
  std::string title;
public:
  Timer();
  Timer(std::string title);
  void Report();
  void Restart(std::string title);
};

#endif // TIMER_HPP

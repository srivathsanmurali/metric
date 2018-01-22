#pragma once

#include <algorithm>
#include <chrono>
#include <limits>
#include <sstream>

namespace metric {
struct TimerValue
{
  size_t count;
  double min;
  double max;
  double avg;

  TimerValue()
    : count(0)
    , min(std::numeric_limits<double>::max())
    , max(0.0)
    , avg(0.0)
  {}

  void addValue(const double& duration)
  {
    min = std::min(min, duration);
    max = std::max(max, duration);
    avg = ((avg * count) + duration) / ++count;
  }
};

class TimerManager
{
public:
private:
};

class Timer
{
public:
private:
}; // class Timer
} // namespace metric

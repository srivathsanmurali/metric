#pragma once

#include <algorithm>
#include <chrono>
#include <cmath>
#include <iomanip>
#include <limits>
#include <map>
#include <mutex>
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

    // Using iterative average update as give in
    // http://www.heikohoffmann.de/htmlthesis/node134.html
    avg = avg + ((duration - avg) / ++count);
  }

  std::string getMilliSeconds()
  {
    std::stringstream ss;
    ss << min << " ms | " << max << " ms | " << avg << " ms" << std::endl;
    return ss.str();
  }

  std::string getDuration(double ms)
  {
    const auto hour = ms / 3600000;
    ms = std::fmod(ms, 3600000);

    const auto min = ms / 60000;
    ms = std::fmod(ms, 60000);

    const auto sec = ms / 1000;
    ms = std::fmod(ms, 1000);

    std::stringstream ss;
    ss << std::fixed << std::setprecision(0) << std::setfill('0')
       << std::setw(2) << hour << ":" << min << ":" << sec << ":"
       << std::setw(3) << ms;

    return ss.str();
  }

  std::string getTime()
  {
    std::stringstream ss;
    ss << getDuration(min) << " | " << getDuration(max) << " | "
       << getDuration(avg) << std::endl;
    return ss.str();
  }
};

class TimerManager
{
public:
  friend class Timer;

  static std::string print(bool inMilliSeconds = false)
  {
    std::stringstream ss;

    ss << "Timing Metrics" << std::endl << "--------------" << std::endl;

    for (auto& timer : instance().timers) {
      ss << timer.first << " | ";

      if (inMilliSeconds)
        ss << timer.second.getMilliSeconds();
      else
        ss << timer.second.getTime();
    }

    return ss.str();
  }

private:
  static TimerManager& instance()
  {
    static TimerManager tm;
    return tm;
  }

  void addTimer(const std::string& name)
  {
    // locks the mutex to keep threadsafe
    // mutex is opened again at end of scope.
    std::lock_guard<std::mutex> lock(mtx);

    auto it = timers.find(name);
    if (it != timers.end()) {
      return;
    }

    TimerValue newTimerValue;
    timers[name] = newTimerValue;
  }

  void addTime(const std::string& name, const double& duration)
  {
    // locks the mutex to keep threadsafe
    // mutex is opened again at end of scope.
    std::lock_guard<std::mutex> lock(mtx);
    timers[name].addValue(duration);
  }

  // mutex used to make sure the timers map is not updated
  // simultaneously by multiple threads.
  std::mutex mtx;
  std::map<std::string, TimerValue> timers;
};

class Timer
{
public:
  inline Timer(const std::string& name_)
    : name(name_)
  {
    TimerManager::instance().addTimer(name);
    start = std::chrono::high_resolution_clock::now();
  }

  inline void stop()
  {
    const auto end = std::chrono::high_resolution_clock::now();
    const double duration =
      std::chrono::duration_cast<std::chrono::milliseconds>(end - start)
        .count();

    // adding the duration to the timing collection
    TimerManager::instance().addTime(name, duration);
  }

private:
  const std::string name;
  std::chrono::high_resolution_clock::time_point start;
}; // class Timer
} // namespace metric

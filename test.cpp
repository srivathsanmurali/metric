#include "metric.h"
#include <iostream>
#include <thread>
#include <vector>

void
checkTimerValue()
{
  metric::TimerValue tv;

  for (int i = 1; i <= 5; i++)
    tv.addValue(i);

  if (tv.count == 5 && tv.min == 1 && tv.max == 5 && tv.avg) {
    std::cout << "All tests pass" << std::endl;
  } else {
    std::cout << "All tests dont pass" << std::endl
              << tv.count << std::endl
              << tv.min << std::endl
              << tv.max << std::endl
              << tv.avg << std::endl;
  }
}

void
testTiming1()
{
  metric::Timer test1("test1");
  std::this_thread::sleep_for(std::chrono::milliseconds(100));

  test1.stop();
}

void
testTiming2()
{
  metric::Timer test2("test2");
  std::this_thread::sleep_for(std::chrono::milliseconds(200));

  test2.stop();
}

int
main()
{
  checkTimerValue();
  std::cout << "test1 sleeps for 100 ms" << std::endl;
  std::cout << "test2 sleeps for 200 ms" << std::endl;

  for (int i = 0; i < 10; i++) {
    testTiming1();
    testTiming2();
  }

  std::cout << metric::TimerManager::print();
  return EXIT_SUCCESS;
}

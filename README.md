# Metric

The tool allows you to measure the time taken to execute a specific code segments.
The tool only uses the standard library given in C++11 standard.

## Add to Project
The library is in a [single header file](metric.h) that can be included in any project that atleast uses C++ 11 standards.

## Usage
Measuring the execution times of the code segments.
```C++
// include metric.h in the files where you would like to measure the execution time.
#include "metric.h"

// surround the code segment with the following lines

// Start the timer by declaring an object and give the operation a name so
// that multiple run's of the code segment could be used to calculate the min, max and avg runtimes.
metric::Timer timer1("Name of the operation");

// Code segment to be tested

// This stops the timer and adds the duration taken for executing code segment to the 
// the average calculation.
timer1.stop();
```
Printing the execution times in the main executable.
```C++
// include the metric.h
#include "metric.h"

// At the end of the excutable after all the timers have completed measuring execution time.
// Print the timer results.

// Print the results in hours:minutes:seconds:milliseconds
metric::TimerManager::print();

// Print the results in milliseconds
metric::TimerManager::print(true);
```

An example can be seen in [test.cpp](test.cpp).

## References
This tool is based on the excellent [sm_timing](https://github.com/ethz-asl/schweizer_messer/tree/master/sm_timing).
But it depends on the boost library and including the boost library to use sm_timing is inefficient. Hence, this tool was written to work without the boost library.

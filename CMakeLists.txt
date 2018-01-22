cmake_minimum_required(VERSION 2.8)
project(metric)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(testMetric test.cpp metric.h)

cmake_minimum_required(VERSION 3.17)
project(crash_course)

set(CMAKE_CXX_STANDARD 17)
set(BOOST_ROOT "C:/Program Files/Boost/boost_1_76_0")
set(BOOSTROOT "C:/Program Files/Boost/boost_1_76_0")

find_package(Boost 1.76.0)
if (NOT Boost_FOUND)
    message(FATAL_ERROR "Could not find boost!")
endif()

add_executable(crash_course catch.hpp scopedPointers.cpp)
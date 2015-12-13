cmake_minimum_required(VERSION 2.8 FATAL_ERROR)

project(MaximumSingleSellProfit CXX)

# Enabling C++11 and pthread for Linux, this is not necessary for "Windows"
if("${CMAKE_SYSTEM_NAME}" MATCHES "Linux")                                                                                                                                                    
  list(APPEND CMAKE_CXX_FLAGS "-std=c++11 -pthread")
endif()

file(GLOB_RECURSE SNIPPET_SOURCES headers/* src/*)

add_executable(MaximumSingleSellProfit ${SNIPPET_SOURCES})
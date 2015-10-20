cmake_minimum_required(VERSION 2.8 FATAL_ERROR)

project(BoostHashSnippet CXX)

# Enabling C++11 and pthread for Linux, this is not necessary for "Windows"
if("${CMAKE_SYSTEM_NAME}" MATCHES "Linux")                                                                                                                                                    
  list(APPEND CMAKE_CXX_FLAGS "-std=c++11 -pthread")
endif()

# Boost framework
# http://www.boost.org
find_package(Boost REQUIRED)

include_directories(${Boost_INCLUDE_DIR})

file(GLOB_RECURSE SNIPPET_SOURCES headers/* src/*)

add_executable(BoostHashSnippet ${SNIPPET_SOURCES})
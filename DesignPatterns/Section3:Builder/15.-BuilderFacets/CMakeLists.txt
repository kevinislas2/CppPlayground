cmake_minimum_required(VERSION 3.14)
project(15__BuilderFacets)

set(CMAKE_CXX_STANDARD 14)

include_directories(.)

add_executable(15__BuilderFacets Person.cpp Person.h PersonBuilder.cpp PersonBuilder.h main.cpp PersonJobBuilder.h PersonAddressBuilder.h)

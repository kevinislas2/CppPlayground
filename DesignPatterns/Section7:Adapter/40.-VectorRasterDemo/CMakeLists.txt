cmake_minimum_required(VERSION 3.14)
project(40__VectorRasterDemo)

set(CMAKE_CXX_STANDARD 14)

include_directories(.)

add_executable(40__VectorRasterDemo
        res/AdapterVisual.ico
        res/AdapterVisual.rc2
        AdapterVisual.aps
        AdapterVisual.cpp
        AdapterVisual.h
        AdapterVisual.rc
        AdapterVisualDlg.cpp)

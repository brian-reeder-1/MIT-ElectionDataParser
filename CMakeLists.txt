cmake_minimum_required(VERSION 3.29)
project(Election_Data_Analysis)

set(CMAKE_CXX_STANDARD 20)

add_executable(Election_Data_Analysis main.cpp
        Votes.h
        Candidates.h)

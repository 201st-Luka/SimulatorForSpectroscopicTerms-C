cmake_minimum_required(VERSION 3.24)
project(SimulatorForSpectroscopicTerms C)

set(CMAKE_C_STANDARD 11)

add_executable(SimulatorForSpectroscopicTerms main.c lib/econfig.c lib/econfig.h lib/combinations.c lib/combinations.h lib/grouping.c lib/grouping.h)

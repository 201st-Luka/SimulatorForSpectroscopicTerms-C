cmake_minimum_required(VERSION 3.24)
project(SimulatorForSpectroscopicTerms C)

set(CMAKE_C_STANDARD 11)

add_executable(SimulatorForSpectroscopicTerms main.c lib/econfig.c lib/econfig.h lib/combinatoric/combinations.c lib/combinatoric/combinations.h lib/utils.c lib/utils.h lib/combinatoric/possibilities.c lib/combinatoric/possibilities.h lib/lib.h lib/grouping/group.c lib/grouping/group.h lib/grouping/groups.c lib/grouping/groups.h lib/grouping/grouping.h lib/combinatoric/combinatoric.h)

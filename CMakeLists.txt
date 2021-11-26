cmake_minimum_required(VERSION 3.12)
project(bote_hashmap)

set(CMAKE_CXX_STANDARD 17)

if(NOT CMAKE_BUILD_TYPE)
    SET(CMAKE_BUILD_TYPE RelWithDebInfo)
endif()

set(SOURCES fancy_index.hpp benchmark.cpp benchmark.hpp)

add_executable(all_bm all_bm.cpp ${SOURCES})
add_executable(std_map_bm std_map_bm.cpp ${SOURCES})
add_executable(std_index_bm std_index_bm.cpp ${SOURCES})
add_executable(fancy_map_bm fancy_map_bm.cpp ${SOURCES})
add_executable(fancy_index_bm fancy_index_bm.cpp ${SOURCES})

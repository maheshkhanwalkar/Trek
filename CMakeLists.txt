cmake_minimum_required(VERSION 3.8)
project(Trek)

set(CMAKE_CXX_STANDARD 14)

set(CXX_FLAGS "-Wall -Wextra -pedantic -Werror -Wshadow -Wold-style-cast\
    -Wsign-conversion -Wsign-promo -Wswitch-default -Weffc++")

set(CMAKE_CXX_FLAGS_DEBUG "${CXX_FLAGS} -O0 -g -fsanitize=address")
set(CMAKE_CXX_FLAGS_RELEASE "${CXX_FLAGS} -O2")

include_directories(.)
add_subdirectory(lib)

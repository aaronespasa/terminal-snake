cmake_minimum_required(VERSION 3.0.0)
project(snake)

# Before:
# $ sudo apt-get install libncurses5-dev

find_package(Curses REQUIRED)
include_directories(${CURSES_INCLUDE_DIRS})

include_directories(include)
file(GLOB SOURCES "src/*.cpp")

add_executable(snake ${SOURCES})

set_property(TARGET snake PROPERTY CXX_STANDARD 17)
target_link_libraries(snake ${CURSES_LIBRARIES})

cmake_minimum_required(VERSION 3.11.3)

# Set the C++ standard we will use
set(CMAKE_CXX_STANDARD 17)
project(monitor)

find_package(Curses REQUIRED)
include_directories(${CURSES_INCLUDE_DIRS})

add_compile_definitions(_GLIBCXX_USE_CXX11_ABI=0)
# Set library output path to /lib
set(LIBRARY_OUTPUT_PATH "${CMAKE_SOURCE_DIR}/lib")

include_directories(include)
file(GLOB SOURCES "src/*.cpp")

# Add the GoogleTest library subdirectories
add_subdirectory(thirdparty/googletest)

add_executable(monitor ${SOURCES})

set_property(TARGET monitor PROPERTY CXX_STANDARD 17)
target_link_libraries(monitor ${CURSES_LIBRARIES})

# Add the testing executable
add_executable(test test/test.cpp src/format.cpp src/linux_parser.cpp src/system.cpp src/processor.cpp)

target_link_libraries(test 
    gtest_main
)

# TODO: Run -Werror in CI.
target_compile_options(monitor PRIVATE -Wall -Wextra)

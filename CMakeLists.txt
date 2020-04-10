cmake_minimum_required(VERSION 3.12)
project(lib3k)

set(CMAKE_CXX_FLAGS "-std=c++17 -Wall -pedantic -Wextra")

add_library(lib3k
	window.cpp
	widget.cpp
	)
target_link_libraries(lib3k -lX11)

add_executable(exe
       main.cpp
)
target_link_libraries(exe lib3k)

target_include_directories(lib3k PUBLIC include)

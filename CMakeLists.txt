cmake_minimum_required(VERSION 3.15)
project(RACTF_CLI)

set(CMAKE_CXX_STANDARD 20)

add_executable(RACTF_CLI main.cpp RACTFCLI.cpp RACTFCLI.hpp RACTFAPI.cpp RACTFAPI.hpp)
target_link_libraries(RACTF_CLI)
cmake_minimum_required(VERSION 3.15)
project(RACTF_CLI)

set(CMAKE_CXX_STANDARD 20)
add_definitions(-DBOOST_ASIO_DISABLE_CONCEPTS)


find_package(cpprestsdk REQUIRED)
add_executable(RACTF_CLI main.cpp CLI.cpp CLI.hpp ractf/API.cpp ractf/API.hpp ractf/Challenge.cpp ractf/Challenge.hpp ractf/Category.cpp ractf/Category.hpp)
target_link_libraries(RACTF_CLI PRIVATE cpprestsdk::cpprest)
target_link_libraries(RACTF_CLI PRIVATE crypto)
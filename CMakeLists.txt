cmake_minimum_required(VERSION 3.20.2)
project(spideroak_exercise)

set(CMAKE_CXX_STANDARD 17)

add_subdirectory(crypto)
add_subdirectory(Program1)
add_subdirectory(Program2)

add_subdirectory(extern/cxxopts)

target_include_directories(Program1 PUBLIC cxxopts)
target_link_libraries(Program1 PUBLIC cxxopts)

target_include_directories(Program2 PUBLIC cxxopts)
target_link_libraries(Program2 PUBLIC cxxopts)

target_include_directories(Program1 PUBLIC crypto)
target_include_directories(Program2 PUBLIC crypto)
target_link_libraries(Program1 PUBLIC crypto)
target_link_libraries(Program2 PUBLIC crypto)

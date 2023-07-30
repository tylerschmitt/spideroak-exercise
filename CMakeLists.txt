cmake_minimum_required(VERSION 3.20.2)
project(spideroak_exercise)

set(CMAKE_CXX_STANDARD 17)

add_subdirectory(lib/crypto)
add_subdirectory(src/Program1)
add_subdirectory(src/Program2)

add_subdirectory(thirdparty/cxxopts)
add_subdirectory(thirdparty/easy-socket)

target_include_directories(Program1 PUBLIC cxxopts)
target_link_libraries(Program1 PUBLIC cxxopts)

target_include_directories(Program1 PUBLIC easy-socket)
target_link_libraries(Program1 PUBLIC easy-socket)

target_include_directories(Program2 PUBLIC cxxopts)
target_link_libraries(Program2 PUBLIC cxxopts)

target_include_directories(Program2 PUBLIC easy-socket)
target_link_libraries(Program2 PUBLIC easy-socket)

target_include_directories(Program1 PUBLIC lib/crypto)
target_include_directories(Program2 PUBLIC lib/crypto)
target_link_libraries(Program1 PUBLIC crypto)
target_link_libraries(Program2 PUBLIC crypto)

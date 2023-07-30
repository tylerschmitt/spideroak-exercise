cmake_minimum_required(VERSION 3.20.2)
project(spideroak_exercise)

set(CMAKE_CXX_STANDARD 17)

add_subdirectory(lib/crypto)

add_executable(Program1 src/Program1/main.cpp)
add_executable(Program2 src/Program2/main.cpp)

add_subdirectory(thirdparty/cxxopts)
add_subdirectory(thirdparty/easy-socket)
add_subdirectory(thirdparty/googletest)

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

add_executable(spideroak_test test/test.cpp)

target_include_directories(spideroak_test PUBLIC lib/crypto)
target_link_libraries(spideroak_test PUBLIC crypto gtest)

add_test(NAME crypto_test COMMAND crypto_test)

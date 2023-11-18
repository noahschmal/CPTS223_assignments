cmake_minimum_required(VERSION 3.16)
project(MA4)

set(CMAKE_CXX_STANDARD 11)

set(CMAKE_CXX_FLAGS  "${CMAKE_CXX_FLAGS} -Wall -Xpreprocessor -fopenmp -I/opt/homebrew/opt/libomp/include")

add_executable(MA4 main.cpp)

find_package(OpenMP REQUIRED) # Find the package
target_link_libraries(${PROJECT_NAME} ${OpenMP_CXX_LIBRARIES}) # Link against it for C++


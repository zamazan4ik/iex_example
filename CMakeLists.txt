cmake_minimum_required(VERSION 3.12)
project(iex_example)

set(CMAKE_CXX_STANDARD 17)

include(conanbuildinfo.cmake)
conan_basic_setup()

include_directories(IEX_CPP_API)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fstandalone-debug")

add_executable(iex_example main.cpp IEX_CPP_API/IEX.cpp)
target_link_libraries(iex_example ${CONAN_LIBS})
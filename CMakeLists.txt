cmake_minimum_required(VERSION 3.13)
project(SKELYA_KEM_encrypt)

set(CMAKE_CXX_STANDARD 17)

set(SOURCE_FILES encryption/scr/main.cpp)

add_executable(SKELYA_KEM_encrypt ${SOURCE_FILES})

cmake_minimum_required(VERSION 3.13)
project(SKELYA_KEM_encrypt)

set(CMAKE_CXX_STANDARD 17)

add_executable(SKELYA_KEM_encrypt main.cpp encryption/decrypt/const.h encryption/encrypt/const.h encryption/keyGeneration/const.h)
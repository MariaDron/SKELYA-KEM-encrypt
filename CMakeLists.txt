cmake_minimum_required(VERSION 3.13)
project(SKELYA_KEM_encrypt)

set(CMAKE_CXX_STANDARD 17)

set(SOURCE_FILES encryption/scr/main.cpp encryption/scr/encrypt/constEnc.h)

add_executable(SKELYA_KEM_encrypt ${SOURCE_FILES})

#[[
add_executable(encryption/scr/decrypt/const.h
        encryption/scr/encrypt/const.h
        encryption/scr/keyGeneration/const.h
        encryption/scr/keyGeneration/keyGeneration.cpp
        encryption/scr/keyGeneration/keyGeneration.h
        encryption/scr/encrypt/encryption.cpp
        encryption/scr/encrypt/encryption.h
        encryption/scr/main.cpp)
]]

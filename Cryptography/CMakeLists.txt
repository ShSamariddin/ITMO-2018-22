cmake_minimum_required(VERSION 3.14)
project(crypt)

set(CMAKE_CXX_STANDARD 17)

add_subdirectory(Kazisskiy)
add_subdirectory(DES)
add_subdirectory(comp128)
add_subdirectory(TwoFish)
add_subdirectory(rc4)
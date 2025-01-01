cmake_minimum_required(VERSION 3.29)
project(HashMapAuthorsVoice)

set(CMAKE_CXX_STANDARD 20)

add_executable(HashMapAuthorsVoice Lab7main.cpp
        hashNode.hpp
        hashMap.hpp
        makeSeuss.hpp
        makeSeuss.cpp
        hashMap.cpp
        hashNode.cpp)

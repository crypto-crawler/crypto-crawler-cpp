cmake_minimum_required (VERSION 3.16)
include(FetchContent)

project (example CXX)

set(CMAKE_CXX_STANDARD 20)

FetchContent_Declare(
    crypto_crawler_cpp
    GIT_REPOSITORY https://github.com/soulmachine/crypto-crawler-cpp
    GIT_TAG main)
FetchContent_MakeAvailable(crypto_crawler_cpp)

add_executable (example example.cpp)

target_link_libraries (example PRIVATE crypto_crawler)

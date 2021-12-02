cmake_minimum_required(VERSION 3.16)
include(FetchContent)
include(GoogleTest)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_EXPORT_COMPILE_COMMANDS TRUE)

find_program(VCPKG "vcpkg")
if(!VCPKG)
  message(
    FATAL_ERROR
      "Could not find vcpkg, please install it following https://vcpkg.io/en/getting-started.html."
  )
endif()

project(
  "crypto_crawler"
  LANGUAGES CXX
  VERSION 1.7.8
  DESCRIPTION
    "A parser library to parser websocket messages from cryptocurrency exchanges."
  HOMEPAGE_URL "https://github.com/soulmachine/crypto-crawler-cpp")

FetchContent_Declare(
  googletest
  URL https://github.com/google/googletest/archive/609281088cfefc76f9d0ce82e1ff6c30cc3591e5.zip
)
# For Windows: Prevent overriding the parent project's compiler/linker settings
set(gtest_force_shared_crt
    ON
    CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

FetchContent_Declare(
  crypto_crawler_ffi
  GIT_REPOSITORY https://github.com/soulmachine/crypto-crawler-ffi
  GIT_TAG main)
FetchContent_MakeAvailable(crypto_crawler_ffi)

add_library(crypto_crawler STATIC crypto_crawler.cpp)
target_link_libraries(crypto_crawler crypto_crawler_ffi)
set_target_properties(PROPERTIES PUBLIC_HEADER
                                 "${CMAKE_CURRENT_SOURCE_DIR}/crypto_crawler.h")
target_include_directories(
  crypto_crawler INTERFACE $<BUILD_INTERFACE:${PROJECT_SOURCE_DIR}/include>
                           $<INSTALL_INTERFACE:${CMAKE_INSTALL_INCLUDEDIR}>)

enable_testing()
add_executable(crypto_crawler_test crypto_crawler_test.cpp)
target_link_libraries(crypto_crawler_test PRIVATE crypto_crawler gtest_main)
gtest_discover_tests(crypto_crawler_test)

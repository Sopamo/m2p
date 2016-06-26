cmake_minimum_required (VERSION 2.6)
project (m2p)
set (M2P_VERSION_MAJOR 0)
set (M2P_VERSION_MINOR 1)

find_package(PkgConfig REQUIRED)

pkg_check_modules(SODIUM REQUIRED libsodium)

include_directories(${SODIUM_INCLUDE_DIRS})
link_directories(${SODIUM_LIBRARY_DIRS})
add_definitions(${SODIUM_FLAGS_OTHER})

include(CheckCXXCompilerFlag)
CHECK_CXX_COMPILER_FLAG("-std=c++14" COMPILER_SUPPORTS_CXX14)
if(COMPILER_SUPPORTS_CXX14)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++14 -pthread")
else()
    message(STATUS "The compiler ${CMAKE_CXX_COMPILER} has no C++11 support. Please use a different C++ compiler.")
endif()

add_subdirectory(m2p)

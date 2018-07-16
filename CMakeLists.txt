
project(smooth)

cmake_minimum_required(VERSION 3.5)

# Add google test as a sub-module
add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/submodules/googletest/googletest ${CMAKE_BINARY_DIR}/googletest)
set(GTEST_INCLUDE_DIRS ${CMAKE_CURRENT_SOURCE_DIR}/submodules/googletest/googletest/include/)
set(GTEST_BOTH_LIBRARIES gtest gtest_main)

if (MSVC)    
    # Changes MD to MT for Windows Visual C++ compilation
    include(${CMAKE_CURRENT_SOURCE_DIR}/cmake/internal_utils.cmake)
    config_compiler_and_linker()
else()
    add_compile_options(-Wall -Wextra -Wpedantic)
endif()

find_package(Threads REQUIRED)

# Eigen include directories
set(EIGEN_INCLUDE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/submodules/eigen-git-mirror/)

# Smooth library
add_library(smoothlib STATIC
    src/polyinterp.c)
target_include_directories(smoothlib PUBLIC include)

file(GLOB INCLUDES "include/*.h")

# Smooth tests
add_executable(smooth_tests
    tests/polyinterptests.cpp
    tests/quicksorttests.cpp
	tests/eigentests.cpp
    ${INCLUDES})
target_include_directories(smooth_tests PUBLIC include ${GTEST_INCLUDE_DIRS} ${EIGEN_INCLUDE_DIR})
set_target_properties(smooth_tests PROPERTIES CXX_STANDARD 11)
target_link_libraries(smooth_tests smoothlib ${GTEST_BOTH_LIBRARIES} ${CMAKE_THREAD_LIBS_INIT})

enable_testing()
add_test(smooth_tests "${CMAKE_BINARY_DIR}/smooth_tests")

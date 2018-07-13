project(smooth)

cmake_minimum_required(VERSION 3.5)

if (MSVC)
    add_compile_options(/W4)
else()
    add_compile_options(-Wall -Wextra -Wpedantic)
endif()

enable_testing()
find_package(Threads REQUIRED)
find_package(GTest REQUIRED)

add_library(smoothlib 
	src/polyinterp.c)
target_include_directories(smoothlib PUBLIC include)

file(GLOB INCLUDES "include/*.h")
add_executable(smooth_tests
	tests/polyinterptests.cpp
	${INCLUDES} include/smooth.h)
target_include_directories(smooth_tests PUBLIC include ${GTEST_INCLUDE_DIRS})
set_target_properties(smooth_tests PROPERTIES CXX_STANDARD 11)
target_link_libraries(smooth_tests smoothlib ${GTEST_BOTH_LIBRARIES} ${CMAKE_THREAD_LIBS_INIT})

add_test(smooth_tests "${CMAKE_BINARY_DIR}/smooth_tests")


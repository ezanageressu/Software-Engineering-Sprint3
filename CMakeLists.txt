cmake_minimum_required(VERSION 3.10.2 FATAL_ERROR)
project(PencilMaker)

set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTOUIC ON)
set(SOURCES src/main.cpp src/mainwindow.cpp)
set(TESTSOURCES src/tests.cpp src/mainwindow.cpp)
set(HEADERS src/mainwindow.h)
set(FORMS src/mainwindow.ui)
set(CMAKE_CXX_FLAGS "${MAKE_CXX_FLAGS} -std=c++0x")

find_package(Qt5 COMPONENTS Core Widgets REQUIRED)

# Locate GTest
find_package(GTest REQUIRED)
include_directories(${GTEST_INCLUDE_DIRS})

if(CMAKE_COMPILER_IS_GNUCC)
    add_definitions(-Wall -Werror)
endif(CMAKE_COMPILER_IS_GNUCC)

add_subdirectory(src)

add_executable(execPencilMaker ${SOURCES} ${HEADERS} ${FORMS})
add_executable(testPencilMaker ${TESTSOURCES} ${HEADERS} ${FORMS})

target_link_libraries(execPencilMaker Qt5::Widgets ${GTEST_LIBRARIES} pthread)
target_link_libraries(testPencilMaker Qt5::Widgets ${GTEST_LIBRARIES} pthread)


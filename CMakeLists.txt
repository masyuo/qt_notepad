cmake_minimum_required(VERSION 3.7)
project (qt_notepad)

set(CMAKE_CXX_STANDARD 14)

set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(CMAKE_AUTOMOC ON)
find_package(Qt5 COMPONENTS Core Widgets REQUIRED)


include_directories(${CMAKE_SOURCE_DIR}/headers)
set(HEADER_LIST headers/notepad.h)
set(SOURCE_LIST src/main.cpp src/notepad.cpp)
set(SOURCES ${HEADER_LIST} ${SOURCE_LIST})



add_executable(${PROJECT_NAME} ${SOURCES})
target_link_libraries(${PROJECT_NAME} Qt5::Core Qt5::Widgets)
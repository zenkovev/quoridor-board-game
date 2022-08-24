cmake_minimum_required(VERSION 3.1)
project(Quoridor)
set(CMAKE_CXX_STANDARD 11)

set(LIBRARY_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/lib)
set(EXECUTABLE_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/bin)

find_package(PkgConfig)
pkg_check_modules(GTKMM gtkmm-3.0)

link_directories(${GTKMM_LIBRARY_DIRS})
include_directories(${GTKMM_INCLUDE_DIRS})

add_subdirectory(code)
set(SOURCES_HELP TypeOfStep Table Participant TableImage AllImage ProcessingSignals Step)

add_executable(Quoridor main.cpp)
add_dependencies(Quoridor ${SOURCES_HELP})
target_link_libraries(Quoridor ${SOURCES_HELP})

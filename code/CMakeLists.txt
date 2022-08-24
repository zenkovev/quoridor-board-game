cmake_minimum_required(VERSION 3.1)
project(QuoridorHelpLibraries)
set(CMAKE_CXX_STANDARD 11)

find_package(PkgConfig)
pkg_check_modules(GTKMM gtkmm-3.0)

link_directories(${GTKMM_LIBRARY_DIRS})
include_directories(${GTKMM_INCLUDE_DIRS})

include_directories(${CMAKE_CURRENT_SOURCE_DIR}/image)
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/include)
#for all targets

add_library(TypeOfStep ${CMAKE_CURRENT_SOURCE_DIR}/src/TypeOfStep.cpp)

add_library(Table ${CMAKE_CURRENT_SOURCE_DIR}/src/Table.cpp)

add_library(Participant ${CMAKE_CURRENT_SOURCE_DIR}/src/Participant.cpp)

add_library(TableImage ${CMAKE_CURRENT_SOURCE_DIR}/src/TableImage.cpp)
target_link_libraries(TableImage ${GTKMM_LIBRARIES})

add_library(AllImage ${CMAKE_CURRENT_SOURCE_DIR}/src/AllImage.cpp)
target_link_libraries(AllImage ${GTKMM_LIBRARIES})

add_library(ProcessingSignals ${CMAKE_CURRENT_SOURCE_DIR}/src/ProcessingSignals.cpp)
target_link_libraries(ProcessingSignals ${GTKMM_LIBRARIES})

add_library(Step ${CMAKE_CURRENT_SOURCE_DIR}/src/Step.cpp)
target_link_libraries(Step ${GTKMM_LIBRARIES})
target_link_libraries(Step TypeOfStep Table Participant TableImage AllImage ProcessingSignals)

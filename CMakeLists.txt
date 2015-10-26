cmake_minimum_required(VERSION 2.8.8)

project(syntactical_an)

add_definitions("-std=gnu++11")

include_directories(src)
set(SRC
  src/syntactical_an.cpp
  src/alexical_an.cpp
)

#
# DEPS
#

find_package(Threads REQUIRED)

#
# BIN
#

add_library(core OBJECT ${SRC})
set(COMMON_LIBRARIES
  ${CMAKE_THREAD_LIBS_INIT}
)

add_executable(syntactical_an src/main.cpp $<TARGET_OBJECTS:core>)
target_link_libraries(syntactical_an ${COMMON_LIBRARIES})

#add_executable(syntactical_an_tests src/alexical_tests.cpp $<TARGET_OBJECTS:core>)
#target_link_libraries(an_alexico_tests ${COMMON_LIBRARIES})

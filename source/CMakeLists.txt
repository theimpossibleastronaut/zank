cmake_minimum_required(VERSION 3.2 FATAL_ERROR)

SET(ProjectName zank)

SET(BIN_OUTPUT ${ProjectName})
set(CMAKE_C_FLAGS "-Wall -g -O0")
add_executable (${BIN_OUTPUT} main.c functions.c usage.c net.c utils.c
								graphics.c military.c)

message(STATUS "Searching for curses")
include(FindCurses)
IF (CURSES_FOUND)
  SET(EXTERNAL_LIBS ${EXTERNAL_LIBS} ${CURSES_LIBRARIES})
  SET(INCLUDE_DIRECTORIES ${INCLUDE_DIRECTORIES} ${CURSES_INCLUDE_DIRS})
ELSE()
  message (FATAL_ERROR "curses library not found")
ENDIF()

include_directories("${CMAKE_SOURCE_DIR}/../external/json-c/local/include/json-c")

target_link_libraries (${BIN_OUTPUT} ${EXTERNAL_LIBS} ${CMAKE_SOURCE_DIR}/../external/json-c/local/lib/libjson-c.a)

cmake_minimum_required(VERSION 3.2 FATAL_ERROR)

SET(ProjectName Zank)

SET(BIN_OUTPUT ${ProjectName})
add_executable (${BIN_OUTPUT} main.c functions.c usage.c)

message(STATUS "Searching for curses")
include(FindCurses)
IF (CURSES_FOUND)
  SET(EXTERNAL_LIBS ${EXTERNAL_LIBS} ${CURSES_LIBRARIES})
  SET(INCLUDE_DIRECTORIES ${INCLUDE_DIRECTORIES} ${CURSES_INCLUDE_DIRS})
ELSE()
  message (FATAL "curses library not found")
ENDIF()

target_link_libraries (${BIN_OUTPUT} ${EXTERNAL_LIBS})


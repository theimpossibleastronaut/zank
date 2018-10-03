cmake_minimum_required(VERSION 3.2 FATAL_ERROR)

SET(ProjectName Zank)

SET(BIN_OUTPUT Zank)
add_executable (${BIN_OUTPUT} main.c functions.c)

message(STATUS "Searching for curses")
include(FindCurses)
IF (CURSES_FOUND)
  SET(EXTERNAL_LIBS ${EXTERNAL_LIBS} ${CURSES_LIBRARIES})
	INCLUDE_DIRECTORIES(${CURSES_INCLUDE_DIRS})
ELSE()
	message (FATAL "curses library not found")
ENDIF()

target_link_libraries (${BIN_OUTPUT} ${EXTERNAL_LIBS})

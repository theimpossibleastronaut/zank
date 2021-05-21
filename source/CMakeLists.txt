cmake_minimum_required(VERSION 3.2 FATAL_ERROR)

project(zank)
#SET(ProjectName zank)

SET(BIN_OUTPUT ${PROJECT_NAME})
set(CMAKE_C_FLAGS "-Wall -g -O0")
add_executable (${BIN_OUTPUT} main.c functions.c usage.c net.c utils.c
								graphics.c military.c)

include(FindPkgConfig)
pkg_check_modules(JSONC REQUIRED json-c)
SET(EXTERNAL_LIBS ${EXTERNAL_LIBS} ${JSONC_LIBRARIES})
SET(INCLUDE_DIRECTORIES ${INCLUDE_DIRECTORIES} ${JSONC_INCLUDE_DIRS})
message(STATUS "Searching for curses")
include(FindCurses)
IF (CURSES_FOUND)
  SET(EXTERNAL_LIBS ${EXTERNAL_LIBS} ${CURSES_LIBRARIES})
  SET(INCLUDE_DIRECTORIES ${INCLUDE_DIRECTORIES} ${CURSES_INCLUDE_DIRS})
ELSE()
  message (FATAL_ERROR "curses library not found")
ENDIF()

include_directories(${INCLUDE_DIRECTORIES})

target_link_libraries (${BIN_OUTPUT} ${EXTERNAL_LIBS})

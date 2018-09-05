cmake_minimum_required(VERSION 3.0)

project(networking_programming C)


include(CheckIncludeFile)

check_include_file( stdio.h HAVE_STDIO_H )
check_include_file( stdlib.h HAVE_STDLIB_H )
CHECK_INCLUDE_FILE( sys/mman.h HAVE_MMAN_H )
check_include_file( sys/stat.h HAVE_STAT_H )
check_include_file( fcntl.h HAVE_FNCTL_H )
check_include_file( signal.h HAVE_SIGNAL_H )

if(NOT (HAVE_STDIO_H AND HAVE_STDLIB_H AND HAVE_MMAN_H AND HAVE_STAT_H AND HAVE_FNCTL_H AND HAVE_SIGNAL_H ) )
    message(FATAL_ERROR "Error: Missing required header files")
endif()

include_directories(include)

add_subdirectory(examples)
cmake_minimum_required(VERSION 3.10 FATAL_ERROR)

#project specification
project(SglToolkit VERSION 1.4 DESCRIPTION "Simple OpenGL Toolkit - An engine with built in tools for OpenGL functionalities")
set(LIB_NAME SglToolkit)
#config
configure_file(${CMAKE_SOURCE_DIR}/include/SgTDefineFile.h ${CMAKE_BINARY_DIR}/include/SgTDefineFile.h @ONLY)

#set c++ version to 17
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

#set output dir
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)

#add source
add_subdirectory(${CMAKE_SOURCE_DIR}/src)
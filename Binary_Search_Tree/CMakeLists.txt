cmake_minimum_required(VERSION 3.9)
project(SearchTree)

set(CMAKE_CXX_STANDARD 11)

set(SOURCE_EXE main.cpp) # set main exe file

set(SOURCES_LIB node.cpp tree.cpp iterator.cpp) # set static libraries

add_library(btree STATIC ${SOURCES_LIB})

add_executable(main ${SOURCE_EXE})	# create executable file with name main

target_link_libraries(main btree)



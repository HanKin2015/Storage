#Cmake 最低版本要求
cmake_minimum_required(VERSION 3.5.1)
 
#项目名称
project(CMakeExp)
 
message(STATUS "CMakeExpMaster.") 
#set(TEST_OPTION OFF)
 
option(TEST_OPTION "test opiton" ABC)
 
if (DEFINED TEST_OPTION)
        message(STATUS "TEST_OPTION defined: " ${TEST_OPTION})
else ()     
        message(STATUS "TEST_OPTION un-defined: " ${TEST_OPTION})
endif()
 
if (TEST_OPTION)
        message(STATUS "TEST_OPTION ON.")
        add_definitions(-DTEST_OPTION)
else ()
        message(STATUS "TEST_OPTION OFF.")
endif()
 
if (NOT TEST_OPTION)
        message(STATUS "NOT-TEST_OPTION ON.")
else ()
        message(STATUS "NOT-TEST_OPTION OFF.")
endif()      
                                                                                                                                                          
add_subdirectory(sub)
add_definitions(-TEST_OPTION)
add_definitions(-DHJ=345)
add_definitions(-DJH)
add_executable(test2 test.c)

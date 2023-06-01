#Cmake 最低版本要求
cmake_minimum_required(VERSION 3.5.1)
 
#项目名称
project(CMakeExpSub)
 
message(STATUS "\n\nCMakeExpSub.") 
 
option(TEST_OPTION "test opiton" ON) 
 
if (DEFINED TEST_OPTION)
        message(STATUS "TEST_OPTION defined: " ${TEST_OPTION})
else ()
        message(STATUS "TEST_OPTION un-defined: " ${TEST_OPTION})
endif()
 
if (TEST_OPTION)
        message(STATUS "TEST_OPTION ON.")
else ()
        message(STATUS "TEST_OPTION OFF.")
endif()

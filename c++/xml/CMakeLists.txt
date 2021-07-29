#…Ë÷√C±‡“Î∆˜  
set(CMAKE_C_FLAGS "-g -Wall  -I D:\\other\\Tools\\msys64\\mingw64\\include -L D:\\other\\Tools\\msys64\\mingw64\\lib")#  
  
set(CMAKE_CXX_COMPILER "g++")#…Ë÷√C++±‡“Î∆˜  
set(CMAKE_CXX_FLAGS "-g -Wall  -I D:/other/Tools/msys64/mingw64/include -L D:/other/Tools/msys64/mingw64/lib")  
  
PROJECT (XML CXX)  
SET(SRC_LIST main.cpp tinyxml2.cpp)  
ADD_EXECUTABLE(main ${SRC_LIST})  
  
MESSAGE(STATUS "This is BINARY dir " ${HELLO_BINARY_DIR})  
MESSAGE(STATUS "This is SOURCE dir " ${HELLO_SOURCE_DIR}) 
# OpenCV入门

## 1、OpenCV安装
```
sudo apt-get install libopencv-dev
```

## 2、编译运行
使用CmakeList.txt文件进行编译
```
cmake_minimum_required(VERSION 3.10)
project(OpenCVExample)

find_package(OpenCV REQUIRED)

add_executable(OpenCVExample main.cpp)

target_link_libraries(OpenCVExample ${OpenCV_LIBS})

MESSAGE(STATUS "OpenCV_LIBS=${OpenCV_LIBS}")
```
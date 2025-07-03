TEMPLATE = app
CONFIG += c++14  # 使用 C++14
QMAKE_CXXFLAGS += -std=c++14 -g
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets
SOURCES += main.cpp  # 添加源文件
#HEADERS += json.hpp  # 添加头文件（如果有）


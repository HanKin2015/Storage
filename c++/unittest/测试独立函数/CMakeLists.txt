cmake_minimum_required(VERSION 3.15)
project(MyProject VERSION 1.0.0)

# 设置C++标准
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# 生成编译命令数据库（用于Clangd等工具）
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# 添加主库
add_library(my_library STATIC
  src/math_functions.cpp
)
target_include_directories(my_library
  PUBLIC
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
    $<INSTALL_INTERFACE:include>
)

# 添加通用编译选项
target_compile_options(my_library PRIVATE
  -Wall -Wextra -Wpedantic -Werror
)

# 为Debug配置添加调试选项
target_compile_options(my_library PRIVATE
  $<$<CONFIG:DEBUG>:-O0 -g3>
)

# 为Release配置添加优化选项
target_compile_options(my_library PRIVATE
  $<$<CONFIG:RELEASE>:-O3>
)

# 设置编译选项（传统方法）
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra -Wpedantic -Werror")
set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -O0 -g3")
set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} -O3")

# 添加可执行文件
add_executable(my_app src/main.cpp)
target_link_libraries(my_app PRIVATE my_library)

# 安装目标
install(TARGETS my_library my_app
  EXPORT MyProjectTargets
  ARCHIVE DESTINATION lib
  LIBRARY DESTINATION lib
  RUNTIME DESTINATION bin
)
install(DIRECTORY include/ DESTINATION include)

# 添加测试子目录
option(BUILD_TESTS "Build the tests" ON)
if(BUILD_TESTS)
  enable_testing()
  add_subdirectory(tests)
endif()
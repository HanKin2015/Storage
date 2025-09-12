#######################################################
# 文 件 名: CMakeLists.txt
# 文件描述: 在 CMake 中，可以通过 FetchContent 模块（CMake 3.11+）实现在线下载依赖库
# 备    注: FetchContent 更现代、使用更简便，推荐优先使用
# 作    者: HanKin
# 创建日期: 2025.09.12
# 修改日期：2025.09.12
# 
# Copyright (c) 2025 HanKin. All rights reserved.
#######################################################
cmake_minimum_required(VERSION 3.11)
project(MyProject)

# 引入 FetchContent 模块
include(FetchContent)

# 声明要下载的 fmt 库（从 GitHub）
FetchContent_Declare(
    fmt                    # 依赖名称
    GIT_REPOSITORY https://github.com/fmtlib/fmt.git
    GIT_TAG        10.1.1  # 指定版本标签（可替换为最新版本）或 GIT_COMMIT 提交哈希
    # 其他可选参数：SOURCE_DIR 本地目录，BINARY_DIR 构建目录等
)

# 下载并构建 fmt（首次配置时下载，后续会缓存）
FetchContent_MakeAvailable(fmt)

# 创建可执行文件
add_executable(myapp main.cpp)

# 链接 fmt 库到目标
target_link_libraries(myapp PRIVATE fmt::fmt)
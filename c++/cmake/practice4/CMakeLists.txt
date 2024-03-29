# CMake 最低版本要求
cmake_minimum_required(VERSION 3.5.1)

# 项目名称
project(CMakeStudy)

# 宏定义开关选项，布尔类型变量OFF或ON
option(ENABLE_LIBUVC_BACKEND "enable libuvc backend for uvc device operation [default=ON]" ON)
option(BUILD_TESTING "enable test building" ON)
option(BUILD_COVERAGE_REPORT "enable coverage report generation" OFF)

# 定义一个普通类型的变量
set(SRC_FILES main.cpp foo.cpp bar.cpp)

# 用于查找和加载外部依赖库，REQUIRED 表示如果找不到依赖库则停止 CMake 构建过程
find_package(Threads REQUIRED)
find_package(PkgConfig REQUIRED)
pkg_check_modules(UDEV REQUIRED libudev)

if(BUILD_TESTING)
    # 覆盖率
    if(BUILD_COVERAGE_REPORT)
        if(CMAKE_BUILD_TYPE STREQUAL "Debug")
            include(${PROJECT_SOURCE_DIR}/cmake/CodeCoverage.cmake)
            append_coverage_compiler_flags()
            setup_target_for_coverage_gcovr_xml(
                NAME gcovr_xml
                EXECUTABLE ctest -V -j ${PROCESSOR_COUNT}
                DEPENDENCIES ${PROJECT_NAME}_shared
                BASE_DIRECTORY "${PROJECT_SOURCE_DIR}"
                EXCLUDE "tests/*"
            )
            setup_target_for_coverage_gcovr_html(
                NAME gcovr_html
                EXECUTABLE ctest -V -j ${PROCESSOR_COUNT}
                DEPENDENCIES ${PROJECT_NAME}_shared
                BASE_DIRECTORY "${PROJECT_SOURCE_DIR}"
                EXCLUDE "tests/*"
            )
        else()
            message(WARNING "Code coverage results with an optimised (non-Debug) build may be misleading")
        endif()
        
    endif()
    
    # 单元测试
    enable_testing()
    add_subdirectory(tests)
endif()

# 用于将一个文件作为模板，根据用户定义的变量值生成一个新的文件
configure_file(
    ${CMAKE_CURRENT_SOURCE_DIR}/config.h.in
    ${CMAKE_BINARY_DIR}/include/config.h
)

# 源代码文件
set(${PROJECT_NAME}_SRC
    mymath.cpp
    main.cpp
)

# 使用list命令增加文件
if(ENABLE_LIBUVC_BACKEND)
    list(APPEND ${PROJECT_NAME}_SRC
        mymath.h
    )
endif()

# 包含头文件
set(${PROJECT_NAME}_PUBLIC_INCLUDE_DIR
    ${PROJECT_SOURCE_DIR}/
    ${PROJECT_BINARY_DIR}/include
    ${PROJECT_SOURCE_DIR}/../libusb-1.0.19/libusb
)
set(${PROJECT_NAME}_PRIVATE_INCLUDE_DIR
    ${PROJECT_SOURCE_DIR}/../three-part-depends/x264
    ${PROJECT_SOURCE_DIR}/../spice-0.12.5/libsgax/ffmpeg/include/ffmpeg/
)
# 不同架构之间判断
if(CMAKE_HOST_SYSTEM_PROCESSOR MATCHES "x86_64")
    list(APPEND ${PROJECT_NAME}_PRIVATE_INCLUDE_DIR
        /usr/include
    )
    link_directories(
        /usr/local/lib/
    )
    message(STATUS "CMAKE_HOST_SYSTEM_PROCESSOR=" ${CMAKE_HOST_SYSTEM_PROCESSOR})
else()
    list(APPEND ${PROJECT_NAME}_PRIVATE_INCLUDE_DIR
        ${PROJECT_SOURCE_DIR}/../three-part-depends/libjpeg-turbo-1.4.1
    )
    link_directories(
        /usr/local/lib/
        /usr/lib/loongarch64-linux-gnu/
    )
    message(STATUS "CMAKE_HOST_SYSTEM_PROCESSOR=" ${CMAKE_HOST_SYSTEM_PROCESSOR})
endif()


set(${PROJECT_NAME}_LINK_LIBS
    /usr/local/lib/libusb-1.0.so.0.3.0
)

list(APPEND ${PROJECT_NAME}_LINK_LIBS
    Threads::Threads
)

# 生成so文件
#add_library(${PROJECT_NAME}_shared SHARED
#    ${${PROJECT_NAME}_SRC}
#)

# 生成执行文件
add_executable(${PROJECT_NAME}_shared
    ${${PROJECT_NAME}_SRC}
)

# target_include_directories 是 CMake 中用于指定目标（target）的头文件搜索路径的命令
# SYSTEM 表示这些头文件是系统头文件，会被编译器以不同的方式处理；BEFORE 表示这些路径会被添加到已有的路径之前；INTERFACE 表示这些路径只会被添加到目标的接口属性中，不会被添加到目标自身的编译选项中；PUBLIC 表示这些路径会被添加到目标自身的编译选项中，同时也会被添加到目标的依赖项的编译选项中；PRIVATE 表示这些路径只会被添加到目标自身的编译选项中，不会被添加到目标的依赖项的编译选项中。
target_include_directories(${PROJECT_NAME}_shared
    PUBLIC
    ${${PROJECT_NAME}_PUBLIC_INCLUDE_DIR}
    PRIVATE
    ${${PROJECT_NAME}_PRIVATE_INCLUDE_DIR}
)

# target_link_libraries 是 CMake 中用于将库链接到目标文件的命令
target_link_libraries(${PROJECT_NAME}_shared
    PUBLIC
    ${${PROJECT_NAME}_LINK_LIBS}
    ${UDEV_LIBRARIES}
)

# 设置了 C++ 标准为 11
# 要求编译器必须支持这个标准
# 禁用了 C++ 扩展
# 将输出路径设置为 ${CMAKE_BINARY_DIR}
# COMPILE_FLAGS：编译选项
# LINK_FLAGS：链接选项
# INCLUDE_DIRECTORIES：头文件搜索路径
# LINK_DIRECTORIES：库文件搜索路径
# OUTPUT_NAME：输出文件名
# ARCHIVE_OUTPUT_DIRECTORY：静态库输出路径
# LIBRARY_OUTPUT_DIRECTORY：动态库输出路径
set_target_properties(${PROJECT_NAME}_shared
    PROPERTIES
    OUTPUT_NAME "main"
    CXX_STANDARD 11
    CXX_STANDARD_REQUIRED YES
    CXX_EXTENSIONS NO
    RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}"
    POSITION_INDEPENDENT_CODE TRUE
    INSTALL_RPATH "${CMAKE_INSTALL_PREFIX}/lib"
    BUILD_WITH_INSTALL_RPATH TRUE
    SKIP_BUILD_RPATH FALSE
)

message(STATUS "[main options]")
message(STATUS "ENABLE_LIBUVC_BACKEND=" ${ENABLE_LIBUVC_BACKEND})
message(STATUS "BUILD_TESTING=" ${BUILD_TESTING})
message(STATUS "BUILD_COVERAGE_REPORT=" ${BUILD_COVERAGE_REPORT})
message(STATUS "${${PROJECT_NAME}_SRC}=" ${${PROJECT_NAME}_SRC})
message(STATUS "PROJECT_NAME_SRC=" ${${PROJECT_NAME}_SRC})
message(STATUS "PROJECT_NAME_SRC=" ${CMakeStudy_SRC})


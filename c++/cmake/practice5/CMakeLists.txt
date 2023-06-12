# CMake 最低版本要求
cmake_minimum_required(VERSION 3.5.1)

# 项目名称
project(CMakeStudy)

# 宏定义开关选项，布尔类型变量OFF或ON
option(ENABLE_LIBUVC_BACKEND "enable libuvc backend for uvc device operation [default=ON]" ON)
option(BUILD_TESTING "enable test building" ON)
option(BUILD_COVERAGE_REPORT "enable coverage report generation" OFF)

# pthread required (gtest links to target "Threads::Threads" but the target was not found)
set(THREADS_PREFER_PTHREAD_FLAG ON)
find_package(Threads REQUIRED)

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

# 源代码文件
set(${PROJECT_NAME}_SRC
    mymath.cpp
)

list(APPEND ${PROJECT_NAME}_LINK_LIBS
    Threads::Threads
)

# 使用list命令增加文件
if(ENABLE_LIBUVC_BACKEND)
    list(APPEND ${PROJECT_NAME}_SRC
        mymath.h
    )
endif()

# 生成so文件
add_library(${PROJECT_NAME}_shared SHARED
    ${${PROJECT_NAME}_SRC}
)

set_target_properties(${PROJECT_NAME}_shared
    PROPERTIES
    OUTPUT_NAME "mymath"
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
message(STATUS "PROJECT_SOURCE_DIR=" ${PROJECT_SOURCE_DIR})
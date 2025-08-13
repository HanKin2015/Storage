cmake_minimum_required(VERSION 3.16)
project(hello_linux_driver)

# 设置内核源码路径
set(KERNEL_DIR /lib/modules/$(uname -r)/build)

# 添加目标模块
add_custom_target(hello_linux_driver ALL
                  COMMAND make -C ${KERNEL_DIR} M=${CMAKE_CURRENT_SOURCE_DIR} modules
                  WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
                  )

# 清理命令
add_custom_target(clean
                  COMMAND make -C ${KERNEL_DIR} M=${CMAKE_CURRENT_SOURCE_DIR} clean
                  WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
                  )

MESSAGE(STATUS "OpenCV_LIBS=${OpenCV_LIBS}")
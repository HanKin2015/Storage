include(${PROJECT_SOURCE_DIR}/cmake/libgtest.cmake)

set(TEST_SETS_NAME "unit_test")

add_executable(${TEST_SETS_NAME}
    unit_test.cpp
    ${PROJECT_SOURCE_DIR}/mymath.cpp
)

target_include_directories(${TEST_SETS_NAME}
    PRIVATE
    ${GTEST_INCLUDES}
    ${PROJECT_SOURCE_DIR}
    ${PROJECT_BINARY_DIR}/include
)

target_link_libraries(${TEST_SETS_NAME}
    ${GTEST_LIBS}
    my_mock
)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")
set_target_properties(${TEST_SETS_NAME}
    PROPERTIES
    CMAKE_CXX_STANDARD 11
)

add_test(
    NAME ${TEST_SETS_NAME}
    COMMAND ${TEST_SETS_NAME}
)

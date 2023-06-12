include(${PROJECT_SOURCE_DIR}/cmake/libgtest.cmake)

set(TEST_SETS_NAME "reserved_test")

add_executable(${TEST_SETS_NAME}
    test.cpp
)

target_include_directories(${TEST_SETS_NAME}
    PRIVATE
    ${GTEST_INCLUDES}
)

target_link_libraries(${TEST_SETS_NAME}
    PRIVATE
    ${GTEST_LIBS}
    ${PROJECT_NAME}_shared
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

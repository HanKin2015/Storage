add_library(my_mock STATIC
    test.c
)

target_include_directories(my_mock
    PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}/include
    ${CMAKE_PROJECT_SOURCE_DIR}
)

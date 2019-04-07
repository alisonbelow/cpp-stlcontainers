include(${PROJECT_SOURCE_DIR}/cmake/googletest-download-macro.cmake)

# Call macro from googletest-macro.cmake
# download module path, download root path
download_googletest(
    ${PROJECT_SOURCE_DIR}/cmake
    ${PROJECT_SOURCE_DIR}/googletest
)

# Use to get code coverage
if(CMAKE_CXX_COMPILER_ID MATCHES GNU)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fprofile-arcs -ftest-coverage")
endif()


# Get all test files
set(PROJECT_TEST_DIR ${PROJECT_SOURCE_DIR}/test)
file(GLOB TEST_FILES_VECTOR
    ${PROJECT_TEST_DIR}/vector/*.cpp
)

file(GLOB TEST_FILES_STRING
    ${PROJECT_TEST_DIR}/string/*.cpp
)

file(GLOB TEST_FILES_STACK
    ${PROJECT_TEST_DIR}/stack/*.cpp
)

file(GLOB TEST_FILES_QUEUE
    ${PROJECT_TEST_DIR}/queue/*.cpp
)

# Set executables
add_executable(cpp-stlcontainer_unittests_vector unit_tests.cpp ${TEST_FILES_VECTOR})
add_executable(cpp-stlcontainer_unittests_string unit_tests.cpp ${TEST_FILES_STRING})
add_executable(cpp-stlcontainer_unittests_stack unit_tests.cpp ${TEST_FILES_STACK})
add_executable(cpp-stlcontainer_unittests_queue unit_tests.cpp ${TEST_FILES_QUEUE})

# Link against downloaded + generated library gtest_main
target_link_libraries(cpp-stlcontainer_unittests_vector gtest_main pthread)
target_link_libraries(cpp-stlcontainer_unittests_string gtest_main pthread)
target_link_libraries(cpp-stlcontainer_unittests_stack gtest_main pthread)
target_link_libraries(cpp-stlcontainer_unittests_queue gtest_main pthread)

# Add tests
add_test(
    cpp-stlcontainer_unittests_vector
    unit
    COMMAND
    ${CMAKE_BINARY_DIR}/${CMAKE_INSTALL_BINDIR/cpp-stlcontainer_unittests_vector}
)

add_test(
    cpp-stlcontainer_unittests_string
    unit
    COMMAND
    ${CMAKE_BINARY_DIR}/${CMAKE_INSTALL_BINDIR/cpp-stlcontainer_unittests_string}
)

add_test(
    cpp-stlcontainer_unittests_stack
    unit
    COMMAND
    ${CMAKE_BINARY_DIR}/${CMAKE_INSTALL_BINDIR/cpp-stlcontainer_unittests_stack}
)

add_test(
    cpp-stlcontainer_unittests_queue
    unit
    COMMAND
    ${CMAKE_BINARY_DIR}/${CMAKE_INSTALL_BINDIR/cpp-stlcontainer_unittests_queue}
)

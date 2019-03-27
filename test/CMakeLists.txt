include(${PROJECT_SOURCE_DIR}/cmake/googletest-download-macro.cmake)

# Call macro from googletest-macro.cmake
# download module path, download root path
download_googletest(
    ${PROJECT_SOURCE_DIR}/cmake
    ${PROJECT_SOURCE_DIR}/googletest
)

# Get all test files
set(PROJECT_TEST_DIR ${PROJECT_SOURCE_DIR}/test)
file(GLOB TEST_FILES 
        ${PROJECT_TEST_DIR}/string/*.cpp
)

# Set executables
add_executable(cpp-stlcontainer_unittests unit_tests.cpp ${TEST_FILES})

# Link against downloaded + generated library gtest_main
target_link_libraries(cpp-stlcontainer_unittests gtest_main pthread)
# target_link_libraries(cpp-stlcontainer_unittests gtest_main cpp-container pthread)  Do we need to link against main project?

# Add tests
add_test(
    NAME
    unit
    COMMAND
    ${CMAKE_BINARY_DIR}/${CMAKE_INSTALL_BINDIR/cpp-stlcontainer_unittests}
)
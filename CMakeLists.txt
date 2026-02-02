cmake_minimum_required(VERSION "3.12")
project("sidemade")

# Make cmake modules visible to CMake
list (APPEND CMAKE_MODULE_PATH "${PROJECT_SOURCE_DIR}/cmake")

find_package(Eigen3 REQUIRED)
find_package(yaml-cpp REQUIRED)

file(GLOB_RECURSE SRC_FILES CONFIGURE_DEPENDS src/*.cpp)
list(REMOVE_ITEM SRC_FILES "${PROJECT_SOURCE_DIR}/src/main.cpp")

add_executable("${PROJECT_NAME}" "${SRC_FILES}" src/main.cpp)

set_property(TARGET ${PROJECT_NAME} PROPERTY CXX_STANDARD 11)

target_link_libraries("${PROJECT_NAME}" PRIVATE Eigen3::Eigen yaml-cpp)

#---- UNIT TESTS ----

include(CTest)

find_package(Boost 1.71 REQUIRED unit_test_framework)

file(GLOB_RECURSE TEST_FILES CONFIGURE_DEPENDS tests/*.cpp)

# CHANGED: Removed "tests/test_matrixIO.cpp" because it is already inside TEST_FILES
add_executable(testsidemade "${TEST_FILES}" "${SRC_FILES}")

target_include_directories(testsidemade PRIVATE ${PROJECT_SOURCE_DIR}/src)

# CHANGED: Added yaml-cpp because SRC_FILES depend on it
target_link_libraries(testsidemade 
    Boost::unit_test_framework 
    Eigen3::Eigen
    yaml-cpp
)

# Existing tests
add_test(NAME "MatrixSolverTests" COMMAND ${CMAKE_CURRENT_BINARY_DIR}/testsidemade --run_test=MatrixSolverTests/*)
add_test(NAME "ConfigurationTests" COMMAND ${CMAKE_CURRENT_BINARY_DIR}/testsidemade --run_test=ConfigurationTests/* WORKING_DIRECTORY ${PROJECT_SOURCE_DIR}/tests)

# OPTIONAL: Register the new test suite
add_test(NAME "matrixIO_tests" COMMAND ${CMAKE_CURRENT_BINARY_DIR}/testsidemade --run_test=matrixIO_tests/*)
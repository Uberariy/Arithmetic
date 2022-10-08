cmake_minimum_required(VERSION 3.16)
project(arithmath)

set(CMAKE_CXX_STANDARD 20)

include(FetchContent)
FetchContent_Declare(
        googletest
        # Specify the commit you depend on and update it regularly.
        URL https://github.com/google/googletest/archive/5376968f6948923e2411081fd9372e71a59d8e77.zip
)
# For Windows: Prevent overriding the parent project's compiler/linker settings
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

set(exceptions lib/except/exceptions.hpp)
set(Rational_number lib/Rational_number.hpp lib/Rational_number.cpp)
set(Matrix lib/Matrix.hpp lib/Matrix.cpp)

add_library(arithmath ${Rational_number} ${Matrix} ${exceptions})

add_executable(test lib/Matrix.cpp lib/Matrix_coords.hpp tmptest.cpp)
target_link_libraries(test arithmath)
target_link_libraries(test gtest_main)
add_test(NAME test COMMAND test)

add_executable(Rational_number_test lib/Rational_number.cpp lib/Rational_number.hpp lib/test/Rational_number_test.cpp)
target_link_libraries(Rational_number_test arithmath)
target_link_libraries(Rational_number_test gtest_main)
add_test(NAME Rational_number_test COMMAND Rational_number_test)

add_executable(Matrix_test lib/Matrix.hpp lib/Matrix.cpp lib/test/Matrix_test.cpp)
target_link_libraries(Matrix_test arithmath)
target_link_libraries(Matrix_test gtest_main)
add_test(NAME Matrix_test COMMAND Matrix_test)
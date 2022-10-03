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

add_executable(arithmath lib/Rational_number.cpp lib/Rational_number.hpp tmptest.cpp)

add_executable(Rational_number_test lib/Rational_number.cpp lib/Rational_number.hpp lib/test/Rational_number_test.cpp)
target_link_libraries(Rational_number_test gtest_main)
add_test(NAME Rational_number_constructor_test COMMAND Rational_number_constructor_test)
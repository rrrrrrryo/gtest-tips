cmake_minimum_required(VERSION 3.28)
project(gtest_sample VERSION 0.1.0 LANGUAGES C CXX)

include(FetchContent)
FetchContent_Declare(
  googletest
  # Specify the commit you depend on and update it regularly.
  URL https://github.com/google/googletest/archive/5376968f6948923e2411081fd9372e71a59d8e77.zip
)
# For Windows: Prevent overriding the parent project's compiler/linker settings
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

# Now simply link against gtest or gtest_main as needed. Eg
add_executable(test_sample test_sample.cpp sample_communicator.cpp)
set_property(TARGET test_sample PROPERTY CXX_STANDARD 20)


target_link_libraries(test_sample gtest_main)
target_link_libraries(test_sample gmock_main)
target_include_directories(
  test_sample PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/include
)

enable_testing()

cmake_minimum_required(VERSION 3.14)
project(sample)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_FLAGS "-Wall -Wextra -pthread")
set(CMAKE_CXX_FLAGS_DEBUG "-O0 -g3 -ggdb")
set(CMAKE_CXX_FLAGS_RELEASE "-O3")
set(CMAKE_SKIP_INSTALL_RULES True)

include(FetchContent)
FetchContent_Declare(
    googletest
    URL https://github.com/google/googletest/archive/609281088cfefc76f9d0ce82e1ff6c30cc3591e5.zip
)
# For Windows: Prevent overriding the parent project's compiler/linker settings
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

enable_testing()

file(GLOB_RECURSE SRC_FILES src/*.cpp)
add_subdirectory(samples)
add_executable(
  app 
  ${SRC_FILES}
  tests.cpp)
target_link_libraries(
    app
    gtest_main
)
target_include_directories(app PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/src/include)

include(GoogleTest)
gtest_discover_tests(app)

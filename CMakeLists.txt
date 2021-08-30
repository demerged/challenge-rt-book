cmake_minimum_required(VERSION 3.14)
project(sample)

# GoogleTest requires at least C++11
set(CMAKE_CXX_STANDARD 17)

include(FetchContent)
FetchContent_Declare(
    googletest
    URL https://github.com/google/googletest/archive/609281088cfefc76f9d0ce82e1ff6c30cc3591e5.zip
)
# For Windows: Prevent overriding the parent project's compiler/linker settings
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

enable_testing()

add_executable(
  app 
  Camera.cpp
  Checker_pattern.cpp
  Computation.cpp
  Cube.cpp
  Experimental_pattern.cpp
  Gradient_pattern.cpp
  Intersection.cpp
  Light.cpp
  Material.cpp
  Matrix.cpp
  Pattern.cpp
  Plane.cpp
  Ray.cpp
  Ring_pattern.cpp
  rt.cpp
  Shape.cpp
  Sphere.cpp
  Stripe_pattern.cpp
  World.cpp
  basic_tests.cpp)
target_link_libraries(
    app
    gtest_main
)

include(GoogleTest)
gtest_discover_tests(app)

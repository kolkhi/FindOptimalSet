# CMakeList.txt : Top-level CMake project file, do global configuration
# and include sub-projects here.
#
cmake_minimum_required (VERSION 3.8)

set(CMAKE_CXX_STANDARD 17)
set(Boost_USE_STATIC_LIBS OFF)
set(BOOST_ROOT "D:\\Dev\\boost_1_78_0")

project ("FindOptimalSet")

# Include sub-projects.
add_subdirectory ("FindOptimalSet")

enable_testing()
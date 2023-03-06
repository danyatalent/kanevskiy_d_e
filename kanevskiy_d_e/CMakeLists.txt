cmake_minimum_required (VERSION 3.8)
project ("kanevskiy_d_e")
find_package(doctest REQUIRED)
set_property(GLOBAL PROPERTY USE_FOLDERS ON)
set_property(GLOBAL PROPERTY PREDEFINED_TARGETS_FOLDER "cmake")

set(CMAKE_VERBOSE_MAKEFILE True)
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED True) 
enable_testing()

add_subdirectory(prj.lab)
add_subdirectory(prj.test)

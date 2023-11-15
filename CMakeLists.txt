# CMakeList.txt : Top-level CMake project file, do global configuration
# and include sub-projects here.
#
cmake_minimum_required (VERSION 3.15)

project("santa-challenge"
        VERSION 1.0
        DESCRIPTION "Help Santa deliver his packages.")

# specify the C++ standard
set(CMAKE_CXX_STANDARD 20) 
set(CMAKE_CXX_STANDARD_REQUIRED True)
set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -D_DEBUG")
if(NOT WIN32)
	set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -pthread")	# pthread is needed
endif()

# Include sub-projects.
add_subdirectory(source)
add_subdirectory(unittests)
# add_subdirectory(lib)


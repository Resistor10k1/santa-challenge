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
if(NOT WIN32)
	set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -pthread")	# pthread is needed
endif()

message(STATUS "C compiler is: ${CMAKE_C_COMPILER}")
message(STATUS "CXX compiler is: ${CMAKE_CXX_COMPILER}")
message(STATUS "CXX standard is: ${CMAKE_CXX_STANDARD}")

# Main executable ===============================================
message(STATUS "Prepare build of main app...")

# Debug executable ...
# set(CMAKE_BUILD_TYPE Debug)
# set(compile_options -O0)
# message(STATUS "Build config: ${CMAKE_BUILD_TYPE}")
# add_executable("${PROJECT_NAME}_d")
# add_subdirectory(source)
# add_compile_options(${compile_options})
# message(STATUS "main compile options: ${compile_options}")
# find_package(OpenMP REQUIRED)
# target_link_libraries("${PROJECT_NAME}_d" PRIVATE OpenMP::OpenMP_CXX)

# Release executable ...
set(CMAKE_BUILD_TYPE Release)
set(compile_options -O3)
message(STATUS "Build config: ${CMAKE_BUILD_TYPE}")
add_executable(${PROJECT_NAME})
add_subdirectory(source)
add_compile_options(${compile_options})

if(${EVAL_MAGIC_NUMBERS} STREQUAL "true")
        target_compile_definitions(${PROJECT_NAME} PRIVATE EVAL_MAGIC_NUMBERS)
endif()

message(STATUS "main compile options: ${compile_options}")
find_package(OpenMP REQUIRED)
target_link_libraries(${PROJECT_NAME} PRIVATE OpenMP::OpenMP_CXX)


# Executable with tests ===============================================
message(STATUS "Prepare unittest...")

# for google-test
#DOWNLOAD_EXTRACT_TIMESTAMP true
include(FetchContent)
FetchContent_Declare(
googletest
# Specify the commit you depend on and update it regularly.
URL https://github.com/google/googletest/archive/837f2229a905f44678fd6dc9af83f9a9f08e4a8f.zip
)
# For Windows: Prevent overriding the parent project's compiler/linker settings
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

set(CMAKE_BUILD_TYPE Debug)
set(compile_options -O0)

message(STATUS "Build config: ${CMAKE_BUILD_TYPE}")
message(STATUS "tests compile options: ${compile_options}")

add_executable(santaChallengeTest)
add_subdirectory(unittests)
add_compile_options(${compile_options})
add_test(NAME SantaChallenge_test COMMAND ./santaChallengeTest)

# Enable testing in CI pipeline
enable_testing()


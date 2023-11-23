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

if("${SOURCE}" STREQUAL "main")
        message(STATUS "Prepare build of main app...")
        message(STATUS "Build config: ${CMAKE_BUILD_TYPE}")
        # add_executable(${PROJECT_NAME})
        # target_sources(${PROJECT_NAME}
        #         PRIVATE
        #                 main.cpp
        # )
        add_subdirectory(source)

        if("${CMAKE_BUILD_TYPE}" STREQUAL "Release")
                message(STATUS "Compile options -O3")
                add_compile_options(-O3)
        else()
                message(STATUS "Compile options -O0")
                add_compile_options(-O0)
        endif()

        find_package(OpenMP REQUIRED)
        target_link_libraries(${PROJECT_NAME} PRIVATE OpenMP::OpenMP_CXX)
else()
        message(STATUS "Prepare unittest...")
        message(STATUS "Build config: ${CMAKE_BUILD_TYPE}")

        set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -D_DEBUG")
        add_compile_options(-O0)

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

# Executable with math tests ===============================================

        file(GLOB test_targets
                "${PROJECT_SOURCE_DIR}/source/misc.cpp"
                "${PROJECT_SOURCE_DIR}/source/Gift.cpp"
        )

        add_executable(santaChallengeTest)
        target_sources(santaChallengeTest
                PRIVATE
                        ${test_targets}
                        unittests/unittest_misc.cpp
                        unittests/unittest_Gift.cpp
        )
        target_include_directories(santaChallengeTest PRIVATE "${PROJECT_SOURCE_DIR}/include")
        target_link_libraries(santaChallengeTest PRIVATE gtest_main)
        add_test(NAME SantaChallenge_test COMMAND ./santaChallengeTest)
# Executable with math tests ===============================================

    # Enable testing in CI pipeline
	enable_testing()
endif()


# CMakeList.txt : CMake project for CircuitAnalyzer, include source and define
# project specific logic here.
#
cmake_minimum_required (VERSION 3.15)

file(GLOB test_targets
        "${PROJECT_SOURCE_DIR}/source/misc.cpp"
        "${PROJECT_SOURCE_DIR}/source/Gift.cpp"
        "${PROJECT_SOURCE_DIR}/source/Santa.cpp"
        "${PROJECT_SOURCE_DIR}/source/TripManager.cpp"
)

set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -D_DEBUG")
target_sources(santaChallengeTest
        PRIVATE
                ${test_targets}
                unittest_misc.cpp
                unittest_Gift.cpp
                unittest_Santa.cpp
)
target_include_directories(santaChallengeTest PRIVATE "${PROJECT_SOURCE_DIR}/include")
target_link_libraries(santaChallengeTest PRIVATE gtest_main)
# add_test(NAME SantaChallenge_test COMMAND ./santaChallengeTest)

# # Enable testing in CI pipeline
# enable_testing()

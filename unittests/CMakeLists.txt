# CMakeList.txt : CMake project for CircuitAnalyzer, include source and define
# project specific logic here.
#
cmake_minimum_required (VERSION 3.15)

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

file(GLOB test_targets
          #"${PROJECT_SOURCE_DIR}/source/main.cpp"
          "${PROJECT_SOURCE_DIR}/source/Module.cpp")

add_executable(santaChallengeTest)
target_sources(santaChallengeTest
        PRIVATE
                ${test_targets}
                unittest_Module.cpp
)
target_include_directories(santaChallengeTest PRIVATE "${PROJECT_SOURCE_DIR}/include")
# Now simply link against gtest or gtest_main as needed.
target_link_libraries(santaChallengeTest PRIVATE gtest_main)
add_test(NAME cppTemplate_test COMMAND ./unittests/santaChallengeTest)

enable_testing()

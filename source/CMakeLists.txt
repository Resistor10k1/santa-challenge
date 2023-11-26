# CMakeList.txt : CMake project for cppTemplate, include source and define
# project specific logic here.
#
cmake_minimum_required (VERSION 3.15)

target_sources(${PROJECT_NAME}
        PRIVATE
                main.cpp
                misc.cpp
                Gift.cpp
                TripManager.cpp
                Santa.cpp
)
target_include_directories(${PROJECT_NAME} PRIVATE "${PROJECT_SOURCE_DIR}/include")

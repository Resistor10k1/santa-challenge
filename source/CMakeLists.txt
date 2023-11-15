# CMakeList.txt : CMake project for cppTemplate, include source and define
# project specific logic here.
#
cmake_minimum_required (VERSION 3.15)

# Add source to this project's executable.
# add_executable(${TARGET_NAME} ${APP_SOURCES} ${COMMON_SOURCES})

# target_include_directories(${TARGET_NAME} PRIVATE "${PROJECT_SOURCE_DIR}/include")

# target_link_libraries(${TARGET_NAME} PRIVATE ${LIB})



# set(TEST_SOURCES 
#     "unittest_Module.cpp")

# set(LIB templateLib)

# set(TARGET_NAME testcppTemplate)

# file(GLOB test_targets
#           #"${PROJECT_SOURCE_DIR}/source/main.cpp"
#           "${PROJECT_SOURCE_DIR}/source/Module.cpp")

# Add source to this project's executable.
add_executable(${PROJECT_NAME})
target_sources(${PROJECT_NAME}
        PRIVATE
                main.cpp
                formulas.cpp
                Module.cpp
)
target_include_directories(${PROJECT_NAME} PRIVATE "${PROJECT_SOURCE_DIR}/include")
# target_link_libraries(${TARGET_NAME} ${LIB})

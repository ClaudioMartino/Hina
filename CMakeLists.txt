cmake_minimum_required(VERSION 3.8)
project(hina VERSION 0.1)

# Look for Open CV library (already built)
find_package(OpenCV REQUIRED)
include_directories(${OpenCV_INCLUDE_DIRS})

# Build alglib library
file(GLOB_RECURSE ALGLIB_SRC ${CMAKE_CURRENT_SOURCE_DIR}/src/alglib-cpp/*.cpp)
add_library(alglib STATIC ${ALGLIB_SRC})
target_include_directories(alglib PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/src/alglib-cpp)

# Build main
add_executable(hina ${CMAKE_CURRENT_SOURCE_DIR}/src/main.cpp ${CMAKE_CURRENT_SOURCE_DIR}/src/distance.cpp ${CMAKE_CURRENT_SOURCE_DIR}/src/clusters.cpp)

# Link libraries
target_link_libraries(hina PUBLIC ${OpenCV_LIBS})
target_link_libraries(hina PUBLIC alglib)

cmake_minimum_required(VERSION 3.8)
project(hina VERSION 0.1)

# Look for Open CV library
find_package(OpenCV REQUIRED)
include_directories(${OpenCV_INCLUDE_DIRS})

add_executable(hina
${CMAKE_CURRENT_SOURCE_DIR}/src/alglib-cpp/dataanalysis.cpp
${CMAKE_CURRENT_SOURCE_DIR}/src/alglib-cpp/ap.cpp
${CMAKE_CURRENT_SOURCE_DIR}/src/alglib-cpp/alglibinternal.cpp
${CMAKE_CURRENT_SOURCE_DIR}/src/alglib-cpp/alglibmisc.cpp
${CMAKE_CURRENT_SOURCE_DIR}/src/alglib-cpp/linalg.cpp
${CMAKE_CURRENT_SOURCE_DIR}/src/alglib-cpp/statistics.cpp
${CMAKE_CURRENT_SOURCE_DIR}/src/alglib-cpp/specialfunctions.cpp
${CMAKE_CURRENT_SOURCE_DIR}/src/alglib-cpp/optimization.cpp
${CMAKE_CURRENT_SOURCE_DIR}/src/alglib-cpp/solvers.cpp
${CMAKE_CURRENT_SOURCE_DIR}/src/alglib-cpp/fasttransforms.cpp
${CMAKE_CURRENT_SOURCE_DIR}/src/distance.cpp
${CMAKE_CURRENT_SOURCE_DIR}/src/clusters.cpp
${CMAKE_CURRENT_SOURCE_DIR}/src/main.cpp
)

target_include_directories(hina PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/src/alglib-cpp)

target_link_libraries(hina PUBLIC ${OpenCV_LIBS})

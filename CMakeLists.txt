cmake_minimum_required(VERSION 3.8)
project(hina VERSION 0.1)

# Look for Open CV library
find_package(OpenCV REQUIRED)
include_directories(${OpenCV_INCLUDE_DIRS})

add_executable(hina
${CMAKE_CURRENT_SOURCE_DIR}/src/alglib-cpp/src/dataanalysis.cpp
${CMAKE_CURRENT_SOURCE_DIR}/src/alglib-cpp/src/ap.cpp
${CMAKE_CURRENT_SOURCE_DIR}/src/alglib-cpp/src/alglibinternal.cpp
${CMAKE_CURRENT_SOURCE_DIR}/src/alglib-cpp/src/alglibmisc.cpp
${CMAKE_CURRENT_SOURCE_DIR}/src/alglib-cpp/src/linalg.cpp
${CMAKE_CURRENT_SOURCE_DIR}/src/alglib-cpp/src/statistics.cpp
${CMAKE_CURRENT_SOURCE_DIR}/src/alglib-cpp/src/specialfunctions.cpp
${CMAKE_CURRENT_SOURCE_DIR}/src/alglib-cpp/src/optimization.cpp
${CMAKE_CURRENT_SOURCE_DIR}/src/alglib-cpp/src/solvers.cpp
${CMAKE_CURRENT_SOURCE_DIR}/src/alglib-cpp/src/fasttransforms.cpp
${CMAKE_CURRENT_SOURCE_DIR}/src/distance.cpp
${CMAKE_CURRENT_SOURCE_DIR}/src/clusters.cpp
${CMAKE_CURRENT_SOURCE_DIR}/src/main.cpp
)

target_include_directories(hina PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/src/alglib-cpp/src)

target_link_libraries(hina PUBLIC ${OpenCV_LIBS})

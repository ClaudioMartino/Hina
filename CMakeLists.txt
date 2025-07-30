cmake_minimum_required(VERSION 3.8)
project(hina VERSION 0.1)

# Look for Open CV library
find_package(OpenCV REQUIRED)
include_directories(${OpenCV_INCLUDE_DIRS})

set(HINA_SOURCE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/src)
set(ALGLIB_SOURCE_DIR ${HINA_SOURCE_DIR}/alglib-cpp/src)

set(ALGLIB_SOURCES
  ${ALGLIB_SOURCE_DIR}/dataanalysis.cpp
  ${ALGLIB_SOURCE_DIR}/ap.cpp
  ${ALGLIB_SOURCE_DIR}/alglibinternal.cpp
  ${ALGLIB_SOURCE_DIR}/alglibmisc.cpp
  ${ALGLIB_SOURCE_DIR}/linalg.cpp
  ${ALGLIB_SOURCE_DIR}/statistics.cpp
  ${ALGLIB_SOURCE_DIR}/specialfunctions.cpp
  ${ALGLIB_SOURCE_DIR}/optimization.cpp
  ${ALGLIB_SOURCE_DIR}/solvers.cpp
  ${ALGLIB_SOURCE_DIR}/fasttransforms.cpp
)
set(HINA_SOURCES
  ${HINA_SOURCE_DIR}/distance.cpp
  ${HINA_SOURCE_DIR}/clusters.cpp
)

add_executable(hina ${ALGLIB_SOURCES} ${HINA_SOURCES} ${HINA_SOURCE_DIR}/main.cpp)
target_include_directories(hina PUBLIC ${ALGLIB_SOURCE_DIR})
target_link_libraries(hina PUBLIC ${OpenCV_LIBS})

add_executable(test ${ALGLIB_SOURCES} ${HINA_SOURCES} ${CMAKE_CURRENT_SOURCE_DIR}/testing/main.cpp)
target_include_directories(test PUBLIC ${ALGLIB_SOURCE_DIR} ${HINA_SOURCE_DIR})
target_link_libraries(test PUBLIC ${OpenCV_LIBS})



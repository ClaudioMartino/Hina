cmake_minimum_required(VERSION 3.19)
#SET(CMAKE_BUILD_TYPE Debug)
project(hina LANGUAGES CXX)

find_package(Qt6 6.5 REQUIRED COMPONENTS Core Widgets)

# Look for Open CV library
find_package(OpenCV REQUIRED)
include_directories(${OpenCV_INCLUDE_DIRS})

set(HINA_SOURCE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/../src)
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

qt_standard_project_setup()

qt_add_executable(hina
    WIN32 MACOSX_BUNDLE
    main.cpp
    hina_ui.cpp
    hina_ui.h
    hina_ui.ui
    ${ALGLIB_SOURCES} ${HINA_SOURCES}
    ../src/hina.h
)

target_link_libraries(hina
    PRIVATE
        Qt::Core
        Qt::Widgets
    PUBLIC
        ${OpenCV_LIBS})

target_include_directories(hina PUBLIC ${ALGLIB_SOURCE_DIR})

include(GNUInstallDirs)

install(TARGETS hina
    BUNDLE  DESTINATION .
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
)

qt_generate_deploy_app_script(
    TARGET hina
    OUTPUT_SCRIPT deploy_script
    NO_UNSUPPORTED_PLATFORM_ERROR
)
install(SCRIPT ${deploy_script})

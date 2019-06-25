#
# PROJECT
#
cmake_minimum_required (VERSION 3.14)
project (
  YahooFinanceCrawler
  VERSION 0.1.2
  LANGUAGES CXX
)

#
# GLOBAL VARIABLE
#
set (LONGLP_PROJECT_TARGET_NAME ${PROJECT_NAME})
set (LONGLP_PROJECT_DIR ${CMAKE_CURRENT_SOURCE_DIR})
set (LONGLP_PROJECT_SRC_DIR ${LONGLP_PROJECT_DIR}/src)
set (LONGLP_PROJECT_EXTERNAL_DIR ${LONGLP_PROJECT_DIR}/external)

#
# INCLUDE MODULES AND DEPENDENCIES
#
add_subdirectory (tools/cmake)
longlp_download_conan_cmake_if_not_exist (
  ${PROJECT_SOURCE_DIR}/conan.cmake ## need to pass absolute path
)
include (conan.cmake)
conan_cmake_run (
  CONANFILE conanfile.txt
  BASIC_SETUP
  CMAKE_TARGETS
  BUILD missing
)

longlp_desired_compile_options (LONGLP_COMPILE_OPTIONS)
longlp_desired_compile_features (LONGLP_COMPILE_FEATURES)
set (CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${LONGLP_PROJECT_DIR}/tools/cmake/")
find_package (HTMLCXX REQUIRED)
find_package (Qt5 REQUIRED COMPONENTS Core Gui Widgets WebEngine WebEngineCore WebEngineWidgets)
#
# SETUP TARGET
#
# Find includes in the build directories
set (CMAKE_INCLUDE_CURRENT_DIR ON)

# Turn on automatic invocation of the MOC, UIC & RCC
set (CMAKE_AUTOMOC ON)
set (CMAKE_AUTOUIC ON)
set (CMAKE_AUTORCC ON)

add_subdirectory (external)
add_subdirectory (src)


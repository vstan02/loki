cmake_minimum_required(VERSION 3.9)
project(
  Loki
  VERSION 0.0.0
  DESCRIPTION "A fast and easy to use virtual machine"
  LANGUAGES CXX
)

if(CMAKE_PROJECT_NAME STREQUAL PROJECT_NAME)
  set(CMAKE_CXX_STANDARD 17 CACHE STRING "The C++ standard to use")
  set(CMAKE_CXX_STANDARD_REQUIRED ON)
  set(CMAKE_CXX_EXTENSIONS OFF)

  file(TO_CMAKE_PATH "${PROJECT_BINARY_DIR}/CMakeLists.txt" LOC_PATH)
  if(EXISTS "${LOC_PATH}")
    message(FATAL_ERROR "You cannot build in a source directory (or any directory with a CMakeLists.txt file). Please make a build subdirectory. Feel free to remove CMakeCache.txt and CMakeFiles.")
  endif()

  include(CheckIPOSupported)
  check_ipo_supported(RESULT IPO_SUPPORTED)
  if(IPO_SUPPORTED)
    message(STATUS "Interprocedural optimization supported")
  else()
    message(STATUS "Interprocedural optimization not supported")
  endif()

  if(MSVC)
    add_compile_options(/W4 /WX)
  else()
    add_compile_options(-Wall -Wextra -pedantic -Werror)
  endif()
endif()

set(LOKI_PUBLIC_DIR "${CMAKE_CURRENT_SOURCE_DIR}/include")
set(LOKI_SOURCE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/src")
set(LOKI_DEMO_DIR "${CMAKE_CURRENT_SOURCE_DIR}/demo")

file(GLOB LOKI_PUBLIC "${LOKI_PUBLIC_DIR}/*.hpp" "${LOKI_PUBLIC_DIR}/**/*.hpp")
file(GLOB LOKI_SOURCES "${LOKI_SOURCE_DIR}/*.cpp" "${LOKI_SOURCE_DIR}/**/*.cpp")
file(GLOB LOKI_DEMO "${LOKI_DEMO_DIR}/*.cpp" "${LOKI_DEMO_DIR}/**/*.cpp")

add_library(loki "${LOKI_SOURCES}")
target_include_directories(loki PRIVATE "${LOKI_SOURCE_DIR}")
target_include_directories(loki PUBLIC "${LOKI_PUBLIC_DIR}")
if(IPO_SUPPORTED)
  set_target_properties(loki PROPERTIES INTERPROCEDURAL_OPTIMIZATION TRUE)
endif()

add_executable(demo "${LOKI_DEMO}")
target_include_directories(demo PRIVATE "${LOKI_PUBLIC_DIR}")
target_include_directories(demo PRIVATE "${LOKI_DEMO_DIR}")
target_link_libraries(demo loki)

install(FILES ${LOKI_PUBLIC} DESTINATION include/loki)
install(TARGETS loki ARCHIVE DESTINATION lib)

cmake_minimum_required (VERSION 3.0.2)

project(constexpr
  VERSION 0.2
  LANGUAGES CXX
)

# ---- Add dependencies via CPM ----

include(cmake/CPM.cmake)

# PackageProject.cmake will be used to make our target installable
CPMAddPackage(
  NAME PackageProject.cmake
  GITHUB_REPOSITORY TheLartians/PackageProject.cmake
  VERSION 1.2
)

# ---- Create library ----

add_library(constexpr INTERFACE)
target_include_directories(constexpr INTERFACE ${CMAKE_CURRENT_LIST_DIR}/include)
set_target_properties(constexpr PROPERTIES INTERFACE_COMPILE_FEATURES cxx_std_17)
target_compile_options(constexpr INTERFACE "$<$<BOOL:${MSVC}>:/permissive->")

# ---- Create an installable target ----
# this allows users to install and find the library via `find_package()`.

packageProject(
  NAME ${PROJECT_NAME}
  VERSION ${PROJECT_VERSION}
  BINARY_DIR ${PROJECT_BINARY_DIR}
  INCLUDE_DIR ${PROJECT_SOURCE_DIR}/include
  INCLUDE_DESTINATION include/${PROJECT_NAME}-${PROJECT_VERSION}
  DEPENDENCIES ""
)
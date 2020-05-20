cmake_minimum_required (VERSION 3.0.2)

project (constexprTests)

# ---- Options ----

option(ENABLE_TEST_COVERAGE "Enable test coverage" OFF)
option(TEST_INSTALLED_VERSION "Test the version found by find_package" OFF)

# ---- Dependencies ----

include(../cmake/CPM.cmake)

if (TEST_INSTALLED_VERSION)
  find_package(constexpr REQUIRED)
else()
  CPMAddPackage(
    NAME constexpr
    SOURCE_DIR ${CMAKE_CURRENT_LIST_DIR}/..
  )
endif()

CPMAddPackage(
  NAME Format.cmake
  GITHUB_REPOSITORY TheLartians/Format.cmake
  VERSION 1.3
)

option(USE_CLANG "build application with clang" ON)

# disabled legacy tests as they fail under the new configuration: cx_counter, cx_pcg32
add_executable (test_constexpr main cx_algorithm cx_array cx_guid cx_hash cx_math cx_numeric cx_strenc cx_typeid cx_utils)
target_link_libraries(test_constexpr constexpr)

if (CMAKE_CXX_COMPILER_ID MATCHES "Clang" OR CMAKE_CXX_COMPILER_ID MATCHES "GNU")
  target_compile_options(test_constexpr PUBLIC -Wall -pedantic -Wextra -Werror)
elseif(MSVC)
  target_compile_options(test_constexpr PUBLIC /W4 /WX)
  target_compile_definitions(test_constexpr PUBLIC DOCTEST_CONFIG_USE_STD_HEADERS)
endif()

# ---- code coverage ----

if (ENABLE_TEST_COVERAGE)
  target_compile_options(test_constexpr PUBLIC -O0 -g -fprofile-arcs -ftest-coverage)
  target_link_options(test_constexpr PUBLIC -fprofile-arcs -ftest-coverage)
endif()

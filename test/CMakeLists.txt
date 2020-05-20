cmake_minimum_required (VERSION 3.0.2)

project (constexpr)
add_subdirectory(${CMAKE_CURRENT_LIST_DIR}/.. ${CMAKE_CURRENT_BINARY_DIR}/_deps/constexpr)

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

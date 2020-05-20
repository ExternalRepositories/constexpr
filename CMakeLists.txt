cmake_minimum_required (VERSION 3.0.2)

project(constexpr)

add_library(constexpr INTERFACE)
target_include_directories(constexpr INTERFACE ${CMAKE_CURRENT_LIST_DIR}/include)
set_target_properties(constexpr PROPERTIES INTERFACE_COMPILE_FEATURES cxx_std_17)

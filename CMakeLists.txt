cmake_minimum_required(VERSION 3.8)

add_library(ObGL)
add_library(ObGL::ObGL ALIAS ObGL)
target_compile_features(ObGL PRIVATE cxx_std_11)

if (MSVC)
    target_compile_options(ObGL PRIVATE /WX /W4)
else()
    target_compile_options(ObGL PRIVATE -Werror -Wall -Wextra -Wpedantic -pedantic-errors -Wconversion -Wsign-conversion)
endif()

# ---Add glpp---
add_subdirectory(lib/glpp)
target_link_libraries(ObGL PUBLIC glpp::glpp)

# ---Add source files---
target_include_directories(ObGL INTERFACE include)
target_sources(ObGL PRIVATE
    src/dummy.cpp
)
cmake_minimum_required(VERSION 3.8)

set(WARNINGS_AS_ERRORS_FOR_GLPP_EXTENDED OFF CACHE BOOL "ON iff you want to treat warnings as errors")

add_library(glpp-extended)
add_library(glpp::extended ALIAS glpp-extended)
target_compile_features(glpp-extended PRIVATE cxx_std_17)

# Set warning level
if(MSVC)
    target_compile_options(glpp-extended PRIVATE /W4)
else()
    target_compile_options(glpp-extended PRIVATE -Wall -Wextra -Wpedantic -pedantic-errors -Wconversion -Wsign-conversion)
endif()

# Maybe enable warnings as errors
if(WARNINGS_AS_ERRORS_FOR_GLPP_EXTENDED)
    if(MSVC)
        target_compile_options(glpp-extended PRIVATE /WX)
    else()
        target_compile_options(glpp-extended PRIVATE -Werror)
    endif()
endif()

# ---Add glpp---
add_subdirectory(lib/glpp)
target_link_libraries(glpp-extended PUBLIC glpp::glpp)

# ---Add glm---
add_subdirectory(lib/glm)
target_link_libraries(glpp-extended PUBLIC glm)

# ---Add source files---
if(WARNINGS_AS_ERRORS_FOR_GLPP_EXTENDED)
    target_include_directories(glpp-extended INTERFACE include)
else()
    target_include_directories(glpp-extended SYSTEM INTERFACE include)
endif()

file(GLOB_RECURSE SRC_FILES CONFIGURE_DEPENDS src/*.cpp)
target_sources(glpp-extended PRIVATE ${SRC_FILES})
cmake_minimum_required(VERSION 3.8)

add_library(glpp-extended)
add_library(glpp::extended ALIAS glpp-extended)
target_compile_features(glpp-extended PRIVATE cxx_std_17)

if (MSVC)
    target_compile_options(glpp-extended PRIVATE /WX /W4)
else()
    target_compile_options(glpp-extended PRIVATE -Werror -Wall -Wextra -Wpedantic -pedantic-errors -Wconversion -Wsign-conversion)
endif()

# ---Add glpp---
add_subdirectory(lib/glpp)
target_link_libraries(glpp-extended PUBLIC glpp::glpp)
# ---Add glm--- 
add_subdirectory(lib/glm) 
target_link_libraries(glpp-extended PUBLIC glm) 

# ---Add source files---
target_include_directories(glpp-extended INTERFACE include)
target_sources(glpp-extended PRIVATE
    src/Program.cpp
    src/RenderTarget.cpp
    src/Texture1D.cpp
    src/Texture2D.cpp
)
# ObjectsGL

## Including

To add this library to your project, simply add these two lines to your *CMakeLists.txt*:
```cmake
add_subdirectory(path/to/glpp)
target_link_libraries(${PROJECT_NAME} PRIVATE glpp::extended)
```

Then include it as:
```cpp
#include <glpp/extended.hpp>
```
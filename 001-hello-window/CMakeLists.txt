# 设置CMake的最低版本要求
cmake_minimum_required(VERSION 3.10)
# 设置项目名称
project(HelloWorld)

# vcpkg集成
set(VCPKG_ROOT D:/software6/vcpkg/)
set(CMAKE_TOOLCHAIN_FILE ${VCPKG_ROOT}/scripts/buildsystems/vcpkg.cmake)
set(CMAKE_PREFIX_PATH ${VCPKG_ROOT}/installed/x64-mingw-static/share)

# 查找所需的包
find_package(glad CONFIG REQUIRED)
find_package(glfw3 CONFIG REQUIRED)

# 添加可执行文件
add_executable(HelloWorld main.cpp)

# 链接所需的库
target_link_libraries(HelloWorld PRIVATE glad::glad glfw)

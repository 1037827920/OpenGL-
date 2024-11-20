# 设置CMake的最低版本要求
cmake_minimum_required(VERSION 3.10)
# 设置项目名称
project(HelloFactory)

# vcpkg集成, 这里要换成你自己的vcpkg工具链文件和共享库路径
set(VCPKG_ROOT D:/software6/vcpkg/)
set(CMAKE_TOOLCHAIN_FILE ${VCPKG_ROOT}/scripts/buildsystems/vcpkg.cmake)
set(CMAKE_PREFIX_PATH ${VCPKG_ROOT}/installed/x64-mingw-static/share)

# 查找所需的包
find_package(glad CONFIG REQUIRED)
find_package(glfw3 CONFIG REQUIRED)

# 搜索并收集utils文件夹下的所有源文件
file(GLOB UTILS "utils/*.cpp", "utils/*.h")

# 添加可执行文件（还要加入utils文件夹下的源文件）
add_executable(HelloFactory main.cpp ${UTILS})

# 链接所需的库
target_link_libraries(HelloFactory PRIVATE glad::glad glfw)
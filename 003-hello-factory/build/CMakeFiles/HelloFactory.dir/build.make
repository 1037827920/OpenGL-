# CMAKE generated file: DO NOT EDIT!
# Generated by "MinGW Makefiles" Generator, CMake Version 3.30

# Delete rule output on recipe failure.
.DELETE_ON_ERROR:

#=============================================================================
# Special targets provided by cmake.

# Disable implicit rules so canonical targets will work.
.SUFFIXES:

# Disable VCS-based implicit rules.
% : %,v

# Disable VCS-based implicit rules.
% : RCS/%

# Disable VCS-based implicit rules.
% : RCS/%,v

# Disable VCS-based implicit rules.
% : SCCS/s.%

# Disable VCS-based implicit rules.
% : s.%

.SUFFIXES: .hpux_make_needs_suffix_list

# Command-line flag to silence nested $(MAKE).
$(VERBOSE)MAKESILENT = -s

#Suppress display of executed commands.
$(VERBOSE).SILENT:

# A target that is always out of date.
cmake_force:
.PHONY : cmake_force

#=============================================================================
# Set environment variables for the build.

SHELL = cmd.exe

# The CMake executable.
CMAKE_COMMAND = D:\software6\CMake\bin\cmake.exe

# The command to remove a file.
RM = D:\software6\CMake\bin\cmake.exe -E rm -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = D:\Code\computer-graphic\Practice\003-hello-factory

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = D:\Code\computer-graphic\Practice\003-hello-factory\build

# Include any dependencies generated for this target.
include CMakeFiles/HelloFactory.dir/depend.make
# Include any dependencies generated by the compiler for this target.
include CMakeFiles/HelloFactory.dir/compiler_depend.make

# Include the progress variables for this target.
include CMakeFiles/HelloFactory.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/HelloFactory.dir/flags.make

CMakeFiles/HelloFactory.dir/main.cpp.obj: CMakeFiles/HelloFactory.dir/flags.make
CMakeFiles/HelloFactory.dir/main.cpp.obj: CMakeFiles/HelloFactory.dir/includes_CXX.rsp
CMakeFiles/HelloFactory.dir/main.cpp.obj: D:/Code/computer-graphic/Practice/003-hello-factory/main.cpp
CMakeFiles/HelloFactory.dir/main.cpp.obj: CMakeFiles/HelloFactory.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir=D:\Code\computer-graphic\Practice\003-hello-factory\build\CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/HelloFactory.dir/main.cpp.obj"
	D:\software6\msys2\mingw64\bin\g++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/HelloFactory.dir/main.cpp.obj -MF CMakeFiles\HelloFactory.dir\main.cpp.obj.d -o CMakeFiles\HelloFactory.dir\main.cpp.obj -c D:\Code\computer-graphic\Practice\003-hello-factory\main.cpp

CMakeFiles/HelloFactory.dir/main.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing CXX source to CMakeFiles/HelloFactory.dir/main.cpp.i"
	D:\software6\msys2\mingw64\bin\g++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E D:\Code\computer-graphic\Practice\003-hello-factory\main.cpp > CMakeFiles\HelloFactory.dir\main.cpp.i

CMakeFiles/HelloFactory.dir/main.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling CXX source to assembly CMakeFiles/HelloFactory.dir/main.cpp.s"
	D:\software6\msys2\mingw64\bin\g++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S D:\Code\computer-graphic\Practice\003-hello-factory\main.cpp -o CMakeFiles\HelloFactory.dir\main.cpp.s

CMakeFiles/HelloFactory.dir/utils/TriangleModel.cpp.obj: CMakeFiles/HelloFactory.dir/flags.make
CMakeFiles/HelloFactory.dir/utils/TriangleModel.cpp.obj: CMakeFiles/HelloFactory.dir/includes_CXX.rsp
CMakeFiles/HelloFactory.dir/utils/TriangleModel.cpp.obj: D:/Code/computer-graphic/Practice/003-hello-factory/utils/TriangleModel.cpp
CMakeFiles/HelloFactory.dir/utils/TriangleModel.cpp.obj: CMakeFiles/HelloFactory.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir=D:\Code\computer-graphic\Practice\003-hello-factory\build\CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building CXX object CMakeFiles/HelloFactory.dir/utils/TriangleModel.cpp.obj"
	D:\software6\msys2\mingw64\bin\g++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/HelloFactory.dir/utils/TriangleModel.cpp.obj -MF CMakeFiles\HelloFactory.dir\utils\TriangleModel.cpp.obj.d -o CMakeFiles\HelloFactory.dir\utils\TriangleModel.cpp.obj -c D:\Code\computer-graphic\Practice\003-hello-factory\utils\TriangleModel.cpp

CMakeFiles/HelloFactory.dir/utils/TriangleModel.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing CXX source to CMakeFiles/HelloFactory.dir/utils/TriangleModel.cpp.i"
	D:\software6\msys2\mingw64\bin\g++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E D:\Code\computer-graphic\Practice\003-hello-factory\utils\TriangleModel.cpp > CMakeFiles\HelloFactory.dir\utils\TriangleModel.cpp.i

CMakeFiles/HelloFactory.dir/utils/TriangleModel.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling CXX source to assembly CMakeFiles/HelloFactory.dir/utils/TriangleModel.cpp.s"
	D:\software6\msys2\mingw64\bin\g++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S D:\Code\computer-graphic\Practice\003-hello-factory\utils\TriangleModel.cpp -o CMakeFiles\HelloFactory.dir\utils\TriangleModel.cpp.s

# Object files for target HelloFactory
HelloFactory_OBJECTS = \
"CMakeFiles/HelloFactory.dir/main.cpp.obj" \
"CMakeFiles/HelloFactory.dir/utils/TriangleModel.cpp.obj"

# External object files for target HelloFactory
HelloFactory_EXTERNAL_OBJECTS =

HelloFactory.exe: CMakeFiles/HelloFactory.dir/main.cpp.obj
HelloFactory.exe: CMakeFiles/HelloFactory.dir/utils/TriangleModel.cpp.obj
HelloFactory.exe: CMakeFiles/HelloFactory.dir/build.make
HelloFactory.exe: D:/software6/vcpkg/installed/x64-mingw-static/debug/lib/libglad.a
HelloFactory.exe: D:/software6/vcpkg/installed/x64-mingw-static/debug/lib/libglfw3.a
HelloFactory.exe: CMakeFiles/HelloFactory.dir/linkLibs.rsp
HelloFactory.exe: CMakeFiles/HelloFactory.dir/objects1.rsp
HelloFactory.exe: CMakeFiles/HelloFactory.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --bold --progress-dir=D:\Code\computer-graphic\Practice\003-hello-factory\build\CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Linking CXX executable HelloFactory.exe"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles\HelloFactory.dir\link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/HelloFactory.dir/build: HelloFactory.exe
.PHONY : CMakeFiles/HelloFactory.dir/build

CMakeFiles/HelloFactory.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles\HelloFactory.dir\cmake_clean.cmake
.PHONY : CMakeFiles/HelloFactory.dir/clean

CMakeFiles/HelloFactory.dir/depend:
	$(CMAKE_COMMAND) -E cmake_depends "MinGW Makefiles" D:\Code\computer-graphic\Practice\003-hello-factory D:\Code\computer-graphic\Practice\003-hello-factory D:\Code\computer-graphic\Practice\003-hello-factory\build D:\Code\computer-graphic\Practice\003-hello-factory\build D:\Code\computer-graphic\Practice\003-hello-factory\build\CMakeFiles\HelloFactory.dir\DependInfo.cmake "--color=$(COLOR)"
.PHONY : CMakeFiles/HelloFactory.dir/depend


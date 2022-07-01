# OpenGl C++ application

Examples how to use openGL API's.

      - Basic Triangle.
      - Orthographic projection - NDC space. (with viewing transformations)
      - Orthographic projection - Non NDC space.
      - Model Transformations.

## SetUp

- Install [VS Code](https://code.visualstudio.com/)
- Install [CMake](https://cmake.org/) and [Ninja](https://ninja-build.org/)
- Install [Calng](https://releases.llvm.org/download.html) to build as desktop executable.
- Install Extensions
      Microsoft c++  
      Cmake
      CodeLLDB - to debug in windows Clang c++

## Build

Open VSCode  
From VS Code - Run following tasks from *Terminal* menu

1) Generate Configuration - To generate project files in Build folder.  
2) Build - Produces executable in Build directory.

To generate nuget package

```cmd
cd build
cmake --install .
cpack
```

## Dependencies

GLM,GLAD and GLFW.  
While configuring/building Cmake script automatically downloads the required packages from github.

## Execute

Run following command from build directory.  

```cmd
   ./demoTutorials.exe
```

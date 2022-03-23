# OpenGl C++ application
Orthographic projection to configure top-left corner as orizon(0, 0).  
and size as windows size. This makes developer to use coordinates in integers ove flosting point numbers.

Check tutorial on [VAO,VBO](https://www.youtube.com/watch?v=hrZbyd4qPnk)  
 and [Projection](https://www.youtube.com/watch?v=YfaSzg6XG6A) another way to make NDC coordinates to visible by translating.  
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

1) Generate WinBuild - To generate project files in Build folder.  
2) Build - Produces executable in Build directory.

## Execute

Run follwoing command in command promt from build directory.  

```cmd
   ./helloTriangle.exe
```

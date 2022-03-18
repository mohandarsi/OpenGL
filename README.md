# OpenGL

## What is OpenGL?  

[OpenGL](https://www.khronos.org/opengl/wiki/FAQ#What_is_OpenGL.3F) is the name for the specification that describes the behavior of a rasterization-based rendering system.  
It defines the API through which a client application can control this system.  
Hardware vendors, the people who make GPUs, are responsible for writing implementations of the OpenGL rendering system.Their implementations, commonly called "drivers", translate OpenGL API commands into GPU commands.  **If a particular piece of hardware is unable to implement all of the OpenGL specification via hardware, the hardware vendor must still provide this functionality, typically via a software-based implementation of the features missing from hardware.**

OpenGL doesn't have any source code. GL is a specification which can be found on this [website](https://www.khronos.org/opengl/wiki/Main_Page). It describes the interface the programmer uses and expected behavior. OpenGL is an open specification.  

Unlike directX, OpenGL is cross platform. OpenGL's design originated during the early days of computer graphics and was designed as a state machine, so its interface differs greatly from modern graphics APIs. DirectX 11, while closer to modern GPU architectures than OpenGL, tries to be easy for developers by delegating tasks that Vulkan, DirectX 12, and Metal currently leave the developer responsible for to the driver

OpenGL samples

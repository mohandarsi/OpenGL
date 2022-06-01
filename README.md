# OpenGL

## What is OpenGL?  

[OpenGL](https://www.khronos.org/opengl/wiki/FAQ#What_is_OpenGL.3F) is the name for the specification that describes the behavior of a rasterization-based rendering system.  
It defines the API through which a client application can control this system.  
Hardware vendors, the people who make GPUs, are responsible for writing implementations of the OpenGL rendering system.Their implementations, commonly called "drivers", translate OpenGL API commands into GPU commands.  **If a particular piece of hardware is unable to implement all of the OpenGL specification via hardware, the hardware vendor must still provide this functionality, typically via a software-based implementation of the features missing from hardware.**

OpenGL doesn't have any source code. GL is a specification which can be found on this [website](https://www.khronos.org/opengl/wiki/Main_Page). It describes the interface the programmer uses and expected behavior. OpenGL is an open specification.  

Unlike directX, OpenGL is cross platform. OpenGL's design originated during the early days of computer graphics and was designed as a state machine, so its interface differs greatly from modern graphics APIs. DirectX 11, while closer to modern GPU architectures than OpenGL, tries to be easy for developers by delegating tasks that Vulkan, DirectX 12, and Metal currently leave the developer responsible for to the driver.

### **Some important points to know**

1) OpenGL(GLM)/GLSL by default uses column major matrix's which can be efficient for cache locality. [Reference](https://www.scratchapixel.com/lessons/mathematics-physics-for-computer-graphics/geometry/row-major-vs-column-major-vector) . Due to this call order of matrix's are in the reverse of the order the transforms are applied: "take P, transform by T, transform by Rz, transform by Ry" is written as P′=Ry∗Rz∗T∗P.

2) By default(with out any transformation MVP), opengl can draw all vertices which are mapped to NDC (-1,1). If the vertices fall out of this range, program need to use transforamtion to make them visible in screen.  
   - In [Basic Triangle demo](https://github.com/mohandarsi/OpenGL/tree/master/helloTraingle) program uses NDC vertices. Hence we dont need any transformations *(projection matrix)*.
   - In [Orthographic Projection demo](https://github.com/mohandarsi/OpenGL/tree/master/orthographicProjection) uses non-NDC vertices for which we need to use transformations.  

3) OpenGL  doesn’t enforce either right or left handedness.  OpenGL (NDC) is a left-handed coordinate system *[Appendix D - WebGL/OpenGL: Left or Right Handed?  - WebGl Programming Guide]* when viewing volume is **not** specified opengl acts as LeftHanded (positive Z-Axis points into screen). When program specify viewing volume ( Projection matrix's with near < far) in glm::Ortho() OpenGL follows the right-handed coordinate system. Refer also [derivation](https://www.scratchapixel.com/lessons/3d-basic-rendering/perspective-and-orthographic-projection-matrix/orthographic-projection-matrix) on orthogonal matrix.
     - This can be demoed via [OrthographicProjection NDC](https://github.com/mohandarsi/OpenGL/blob/master/DemoTutorials/src/orthographicProjectionNDC.cpp).if OpenGL is right handed(Negative Z-Axis points into screen) , Blue traingle (Z= -0.1) should be front and Red traingle(Z= -0.5) should be back of Blue traingle. But this is not the case. The projection transformation (Changes the Z- direction via RH projection), brings the blue traingle to the front.
  
## How its different than OpenGLEs and WebGL  

**OpenGL** is a desktopcomputer-centric API (like Direct3D).  

**OpenGL for Embedded Systems (OpenGL ES or GLES)** is a subset of the OpenGL API for rendering 2D and 3D computer graphics designed for embedded systems like smartphones, tablet computers, video game consoles and PDAs. Android,IOS uses OpenGL ES.

**WebGL** (Short for Web Graphics Library) is a JavaScript API which is derived from OpenGL ES 2.0 which has less capabilities and is simpler to use. WebGL is also designed to run in a browser, and has therefore a few limitations more then OpenGL ES 2.0.

# Avataar.ai Graphics Engineer Interview Test

An OpenGL project showcasing PBR material with varying metallic and roughness values.

![Screenshot](/images/material_test.jpg "Screenshot")

## Features

- Physically Based Material using Micro-Facet BRDF
- Sphere selection with debug normal view on selection.

## Prerequisites

- Windows 11 22H2
- Microsoft Visual Studio 2022
    - MSVC v143 C++ Compiler
- Cmake 3.26 or greater

> NOTE: I have tested the project on the above configuration. It should compile on lower versions or different
> compilers. (Haven't tested it yet). But the platform should support `C++17` and `OpenGL 3.3`

## Installation and Usage

- Download zip or recursively clone from repository:

```commandline
git clone https://github.com/SurajShettigar/avataar_ge_test.git
```

- If using Cmake command line, use the following commands in the project root directory:

```commandline
cmake -G "Visual Studio 17 2022" -B "./build/debug" -S .
```

- Run `material_test` target.

```commandline
cmake --build "./build/debug" --target material_test
```

- Run the executable `material_test.exe` located in the `bin` or `Debug` or `Release` folder inside the `build`
  directory.

<p style="text-align: center;"><b>OR</b></p>

- Use Cmake GUI to generate Visual Studio 2022 solution or if using CLion, open the project directly with cmake
  toolchain set to Visual Studio.
- Once the VS project is generated, open it and build `material_test`.
  > NOTE: If you follow above steps, `Cmake` should copy `data` and `shaders` folder into the build directory (in the
  above example, it would be copied to `build\debug` folder). If you face an issue where those folders are not copied,
  copy it the build folder.

## Project Structure

- The material test scene source code is under `material_test` folder.
- `main.cpp` and `app.cpp` is the entry-point of the application.
- Material sphere grid is generated by the static function `getMaterialTestScene()` in `Scene` class.
- All the rendering logic is executed by `Renderer` object.
- There are two main shaders to show PBR material and normal shading. Shaders are located under `shaders` folder.
- `globals.hpp` has all the constants and pre-defined configurations.

## Third-party libraries used

- [glad](https://glad.dav1d.de/)
- [glfw](https://github.com/glfw/glfw/)
- [glm](https://github.com/g-truc/glm)
- [tinyobjloader](https://github.com/tinyobjloader/tinyobjloader)
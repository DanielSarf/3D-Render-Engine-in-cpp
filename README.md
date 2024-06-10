# 3D Render Engine in C++

## Description

**This started as my 2nd Semester project but my goal is to make this an open-source render engine for Blender that lets 3D artists create amazing art on low-end machines. This project is still in early development, you can see the roadmap below for my future plans for this project. Contributions are highly appreciated!**

## Features

- CPU Rendering
- Linux and Windows support
- Solid and gradient HDRI (Custom HDRI support coming soon!)
- Add Sphere objects
- Metalic and Diffuse Materials
- Custom resolution for image output, Start/End Frame, Number of Samples, Max Ray Bounces, and Focal Length
- Output images in .PPM and .BMP formats

## Compilation

To compile on Linux, use the following command:

```sh
g++ -g -O3 -ffast-math -march=native -funroll-loops -pthread -fopenmp Source.cpp Utilities.cpp Vector3.cpp Camera.cpp Color.cpp Material.cpp Object.cpp Scene.cpp RenderEngine.cpp Image.cpp Ray.cpp -o ${fileDirname}/3DRenderEngine.o
```

This command uses various optimization flags to ensure the render engine performs efficiently. It compiles multiple source files into an executable named `3DRenderEngine.o`.

## Running the Project on Windows

To run this project on Windows using Visual Studio, follow these steps:

1. **Create a New Project in Visual Studio**:

2. **Add Source Files**:
   - Right-click on the "Source Files" folder in Solution Explorer.
   - Select "Add" > "Existing Item..." and add all the `.cpp` files.

3. **Add Header Files**:
   - Right-click on the "Header Files" folder in Solution Explorer.
   - Select "Add" > "Existing Item..." and add all the `.h` files.

4. **Build and Run**:
   - Build the project by clicking "Build" > "Build Solution".
   - Run the project in Release mode.

## Hyperparameters

The following hyperparameters can be configured in the source code to adjust the rendering process:

- `WIDTH`: Width of the rendered image (default: 1920)
- `HEIGHT`: Height of the rendered image (default: 1080)
- `STARTFRAME`: The starting frame for rendering (default: 1)
- `ENDFRAME`: The ending frame for rendering (default: 1)
- `NUMBEROFSAMPLES`: Number of samples per pixel (default: 100)
- `DEPTH`: Depth of the rendering (default: 12)
- `FOCALLENGTH`: Focal length of the camera (default: 0.15f)

Also you can add and remove spheres! Look in Source.cpp for an example.

## Rendered Image Examples

Here are examples of images rendered using this Render Engine vs Blender Cycles:

**This Render Engine's Render**:
![Render Engine Render](Comparison/Render%20Engine%20Render.bmp)

**Blender Cycles Render**:
![Blender Render](Comparison/Blender%20Render.png)

## Roadmap

Here are the upcoming features and improvements planned for this project:

- Enable Vulkan support for GPU Rendering
- Add graphical user interface (GUI)
- Support for importing 3D Meshes
- Include more materials
- Implement various types of lights
- Add custom HDRI support
- Integration with Blender
- Implementation of the latest rendering technologies
- Implement some ideas I have for improving render time
- Optimized for performance on low-end machines
- And more...

## License

This project is licensed under the MIT License. See the [LICENSE](LICENSE) file for more details.

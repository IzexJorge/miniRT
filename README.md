
_This project has been created as part
of the 42 curriculum by jescuder and jose-jim._

# miniRT
My first RayTracer with MiniLibX

## Description
This project is about creating a program that renders an image of the scene received as input.
The scene is composed of 3D geometric objects, a camera, a light and an ambient lighting.
The ambient lighting makes sure objects are never completely in the dark, even if the light doesn't reach them.
The image is rendered using a ray tracing technique. For each pixel in the image, the program creates a ray from the camera and computes its intersections with the objects in the scene, determining the closest visible surface. At the intersection point, lighting calculations are performed using the surface normal and the light position to compute the final color. Additional rays are then cast toward the light source to check for intersecting geometry and determine whether the point lies in shadow.

## Instructions
To start using the program, first clone this repository into your machine with Git, or download it. This program is intended to run on Linux due to the MiniLibX dependency.
To compile the program, execute the command 'make' in your terminal. This will create the executable 'miniRT'.
The repository includes a folder 'scenes' with a set of different scenes, but you can create any scene you want, respecting the format detailed further below in these instructions.
To execute, use the following command format:
```
./miniRT <scene_path>
```
This example uses the scene 'scene1', which is included in the repository:
```
./miniRT scenes/scene1.rt
```
A scene file must have a .rt extension.
The format for scenes is the following (the indentation is not mandatory):
```
A					ratio					r,g,b
C	x,y,z	a,b,c	FOV
L	x,y,z			ratio

sp	x,y,z			diameter				r,g,b
pl	x,y,z	a,b,c							r,g,b
cy	x,y,z	a,b,c	diameter	height		r,g,b
```
Each line is an element, which type is determined by the first string and its attributes are defined by the rest of the information:
- A. The Ambient Lighting.
- C. The Camera.
- L. The Light.
- sp. A sphere.
- pl. A plane.
- cy. A cylinder.

There must be exactly one Ambient Lighting, one Camera and one Light.
There can be any number of spheres, planes or cylinders.
The order of the elements doesn't have any effect.
The order and presence of the attributes of each element is mandatory.
Coordinates (x,y,z), diameter and height have a range of [-10000.0, 10000.0].
Orientation vectors (a,b,c) **must be normalized** and their axis values have a range of [-1.0, 1.0].
Normalized means the vector length is exactly 1. The length formula is √(a² + b² + c²). The easiest way is to set one of the axis values to 1 and the rest to 0.
The Ambient Lighting and Light brightness intensity ratios have a range of [0.0, 1.0].
Colors (r,g,b) have a range of [0, 255].
The FOV (Field of View) has a range of [0, 180].
If the format is not respected, the program will show an error message that specifies what is wrong.

## Resources

AI has been used only to ask questions about certain technical mathematical aspects of the project, when in doubt while reading different resources about ray tracing and float number operations.

For the raytracer logic the following resources have been consulted, among others:

Ström, J., Åström, K., & Akenine-Möller, T. *(s.f.).* **_Immersive Linear Algebra_**.
https://immersivemath.com/ila/ch01_introduction/ch01.html

Buck, J. *(2019).* **_The Ray Tracer Challenge_**. Pragmatic Bookshelf.
https://books.out.csli.me/NonFiction/Programming/The%20Ray%20Tracer%20Challenge-Pragmatic%20Bookshelf%20%282019%29%20-%20Jamis%20Buck.pdf

Scratchapixel. *(s.f.).* **_The Foundations of 3D Rendering_**.
https://www.scratchapixel.com/index.html

Shirley, P. *(s.f.).* **_Ray Tracing in One Weekend_**.
https://raytracing.github.io

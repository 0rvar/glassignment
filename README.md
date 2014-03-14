# A3 - Walking in the air
This is the code for the third assignment of 
the course Computer Graphics and Visualization, given
on the spring term of 2014.

The program opens 3d models in the [off format](https://en.wikipedia.org/wiki/OFF_(file_format) and
permits keyboard interaction to modify the model-view transform of the model,
allowing for translation along the x and y axes, scaling and rotating around the z axis.

Move the camera with wasd and by moving the mouse while holding a mouse button.
Change the fov with the mouse-wheel.

## Compiling
The program requires Glut and Glew to compile, and is configured to be compiled with g++.

Compile with:

```make```

## Running
```./main [off-file]```

## Testing
Unit tests can be compiled and executed with make, and have no extra dependencies:

```
make test
```

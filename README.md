# A2 - Vertex rendering with projection
This is the code for the second assignment of 
the course Computer Graphics and Visualization, given
on the spring term of 2014.

The program opens 3d models in the [off format](https://en.wikipedia.org/wiki/OFF_(file_format) and
permits keyboard interaction to modify the model-view transform of the model,
allowing for translation along the x and y axes, scaling and rotating around the z axis.

A GUI allows for changing the perspective and camera position of the scene.

## Compiling
The program requires Glut and Glew to compile, and is configured to be compiled with g++.

Compile with:

```make```

## Running
```./main [off-file]```

## Usage
The following keyboard shortcuts are available in the program:

* **o**: Open a file
* **+|-**: Modify the transform according to the current mode:
* **t**: Enter translation mode
* **s**: Enter scaling mode
* **r**: Enter rotation mode

Additionally, the following shortcuts are avaiable:

* **&lt;up&gt;**: Translate y +
* **&lt;down&gt;**: Translate y -
* **&lt;right&gt;**: Translate x +
* **&lt;left&gt;**: Translate x -
* **&lt;S&gt;&lt;up&gt;**: Increase scale
* **&lt;S&gt;&lt;down&gt;**: Decrease scale
* **&lt;S&gt;&lt;left&gt;**: Increase rotation
* **&lt;S&gt;&lt;right&gt;**: Decrease rotation

## Testing
Unit tests can be compiled and executed with make, and have no extra dependencies:

```
make test
```

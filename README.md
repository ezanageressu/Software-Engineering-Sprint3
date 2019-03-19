# Hello World Window
This project prints "Hello World" in a new window using Qt. The project is originally developed for Linux OS and has been tested that it works on MacOS X.
## Required Packages
- GNU C++: [Download Here](https://gcc.gnu.org/install/)
- Qt: [Download Here](https://www.qt.io/download)
- CMake: [Download Here](https://cmake.org/install)
- Doxygen: [Download Here](https://sourceforge.net/projects/doxygen/)
## Possible Build Issues
* Make sure you have installed the relevant Qt libraries. Once the libraries have been install, ensure
that you have added them to the include path. This can be done by editting your .bashrc file.
```
$ sudo nano ~/.bashrc
```
Now add the following lines to the end of the file.
```
PATH=$PATH:location_of_Qt_libraries
export PATH
```
* If you encounter the build error message
```
cannot find -lGL
```
install the necessary libraries with the following command:
```
$ sudo apt-get install libgl1-mesa-dev
```

## Build Instructions
```
$ mkdir build
$ cd build
$ cmake .. && make
```
The executable is generated as "hello" in the "build" directory. To run enter:
```
$ ./hello
```

## Documentation Generation Instructions
```
$ doxygen docs/Doxyfile
```
The HTML and LaTeX formatted documentation can be found in "build" directory. To open it in your default browser, enter:
```
$ open html/index.html
```

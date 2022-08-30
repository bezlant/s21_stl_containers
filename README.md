# STL Containers

### Table of Contents
* [Introduction](#introduction)
* [Goals](#goals)
* [Build](#build)
* [Tests](#tests)

### Introduction

Implementation of C++ standard template library containers: *list, map, queue, set, stack and vector*. The library provides a full set of standard methods and attributes for element handling, container capacity checking and iteration. 

##### Each type of containers provides the user with the following methods:
- standard constructors (default constructor, copy constructor, move constructor, constructor with initialization list)
- methods for accessing container elements (e.g. accessing an element with the index i)
- methods for checking if a container is full (e.g. the number of elements in the container, check if the container is empty)
- methods for changing the container (removing and adding new elements, cleaning the container)
- methods for dealing with the container iterator.
### Goals

- [ ] Outline the project structure
- [ ] Integrate CMake
- [ ] Integrate Gtest
- [ ] List class
- [ ] Map class
- [ ] Queue class
- [ ] Set class
- [ ] Stack class
- [ ] Vector class

### Build

```
$ git clone https://github.com/bezlant/s21_stl_containers
$ cd s21_stl_containers
$ mkdir build && cd build 
$ cmake ..
$ make
```

### Tests
* Unit tests are implemented using [googletest](https://google.github.io/googletest/) & coverage report with [llvm-cov](https://llvm.org/docs/CommandGuide/llvm-cov.html)

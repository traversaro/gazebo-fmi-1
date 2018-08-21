# gazebo-fmi

[Functional Mock-up Interface (FMI)](https://fmi-standard.org/) import plugins for the [Gazebo Simulator](http://gazebosim.org/).

# Overview
- [About versioning](#about-versioning)
- [Background](#background)
- [Dependencies](#dependencies)
- [Build the plugins](#build-the-plugins)
- [Use the plugins](#use-the-plugins)
- [Test the plugins](#test-the-plugins)


# About versioning
The project is undergoing _heavy_ development: APIs may still be subject to changes, and some functionalities may be broken.


# Background
This repository contains plugins for the [Gazebo robotic simulator](http://gazebosim.org/) to enable
[co-simulation](https://en.wikipedia.org/wiki/Co-simulation) between the physics simulation of Gazebo
and simulation tools that support the [Functional Mock-up Interface (FMI)](https://fmi-standard.org/) standard.
At the moment, the report just contains a plugin that **import** Functional Mock-up Units (FMUs) for simulation of the actuator dynamics.

A good introductory paper to the co-simulation concept is available at https://arxiv.org/abs/1702.00686 .

# Dependencies
gazebo-fmi depends on
- [Gazebo](http://gazebosim.org/) - `version >= 7`
- [FMILibrary](https://jmodelica.org/) (see https://github.com/svn2github/FMILibrary for an updated GitHub mirror) - `version >= 2.0.3`

We recommend to install Gazebo as described  in [official documentation](http://gazebosim.org/tutorials?cat=install).
For FMILibrary, one option is to compile it as any CMake project and then add its installation prefix to [`CMAKE_PREFIX_PATH`](https://cmake.org/cmake/help/v3.10/variable/CMAKE_PREFIX_PATH.html).
See [CGold guide](https://cgold.readthedocs.io/en/latest/first-step.html) if you need some details on how to build a CMake project.

An easier option is provided by the gazebo-fmi repository which downloads and compiles the FMILibrary internally within its build folder using CMake's FetchContent option. This is performed when FMILibrary package is not already existing in the system or if the FMILibrary related environment variable (`FMILibrary_ROOT`) is not set, making gazebo-fmi unable to find FMILibrary package. To use this option, the CMake option `USES_SYSTEM_FMILIBRARY` should be set to `OFF`.

# Build the plugins
Use the following commands to build and install the plugin.

### Build
With `make` facilities:
```bash
$ git clone https://github.com/robotology-playground/gazebo-fmi
$ cd gazebo-fmi
$ mkdir build && cd build
$ cmake ..
$ make
$ [sudo] make install
```

With IDE build tool facilities:
```bash
$ git clone https://github.com/robotology-playground/gazebo-fmi
$ cd gazebo-fmi
$ mkdir build && cd build
$ cmake ..
$ cmake --build . --target ALL_BUILD --config Release
$ cmake --build . --target INSTALL --config Release
```

See [CGold guide](https://cgold.readthedocs.io/en/latest/first-step.html) if you need more details on how to build a CMake project.

# Use the plugins
See plugin-specific documentation on how to use each plugin:
* [gazebo-fmi-actuator documentation](plugins/actuator/README.md)


# Test the plugins 
For running the automatic tests of the plugins contained in this repo, you need the additional dependency of the [OpenModelica](https://openmodelica.org/) compiler. The OpenModelica compiler is used to generate test FMUs from [Modelica](https://www.modelica.org/) models. We recommend to use OpenModelica at least version 1.13 (the `nightly` version as of August 2018) as OpenModelica 1.12 has several bugs related to FMU generation (see https://github.com/robotology/gazebo-fmi/issues/5 and https://trac.openmodelica.org/OpenModelica/ticket/4135 ). 

Once you  installed OpenModelica on your system, you can regenerated the project with the `BUILD_TESTING` CMake option set to `ON` to compile the tests. Once test are compiled, you can run them using [ctest](https://cmake.org/cmake/help/latest/manual/ctest.1.html), for example run:
```cmake
$ ctest [-VV]
```
to run all the tests.

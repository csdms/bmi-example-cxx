[![Basic Model Interface](https://img.shields.io/badge/CSDMS-Basic%20Model%20Interface-green.svg)](https://bmi.readthedocs.io/)
[![Build/Test CI](https://github.com/csdms/bmi-example-cxx/workflows/Build/Test%20CI/badge.svg)](https://github.com/csdms/bmi-example-cxx/actions?query=workflow%3A%22Build%2FTest+CI%22)

# bmi-example-cxx

An example of implementing the
[C++ bindings](https://github.com/csdms/bmi-cxx)
for the CSDMS
[Basic Model Interface](https://bmi-spec.readthedocs.io) (BMI).


## Overview

This is an example of implementing a BMI for a simple model
that solves the diffusion equation
on a uniform rectangular plate
with Dirichlet boundary conditions.
The model and its BMI are written in C++.
Tests of the BMI are provided.

This repository is organized with the following directories:

<dl>
    <dt>heat</dt>
	<dd>Holds the model, the BMI for the model, and a sample main program</dd>
	<dt>testing</dt>
	<dd>Tests that cover the BMI of the model</dd>
</dl>

## Build/Install

This example can be built on Linux, macOS, and Windows.

**Prerequisites:**
* A C++ compiler
* CMake
* pkg-config
* The C++ BMI bindings. Follow the build and install directions
  given in the
  [README](https://github.com/csdms/bmi-cxx/blob/master/README.md)
  in that repository. You can choose to install them from source or
  through a conda binary.

### Linux and macOS

To build and install this example from source with cmake,
using the current C++ BMI version, run

    mkdir _build && cd _build
    export PKG_CONFIG_PATH=<path-to-installation>  # optional: only needed for non-standard install location
    cmake .. -DCMAKE_INSTALL_PREFIX=<path-to-installation>
    make
    make install

where `<path-to-installation>` is the base directory
in which the C++ BMI bindings have been installed
(`/usr/local` is the default).
When installing into a conda environment,
use the `CONDA_PREFIX` environment variable.

The installation will look like
(on macOS, using v2.0 of the BMI specification):

```bash
.
|-- bin
|   `-- run_bmiheatcxx
|-- include
|   |-- bmi.hxx
|   `-- bmi_heat.hxx
`-- lib
    |-- libbmiheatcxx.dylib
    `-- pkgconfig
        |-- bmicxx.pc
        `-- heatcxx.pc

4 directories, 6 files
```

From the build directory,
run unit tests on the sample implementation with

    ctest

### Windows

An additional prerequisite is needed for Windows:

* Microsoft Visual Studio 2017 or Microsoft Build Tools for Visual Studio 2017

To configure this example from source with cmake
using the current C++ BMI version,
run the following in a [Developer Command Prompt](https://docs.microsoft.com/en-us/dotnet/framework/tools/developer-command-prompt-for-vs)

    mkdir _build && cd _build
    set "PKG_CONFIG_PATH=<path-to-installation>"  &:: optional: only needed for non-standard install location
    cmake .. ^
	  -G "NMake Makefiles" ^
	  -DCMAKE_INSTALL_PREFIX=<path-to-installation> ^
	  -DCMAKE_BUILD_TYPE=Release

where `<path-to-installation>` is the base directory
in which the C BMI bindings have been installed
(`"C:\Program Files (x86)"` is the default;
note that quotes and an absolute path are needed).
When installing into a conda environment,
use the `%CONDA_PREFIX%` environment variable.

Then, to build and install:

	cmake --build . --target install --config Release

From the build directory,
run unit tests on the sample implementation with

    ctest


## Use

Run the heat model through its BMI with the `run_bmiheatcxx` program,
which takes a model configuration file
(see the [testing](./testing) directory for a sample)
as a required parameter.
If `run_bmiheatcxx` is in your path, run it with

    run_bmiheatcxx config.txt

Output from the model is written to the file **bmiheatcxx.out**
in the current directory.

Deprecated, use [new, faster version](https://github.com/Scthe/opencl-hash)
==============


## Introduction

There is an alphabet of following 16 characters: **_acdegilmnoprstuw_**. Hash of 9-letter word created based on this alphabet is provided and so is the hashing function. Would You kindly find the original word for us ?


Originally posted at [Fog Creek] careers page. I was not sure if I should apply, but I had tons of fun ( see #Other) and finally tried OpenCL.


## Solutions

I've written 2 solutions for this problem. It would not be exciting if the only difference would be a language so one is c++11 and the other one OpenCL.


## Usage

Goto [Main] and run the main function.


## Stopwatch

* **C++**: ~45 min
* **OpenCL**: ~4 min

####Hardware:
* **CPU**: AMD FX-6300
* **GPU**: Nvidia GTS 450


## Files

* [Main] main function lives here
* [Main_cpp] C++11 implementation
* [Main_cl] heart of OpenCL implementation
* [OpenCL_utils] some OpenCL utils functions
* [open_cl_kernel] kernel executed on the GPU


## Other

**OPENCL IMPLEMENTATION IS WRITTEN IN HIGHLY INEFFICIENT WAY.** ( But it doesn't matter since it is fast enough to finish in a time it takes me to make a coffee).

Also, during development I've crashed the driver. Like a lot. Still, not bad as it was my first experience with OpenCL.


[Fog Creek]: http://www.fogcreek.com/
[Main]: Main.cpp
[Main_cpp]: Main_cpp.cpp
[Main_cl]: Main_cl.cpp
[OpenCL_utils]: OpenCL_utils.h
[open_cl_kernel]: open_cl_kernel.cl

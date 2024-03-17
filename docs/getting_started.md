# Getting started
This chapter has some short guides on getting started with various build systems.

## Arduino IDE
1. [Download this repo as .zip](https://github.com/HAN-IOT-LAB-2324/CayenneLPP_MemOptimized/archive/refs/heads/master.zip).

2. Open the IDE and click to the "Sketch" menu and then Include Library > Add .ZIP Library. 

3. Open the .zip file you just downloaded :)

For more info see the [official arduino guide](https://docs.arduino.cc/software/ide-v1/tutorials/installing-libraries/).


## PlatformIO
1. Open your PlatformIO project
2. Add this line to your `platformio.ini` file:
    ```ini
    lib_deps = https://github.com/HAN-IOT-LAB-2324/CayenneLPP_MemOptimized
    ```
3. You can now use this library!

## CMake
1. Add these lines to your project before your `add_executable` statement:
```cmake
include(FetchContent)
FetchContent_Declare(
  CayenneLPP
  GIT_REPOSITORY https://github.com/HAN-IOT-LAB-2324/CayenneLPP_MemOptimized.git
  GIT_TAG        master
)

FetchContent_MakeAvailable(CayenneLPP)
```
2. Link your main executable with this library
```cmake
target_link_executable(main CayenneLPP)
```
**Replace main with your main target name!**

3. Good job! Now it should compile!
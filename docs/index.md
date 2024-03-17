# Welcome

Welcome to the CayenneIMP GitHub project. This project is based on the original [CayenneLPP](https://github.com/myDevicesIoT/CayenneLPP) encoder library. But has some patches and additions which improves performance and decreases flash usage. 

## Project layout

    src/  # The folder with the code source files.
        CayenneLPP.hpp # Implementation of the Cayenne Encoder class
        CayenneTypes.hpp # Types and macro's used by the Cayenne Encoder
    tests/ # The folder with the Unit test code
        src/
            test_memorysize.cpp # Unit test for the type helper functions
        CMakeLists.txt # Configuration file for including test in the CMake build
    docs/ # The folder with the documentation
        ... # markdown files with documentation
    library.json # Configuration file for PlatformIO build system
    CMakeLists.txt # Configuration file for CMake build system
    mkdocs.yml # Configuration file for mkdocs documentation generation

## Dependencies

This project utilizes C++11 functionality and the `memcpy` functions from the c stdlib.
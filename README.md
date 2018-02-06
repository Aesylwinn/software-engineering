# Getting Started

Note: The android application has not been fully set up yet. This process will
change once it has.

Qt5 is required for the development of this project. Depending on your platform
you may be able to dowload it using a package manager. Otherwise it can be found
downloaded at https://www.qt.io/download.

The source code can be retrieved using git. There are many git clients
available. On Windows you can use a command line interface with the client
available at https://git-scm.com/downloads.

CMake is a cross platform build system that makes dependency handling much
easier. It can be downloaded at https://cmake.org/download/.

Step 1: Use git to clone this repository onto your machine.

From the terminal, this can be done using the following commands:

`cd where/I/want/the/repo`

`git clone https://github.com/Aesylwinn/software-engineering.git`

Step 2: Open the project with Qt Creator.

Perform `File -> Open File or Project...` after opening Qt Creator. Navigate
to the location you cloned the repository and open the top level CMakeLists.txt
file. Configure the project for your environment.

You should now be able to build and run the various executables and libraries.

# Compiling for Android

To compile with android you will need to run cmake with the following command
in a separate directory.

On Linux:

`cmake -DCMAKE_TOOLCHAIN_FILE=path/to/the/android.toolchain.cmake .`

On Windows:

`cmake -G"MinGW Makefiles"
      -DCMAKE_TOOLCHAIN_FILE=<qt-android-cmake>/toolchain/android.toolchain.cmake 
      -DCMAKE_MAKE_PROGRAM="%ANDROID_NDK%/prebuilt/windows/bin/make.exe" .`



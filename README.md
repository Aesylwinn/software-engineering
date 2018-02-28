# Setting Up A Development Environment

## Qt

Qt5 is required for the development of this project. You will need to download
it from https://www.qt.io/download. The open source version is all that's
required. The version distributed with some package managers is not suitable
for Android development.

When running the installer, there is the option to choose from several versions
of Qt. Be sure to get the latest stable version. At the time of writing, this
was version 5.10.0. You will need toolchains for both your machine and for
Android, so be sure to select all of them. For example:

`MSVC 2017 64 bit`
`Android x86`
`Android ARMv7`

You will also need to have a compiler capable of compiling modern c++. On
windows, Visual Studio seems to work the best. There have been issues with
MinGW.

## Java

The Java JDK can be found at
http://www.oracle.com/technetwork/java/javase/downloads/jdk8-downloads-2133151.html.
This is required for Android development.

## Android

Android studio is required for Android development. You can find it at
https://developer.android.com/studio/index.html. It will install the Android
SDK which will be used by Qt.

From the Sdk updater included with Android studio, be sure to install the
platform tools for API level 10 (Gingerbread).

The Android NDK is required for cross-compiling. It can be found at
https://developer.android.com/ndk/downloads/index.html. This will be used by
Qt. Extract this where you wish.

## Google test framework

This project uses the google test framework available at
`https://github.com/google/googletest`. You will need to download the repo and
set the `GOOGLETEST_DIR` environment variable to point at the repo.

On Windows:
1. `git clone https://github.com/google/googletest.git` in whatever folder you
    want.  **Remember where this folder is located.** You will set the
    `GOOGLETEST_DIR` environment variable to point at this repo.
2. In your File Explorer, right click on This PC/Computer and select Properties
3. Under the Properties section, select Advanced System Settings
4. Select Environment Variables
5. In the User Variables Section, select New and type in `GOOGLETEST_DIR` for
    the name.
6. For the Variable Value section, you will want to find the folder where you
    cloned the googletest repository. Enter into said folder. Copy the path by
    right-clicking the white bar above the files. Copy this path and paste it in
    the Variable Value section. Select OK.

## Bringing it all together

Configuring Qt to use Android can be done by following the steps found at
http://doc.qt.io/qt-5/androidgs.html. *Do this before opening the project!*

In short:
1. Open `QtCreator`.
2. Navigate to `Tools->Options...->Devices->Android`.
3. Set the JDK location, Android SDK location, and Android NDK location.
4. Make sure the box to automatically create kits is checked and click `Apply`.
5. While still in `Tools->Options` navigate to `Build & Run->Kits`, if all is
   good then you will see both the Desktop and Android toolchains.

## Git

The source code can be retrieved using git. There are many git clients
available. Once such client is https://git-scm.com/downloads.


# Getting The Code

First you need to clone the repository. From a terminal, this can be done by
navigating to where you want the repository and executing the following
command:

`git clone https://github.com/Aesylwinn/software-engineering.git`

Once you have the code, you can then open the `se.pro` file with QtCreator.
QtCreator will allow you to configure the project for your environment. Be sure
to select all the `kits` you wish to build for.

# Compilation

Once your development environment has been setup and Qt has been configured, you
are ready for compilation. When selecting the se.pro the Qt creator window will
pop up When compiling, Qt creator will bring up a screen asking you to select
the Kits wanted to configure the project.

To have everything working perfectly with what we tested, the user will check
1. Android for armeabi-v7a (GCC 4.9, Qt 5.10.0 for Android armv7)
2. Android for x86 (GCC 4.9, Qt 5.10.0 for Android x86)
3. Desktop Qt 5.10 MSVC2017 64bit or Desktop Qt 5.10 MSVC2017 32bit (depending
    on your computer)

Once those are selected, click on configure project and wait for the editor to
finish. Once done the project will appear in the edit tab of Qt. When the
project appears, we will need to now build the project. To build a project there
are two different ways you can do so by:
* Right clicking the folder called se or the top drop-down folder and selecting
    build
* Or hitting ctrl B

Once it is done building we are ready to start running the code.

# Running the Code

There are two primary executables that can be ran by the user. The other folders
are for a shared library and the tests. The user can run the mobile-app and the
web-app.

To run the web-app there are two options the user can choose between.
* They can right click the folder that says web-app and select run
* Or they can click the bottom left button that says DEBUG
    1. Then select Desktop Qt 5.10 MSVC2017 64bit or Desktop Qt 5.10 MSVC2017
        32bit (depending on your computer) and in the RUN column select web-app
    2. Select the web-app project as the one to debug.
    3. Once that is selected click the green play button right underneath the
        DEBUG button

Running the mobile-app is quite similar to option 2 for running the web-app.
Simply choose the appropriate Android kit. If using the emulator, then you
probably need to use the x86 Arm kit. To run on the emulator, be sure to:
1. Start the emulator from Android Studio (if you are constrained for RAM, then
    close Android Studio afterwards)
2. Select the Android toolkit for compilation
3. Click the play button and go through the steps of choosing an Android device
    to run on

The mobile-app can technically be ran on the Desktop if you desire. At later
points, this is not guaranteed to continue working well, if at all.

To run the tests (See the Google Test Framework section above to set it up):
1. Change your toolkit back to the Desktop toolchain.
2. Rebuild the QT Project by right-clicking the top level folder and selecting
    ‘rebuild’
3. Right click on the test sub-folder and select run:

# Acceptance Testing

1. The web-app
    * The application opens without crashing when ran
    * The user can choose between different pages by clicking on the tabs

2. The mobile-app
    * The application opens without crashing when ran

# Class diagram

`https://drive.google.com/file/d/18EtRpsullT92mjS7xp_xUL_yVvVojBth/view`

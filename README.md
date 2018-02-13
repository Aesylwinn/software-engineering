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

`git clone https://github.com/google/googletest.git`

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

# Git Usage

Please create a new branch. Do not attempt to directly push to the master
branch. For sanity reasons, protections have been enabled to prevent this.
Instead, push your new branch to github. You can then create a pull request on
github and merge the branch into master.

# Useful Git Commands

To create a new branch (off of the currently selected branch):

`git checkout -B BranchName`

To fetch changes without automatically merging:

`git fetch origin BranchName`

To merge a fetched branch into the current one:

`git merge origin/BranchName`

To stage files before a commit:

`git add file1 file2`

To commit staged files:

`git commit -m "Brief and descriptive commit message"`

To push a branch:

`git push origin BranchName`

# Class diagram

`https://drive.google.com/file/d/18EtRpsullT92mjS7xp_xUL_yVvVojBth/view`

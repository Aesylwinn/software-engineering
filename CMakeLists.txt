cmake_minimum_required(VERSION 3.1 FATAL_ERROR)

project(
    Interests
    VERSION 0.0.1
    LANGUAGES CXX
)

# Dependencies
find_package(Qt5Widgets REQUIRED)

# Qt5 generates moc files that need some setup
set(CMAKE_AUTOMOC ON)
set(CMAKE_INCLUDE_CURRENT_DIR ON)

# Source
add_subdirectory(src)


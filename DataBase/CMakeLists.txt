cmake_minimum_required(VERSION 3.5)
project(DataBase VERSION 0.1 LANGUAGES CXX)
add_library(data SHARED
    data.h data.cpp)
target_link_libraries(data PRIVATE Qt${QT_VERSION_MAJOR}::Widgets)  # Link Qt's Widgets and SQL modules
find_package(QT NAMES Qt6 Qt5 REQUIRED COMPONENTS Widgets Sql)  # Add the Sql component here
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Widgets Sql)  # Add the Sql component here




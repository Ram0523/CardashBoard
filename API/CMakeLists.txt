project(API LANGUAGES CXX)
add_library(api SHARED api.h api.cpp)
find_package(QT NAMES Qt6 Qt5 REQUIRED COMPONENTS Widgets)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Widgets )
target_link_libraries(api PRIVATE Qt${QT_VERSION_MAJOR}::Widgets)  # Link Qt's Widgets and SQL modules




target_include_directories(api PUBLIC data)
target_link_libraries(api PRIVATE data)

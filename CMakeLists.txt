cmake_minimum_required(VERSION 3.5)

project(CarDashBoard VERSION 0.1 LANGUAGES CXX)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_subdirectory(DataBase/)
add_subdirectory(API/)
add_subdirectory(Details/)

add_subdirectory(googletest/)
add_subdirectory(googlemock/)

find_package(QT NAMES Qt6 Qt5 REQUIRED COMPONENTS Widgets )
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Widgets )

find_package(QT NAMES Qt6 Qt5 REQUIRED COMPONENTS  Test)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Test)

find_package(QT NAMES Qt6 Qt5 REQUIRED COMPONENTS Widgets Sql)  # Add the Sql component here
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Widgets Sql)  # Add the Sql component here


set(PROJECT_SOURCES
        main.cpp
        mainwindow.cpp
        mainwindow.h
        mainwindow.ui
)

if(${QT_VERSION_MAJOR} GREATER_EQUAL 6)
    qt_add_executable(CarDashBoard
        MANUAL_FINALIZATION
        ${PROJECT_SOURCES}          
DataBase/data.h DataBase/data.cpp
API/api.h  API/api.cpp
Details/details.h Details/details.cpp
dashboard.h dashboard.cpp dashboard.ui
user_prefrence.h user_prefrence.cpp user_prefrence.ui
add_user.h add_user.cpp add_user.ui
Resources.qrc
ApiTester.cpp
cardashboard.qml

    )
# Define target properties for Android with Qt 6 as:
#    set_property(TARGET CarDashBoard APPEND PROPERTY QT_ANDROID_PACKAGE_SOURCE_DIR
#                 ${CMAKE_CURRENT_SOURCE_DIR}/android)
# For more information, see https://doc.qt.io/qt-6/qt-add-executable.html#target-creation
else()
    if(ANDROID)
        add_library(CarDashBoard SHARED
            ${PROJECT_SOURCES}
        )
# Define properties for Android with Qt 5 after find_package() calls as:
#    set(ANDROID_PACKAGE_SOURCE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/android")
    else()
        add_executable(CarDashBoard
            ${PROJECT_SOURCES}
        )
    endif()
endif()

target_link_libraries(CarDashBoard PRIVATE Qt${QT_VERSION_MAJOR}::Widgets)
target_link_libraries(CarDashBoard PRIVATE Qt${QT_VERSION_MAJOR}::Sql)
target_link_libraries(CarDashBoard PRIVATE Qt${QT_VERSION_MAJOR}::Test)

target_include_directories(CarDashBoard PUBLIC DataBase)
target_link_libraries(CarDashBoard PRIVATE data)

target_include_directories(CarDashBoard PUBLIC API)
target_link_libraries(CarDashBoard PRIVATE api)
target_include_directories(CarDashBoard PUBLIC Details)
target_link_libraries(CarDashBoard PRIVATE details)

target_include_directories(CarDashBoard PUBLIC googletest/ googlemock/)
target_link_libraries(CarDashBoard PRIVATE gtest gmock)

# Qt for iOS sets MACOSX_BUNDLE_GUI_IDENTIFIER automatically since Qt 6.1.
# If you are developing for iOS or macOS you should consider setting an
# explicit, fixed bundle identifier manually though.
if(${QT_VERSION} VERSION_LESS 6.1.0)
  set(BUNDLE_ID_OPTION MACOSX_BUNDLE_GUI_IDENTIFIER com.example.CarDashBoard)
endif()
set_target_properties(CarDashBoard PROPERTIES
    ${BUNDLE_ID_OPTION}
    MACOSX_BUNDLE_BUNDLE_VERSION ${PROJECT_VERSION}
    MACOSX_BUNDLE_SHORT_VERSION_STRING ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}
    MACOSX_BUNDLE TRUE
    WIN32_EXECUTABLE TRUE
)

include(GNUInstallDirs)
install(TARGETS CarDashBoard
    BUNDLE DESTINATION .
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)

if(QT_VERSION_MAJOR EQUAL 6)
    qt_finalize_executable(CarDashBoard)
endif()


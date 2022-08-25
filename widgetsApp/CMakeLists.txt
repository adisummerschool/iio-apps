cmake_minimum_required(VERSION 3.5)

project(widgetsApp VERSION 0.1 LANGUAGES CXX)

set(CMAKE_INCLUDE_CURRENT_DIR ON)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)


find_package(QT NAMES Qt6 Qt5 REQUIRED COMPONENTS Widgets REQUIRED Svg)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Widgets REQUIRED Svg)
set(QFI_INCLUDE_DIRS /home/andrei/QFlightinstruments/src)
set(QFI_LIBRARIES /home/andrei/QFlightinstruments/lib/libqfi.so)

set(PROJECT_SOURCES
        main.cpp
        mainwindow.cpp
        mainwindow.h
        mainwindow.ui
)

if(${QT_VERSION_MAJOR} GREATER_EQUAL 6)
    qt_add_executable(widgetsApp
        MANUAL_FINALIZATION
        ${PROJECT_SOURCES}
    )
# Define target properties for Android with Qt 6 as:
#    set_property(TARGET widgetsApp APPEND PROPERTY QT_ANDROID_PACKAGE_SOURCE_DIR
#                 ${CMAKE_CURRENT_SOURCE_DIR}/android)
# For more information, see https://doc.qt.io/qt-6/qt-add-executable.html#target-creation
else()
    if(ANDROID)
        add_library(widgetsApp SHARED
            ${PROJECT_SOURCES}
        )
# Define properties for Android with Qt 5 after find_package() calls as:
#    set(ANDROID_PACKAGE_SOURCE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/android")
    else()
        add_executable(widgetsApp
            ${PROJECT_SOURCES}
        )
    endif()
endif()

find_package(Qt5 REQUIRED COMPONENTS Concurrent)
target_link_libraries(widgetsApp PRIVATE Qt${QT_VERSION_MAJOR}::Widgets iio PRIVATE Qt5::Concurrent PUBLIC ${QFI_INCLUDE_DIRS})
target_link_libraries(widgetsApp PRIVATE Qt5::Widgets iio  ${QFI_LIBRARIES} Qt5::Svg)
target_include_directories(widgetsApp PUBLIC ${QFI_INCLUDE_DIRS})


set_target_properties(widgetsApp PROPERTIES
    MACOSX_BUNDLE_GUI_IDENTIFIER my.example.com
    MACOSX_BUNDLE_BUNDLE_VERSION ${PROJECT_VERSION}
    MACOSX_BUNDLE_SHORT_VERSION_STRING ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}
    MACOSX_BUNDLE TRUE
    WIN32_EXECUTABLE TRUE
)

install(TARGETS widgetsApp
    BUNDLE DESTINATION .
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR})

if(QT_VERSION_MAJOR EQUAL 6)
    qt_finalize_executable(widgetsApp)
endif()



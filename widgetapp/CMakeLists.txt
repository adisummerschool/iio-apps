cmake_minimum_required(VERSION 3.5)

project(widgetapp LANGUAGES CXX)

set(CMAKE_INCLUDE_CURRENT_DIR ON)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)



find_package(QT NAMES Qt6 Qt5 COMPONENTS Widgets Svg REQUIRED)
find_package(Qt${QT_VERSION_MAJOR} COMPONENTS Widgets Svg REQUIRED)

set(QFI_INCLUDE_DIRS /home/analog/QFlightinstruments/src)
set(QFI_LIBRARIES /home/analog/QFlightinstruments/lib/libqfi.so)

set(PROJECT_SOURCES
        main.cpp
        mainwindow.cpp
        mainwindow.h
        mainwindow.ui
)

if(${QT_VERSION_MAJOR} GREATER_EQUAL 6)
    qt_add_executable(widgetapp
        ${PROJECT_SOURCES}
    )
else()
    if(ANDROID)
        add_library(widgetapp SHARED
            ${PROJECT_SOURCES}
        )
    else()
        add_executable(widgetapp
            ${PROJECT_SOURCES}
        )
    endif()
endif()

target_include_directories(widgetapp PUBLIC ${QFI_INCLUDE_DIRS})

target_link_libraries(widgetapp PRIVATE Qt${QT_VERSION_MAJOR}::Widgets iio     ${QFI_LIBRARIES}
        Qt${QT_VERSION_MAJOR}::Svg)

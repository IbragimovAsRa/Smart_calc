
cmake_minimum_required(VERSION 3.5)

project(smart_calc VERSION 0.1 LANGUAGES CXX C)

set(CMAKE_INCLUDE_CURRENT_DIR ON)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_AUTOUIC_SEARCH_PATHS ui/)

find_package(QT NAMES Qt6 Qt5 REQUIRED COMPONENTS Widgets)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Widgets)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Widgets PrintSupport)

set(PROJECT_SOURCES
  main.cpp
        mainwindow.cpp
        mainwindow.h
        mainwindow.ui

        ../datastructs/stack_num.c
        ../datastructs/stack_num.h
        ../datastructs/linked_list.c
        ../datastructs/linked_list.h
        ../datastructs/stack_list.c
        ../datastructs/stack_list.h

        ../parse_input.c
        ../reverse_polish_notation.c
        ../utils.c
        ../calculations.c
        ../parse_input.h
        ../reverse_polish_notation.h
        ../utils.h
        ../calculations.h

        qcustomplot.cpp
        qcustomplot.h

        creditwindow.h creditwindow.cpp creditwindow.ui
        depositwindow.h depositwindow.cpp depositwindow.ui
)

if(${QT_VERSION_MAJOR} GREATER_EQUAL 6)
    qt_add_executable(smart_calc
        MANUAL_FINALIZATION
        ${PROJECT_SOURCES}
    )
# Define target properties for Android with Qt 6 as:
#    set_property(TARGET smart_calc APPEND PROPERTY QT_ANDROID_PACKAGE_SOURCE_DIR
#                 ${CMAKE_CURRENT_SOURCE_DIR}/android)
# For more information, see https://doc.qt.io/qt-6/qt-add-executable.html#target-creation
else()
    if(ANDROID)
        add_library(smart_calc SHARED
            ${PROJECT_SOURCES}
        )
# Define properties for Android with Qt 5 after find_package() calls as:
#    set(ANDROID_PACKAGE_SOURCE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/android")
    else()
        add_executable(smart_calc
            ${PROJECT_SOURCES}
        )
    endif()
endif()

target_link_libraries(smart_calc PRIVATE Qt${QT_VERSION_MAJOR}::Widgets)
target_link_libraries(smart_calc PRIVATE Qt${QT_VERSION_MAJOR}::PrintSupport)
set_target_properties(smart_calc PROPERTIES
    MACOSX_BUNDLE_GUI_IDENTIFIER my.example.com
    MACOSX_BUNDLE_BUNDLE_VERSION ${PROJECT_VERSION}
    MACOSX_BUNDLE_SHORT_VERSION_STRING ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}
    MACOSX_BUNDLE TRUE
    WIN32_EXECUTABLE TRUE
)

install(TARGETS smart_calc
    BUNDLE DESTINATION .
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR})

if(QT_VERSION_MAJOR EQUAL 6)
    qt_finalize_executable(smart_calc)
endif()

cmake_minimum_required(VERSION 3.5)

project(Proyecto_Compiladoresv2 VERSION 0.1 LANGUAGES CXX)

set(CMAKE_INCLUDE_CURRENT_DIR ON)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(QT NAMES Qt6 Qt5 REQUIRED COMPONENTS Widgets)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Widgets)

set(PROJECT_SOURCES
        main.cpp
        widget.cpp
        widget.h
        widget.ui
        ClaseAFN.h
        ClaseAFN.cpp
        ClaseAFD.h
        ClaseAFD.cpp
        ClaseNodo.h
        ClaseNodo.cpp
        ClaseEstado.h
        ClaseEstado.cpp
        ClaseTransicion.h
        ClaseTransicion.cpp
        ConIj.h
        ConIj.cpp
        AnalizLexico.h
        AnalizLexico.cpp
        Estado_AnalizLexico.h
        Estado_AnalizLexico.cpp
        ER_AFN.h
        ER_AFN.cpp
        EvaluadorExp1.h
        EvaluadorExp1.cpp

)

if(${QT_VERSION_MAJOR} GREATER_EQUAL 6)
    qt_add_executable(Proyecto_Compiladoresv2
        MANUAL_FINALIZATION
        ${PROJECT_SOURCES}
    )
# Define target properties for Android with Qt 6 as:
#    set_property(TARGET Proyecto_Compiladoresv2 APPEND PROPERTY QT_ANDROID_PACKAGE_SOURCE_DIR
#                 ${CMAKE_CURRENT_SOURCE_DIR}/android)
# For more information, see https://doc.qt.io/qt-6/qt-add-executable.html#target-creation
else()
    if(ANDROID)
        add_library(Proyecto_Compiladoresv2 SHARED
            ${PROJECT_SOURCES}
        )
# Define properties for Android with Qt 5 after find_package() calls as:
#    set(ANDROID_PACKAGE_SOURCE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/android")
    else()
        add_executable(Proyecto_Compiladoresv2
            ${PROJECT_SOURCES}
        )
    endif()
endif()

target_link_libraries(Proyecto_Compiladoresv2 PRIVATE Qt${QT_VERSION_MAJOR}::Widgets)

set_target_properties(Proyecto_Compiladoresv2 PROPERTIES
    MACOSX_BUNDLE_GUI_IDENTIFIER my.example.com
    MACOSX_BUNDLE_BUNDLE_VERSION ${PROJECT_VERSION}
    MACOSX_BUNDLE_SHORT_VERSION_STRING ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}
    MACOSX_BUNDLE TRUE
    WIN32_EXECUTABLE TRUE
)

install(TARGETS Proyecto_Compiladoresv2
    BUNDLE DESTINATION .
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR})

if(QT_VERSION_MAJOR EQUAL 6)
    qt_finalize_executable(Proyecto_Compiladoresv2)
endif()

cmake_minimum_required(VERSION 3.5)

project(GUI VERSION 0.1 LANGUAGES CXX)

set(CMAKE_INCLUDE_CURRENT_DIR ON)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(INSTALL_EXAMPLEDIR "${INSTALL_EXAMPLESDIR}/multimediawidgets/player")

find_package(QT NAMES Qt6 Qt5 REQUIRED COMPONENTS Widgets LinguistTools)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Widgets LinguistTools)


set(TS_FILES GUI_zh_CN.ts)

set(PROJECT_SOURCES
        data.h
        data.cpp
        main.cpp
        mainwindow.cpp
        mainwindow.h
        mainwindow.ui
        Artifact.h
        Artifact.cpp
        Character.h
        Character.cpp
        Weapon.h
        Weapon.cpp
        Import.h
        Import.cpp
        #Resources.qrc
        ImportCharacter.h
        ImportCharacter.cpp
        ImportWeapon.h
        ImportWeapon.cpp
        importwidget.h
        importwidget.cpp
        importwidget.ui
        isoverwrite.h
        isoverwrite.cpp
        isoverwrite.ui
        importmanually.h
        importmanually.cpp
        importmanually.ui
        backpack.h
        backpack.cpp
        backpack.ui
        isdelete.h
        isdelete.cpp
        isdelete.ui
        upcombobox.h
        upcombobox.cpp
        favorite.h
        favorite.cpp
        favorite.ui
        FavoriteOri.h
        FavoriteOri.cpp
        favdelmod.h
        favdelmod.cpp
        favdelmod.ui
        rating.h
        rating.cpp
        rating.ui
        characterselecte.h
        characterselecte.cpp
        characterselecte.ui
        weaponselect.h
        weaponselect.cpp
        weaponselect.ui
        ${TS_FILES}
)

if(${QT_VERSION_MAJOR} GREATER_EQUAL 6)
    qt_add_executable(GUI
        MANUAL_FINALIZATION
        ${PROJECT_SOURCES}
    )
# Define target properties for Android with Qt 6 as:
#    set_property(TARGET GUI APPEND PROPERTY QT_ANDROID_PACKAGE_SOURCE_DIR
#                 ${CMAKE_CURRENT_SOURCE_DIR}/android)
# For more information, see https://doc.qt.io/qt-6/qt-add-executable.html#target-creation

    qt_create_translation(QM_FILES ${CMAKE_SOURCE_DIR} ${TS_FILES})
else()
    if(ANDROID)
        add_library(GUI SHARED
            ${PROJECT_SOURCES}
        )
# Define properties for Android with Qt 5 after find_package() calls as:
#    set(ANDROID_PACKAGE_SOURCE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/android")
    else()
        add_executable(GUI
            ${PROJECT_SOURCES}
        )
    endif()

    qt5_create_translation(QM_FILES ${CMAKE_SOURCE_DIR} ${TS_FILES})
endif()

target_link_libraries(GUI PRIVATE Qt${QT_VERSION_MAJOR}::Widgets)

set_target_properties(GUI PROPERTIES
    MACOSX_BUNDLE_GUI_IDENTIFIER my.example.com
    MACOSX_BUNDLE_BUNDLE_VERSION ${PROJECT_VERSION}
    MACOSX_BUNDLE_SHORT_VERSION_STRING ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}
    MACOSX_BUNDLE TRUE
    WIN32_EXECUTABLE TRUE
)

if(QT_VERSION_MAJOR EQUAL 6)
    qt_finalize_executable(GUI)
endif()

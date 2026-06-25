cmake_minimum_required(VERSION 3.16)

project(StoryForge VERSION 0.1 LANGUAGES CXX)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(QT NAMES Qt6 Qt5 REQUIRED COMPONENTS Widgets Svg LinguistTools)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Widgets Svg LinguistTools)

set(TS_FILES StoryForge_en_US.ts)

set(PROJECT_SOURCES
        src/main.cpp
        src/ui/mainwindow.cpp

        ${TS_FILES}
)

if(${QT_VERSION_MAJOR} GREATER_EQUAL 6)

    qt_add_executable(StoryForge
        MANUAL_FINALIZATION
        ${PROJECT_SOURCES}
        resources/resources.qrc
        resources/styles.qss
        src/ui/components/nav/sidebar.h src/ui/components/nav/sidebar.cpp
        src/ui/components/nav/navrail.h src/ui/components/nav/navrail.cpp
        resources/navrailstyles.qss
        src/ui/components/nav/manuscriptpanel.h src/ui/components/nav/manuscriptpanel.cpp
        src/ui/components/nav/actsectionheader.h src/ui/components/nav/actsectionheader.cpp
        src/ui/components/nav/scenedata.h
        src/ui/components/nav/scenerow.h src/ui/components/nav/scenerow.cpp
        resources/manuscriptpanelstyles.qss
        src/ui/components/nav/topbar.h src/ui/components/nav/topbar.cpp
        src/ui/components/nav/storymenu.h src/ui/components/nav/storymenu.cpp
        src/ui/components/nav/storymenurow.h src/ui/components/nav/storymenurow.cpp
        resources/storymenustyles.qss
        resources/topbarstyles.qss



    )
# Define target properties for Android with Qt 6 as:
#    set_property(TARGET StoryForge APPEND PROPERTY QT_ANDROID_PACKAGE_SOURCE_DIR
#                 ${CMAKE_CURRENT_SOURCE_DIR}/android)
# For more information, see https://doc.qt.io/qt-6/qt-add-executable.html#target-creation

    qt_create_translation(QM_FILES ${CMAKE_SOURCE_DIR} ${TS_FILES})
else()
    if(ANDROID)
        add_library(StoryForge SHARED
            ${PROJECT_SOURCES}
        )
# Define properties for Android with Qt 5 after find_package() calls as:
#    set(ANDROID_PACKAGE_SOURCE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/android")
    else()
        add_executable(StoryForge
            ${PROJECT_SOURCES}
        )
    endif()

    qt5_create_translation(QM_FILES ${CMAKE_SOURCE_DIR} ${TS_FILES})
endif()

target_link_libraries(StoryForge PRIVATE Qt${QT_VERSION_MAJOR}::Widgets Qt${QT_VERSION_MAJOR}::Svg)

# Qt for iOS sets MACOSX_BUNDLE_GUI_IDENTIFIER automatically since Qt 6.1.
# If you are developing for iOS or macOS you should consider setting an
# explicit, fixed bundle identifier manually though.
if(${QT_VERSION} VERSION_LESS 6.1.0)
  set(BUNDLE_ID_OPTION MACOSX_BUNDLE_GUI_IDENTIFIER com.example.StoryForge)
endif()
set_target_properties(StoryForge PROPERTIES
    ${BUNDLE_ID_OPTION}
    MACOSX_BUNDLE_BUNDLE_VERSION ${PROJECT_VERSION}
    MACOSX_BUNDLE_SHORT_VERSION_STRING ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}
    MACOSX_BUNDLE TRUE
    WIN32_EXECUTABLE TRUE
)

include(GNUInstallDirs)
install(TARGETS StoryForge
    BUNDLE DESTINATION .
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)

if(QT_VERSION_MAJOR EQUAL 6)
    qt_finalize_executable(StoryForge)
endif()

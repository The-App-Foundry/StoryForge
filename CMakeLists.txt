cmake_minimum_required(VERSION 3.16)

project(StoryForge VERSION 0.1 LANGUAGES CXX)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(QT NAMES Qt6 Qt5 REQUIRED COMPONENTS Widgets Svg SvgWidgets LinguistTools)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Widgets Svg SvgWidgets LinguistTools)

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
        resources/styles/styles.qss
        resources/styles/navrailstyles.qss
        resources/styles/manuscriptpanelstyles.qss
        resources/styles/storymenustyles.qss
        resources/styles/topbarstyles.qss
        resources/styles/stagerailstyles.qss
        resources/styles/conceptrailstyles.qss
        src/ui/components/nav/sidebar.h src/ui/components/nav/sidebar.cpp
        src/ui/components/nav/navrail.h src/ui/components/nav/navrail.cpp
        src/ui/components/nav/manuscriptpanel.h src/ui/components/nav/manuscriptpanel.cpp
        src/ui/components/nav/actsectionheader.h src/ui/components/nav/actsectionheader.cpp
        src/ui/components/nav/scenedata.h
        src/ui/components/nav/scenerow.h src/ui/components/nav/scenerow.cpp
        src/ui/components/nav/topbar.h src/ui/components/nav/topbar.cpp
        src/ui/components/nav/storymenu.h src/ui/components/nav/storymenu.cpp
        src/ui/components/nav/storymenurow.h src/ui/components/nav/storymenurow.cpp
        src/ui/meta.h
        src/ui/components/nav/conceptrail.h src/ui/components/nav/conceptrail.cpp
        src/ui/components/nav/navpillwidget.cpp
        src/ui/components/nav/navpillwidget.h
        src/ui/utils/graphicsutils.h src/ui/utils/graphicsutils.cpp
        src/ui/components/nav/stagerail.h src/ui/components/nav/stagerail.cpp
        src/ui/components/nav/titlebar.h src/ui/components/nav/titlebar.cpp
        src/ui/views/concept/conceptview.h src/ui/views/concept/conceptview.cpp
        src/ui/views/concept/premise/premise.h src/ui/views/concept/premise/premise.cpp
        resources/styles/premisestyles.qss
        src/ui/components/editor/concept/premise/emptystatewidget.h src/ui/components/editor/concept/premise/emptystatewidget.cpp
        resources/icons/document.svg
        resources/icons/edit.svg
        src/ui/components/buttons/iconbutton.h src/ui/components/buttons/iconbutton.cpp
        src/ui/components/editor/concept/premise/formgroup.h src/ui/components/editor/concept/premise/formgroup.cpp
        src/ui/components/editor/concept/premise/form.h src/ui/components/editor/concept/premise/form.cpp
        src/ui/views/concept/premise/premisedata.h


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

target_link_libraries(StoryForge PRIVATE
    Qt${QT_VERSION_MAJOR}::Widgets
    Qt${QT_VERSION_MAJOR}::Svg
    Qt${QT_VERSION_MAJOR}::SvgWidgets
    Qt${QT_VERSION_MAJOR}::Gui
    Qt${QT_VERSION_MAJOR}::Core
)

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

target_include_directories(StoryForge PUBLIC
    "${CMAKE_CURRENT_SOURCE_DIR}/src"
    "${CMAKE_CURRENT_SOURCE_DIR}/include"
)

if(QT_VERSION_MAJOR EQUAL 6)
    qt_finalize_executable(StoryForge)
endif()

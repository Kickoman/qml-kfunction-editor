cmake_minimum_required(VERSION 3.16)

project(qml-kfunction-editor VERSION 0.1 LANGUAGES CXX)

set(CMAKE_AUTOMOC ON)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(Qt6 6.2 REQUIRED COMPONENTS Quick Widgets Charts)

qt_add_executable(appqml-kfunction-editor
    main.cpp
    kfunctionmodelmapper.h
)

qt_policy(SET QTP0001 OLD)
qt_add_qml_module(appqml-kfunction-editor
    URI QmlKfunctionEditor
    VERSION 1.0
    QML_FILES
        Main.qml
        KFunctionQmlView.qml
        KFunctionQmlEditor.qml
    SOURCES
        kfunctionqmlwrapper.h
)

# Qt for iOS sets MACOSX_BUNDLE_GUI_IDENTIFIER automatically since Qt 6.1.
# If you are developing for iOS or macOS you should consider setting an
# explicit, fixed bundle identifier manually though.
set_target_properties(appqml-kfunction-editor PROPERTIES
#    MACOSX_BUNDLE_GUI_IDENTIFIER com.example.appqml-kfunction-editor
    MACOSX_BUNDLE_BUNDLE_VERSION ${PROJECT_VERSION}
    MACOSX_BUNDLE_SHORT_VERSION_STRING ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}
    MACOSX_BUNDLE TRUE
    WIN32_EXECUTABLE TRUE
)

add_subdirectory(kmisc)
target_include_directories(appqml-kfunction-editor
    PRIVATE ${KMISC_INCLUDES}
)
target_link_libraries(appqml-kfunction-editor
    PRIVATE Qt6::Quick Qt6::Widgets Qt6::Charts
)

include(GNUInstallDirs)
install(TARGETS appqml-kfunction-editor
    BUNDLE DESTINATION .
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)

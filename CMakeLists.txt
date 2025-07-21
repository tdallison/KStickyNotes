cmake_minimum_required(VERSION 3.16)
project(KStickyNotes LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)

find_package(Qt6 REQUIRED COMPONENTS Core Gui Qml Quick QuickControls2 Widgets)

qt_add_executable(KStickyNotesApp
    main.cpp
    NoteManager.cpp
    NoteManager.h
)

qt_add_qml_module(KStickyNotes
    URI KStickyNotes
    VERSION 1.0
    QML_FILES Note.qml
    RESOURCE_PREFIX /
        OUTPUT_DIRECTORY "${CMAKE_CURRENT_BINARY_DIR}/KStickyNotes"
)

target_link_libraries(KStickyNotesApp
    PRIVATE
    Qt6::Core
    Qt6::Gui
    Qt6::Qml
    Qt6::Quick
    Qt6::QuickControls2
    Qt6::Widgets
)

install(TARGETS KStickyNotesApp DESTINATION bin)

include(InstallRequiredSystemLibraries)

set(CPACK_GENERATOR "DEB")
set(CPACK_PACKAGE_NAME "kstickynotes")
set(CPACK_PACKAGE_VERSION "1.0.0")
set(CPACK_PACKAGE_CONTACT "Tyler Dallison <tylerdallison@gmail.com>")
set(CPACK_DEBIAN_PACKAGE_MAINTAINER "Tyler Dallison")
set(CPACK_DEBIAN_PACKAGE_SECTION "utils")
set(CPACK_DEBIAN_ARCHITECTURE ${CMAKE_SYSTEM_PROCESSOR})
set(CPACK_DEBIAN_PACKAGE_DEPENDS "qt6-base-dev, qt6-declarative-dev, qt6-quickcontrols2-dev")

include(CPack)

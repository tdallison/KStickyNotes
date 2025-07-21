cmake_minimum_required(VERSION 3.16)
project(KStickyNotes LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(Qt6 REQUIRED COMPONENTS Core Gui Qml Quick QuickControls2 Widgets)

qt_add_executable(KStickyNotes
    main.cpp
    NoteManager.cpp
    NoteManager.h
)

qt_add_qml_module(KStickyNotes
    URI KStickyNotes
    QML_FILES Note.qml
    RESOURCE_PREFIX /
)

target_link_libraries(KStickyNotes
    Qt6::Core
    Qt6::Gui
    Qt6::Qml
    Qt6::Quick
    Qt6::QuickControls2
    Qt6::Widgets
)
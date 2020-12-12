cmake_minimum_required(VERSION 3.4)
project(HeatTransferConvection)

FIND_PACKAGE(GTest REQUIRED)
FIND_PACKAGE(Qt5Widgets)
FIND_PACKAGE(Qt5Gui)

INCLUDE_DIRECTORIES(${GTEST_INCLUDE_DIRS})

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED 1)
SET(CMAKE_INCLUDE_CURRENT_DIR ON)
SET(CMAKE_AUTOMOC ON)
SET(CMAKE_AUTOUIC ON)
SET(CMAKE_AUTORCC ON)

SET(MYSOURCE
    main.cpp
    mainwindow.cpp
    mainwindow.h
    mainwindowform.ui
    outputwindow.h
    outputwindow.cpp
    outputwindow.ui
    stuffpanel.cpp
    stuffpanel.h
    stuffpanel.ui
    mysettings.cpp
    mysettings.h
    mysettings.ui
    )

set( MYRESOURCES icons/icons.qrc)

add_executable(${PROJECT_NAME}
    ${MYSOURCE}
    ${MYRESOURCES}
    )

SET(HEAT_TRANSFER_LIBRARY HeatTransferLibrary)
add_library(${HEAT_TRANSFER_LIBRARY} STATIC
    HeatTransferLibrary.cpp
    HeatTransferLibrary.h
    )


target_link_libraries(
    ${PROJECT_NAME}
    Qt5::Widgets
    Qt5::Gui
    ${HEAT_TRANSFER_LIBRARY}
)

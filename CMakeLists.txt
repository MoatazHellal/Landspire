cmake_minimum_required(VERSION 3.19)
project(Landspire LANGUAGES CXX)

find_package(Qt6 6.5 REQUIRED COMPONENTS Core Widgets Network)

qt_standard_project_setup()

qt_add_executable(Landspire
    WIN32 MACOSX_BUNDLE
    main.cpp
    mainwindow.cpp
    mainwindow.h
    mainwindow.ui
    connectdialogue.h connectdialogue.cpp
    server.h server.cpp
    clientconnection.h clientconnection.cpp
    cardAffinities.h
    cardwidget.h cardwidget.cpp
    cardwidget.h
    resources.qrc
)

qt_add_resources(RESOURCES resources.qrc)
target_sources(Landspire PRIVATE ${RESOURCES})

target_link_libraries(Landspire
    PRIVATE
        Qt::Core
        Qt::Widgets
        Qt::Network
)

include(GNUInstallDirs)

install(TARGETS Landspire
    BUNDLE  DESTINATION .
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
)

qt_generate_deploy_app_script(
    TARGET Landspire
    OUTPUT_SCRIPT deploy_script
    NO_UNSUPPORTED_PLATFORM_ERROR
)
install(SCRIPT ${deploy_script})

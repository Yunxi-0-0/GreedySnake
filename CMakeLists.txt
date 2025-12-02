cmake_minimum_required(VERSION 3.19)
project(GreedySnake LANGUAGES CXX)

find_package(Qt6 6.5 REQUIRED COMPONENTS Core Widgets)

qt_standard_project_setup()

qt_add_executable(GreedySnake
    WIN32 MACOSX_BUNDLE
    main.cpp
    mainwindow.cpp
    mainwindow.h
    page/StartPage.cpp
    page/StartPage.h
    page/GamePage.cpp
    page/GamePage.h
    snake/Snake.cpp
    snake/Snake.h
    component/UpBar.cpp
    component/UpBar.h
    component/GameArea.cpp
    component/GameArea.h
    food/Food.cpp
    food/Food.h

)

target_link_libraries(GreedySnake
    PRIVATE
        Qt::Core
        Qt::Widgets
)

include(GNUInstallDirs)

install(TARGETS GreedySnake
    BUNDLE  DESTINATION .
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
)

qt_generate_deploy_app_script(
    TARGET GreedySnake
    OUTPUT_SCRIPT deploy_script
    NO_UNSUPPORTED_PLATFORM_ERROR
)
install(SCRIPT ${deploy_script})

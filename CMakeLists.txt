cmake_minimum_required(VERSION 3.19)
project(GreedySnake LANGUAGES CXX)

find_package(Qt6 6.5 REQUIRED COMPONENTS Core Widgets Multimedia)

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
    page/MiddlePage.cpp
    page/MiddlePage.h
    page/RankingPage.cpp
    page/RankingPage.h
    page/SettingPage.cpp
    page/SettingPage.h
    snake/Snake.cpp
    snake/Snake.h
    component/UpBar.cpp
    component/UpBar.h
    component/GameArea.cpp
    component/GameArea.h
    component/GameOverDialog.cpp
    component/GameOverDialog.h
    food/Food.cpp
    food/Food.h
    page/Difficultypage.h
    page/Difficultypage.cpp
    tools/Tools.h
    tools/tools.cpp
    compat/mingw_shim.cpp


)

target_link_libraries(GreedySnake
    PRIVATE
        Qt::Core
        Qt::Widgets
        Qt6::Multimedia
    "-lmingwex"
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

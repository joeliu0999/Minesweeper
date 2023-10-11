cmake_minimum_required(VERSION 3.23)
project(Projoect4)

set(CMAKE_CXX_STANDARD 14)
set(SFML_DIR "C:/Libraries/SFML-2.5.1/lib/cmake/SFML")
find_package(SFML 2.5 COMPONENTS graphics audio REQUIRED)

add_executable(Projoect4 main.cpp minesweeper.h minesweeper.cpp Button.h Button.cpp GameState.h GameState.cpp Tile.h Tile.cpp Toolbox.cpp Toolbox.h)
target_link_libraries(Projoect4 sfml-graphics sfml-audio)

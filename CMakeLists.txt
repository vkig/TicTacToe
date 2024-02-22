cmake_minimum_required(VERSION 3.17)
project(TicTacToe)

set(CMAKE_CXX_STANDARD 17)

add_library(graphics graphics.cpp src/GWidget.cpp src/GWidget.hpp src/GButton.cpp src/GButton.hpp src/GSetNumber.cpp src/GSetNumber.hpp src/GSelect.cpp src/GSelect.hpp src/Application.cpp src/Application.hpp src/GameModel.cpp src/GameModel.hpp src/GLabel.cpp src/GLabel.hpp)

include_directories(include)
link_directories(lib)

target_link_libraries( graphics SDL2 SDL2.dll SDL2main SDL2_ttf SDL2_ttf.dll)


add_executable(TicTacToe main.cpp)
target_link_libraries( TicTacToe graphics)

cmake_minimum_required(VERSION 3.17)
project(TicTacToe)

set(CMAKE_CXX_STANDARD 14)

add_library(graphics graphics.cpp GWidget.cpp GWidget.hpp GButton.cpp GButton.hpp GSetNumber.cpp GSetNumber.hpp GSelect.cpp GSelect.hpp Application.cpp Application.hpp)

include_directories(D:/Dokumentumok/OneDrive\ -\ hallgato.ppke.hu/Egyetem/felev_6/BevProgII/include)
link_directories(D:/Dokumentumok/OneDrive\ -\ hallgato.ppke.hu/Egyetem/felev_6/BevProgII/lib)

target_link_libraries( graphics SDL2 SDL2.dll SDL2main SDL2_ttf SDL2_ttf.dll)


add_executable(TicTacToe main.cpp)
target_link_libraries( TicTacToe graphics)

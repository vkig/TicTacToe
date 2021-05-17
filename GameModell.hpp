//
// Created by vkig on 2021. 05. 05..
//

#ifndef TICTACTOE_GAMEMODELL_HPP
#define TICTACTOE_GAMEMODELL_HPP

#include <vector>

class GameModell {
public:
    enum Field{
        O,
        X,
        EMPTY,
        FULL
    };
private:
    std::vector<std::vector<int>> directions = {{1,0}, {0,1}, {1,1}, {1, -1}};
    std::vector<std::vector<Field>> board;
    int _width, _height;
    bool Xturn;
    int steps;
public:
    GameModell(){};

    GameModell(int width, int height);

    void clear(int width, int height);

    GameModell::Field setField(int x, int y);

    Field isWin(int x, int y);

    Field whosTurn();
};


#endif //TICTACTOE_GAMEMODELL_HPP

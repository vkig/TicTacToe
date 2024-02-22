//
// Created by vkig on 2021. 05. 05..
//

#ifndef TICTACTOE_GAMEMODEL_HPP
#define TICTACTOE_GAMEMODEL_HPP

#include <vector>

class GameModel {
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
    int _width{}, _height{};
    bool XTurn{};
    int steps{};
public:
    GameModel()= default;

    GameModel(int width, int height);

    void clear(int width, int height);

    GameModel::Field setField(int x, int y);

    Field isWin(int x, int y);

    Field whosTurn() const;
};


#endif //TICTACTOE_GAMEMODEL_HPP

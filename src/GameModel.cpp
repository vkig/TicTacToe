//
// Created by vkig on 2021. 05. 05..
//

#include "GameModel.hpp"

GameModel::GameModel(int width, int height) {
    clear(width,height);
}

void GameModel::clear(int width, int height) {
    width = std::min(30, std::max(width, 15));
    height = std::min(30, std::max(height,15));
    board = std::vector<std::vector<Field>>(width, std::vector<Field>(height,Field::EMPTY));
    this->_width = width;
    this->_height = height;
    XTurn = true;
    steps = 0;
}

GameModel::Field GameModel::setField(int x, int y){
    if(board[x][y] == EMPTY){
        if(XTurn){
            steps++;
            board[x][y] = X;
            XTurn = false;
            return X;
        }
        else{
            steps++;
            board[x][y] = O;
            XTurn = true;
            return O;
        }
    }
    return EMPTY;
}

GameModel::Field GameModel::isWin(int x, int y){
    int length = 1;
    for(std::vector<int> dir : directions){
        length = 1;
        for(int i = 1; i < 5;i++){
            if(x + dir[0]*i < _width && y + dir[1]*i < _height && x + dir[0]*i >= 0 &&
            y + dir[1]*i >= 0 && board[x + dir[0]*i][y + dir[1]*i] == board[x][y]){
                length++;
            }
            else{
                break;
            }
        }
        for(int i = 1; i < 5;i++){
            if(x + dir[0]*(-i) < _width && y + dir[1]*(-i) < _height && x + dir[0]*(-i) >= 0 &&
            y + dir[1]*(-i) >= 0 && board[x + dir[0]*(-i)][y + dir[1]*(-i)] == board[x][y]){
                length++;
            }
            else{
                break;
            }
        }
        if(length == 5){
            break;
        }
    }
    if(length == 5){
        return board[x][y];
    }
    else if(steps < board.size()*board[0].size()){
        return EMPTY;
    } else {
        return FULL;
    }
}

GameModel::Field GameModel::whosTurn() const {
    if(XTurn){
        return X;
    }
    return O;
}





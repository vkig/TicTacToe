//
// Created by vkig on 2021. 05. 05..
//

#include "GameModell.hpp"

GameModell::GameModell(int width, int height) {
    clear(width,height);
}

void GameModell::clear(int width, int height) {
    width = std::min(30, std::max(width, 15));
    height = std::min(30, std::max(height,15));
    board = std::vector<std::vector<Field>>(width, std::vector<Field>(height,Field::EMPTY));
    Xturn = true;
    steps = 0;
}

GameModell::Field GameModell::setField(int x, int y){
    if(board[x][y] == EMPTY){
        if(Xturn){
            board[x][y] = X;
        }
        else{
            board[x][y] = O;
        }
        steps++;
        return isWin(x, y);
    }
    return EMPTY;
}

GameModell::Field GameModell::isWin(int x, int y){
    for(std::vector<int> dir : directions){
        int length = 1;
        for(int i = 1; i < 6;i++){
            if(board[dir[0]*i][dir[1]*i] == board[x][y]){
                length++;
            }
            else{
                break;
            }
        }
        for(int i = 1; i < 6;i++){
            if(board[dir[0]*(-i)][dir[1]*(-i)] == board[x][y]){
                length++;
            }
            else{
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
}

GameModell::Field GameModell::whosTurn() {
    if(Xturn){
        return X;
    }
    return O;
}





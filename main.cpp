#include "graphics.hpp"
#include "src/GSetNumber.hpp"
#include "src/Application.hpp"
#include "src/GLabel.hpp"
#include "src/GameModel.hpp"

using namespace genv;

class MyApp : public Application{
private:
    std::vector<std::vector<GButton*>> buttonBoard;
    GameModel gameModel;
    GButton* startBtn{};
    GSetNumber* widthSet{};
    GSetNumber* heightSet{};
    GLabel* gl{};
    bool gameStarted = false;
    int tableWidth{};
    int tableHeight{};
    const int tableSize = 600;
public:
    MyApp() = default;
    MyApp(int X, int Y){
        XX = X;
        YY = Y;
        gl = new GLabel(this, XX/2-180, 10,360,30,"Set the width and height of the board!");
        startBtn = new GButton(this, XX / 2 - 50, YY - 30, 100, 30, 2,
                               color(200, 200, 200), color(255, 255, 255), [this]{start();}, GButton::LABELED, color(0, 0, 0),
                               "START");
        widthSet = new GSetNumber(this, XX / 2 - 150, YY / 2 - 25, 100, 50, 2, 15, 15, 30);
        heightSet = new GSetNumber(this, XX / 2 + 50, YY / 2 - 25, 100, 50, 2, 15, 15, 30);
        addWidget(gl);
        addWidget(startBtn);
        addWidget(widthSet);
        addWidget(heightSet);
//        gb1 = new GButton(this,10, 350, 50, 30, 1, genv::color(0, 100, 255),
//                          genv::color(255, 0, 0),[this](){ moveItem(gs1, gs2);},GButton::LABELED, genv::color(255, 255, 255), "1->2");
//        gb2 = new GButton(this,100, 350, 50, 30, 1, genv::color(0, 100, 255),
//                          genv::color(255, 0, 0),[this](){ moveItem(gs2, gs1);},GButton::LABELED, genv::color(255, 255, 255), "2->1");


        gout.open(XX,YY);
        gout<<move_to(0, 0)<<color(0, 0, 0)<<box_to(XX-1, YY-1)<< refresh;
    }

    void start(){
        if(!gameStarted) {
            gameModel = GameModel(widthSet->getValue(), heightSet->getValue());
            startBtn->hide();
            widthSet->hide();
            heightSet->hide();
            tableWidth = widthSet->getValue();
            tableHeight = heightSet->getValue();
            int size = std::max(tableWidth, tableHeight);
            int a = tableSize / size;
            int xoffset = (600 - tableWidth * a) / 2 + 10;
            int yoffset = (600 - tableHeight * a) / 2 + 50;
            for (int i = 0; i < tableWidth; ++i) {
                std::vector<GButton *> tmp;
                for (int j = 0; j < tableHeight; ++j) {
                    auto *btn_tmp = new GButton(this, xoffset + i * a, yoffset + j * a, a, a, 2,
                                                   color(105, 105, 105),
                                                   color(0, 0, 0), [this, i, j]() { setButton(i, j); },
                                                   GButton::LABELED, color(255, 255, 255), "");
                    tmp.push_back(btn_tmp);
                    addWidget(btn_tmp);
                }
                buttonBoard.push_back(tmp);
            }
            startBtn->setText("New Game");
            gameStarted = true;
        }
        else{
            gameModel.clear(tableWidth, tableHeight);
            for(auto & i : buttonBoard){
                for(auto & j : i){
                    j->setEnable(true);
                    j->setText("");
                }
            }
        }
        if (gameModel.whosTurn() == GameModel::X) {
            gl->setText("X's turn, press left button");
        } else {
            gl->setText("O's turn, press left button");
        }
    }

    ~MyApp() override {
        delete startBtn;
        delete widthSet;
        delete heightSet;
        delete gl;
    }
    void setButton(int i, int j){
        GameModel::Field type = gameModel.setField(i, j);
        if(type == GameModel::Field::O){
            buttonBoard[i][j]->setText("O");
            gl->setText("X's turn, press left button");
        } else if(type == GameModel::Field::X){
            buttonBoard[i][j]->setText("X");
            gl->setText("O's turn, press left button");
        }
        type = gameModel.isWin(i, j);
        if(type != GameModel::EMPTY){
            if(type == GameModel::Field::X){
                gl->setText("X won the game! Press New Game!");
            } else if(type == GameModel::Field::O){
                gl->setText("O won the game! Press New Game!");
            } else if(type == GameModel::Field::FULL){
                gl->setText("The table is full! Press New Game!");
            }
            for(auto & k : buttonBoard){
                for(auto & l : k){
                    l->setEnable(false);
                }
            }
        }
    }
};

int main()
{
    MyApp ma(620,690);
    ma.eventManager();
    return 0;
}

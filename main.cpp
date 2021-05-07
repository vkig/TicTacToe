#include "graphics.hpp"
#include "GSetNumber.hpp"
#include "Application.hpp"
#include "GSelect.hpp"
#include "GLabel.hpp"
#include "GameModell.hpp"

using namespace genv;

class MyApp : public Application{
private:
    std::vector<std::vector<GButton*>> buttonBoard;
    GameModell gm;
    GButton* startbtn;
    GSetNumber* widthset;
    GSetNumber* heightset;
    GLabel* gl;
public:
    MyApp(){}
    MyApp(int X, int Y){
        XX = X;
        YY = Y;
        gl = new GLabel(this, XX/2-180, 10,360,30,"Set the width and height of the board!");
        startbtn = new GButton(this, XX/2-50, YY*4/5, 100,30,2,
                               color(200, 200, 200),color(255, 255, 255),[this]{start();},GButton::LABELED,color(0, 0, 0),
                               "START");
        widthset = new GSetNumber(this, XX/2-100,YY/2,50,30,2,15,15,30);
        heightset = new GSetNumber(this, XX/2+50,YY/2,50,30,2,15,15,30);
        addWidget(gl);
        addWidget(startbtn);
        addWidget(widthset);
        addWidget(heightset);
//        gb1 = new GButton(this,10, 350, 50, 30, 1, genv::color(0, 100, 255),
//                          genv::color(255, 0, 0),[this](){ moveItem(gs1, gs2);},GButton::LABELED, genv::color(255, 255, 255), "1->2");
//        gb2 = new GButton(this,100, 350, 50, 30, 1, genv::color(0, 100, 255),
//                          genv::color(255, 0, 0),[this](){ moveItem(gs2, gs1);},GButton::LABELED, genv::color(255, 255, 255), "2->1");


        gout.open(XX,YY);
        gout<<move_to(0, 0)<<color(0, 0, 0)<<box_to(XX-1, YY-1)<< refresh;
    }

    void start(){
        gm = GameModell(widthset->getValue(),heightset->getValue());
        startbtn->hide();
        widthset->hide();
        heightset->hide();
        gl->setText("X's turn, press left button");
        buttonBoard = std::vector<std::vector<GButton*>>(widthset->getValue(),std::vector<GButton*>(nullptr,heightset->getValue()));
        for (int i = 0; i < widthset->getValue(); ++i) {
            for (int j = 0; j < heightset->getValue(); ++j) {

            }
        }
    }

    ~MyApp(){
        delete startbtn;
        /*delete widthset;
        delete heightset;
        delete gl;*/
    }
    void moveItem(GSelect * from, GSelect * to){
        std::string s = from->getSelected();
        if(s != ""){
            to->addItem(s);
            from->removeItem(from->getSelected());
        }
    }
};

int main()
{
    MyApp ma(400,400);
    ma.eventManager();
    return 0;
}

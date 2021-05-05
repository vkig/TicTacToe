#include "graphics.hpp"
#include "GSetNumber.hpp"
#include "Application.hpp"
#include "GSelect.hpp"
#include "GLabel.hpp"

using namespace genv;

class MyApp : public Application{
private:
    std::vector<std::vector<GButton*>> buttonBoard;
    GButton* start;
    GSetNumber* width;
    GSetNumber* height;
    GLabel* gl;
public:
    MyApp(){}
    MyApp(int X, int Y){
        start = new GButton();
        gl = new GLabel(this, XX/2-150, 10,300,30,"ASD");
        addWidget(start);
        addWidget(gl);
//        gb1 = new GButton(this,10, 350, 50, 30, 1, genv::color(0, 100, 255),
//                          genv::color(255, 0, 0),[this](){ moveItem(gs1, gs2);},GButton::LABELED, genv::color(255, 255, 255), "1->2");
//        gb2 = new GButton(this,100, 350, 50, 30, 1, genv::color(0, 100, 255),
//                          genv::color(255, 0, 0),[this](){ moveItem(gs2, gs1);},GButton::LABELED, genv::color(255, 255, 255), "2->1");
        XX = X;
        YY = Y;


        gout.open(XX,YY);
        gout<<move_to(0, 0)<<color(0, 0, 0)<<box_to(XX-1, YY-1)<< refresh;
    }
    ~MyApp(){
        /*delete start;
        delete width;
        delete height;
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
